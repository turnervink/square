module.exports = function(minified) {
  var clayConfig = this;

  function showWeatherSettings() {
    if (this.get() == 0) {
      clayConfig.getItemByMessageKey("CfgKeyWeatherLocation").show();
      clayConfig.getItemByMessageKey("CfgKeyUseCelsius").show();
    } else {
      clayConfig.getItemByMessageKey("CfgKeyWeatherLocation").hide();
      clayConfig.getItemByMessageKey("CfgKeyUseCelsius").hide();
    }
  }

  function showNightModeSettings() {
    if (this.get()) {
      clayConfig.getItemByMessageKey("CfgKeyNightModeStart").show();
      clayConfig.getItemByMessageKey("CfgKeyNightModeEnd").show();
      clayConfig.getItemByMessageKey("CfgKeyNightBackgroundColour").show();
      clayConfig.getItemByMessageKey("CfgKeyNightTextColour").show();
    } else {
      clayConfig.getItemByMessageKey("CfgKeyNightModeStart").hide();
      clayConfig.getItemByMessageKey("CfgKeyNightModeEnd").hide();
      clayConfig.getItemByMessageKey("CfgKeyNightBackgroundColour").hide();
      clayConfig.getItemByMessageKey("CfgKeyNightTextColour").hide();
    }
  }

  function showStepGoalSlider() {
    if (!this.get()) {
      clayConfig.getItemByMessageKey("CfgKeyManualStepGoal").show();
    } else {
      clayConfig.getItemByMessageKey("CfgKeyManualStepGoal").hide();
    }
  }

  function showHealthSettings() {
    var autoGoalToggle = clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal");

    if (this.get() == 2) {
      clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal").show();
      showStepGoalSlider.call(autoGoalToggle);
    } else {
      clayConfig.getItemByMessageKey("CfgKeyManualStepGoal").hide();
      clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal").hide();
    }
  }

  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {
    var _ = minified._;
    var $ = minified.$;
    var HTML = minified.HTML;

    var platform = clayConfig.meta.activeWatchInfo.platform;

    var donateButton = clayConfig.getItemById("donateButton");
    donateButton.on("click", function() {
      window.location.href="https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=XM6V4BDNBC2TJ";
    });

    var weatherModeDropdown = clayConfig.getItemByMessageKey("CfgKeyWeatherMode");
    showWeatherSettings.call(weatherModeDropdown); // Call on page load
    weatherModeDropdown.on("change", showWeatherSettings); // Call on change

    if (clayConfig.getItemByMessageKey("CfgKeyUseNightMode")) {
      var nightModeToggle = clayConfig.getItemByMessageKey("CfgKeyUseNightMode");
      showNightModeSettings.call(nightModeToggle);
      nightModeToggle.on("change", showNightModeSettings);
    }

    var middleBarDropdown = clayConfig.getItemByMessageKey("CfgKeyMiddleBarMode");
    showHealthSettings.call(middleBarDropdown);
    middleBarDropdown.on("change", showHealthSettings);

    if (clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal")) {
      var autoGoalToggle = clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal");
      autoGoalToggle.on("change", showStepGoalSlider);
    }

  });

};
