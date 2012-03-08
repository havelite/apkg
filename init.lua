-- This is a very basic demo init.lua, that should be replaced by the actual
-- lua code for apkg package manager. 
-- Basically, the core of this crap gives you two things: 
-- apkg_applet set to the name of the applet called (argv[0])
-- a table of args apkg_args


-- set apkg_result to the required return code
apkg_result=0

common_help = "(c) AgiliaLinux Developers 2012, Some rights reserved";


applets={};

-- The code below demonstrates a simple mechanism to register new applets in the 
-- app code. 
-- TODO: ByteCompilation of applets in different files
-- TODO: Freaking localisation of messages support. 
-- TODO: everything else
function register_applet(applet)
	print("Registering applet "..applet['name']);
	applets[applet['name']]=applet;
end

applet_apkg = {
	name = 'apkg';
	help = "This utility should not be called directly, use apkg-* instead",
	minargs = 0;
	applet = function(args)
		-- apkg does nothing by default
		print("APKG :: AgiliaLinux Package Manager");
		print(applet_apkg['help'])
		-- and returns a bad result code, since it shouldn't be called
		apkg_result=2;
	end
}

-- TODO: send the rest of argv to lua
register_applet(applet_apkg);
applets[apkg_applet]['applet'](nil);
