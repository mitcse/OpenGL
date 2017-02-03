
# OS X, Linux
EXE = radar

# Windows
# EXE = radar

# Linux 
# LDFLAGS = -lGL -lGLU -lglut

# Windows
# LDFLAGS = -lopengl32 -lglu32 -lglut32

# OS X
LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT -Wno-deprecated

$(EXE): radar.cpp
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS)