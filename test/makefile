# Makefile for 486 Math Test Framework
#
# Compiler settings:
#   CC = wcl           - Watcom C compiler
#   CFLAGS:
#     -0              - Generate 8086 compatible code
#     -d0             - No debug information (reduces exe size)
#     -ml             - Large memory model (separate data/code segments)

CC = wcl
CFLAGS = -0 -d0 -ml

tmath.exe: tmath.obj tmathex.obj
	$(CC) $(CFLAGS) tmath.obj tmathex.obj -fe=tmath.exe

tmath.obj: tmath.c tmath.h
	$(CC) $(CFLAGS) -c tmath.c

tmathex.obj: tmathex.c tmath.h
	$(CC) $(CFLAGS) -c tmathex.c

clean:
	del *.obj
	del tmath.exe

test: tmath.exe
	tmath.exe
