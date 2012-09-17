UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
   LIBPATH += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"

   CC = g++
   COMPILERFLAGS = -Wall -Werror
   CFLAGS = $(COMPILERFLAGS) 

   INCLUDES += "-I."
   INCLUDES += "-I/usr/X11R6/include -I/usr/local/include"

   LIBRARIES = -lGL -lGLU -lglut -lm -lstdc++ 

   assignment1: *.cxx RgbImage.cpp
	   $(CC) -o assignment1 *.cxx RgbImage.cpp $(COMPILERFLAGS) $(LIBRARIES) $(LIBPATH) $(INCLUDES)

else
   LIBPATH += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"

   FRAMEWORK += -framework GLUT
   FRAMEWORK += -framework OpenGL 

   COMPILERFLAGS = -Wall -Werror
   CC = clang 
   CFLAGS = $(COMPILERFLAGS) 
   LIBRARIES = -lGL -lGLU -lm -lstdc++ 

   INCLUDES += "-I/System/Library/Frameworks/OpenGL.framework/Headers"
   INCLUDES += "-I/System/Library/Frameworks/GLUT.framework/Headers"
   INCLUDES += "-I."

   assignment1: *.cxx RgbImage.cpp
	   $(CC) -o assignment1 *.cxx RgbImage.cpp $(COMPILERFLAGS) $(LIBRARIES) $(FRAMEWORK) $(LIBPATH) $(INCLUDES)
endif

