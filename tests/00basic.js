var OpenFLUID = require("../index.js")
var assert = require('assert')


describe("Basic", function() {

  it("version", function() {
    ver = OpenFLUID.getVersion()
    assert(ver !=null && ver !== "")
    console.log("version: " + ver)
  });

  it("blob", function() {
    blob = OpenFLUID.newBlob()
    OpenFLUID.deleteBlob(blob)
  });

});
