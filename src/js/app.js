var Clay = require('pebble-clay');
var customClay = require('./custom-clay');
var clayConfig = require('./config.json');
var clay = new Clay(clayConfig, customClay, {autoHandleEvents: false});

// ---------- Weather ---------- //

var lang;

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
  url;
  var url = 'http://api.openweathermap.org/data/2.5/weather?lat=' + pos.coords.latitude + '&lon=' + pos.coords.longitude + '&appid=2874bea34ea1f91820fa07af69939eea&lang=' + lang;

  console.log("Lat is " + pos.coords.latitude);
  console.log("Lon is " + pos.coords.longitude);
  console.log('URL is ' + url);

  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET',
    function(responseText) {
      console.log("Parsing JSON");

      var json = JSON.parse(responseText); // Parse JSON response

      var temperature = Math.round(((json.main.temp - 273.15) * 1.8) + 32); // Convert from Kelvin to Fahrenheit
      console.log("Temperature in Fahrenheit is " + temperature);

      var temperaturec = Math.round(json.main.temp - 273.15); // Convert from Kelvin to Celsius
      console.log("Temperature in Celsius is " + temperaturec);

      // Conditions
      var conditions = json.weather[0].description;
      console.log("Conditions are " + conditions);

      // Assemble weather info into dictionary
      var dictionary = {
        "CfgKeyTemperature": temperature,
        "CfgKeyCelsiusTemperature": temperaturec,
        "CfgKeyConditions": conditions,
      };

      // Send dictionary to Pebble
      Pebble.sendAppMessage(dictionary,
        function(e) {
          console.log("Weather info sent to Pebble successfully!");
					console.log(e);
        },
        function(e) {
          console.log("Error sending weather info to Pebble!");
					console.log(e);
        }
      );
    }
  );
}

function locationError(err) {
  console.log('Error requesting location!');
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
  console.log("Lang " + lang);

  // Send settings values to watch side
  Pebble.sendAppMessage(dict,
		function(e) {
    	console.log("ACK config settings");
  	},
		function(e) {
    	console.log('NACK config settings');
  	}
	);
});

// ---------- ---------- //

// JS Ready
Pebble.addEventListener("ready", function(e) {
  console.log("PebbleKit JS Ready!");

	getWeather(); // Get weather on launch
});

// AppMessage received
Pebble.addEventListener("appmessage", function (e) {
	console.log('AppMessage received!');
	console.log('Message contents: ' + JSON.stringify(e.payload));

	var messageContents = e.payload;
	console.log(messageContents.CfgKeyConditions);

	if (messageContents.CfgKeyConditions === 0) { // If KEY_CONDITIONS exists in the appmessage NOTE: We are gettings key 0, check for that
		console.log('CfgKeyConditions received in appmessage');
		getWeather(); // Fetch the weather
	}
});
