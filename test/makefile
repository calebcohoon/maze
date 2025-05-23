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

tvector.exe: tmath.obj fixed.obj trig.obj vector.obj tvector.obj tvector.lnk
	wlink @tvector.lnk

tvector.lnk:
	@echo system dos4g > tvector.lnk
	@echo option stack=8k >> tvector.lnk
	@echo name tvector.exe >> tvector.lnk
	@echo file tmath.obj >> tvector.lnk
	@echo file fixed.obj >> tvector.lnk
	@echo file trig.obj >> tvector.lnk
	@echo file vector.obj >> tvector.lnk
	@echo file tvector.obj >> tvector.lnk

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

tinterp.exe: tmath.obj fixed.obj interp.obj tinterp.obj tinterp.lnk
	wlink @tinterp.lnk

tinterp.lnk:
	@echo system dos4g > tinterp.lnk
	@echo option stack=8k >> tinterp.lnk
	@echo name tinterp.exe >> tinterp.lnk
	@echo file tmath.obj >> tinterp.lnk
	@echo file fixed.obj >> tinterp.lnk
	@echo file interp.obj >> tinterp.lnk
	@echo file tinterp.obj >> tinterp.lnk

interp.obj: ..\src\interp.c ..\include\interp.h
	$(CC) $(CFLAGS) ..\src\interp.c

tinterp.obj: tinterp.c tmath.h ..\include\interp.h
	$(CC) $(CFLAGS) tinterp.c

tvertex.exe: tmath.obj fixed.obj vector.obj matrix.obj trig.obj vertex.obj tvertex.obj tvertex.lnk
	wlink @tvertex.lnk

tvertex.lnk:
	@echo system dos4g > tvertex.lnk
	@echo option stack=8k >> tvertex.lnk
	@echo name tvertex.exe >> tvertex.lnk
	@echo file tmath.obj >> tvertex.lnk
	@echo file fixed.obj >> tvertex.lnk
	@echo file vector.obj >> tvertex.lnk
	@echo file matrix.obj >> tvertex.lnk
	@echo file trig.obj >> tvertex.lnk
	@echo file vertex.obj >> tvertex.lnk
	@echo file tvertex.obj >> tvertex.lnk

vertex.obj: ..\src\vertex.c ..\include\vertex.h
	$(CC) $(CFLAGS) ..\src\vertex.c

tvertex.obj: tvertex.c tmath.h ..\include\vertex.h
	$(CC) $(CFLAGS) tvertex.c

ttriang.exe: tmath.obj fixed.obj vector.obj matrix.obj trig.obj vertex.obj triangle.obj ttriang.obj ttriang.lnk
	wlink @ttriang.lnk

ttriang.lnk:
	@echo system dos4g > ttriang.lnk
	@echo option stack=8k >> ttriang.lnk
	@echo name ttriang.exe >> ttriang.lnk
	@echo file tmath.obj >> ttriang.lnk
	@echo file fixed.obj >> ttriang.lnk
	@echo file vector.obj >> ttriang.lnk
	@echo file matrix.obj >> ttriang.lnk
	@echo file trig.obj >> ttriang.lnk
	@echo file vertex.obj >> ttriang.lnk
	@echo file triangle.obj >> ttriang.lnk
	@echo file ttriang.obj >> ttriang.lnk

triangle.obj: ..\src\triangle.c ..\include\triangle.h
	$(CC) $(CFLAGS) ..\src\triangle.c

ttriang.obj: ttriang.c tmath.h ..\include\triangle.h
	$(CC) $(CFLAGS) ttriang.c

clean:
	del *.obj
	del *.lnk
	del *.err
	del *.exe

test: tmath.exe tfixed.exe tvector.exe tmatrix.exe ttrig.exe tinterp.exe tvertex.exe ttriang.exe
	tmath.exe
	tfixed.exe
	tvector.exe
	tmatrix.exe
	ttrig.exe
	tinterp.exe
	tvertex.exe
	ttriang.exe
