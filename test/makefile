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

tfixed.exe: tmath.obj fixed.obj tfixed.obj
	$(CC) $(CFLAGS) tmath.obj fixed.obj tfixed.obj -fe=tfixed.exe

fixed.obj: ..\src\fixed.c ..\include\fixed.h
	$(CC) $(CFLAGS) -c ..\src\fixed.c

tfixed.obj: tfixed.c tmath.h ..\include\fixed.h
	$(CC) $(CFLAGS) -c tfixed.c

clean:
	del *.obj
	del tmath.exe
	del tfixed.exe

test: tmath.exe tfixed.exe
	tmath.exe
	tfixed.exe
