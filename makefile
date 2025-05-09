# 486 3D Maze Game Makefile
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
# -wx    : Maximum warning level
#          - Catches potential issues like:
#            * Uninitialized variables
#            * Type mismatches
#            * Implicit conversions
#            * Unused variables
#          - Essential for maintaining code quality
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
CFLAGS = -3r -fp3 -zq -wx -s -mf -i=.\include
LFLAGS = system dos4g option stack=8k

SRC_DIR = src
OBJS = main.obj timer.obj keyboard.obj

all: maze.exe

maze.exe: $(OBJS)
	wlink $(LFLAGS) name $@ file { $(OBJS) }

main.obj: $(SRC_DIR)\main.c
	$(CC) $(CFLAGS) $(SRC_DIR)\main.c

timer.obj: $(SRC_DIR)\timer.c
	$(CC) $(CFLAGS) $(SRC_DIR)\timer.c

keyboard.obj: $(SRC_DIR)\keyboard.c
	$(CC) $(CFLAGS) $(SRC_DIR)\keyboard.c

clean:
	del *.obj
	del maze.exe
