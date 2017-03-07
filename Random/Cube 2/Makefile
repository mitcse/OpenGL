
# OS X, Linux
EXE = cube

# Windows
# EXE = cube.exe

# Linux 
# LDFLAGS = -lGL -lGLU -lglut

# Windows
# LDFLAGS = -lopengl32 -lglu32 -lglut32

# OS X
LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT -Wno-deprecated

$(EXE): cube.cpp
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS)