Minimal test of using cmake to manage external projects (hidapi). This works fine with the "Unix Makefile" generator and fails with the Ninja generator. Ninja doesn't know how to build libhidapi.a, which is the imported static library target that's tied to the ExternalProject_Add command.

To build, run ```./b``` from the repository root.

(Note, I've only tested this on Mac.)
