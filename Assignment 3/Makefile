UNAME := $(shell uname)

# This assignment compiles on Linux & Mac
# Please build it on the computers in MS239


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

# Run the QT Moc
#OpenGlCore.moc.cxx : OpenGlCore.h
#	moc OpenGlCore.h -oOpenGlCore.moc.cxx
#
AssignmentCore.moc.cxx : AssignmentCore.h
	moc AssignmentCore.h -oAssignmentCore.moc.cxx
#
#Sidebar.moc.cxx : Sidebar.h
#	moc Sidebar.h -o Sidebar.moc.cxx
#
#ModelRenderer.moc.cxx : ModelRenderer.h
#	moc ModelRenderer.h -o ModelRenderer.moc.cxx
#
#RenderOptionManager.moc.cxx : RenderOptionManager.h
#	moc RenderOptionManager.h -o RenderOptionManager.moc.cxx
#
#ModelManager.moc.cxx : ModelManager.h
#	moc ModelManager.h -o ModelManager.moc.cxx
#
#SliderSpinboxController.moc.cxx : SliderSpinboxController.h
#	moc SliderSpinboxController.h -o SliderSpinboxController.moc.cxx
#
#Md2Model.moc.cxx : Md2Model.h
#	moc Md2Model.h -o Md2Model.moc.cxx
#
#GroundModel.moc.cxx : GroundModel.h
#	moc GroundModel.h -o GroundModel.moc.cxx
#
#SidebarUi.ui.h : SidebarUi.ui
#	uic SidebarUi.ui -o SidebarUi.ui.h
#