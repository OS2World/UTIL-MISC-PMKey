CFLAGS = -Sp1 -C+ -Ti+ /Ss+

OBJS = pmkey.obj key.obj btoe.obj hash.obj keycrnch.obj md4c.obj md5c.obj

all: pmkey.exe

clean:
	del $(OBJS) pmkey.res pmkey.exe

pmkey.res: pmkey.rc resource.h
	rc -r pmkey.rc

pmkey.exe: $(OBJS) pmkey.res pmkey.def
	ilink /NOFREE /NOI /NOE /M /DE $(OBJS), pmkey.exe, \
	pmkey.map, , pmkey.def
	rc pmkey.res pmkey.exe

