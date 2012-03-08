-- This is a very basic demo init.lua, that should be replaced by the actual
-- lua code for apkg package manager. 
-- Basically, the core of this crap gives you two things: 
-- apkg_applet set to the name of the applet called (argv[0])
-- a table of args apkg_args


-- set apkg_result to the required return code
apkg_result=1

-- example help implementation
applets_help={
['apkg'] = "This utility should not be called directly, use apkg-* instead",
['apkg-install'] = "install packages...",
}

print(applets_help[apkg_applet]);