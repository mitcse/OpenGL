
# OS X, Linux
EXE = main

# Windows
# EXE = main.exe

# Linux 
# LDFLAGS = -lGL -lGLU -lglut

# Windows
# LDFLAGS = -lopengl32 -lglu32 -lglut32

# OS X
LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT -Wno-deprecated

$(EXE): main.cpp
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS)