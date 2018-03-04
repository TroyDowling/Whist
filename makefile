FMOD_DIR = /usr/local/dept/apps/fmod
FMOD_INCLUDE = -I$(FMOD_DIR)/api/inc -I$(FMOD_DIR)/examples/common
FMOD_LIB = $(FMOD_DIR)/api/lib/libfmodex64.so
TARBALL_FILES = README.md makefile $(wildcard *.cpp *.h *.pam imgs)

# Compiler option setup and library stuff
OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif
AI.o: AI.cpp AI.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c AI.cpp

Card.o:	Card.cpp Card.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c Card.cpp

Gamestate.o: Gamestate.cpp Gamestate.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c Gamestate.cpp

Gamestate: Gamestate.o Card.o Deck.o
	g++ $(OPTS) $(MACOSX_DEFINE) -o Gamestate Gamestate.o Deck.o Card.o

Button.o: Button.cpp Button.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c Button.cpp

hand.o: hand.h hand.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c hand.cpp

Deck.o: Deck.h Deck.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c Deck.cpp

whist:	Whist.o texture.o Gamestate.o Deck.o Card.o hand.o Button.o AI.o
	g++ $(OPTS) -o Whist Whist.o texture.o Card.o Gamestate.o hand.o Deck.o Button.o AI.o $(LIBS)

Whist.o:	Whist.cpp texture.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c Whist.cpp

texture.o:	texture.cpp texture.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c texture.cpp

tarball: $(TARBALL_FILES)
	tar cfz Whist.tar.gz $(TARBALL_FILES)

clear:
	rm *.o
