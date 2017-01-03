module.exports = function(minified) {
  var clayConfig = this;

  function showWeatherSettings() {
    if (this.get() != 2) {
      clayConfig.getItemByMessageKey("CfgKeyWeatherLocation").show();
      clayConfig.getItemByMessageKey("CfgKeyUseCelsius").show();
      clayConfig.getItemByMessageKey("CfgKeyAPIKey").show();
    } else {
      clayConfig.getItemByMessageKey("CfgKeyWeatherLocation").hide();
      clayConfig.getItemByMessageKey("CfgKeyUseCelsius").hide();
      clayConfig.getItemByMessageKey("CfgKeyAPIKey").hide();
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

    disableHealthSettings.call(clayConfig.getItemByMessageKey("CfgKeyEnableHealth"));
  }

  function disableHealthSettings() {
    if (!this.get()) {
      clayConfig.getItemByMessageKey("CfgKeyManualStepGoal").disable();
      clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal").disable();
    } else {
      clayConfig.getItemByMessageKey("CfgKeyManualStepGoal").enable();
      clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal").enable();
    }
  }

  function showHealthSettings() {
    var autoGoalToggle = clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal");
    var enableHealthToggle = clayConfig.getItemByMessageKey("CfgKeyEnableHealth");

    if (this.get() == 2) {
      clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal").show();
      //disableHealthSettings.call(enableHealthToggle);
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

    if (clayConfig.getItemByMessageKey("CfgKeyWeatherMode")) {
      var weatherModeDropdown = clayConfig.getItemByMessageKey("CfgKeyWeatherMode");
      showWeatherSettings.call(weatherModeDropdown); // Call on page load
      weatherModeDropdown.on("change", showWeatherSettings); // Call on change
    }

    if (clayConfig.getItemByMessageKey("CfgKeyUseNightMode")) {
      var nightModeToggle = clayConfig.getItemByMessageKey("CfgKeyUseNightMode");
      showNightModeSettings.call(nightModeToggle);
      nightModeToggle.on("change", showNightModeSettings);
    }

    if (clayConfig.getItemByMessageKey("CfgKeyMiddleBarMode")) {
      var middleBarDropdown = clayConfig.getItemByMessageKey("CfgKeyMiddleBarMode");
      showHealthSettings.call(middleBarDropdown);
      middleBarDropdown.on("change", showHealthSettings);
    }

    if (clayConfig.getItemByMessageKey("CfgKeyEnableHealth")) {
      var enableHealthToggle = clayConfig.getItemByMessageKey("CfgKeyEnableHealth");
      disableHealthSettings.call(enableHealthToggle);
      enableHealthToggle.on("change", disableHealthSettings);
    }

    if (clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal")) {
      var autoGoalToggle = clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal");
      autoGoalToggle.on("change", showStepGoalSlider);
    }

  });

};
