LIBPATH += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"

FRAMEWORK += -framework GLUT
FRAMEWORK += -framework OpenGL 

COMPILERFLAGS = -Wall -Werror
CC = clang 
CFLAGS = $(COMPILERFLAGS) 
LIBRARIES = -lGL -lGLU -lm -lobjc -lstdc++ 

INCLUDES += "-I/System/Library/Frameworks/OpenGL.framework/Headers"
INCLUDES += "-I/System/Library/Frameworks/GLUT.framework/Headers"
INCLUDES += "-I."

assignment1: main.cxx OpenGlDisplay.cxx Image.cxx ImageRenderer.cxx ControlBar.cxx MathHelpers.cxx RgbImage.cpp
	clang -o assignment1 main.cxx OpenGlDisplay.cxx Image.cxx ImageRenderer.cxx ControlBar.cxx MathHelpers.cxx RgbImage.cpp $(COMPILERFLAGS) $(LIBRARIES) $(FRAMEWORK) $(LIBPATH) $(INCLUDES)
