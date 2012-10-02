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
assignment1: *.cxx *.cpp
	$(CC) -o assignment2 *.cxx *.cpp $(COMPILERFLAGS) $(LIBRARIES) $(LIBPATH) $(INCLUDES)

else

# Mac is silly, and uses frameworks
# Actually, wait, this is way easier than Linux's hard-coded paths
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
assignment1 : *.cxx *.cpp OpenGlCore.moc.cxx AssignmentCore.moc.cxx Sidebar.moc.cxx SidebarUi.ui.h
	$(CC) -o assignment2 *.cxx *.cpp $(COMPILERFLAGS) $(LIBRARIES) $(FRAMEWORK) $(LIBPATH) $(INCLUDES)

# Run the QT Moc
OpenGlCore.moc.cxx : OpenGlCore.h
	moc OpenGlCore.h -oOpenGlCore.moc.cxx

AssignmentCore.moc.cxx : AssignmentCore.h
	moc AssignmentCore.h -oAssignmentCore.moc.cxx

Sidebar.moc.cxx : Sidebar.h
	moc Sidebar.h -o Sidebar.moc.cxx

SidebarUi.ui.h : SidebarUi.ui
	uic SidebarUi.ui -o SidebarUi.ui.h

endif

