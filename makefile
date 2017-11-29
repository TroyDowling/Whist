FMOD_DIR = /usr/local/dept/apps/fmod
FMOD_INCLUDE = -I$(FMOD_DIR)/api/inc -I$(FMOD_DIR)/examples/common
FMOD_LIB = $(FMOD_DIR)/api/lib/libfmodex64.so

# Compiler option setup and library stuff
OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

whist:	Whist.o texture.o
	g++ $(OPTS) -o Whist Whist.o texture.o $(LIBS)

Whist.o:	Whist.cpp texture.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c Whist.cpp

texture.o:	texture.cpp texture.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c texture.cpp
