bin_PROGRAMS = apkg
apkg_SOURCES = \
	main.c
	
AM_CFLAGS = $(lua_CFLAGS) -DAPKG_DATA=\"${datarootdir}/apkg/\" -Wall -Werror -I$(top_srcdir)/include
apkg_LDADD = $(lua_LIBS)
