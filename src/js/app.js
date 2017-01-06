var Clay = require('pebble-clay');
var customClay = require('./custom-clay');
var clayConfig = require('./config.json');
var clay = new Clay(clayConfig, customClay, {autoHandleEvents: false});

//var apiKey = require('./apikey');

// ---------- Weather ---------- //

var lang;
var location;
var last_location;

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess(pos) {
  // Construct URL

  if (location != '') {
    console.log("Fetching weather with manual location")
    console.log("Location is " + location);
    var url = 'https://query.yahooapis.com/v1/public/yql?q=select%20item.condition%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22' + location + '%22)%20and%20u%3D"c"&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys&callback=';
  } else {
    console.log("Fetching weather with GPS location");
    console.log("Lat is " + pos.coords.latitude);
    console.log("Lon is " + pos.coords.longitude);
    var url = 'https://query.yahooapis.com/v1/public/yql?q=select%20item.condition%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22' + Math.round(pos.coords.latitude) + '%2C%20' + Math.round(pos.coords.longitude) + '%22)%20and%20u%3D"c"&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys&callback=';
  }

  console.log("URL is " + url);

  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET',
    function(responseText) {
      console.log("Parsing JSON");

      var json = JSON.parse(responseText); // Parse JSON response
      var item = json.query.results.channel.item; // Drill down to current conditions in response

      if (!json.query.results) {
        var dictionary = {
          "CfgKeyWeatherError": "error",
        };
      } else {
        var temperature = parseInt(item.condition.temp);
        console.log("Temperature in Fahrenheit is " + temperature);

        var temperaturec = Math.round((parseInt(item.condition.temp) - 32) / 1.8); // Convert from Kelvin to Celsius
        console.log("Temperature in Celsius is " + temperaturec);

        // Conditions
        var conditions = item.condition.text;
        console.log("Conditions are " + conditions);

        // Assemble weather info into dictionary
        var dictionary = {
          "CfgKeyTemperature": temperature,
          "CfgKeyCelsiusTemperature": temperaturec,
          "CfgKeyConditions": conditions,
        };
      }

      // Send dictionary to Pebble
      Pebble.sendAppMessage(dictionary,
        function(e) {
          console.log("App message sent containing response from weather service");
					console.log(e);
        },
        function(e) {
          console.log("Error sending info to Pebble - response received from weather service");
					console.log(e);
        }
      );
    }
  );
}

function locationError(err) {
  if (location != '') {
    console.log('Error requesting location! Manual location entered.');

    locationSuccess(null);
  } else {
    console.log('Error requesting location! No manual location entered.');

    var dictionary = {
      "CfgKeyWeatherError": "error",
    };

    Pebble.sendAppMessage(dictionary,
      function(e) {
        console.log("Location error info sent to Pebble successfully!");
        console.log(e);
      },
      function(e) {
        console.log("Could not send location error info to Pebble!");
        console.log(e);
      }
    );
  }
}

function getWeather() {
	console.log("Getting weather");
	navigator.geolocation.getCurrentPosition(
		locationSuccess,
		locationError,
		{timeout: 15000, maximumAge: 60000}
	);
}

// ---------- Config ---------- //

// Config opened
Pebble.addEventListener('showConfiguration', function(e) {
	console.log("Showing configuration page");
  Pebble.openURL(clay.generateUrl());
});

// Config closed
Pebble.addEventListener('webviewclosed', function(e) {
  if (e && !e.response) {
		console.log("No response from config page!");
    return;
  }

	console.log("Configuration page returned: " + e.response);

  var dict = clay.getSettings(e.response);

  //console.log("Lang in dict " + dict.CfgKeyLanguage.value);

  var messageKeys = require("message_keys");
  lang = dict[messageKeys.CfgKeyLanguage];
  console.log("Lang is " + lang);

  last_location = location;
  location = dict[messageKeys.CfgKeyWeatherLocation];
  console.log("Location is " + location);

  if (lang === "0") {
    lang = "en"
  } else if (lang === "1") {
    lang = "fr"
  } else if (lang === "2") {
    lang = "es"
  } else if (lang === "3") {
    lang = "de"
  } else if (lang === "4") {
    lang = "it"
  }

  localStorage.lang = lang;
  localStorage.location = location;

  // Send settings values to watch side
  Pebble.sendAppMessage(dict,
		function(e) {
    	console.log("ACK config settings");

      if (location !== last_location) {
        console.log("Location has changed, updating weather");
        getWeather();
      }
  	},
		function(e) {
    	console.log('NACK config settings: ' + JSON.stringify(e));
  	}
	);
});

// ---------- ---------- //

// JS Ready
Pebble.addEventListener("ready", function(e) {
  console.log("PebbleKit JS Ready!");

  lang = localStorage.lang;
  if (localStorage.getItem("location") !== null) {
    location = localStorage.location;
  } else {
    location = '';
  }



	getWeather(); // Get weather on launch
});

// AppMessage received
Pebble.addEventListener("appmessage", function (e) {
	console.log('AppMessage received!');
	console.log('Message contents: ' + JSON.stringify(e.payload));

	var messageContents = e.payload;

	if (messageContents.CfgKeyConditions === 0) { // If CfgKeyConditions exists in the message update the weather
		console.log('CfgKeyConditions received in appmessage');
		getWeather(); // Fetch the weather
	}
});
