#include <sys/cdefs.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/cdefs.h>
#include <libgen.h>

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

void apkg_stack_dump (lua_State *L) {
      int i;
      int top = lua_gettop(L);
      for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
    
          case LUA_TSTRING:  /* strings */
            printf("`%s'", lua_tostring(L, i));
            break;
    
          case LUA_TBOOLEAN:  /* booleans */
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;
    
          case LUA_TNUMBER:  /* numbers */
            printf("%g", lua_tonumber(L, i));
            break;
    
          default:  /* other values */
            printf("%s", lua_typename(L, t));
            break;
    
        }
        printf("  ");  /* put a separator */
      }
      printf("\n");  /* end the listing */
    }

static char initstr[] = "dofile('init.lua');";

static void lua_pusharraystring(lua_State* L , int key , char* value) {
    lua_pushnumber(L, key);
    lua_pushstring(L, value);
    lua_settable(L, -3);
} 

int main(int argc, char **argv)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	//Okay, first we need to find out our name
	char* applet = basename(argv[0]);
	printf("applet: %s\n", applet);
	lua_pushstring(L, applet);
	lua_setglobal(L, "apkg_applet");
	lua_pushnumber(L, argc);
	lua_setglobal(L, "apkg_argc");
	//Now, we need to send the rest of argv directly to lua
	int i;
	lua_newtable(L);
	for (i=1;i<argc; i++)
	{
		lua_pusharraystring(L,i, argv[i]);
	}
	lua_setglobal(L, "apkg_argv");
	
	int error = luaL_loadbuffer(L, initstr, strlen(initstr), "apkg") ||
            lua_pcall(L, 0, 0, 0);
	apkg_check_lua_err(L,error);
	
	lua_getglobal(L, "apkg_result");
    if (!lua_isnumber(L, -1)) {
        printf ("apkg: `apkg_result' should be a number\n");
        return -1;
    }
    int r = lua_tonumber(L,-1);
	printf("apkg: result is %d\n",r);
	return r;
}


