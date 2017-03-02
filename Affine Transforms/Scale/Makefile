
# OS X, Linux
EXE = base

# Windows
# EXE = base.exe

# Linux 
# LDFLAGS = -lGL -lGLU -lglut

# Windows
# LDFLAGS = -lopengl32 -lglu32 -lglut32

# OS X
LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT -Wno-deprecated

$(EXE): base.cpp
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS)