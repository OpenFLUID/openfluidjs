var libOpenFLUID = require("bindings")("libOpenFLUIDjs");

module.exports = {

  getVersion: function() {
    return libOpenFLUID.getVersion()
  },

  newBlob: function() {
    return libOpenFLUID.newBlob();
  },

  deleteBlob: function(blob) {
    libOpenFLUID.deleteBlob(blob);
  },

  printSimulationInfo: function(blob) {
    libOpenFLUID.printSimulationInfo(blob);
  },

  openDataset: function(path) {
    return libOpenFLUID.openDataset(path);
  },

  openProject: function(path) {
    return libOpenFLUID.openProject(path);
  },

  setCurrentOutputDir: function(path) {
    libOpenFLUID.setCurrentOutputDir(path);
  },

  runSimulation: function(blob,verbose=false) {
    libOpenFLUID.runSimulation(blob,Boolean(verbose));
  },

};
