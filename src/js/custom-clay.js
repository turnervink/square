module.exports = function(minified) {
  var clayConfig = this;

  function stepGoalSlider() {

    if (!this.get()) {
      clayConfig.getItemByMessageKey("CfgKeyManualStepGoal").show();
    } else {
      clayConfig.getItemByMessageKey("CfgKeyManualStepGoal").hide();
    }

  }

  function manualGoalSwitch() {

    if (this.get() == "2") {
      console.log("Showing step goal");
      stepGoalSlider.call(clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal"));
      clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal").show();
    } else {
      console.log("Not showing step goal");
      stepGoalSlider.call(clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal"));
      clayConfig.getItemByMessageKey("CfgKeyManualStepGoal").hide();
      clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal").hide();
    }

  }

  function nightModeSection() {

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

  function locationField() {

    if (this.get() == "2") {
      clayConfig.getItemByMessageKey("CfgKeyWeatherLocation").hide();
    } else {
      clayConfig.getItemByMessageKey("CfgKeyWeatherLocation").show();
    }

  }

clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {
  var _ = minified._;
  var $ = minified.$;
  var HTML = minified.HTML;

  var platform = clayConfig.meta.activeWatchInfo.platform;

  var CfgKeyMiddleBarMode = clayConfig.getItemByMessageKey("CfgKeyMiddleBarMode");
  manualGoalSwitch.call(CfgKeyMiddleBarMode);
  CfgKeyMiddleBarMode.on("change", manualGoalSwitch);

  var CfgKeyUseAutomaticStepGoal = clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal");
  stepGoalSlider.call(CfgKeyUseAutomaticStepGoal);
  CfgKeyUseAutomaticStepGoal.on("change", stepGoalSlider);

  var CfgKeyUseNightMode = clayConfig.getItemByMessageKey("CfgKeyUseNightMode");
  nightModeSection.call(CfgKeyUseNightMode);
  CfgKeyUseNightMode.on("change", nightModeSection);

  var CfgKeyWeatherMode = clayConfig.getItemByMessageKey("CfgKeyWeatherMode");
  locationField.call(CfgKeyWeatherMode);
  CfgKeyWeatherMode.on("change", locationField);

});



};
