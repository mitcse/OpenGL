
# OS X, Linux
EXE = ball

# Windows
# EXE = ball.exe

# Linux 
# LDFLAGS = -lGL -lGLU -lglut

# Windows
# LDFLAGS = -lopengl32 -lglu32 -lglut32

# OS X
LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT -Wno-deprecated

$(EXE): ball.cpp
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS)