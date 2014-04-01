'use strict';

/* 
 * initialize the edison library based on its configuration file.
 */
var path = require('path');

var edisonConfig = require("./config.js");
var InterfaceValidator = require("./interface-validator.njs");

// init edison plugin validator
var validator = new InterfaceValidator();

// load component plugins
var component; // current component being processed

function setPluginAccessVariable(plugin) {
	if (!exports[component]) {
		exports[component] = {};
	}
	exports[component][plugin.type] = plugin;
}

//load specified plugins for all supported components
for (component in edisonConfig.components) {
	if (!edisonConfig.components[component] || !edisonConfig.components[component].plugins) {
		console.log("INFO: No plugins configured for component '" + component + "'. Skipping...");
		continue;
	}
	validator.validate(component, edisonConfig.components[component].plugins, setPluginAccessVariable);
}

console.log("The Edison convenience library is now initialized.");

//exports (no real need for this)
exports.config = edisonConfig;

// test function
exports.sayhello = function ()
{
	return "Hello Edison user!";
};
