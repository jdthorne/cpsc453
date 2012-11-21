UNAME := $(shell uname)

# This assignment compiles on Linux & Mac
# Please build it on the computers in MS239

ifeq ($(UNAME), Linux)

# Use G++ with -Wall and -Werror
CC = g++
COMPILERFLAGS = -Wall -Werror
CFLAGS = $(COMPILERFLAGS) 

MOC = moc-qt4
UIC = uic-qt4

# Include headers in the local folder, as well as standard library locations
INCLUDES += "-I."
INCLUDES += "-I/usr/X11R6/include -I/usr/local/include"
INCLUDES += "-I/usr/include/QtCore"
INCLUDES += "-I/usr/include/QtGui"
INCLUDES += "-I/usr/include/QtOpenGL"

# Need OpenGL, GLU, glut, and other fun things
LIBRARIES = -lGL -lGLU -lglut -lm -lstdc++ -lQtCore -lQtGui -lQtOpenGL

assignment2 : *.cxx AssignmentCore.moc.cxx
	$(CC) -o assignment3 *.cxx $(COMPILERFLAGS) $(LIBRARIES) $(FRAMEWORK) $(LIBPATH) $(INCLUDES)

AssignmentCore.moc.cxx : AssignmentCore.h
	$(MOC) AssignmentCore.h -oAssignmentCore.moc.cxx

else

# Mac is silly, and uses frameworks
FRAMEWORK += -framework QtCore
FRAMEWORK += -framework QtGui
FRAMEWORK += -framework QtOpenGL
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
INCLUDES += "-I/Library/Frameworks/QtCore.framework/Versions/4/Headers/"
INCLUDES += "-I/Library/Frameworks/QtGui.framework/Versions/4/Headers/"
INCLUDES += "-I/Library/Frameworks/QtOpenGL.framework/Versions/4/Headers/"
INCLUDES += "-I."

# Actually compile the assignment
assignment2 : *.cxx AssignmentCore.moc.cxx
	$(CC) -o assignment3 *.cxx $(COMPILERFLAGS) $(LIBRARIES) $(FRAMEWORK) $(LIBPATH) $(INCLUDES)

AssignmentCore.moc.cxx : AssignmentCore.h
	moc AssignmentCore.h -oAssignmentCore.moc.cxx

endif

