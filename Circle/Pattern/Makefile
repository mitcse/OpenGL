
# OS X, Linux
EXE = boom

# Windows
# EXE = boom.exe

# Linux 
# LDFLAGS = -lGL -lGLU -lglut

# Windows
# LDFLAGS = -lopengl32 -lglu32 -lglut32

# OS X
LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT -Wno-deprecated

$(EXE): boom.cpp
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS)