# Makefile for 486 Math Test Framework
#
# Compiler and Linker Configuration
# --------------------------------
#
# Compiler Flags Explanation:
# --------------------------
# -3r    : Optimizes for 486 and uses register-based calling convention
#          - Uses registers (EAX, EDX, EBX) for parameter passing instead of stack
#          - More efficient for small parameters
#          - Critical for frequently called math functions in our 3D engine
#
# -fp3   : Enables 486 floating-point optimizations
#          - Uses 487/486DX FPU instructions when available
#          - Falls back to software emulation if no FPU present
#          - Beneficial for any floating-point calculations (though we'll mainly use fixed-point)
#
# -zq    : "Quiet" operation mode
#          - Reduces compiler output to just errors and warnings
#          - Keeps build output clean and manageable
#          - Can be removed for more verbose debugging output
#
# -s     : Removes stack overflow checking
#          - Improves performance by eliminating runtime checks
#          - Safe when stack usage is carefully controlled
#          - Important for renderer performance
#          - Use with caution; stack overflows won't be caught
#
# -mf    : Flat memory model
#          - Enables full 32-bit addressing
#          - All segments (code, data, stack) can access full memory
#          - No segment limitations or far pointers needed
#          - Essential for video memory and buffer access
#          - Simplifies pointer arithmetic
#
# Linker Flags Explanation:
# ------------------------
# system dos4g:
#          - Configures DOS/4GW extender
#          - Enables 32-bit protected mode operation
#          - Provides access to extended memory beyond 640K
#          - Handles protected/real mode switching
#          - Essential for texture storage and double buffering
#
# option stack=8k:
#          - Sets stack size to 8 kilobytes
#          - Balanced for recursion needs (BSP tree traversal)
#          - Leaves memory available for textures and buffers
#          - Can be increased for debug builds if needed
#
# Potential Additional Flags for Future Use:
# ----------------------------------------
# -d2    : Full debugging information (for debug builds)
# -ot    : Time-based optimization
# -zu    : Safer unsigned/signed char conversion
# -6     : Optimize for later 486 models
#
# Note: Memory usage should be carefully monitored as textures
# and double buffering can consume significant memory on a 486 system.

CC = wcc386
CFLAGS = -3r -fp3 -zq -s -mf -i=.\include
LFLAGS = system dos4g option stack=8k

tmath.exe: tmath.obj tmathex.obj
	wlink $(LFLAGS) name $@ file { tmath.obj tmathex.obj }

tmath.obj: tmath.c tmath.h
	$(CC) $(CFLAGS) tmath.c

tmathex.obj: tmathex.c tmath.h
	$(CC) $(CFLAGS) tmathex.c

tfixed.exe: tmath.obj fixed.obj tfixed.obj
	wlink $(LFLAGS) name $@ file { tmath.obj fixed.obj tfixed.obj }

fixed.obj: ..\src\fixed.c ..\include\fixed.h
	$(CC) $(CFLAGS) ..\src\fixed.c

tfixed.obj: tfixed.c tmath.h ..\include\fixed.h
	$(CC) $(CFLAGS) tfixed.c

tvector.exe: tmath.obj fixed.obj vector.obj tvector.obj
	wlink $(LFLAGS) name $@ file { tmath.obj fixed.obj vector.obj tvector.obj }

vector.obj: ..\src\vector.c ..\include\vector.h
	$(CC) $(CFLAGS) ..\src\vector.c

tvector.obj: tvector.c tmath.h ..\include\vector.h
	$(CC) $(CFLAGS) tvector.c

tmatrix.exe: tmath.obj fixed.obj vector.obj trig.obj matrix.obj tmatrix.obj tmatrix.lnk
	wlink @tmatrix.lnk

tmatrix.lnk:
	@echo system dos4g > tmatrix.lnk
	@echo option stack=8k >> tmatrix.lnk
	@echo name tmatrix.exe >> tmatrix.lnk
	@echo file tmath.obj >> tmatrix.lnk
	@echo file fixed.obj >> tmatrix.lnk
	@echo file vector.obj >> tmatrix.lnk
	@echo file trig.obj >> tmatrix.lnk
	@echo file matrix.obj >> tmatrix.lnk
	@echo file tmatrix.obj >> tmatrix.lnk

matrix.obj: ..\src\matrix.c ..\include\matrix.h
	$(CC) $(CFLAGS) ..\src\matrix.c

tmatrix.obj: tmatrix.c tmath.h ..\include\matrix.h
	$(CC) $(CFLAGS) tmatrix.c

ttrig.exe: tmath.obj fixed.obj trig.obj ttrig.obj ttrig.lnk
	wlink @ttrig.lnk

ttrig.lnk:
	@echo system dos4g > ttrig.lnk
	@echo option stack=8k >> ttrig.lnk
	@echo name ttrig.exe >> ttrig.lnk
	@echo file tmath.obj >> ttrig.lnk
	@echo file fixed.obj >> ttrig.lnk
	@echo file trig.obj >> ttrig.lnk
	@echo file ttrig.obj >> ttrig.lnk

trig.obj: ..\src\trig.c ..\include\trig.h
	$(CC) $(CFLAGS) ..\src\trig.c

ttrig.obj: ttrig.c tmath.h ..\include\trig.h
	$(CC) $(CFLAGS) ttrig.c

clean:
	del *.obj
	del *.lnk
	del *.err
	del tmath.exe
	del tfixed.exe
	del tvector.exe
	del tmatrix.exe
	del ttrig.exe

test: tmath.exe tfixed.exe tvector.exe tmatrix.exe ttrig.exe
	tmath.exe
	tfixed.exe
	tvector.exe
	tmatrix.exe
	ttrig.exe
