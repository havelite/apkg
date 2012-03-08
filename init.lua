-- This is a very basic demo init.lua, that should be replaced by the actual
-- lua code for apkg package manager. 
-- Basically, the core of this crap gives you two things: 
-- apkg_applet set to the name of the applet called (argv[0])
-- a table of args apkg_args


-- set apkg_result to the required return code
apkg_result=1

common_help = "(c) AgiliaLinux Developers 2012, Some rights reserved";


applets={};

function register_applet(applet)
	print("Registering applet "..applet['name']);
	applets[applet['name']]=applet;
end

applet_apkg = {
	name = 'apkg';
	help = "This utility should not be called directly, use apkg-* instead",
	minargs = 0;
	applet = function()
	print(applet_apkg['help'])
end
}
register_applet(applet_apkg);

applets[apkg_applet]
print(applets[apkg_applet]['help']);