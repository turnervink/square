var weatherFile = require('./weather.js')

var Clay = require('pebble-clay');
var customClay = require('./custom-clay');
var clayConfig = require('./config.json');
var clay = new Clay(clayConfig, customClay, {autoHandleEvents: false});

// JS Ready
Pebble.addEventListener("ready", function(e) {
  console.log("PebbleKit JS Ready!");

	weatherFile.getWeather();
});

// AppMessage received
Pebble.addEventListener("appmessage", function (e) {
	console.log('AppMessage received!');
	console.log('Message contents: ' + JSON.stringify(e.payload));

	var messageContents = e.payload;
	console.log(messageContents.CfgKeyConditions);

	if (messageContents.CfgKeyConditions === 0) { // If KEY_CONDITIONS exists in the appmessage
		console.log('CfgKeyConditions received in appmessage');
		weatherFile.getWeather(); // Fetch the weather
	}
});

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

  // Get the keys and values from each config item
  var dict = clay.getSettings(e.response);

	lang = parseInt(dict.CfgKeyLanguage);
	localStorage.lang = lang;

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
