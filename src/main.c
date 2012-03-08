#include <sys/cdefs.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/cdefs.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <termios.h>

#include <string.h>
#include <apkg/apkg.h>


static int apkg_check_lua_err(lua_State* L, int status)
{
	if (status && !lua_isnil(L, -1))
	{
		const char* msg = lua_tostring(L, -1);
		if (!msg)
			msg = "(error object is not a string)";
 		fprintf(stderr, "apkg: %s\n", msg);
		lua_pop(L, 1);
		exit(1);
	}
	
	return status;
}

static char initstr[] = "
print ''
";

int main(int argc, char **argv)
{
	lua_State *l = luaL_newstate();
	//Okay, first we need to find out our name
	char* applet = basename(argv[0]);
	lua_pushstring(L, applet);
	lua_setfield(L, -2, "apkg_applet");
	
}


