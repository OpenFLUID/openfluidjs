var OpenFLUID = require("../index.js")
var assert = require('assert')
const path = require('path');

describe("Data", function() {

  it("empty", function() {
    blob = OpenFLUID.newBlob()
    OpenFLUID.printSimulationInfo(blob)
    OpenFLUID.deleteBlob(blob)
  });

  it("dataset", function() {
    blob = OpenFLUID.openDataset(path.join(__dirname,"6fields_3reaches.IN"))
    OpenFLUID.printSimulationInfo(blob)
    OpenFLUID.deleteBlob(blob)
  });

  it("project", function() {
    blob = OpenFLUID.openProject(path.join(__dirname,"Generators.PRJ"))
    OpenFLUID.printSimulationInfo(blob)
    OpenFLUID.deleteBlob(blob)
  });

});
