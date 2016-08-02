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
      clayConfig.getItemByMessageKey("CfgKeyManualStepGoal").hide();
      clayConfig.getItemByMessageKey("CfgKeyUseAutomaticStepGoal").hide();
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

});



};
