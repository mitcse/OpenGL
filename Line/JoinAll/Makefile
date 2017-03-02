
# OS X, Linux
EXE = pattern

# Windows
# EXE = pattern.exe

# Linux 
# LDFLAGS = -lGL -lGLU -lglut

# Windows
# LDFLAGS = -lopengl32 -lglu32 -lglut32

# OS X
LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT -Wno-deprecated

$(EXE): pattern.cpp
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS)