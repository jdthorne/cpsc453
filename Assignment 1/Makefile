UNAME := $(shell uname)

# This assignment compiles on Linux & Mac
# Please build it on the computers in MS239

ifeq ($(UNAME), Linux)

   # Use G++ with -Wall and -Werror
   CC = g++
   COMPILERFLAGS = -Wall -Werror
   CFLAGS = $(COMPILERFLAGS) 

   # Include headers in the local folder, as well as standard library locations
   INCLUDES += "-I."
   INCLUDES += "-I/usr/X11R6/include -I/usr/local/include"

   # Need OpenGL, GLU, glut, and other fun things
   LIBRARIES = -lGL -lGLU -lglut -lm -lstdc++ 

   # Actually compile the assignment
   assignment1: *.cxx RgbImage.cpp
	   $(CC) -o assignment1 *.cxx RgbImage.cpp $(COMPILERFLAGS) $(LIBRARIES) $(LIBPATH) $(INCLUDES)

else

   # Mac is silly, and uses frameworks
   # Actually, wait, this is way easier than Linux's hard-coded paths
   FRAMEWORK += -framework GLUT
   FRAMEWORK += -framework OpenGL 
   FRAMEWORK += -framework Cocoa

   # Same flags as above
   CC = clang 
   COMPILERFLAGS = -Wall -Werror
   CFLAGS = $(COMPILERFLAGS) 

   # Same libs as above
   LIBRARIES = -lGL -lGLU -lm -lstdc++ 
   LIBPATH += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"

   # Same include paths, except Mac-flavoured this time
   INCLUDES += "-I/System/Library/Frameworks/OpenGL.framework/Headers"
   INCLUDES += "-I/System/Library/Frameworks/GLUT.framework/Headers"
   INCLUDES += "-I."

   # Actually compile the assignment
   assignment1: *.cxx RgbImage.cpp
	   $(CC) -o assignment1 *.cxx RgbImage.cpp $(COMPILERFLAGS) $(LIBRARIES) $(FRAMEWORK) $(LIBPATH) $(INCLUDES)
endif

