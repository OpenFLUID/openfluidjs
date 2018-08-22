var OpenFLUID = require("../index.js")
var assert = require('assert')
const path = require('path');


describe("Simulation", function() {

  it("normal", function() {
    pathIN = path.join(__dirname,"Generators.IN")
    pathOUT = path.join(__dirname,"Generators.OUT")
    OpenFLUID.setCurrentOutputDir(pathOUT)
    blob = OpenFLUID.openDataset(pathIN)
    OpenFLUID.runSimulation(blob)
    OpenFLUID.deleteBlob(blob)
  });

  it("verbose", function() {
    pathIN = path.join(__dirname,"Generators.IN")
    pathOUT = path.join(__dirname,"Generators.verbose.OUT")
    OpenFLUID.setCurrentOutputDir(pathOUT)
    blob = OpenFLUID.openDataset(pathIN)
    OpenFLUID.runSimulation(blob,true)
    OpenFLUID.deleteBlob(blob)
  });

  it("project", function() {
    pathPRJ = path.join(__dirname,"Generators.PRJ")
    pathOUT = path.join(__dirname,"Generators.PRJ","OUT")
    blob = OpenFLUID.openProject(pathPRJ)
    OpenFLUID.setCurrentOutputDir(pathOUT)
    OpenFLUID.runSimulation(blob)
    OpenFLUID.deleteBlob(blob)
  });

});
