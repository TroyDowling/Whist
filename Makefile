#----------------------------------------------------------------
# (Cross-)Compiler
#----------------------------------------------------------------
CROSS_COMPILE ?=
CC := $(CROSS_COMPILE)g++

#----------------------------------------------------------------
# Paths
#----------------------------------------------------------------
INCDIR := include
SRCDIR := src
BUILDDIR := build
TARGET := bin/whist

#----------------------------------------------------------------
# Includes
#----------------------------------------------------------------
INC := -I$(INCDIR)

#----------------------------------------------------------------
# Sources and objects
#----------------------------------------------------------------
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

#----------------------------------------------------------------
# CFLAGS
#----------------------------------------------------------------
CFLAGS-y := $(CFLAGS)
CFLAGS-y += -std=c++11
CFLAGS-y += -Wall -Wextra -Wshadow -Wno-unused-parameter -Wno-unused-function

ifdef DEBUG
CFLAGS-y += -DDEBUG
DBG := -g -DDEBUG -pg -no-pie -fno-omit-frame-pointer -fno-inline-functions -fno-inline-functions-called-once -fno-optimize-sibling-calls
else
CFLAGS-y += -O3
DBG :=
endif

#----------------------------------------------------------------
# Libraries
#----------------------------------------------------------------
# Standard libraries.
LIB := -lm -lGL -lGLU -lglut

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo "$(CC) $(OBJECTS) $(LIB) $(DBG) -o $(TARGET)"; $(CC) $(OBJECTS) $(LIB) $(DBG) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS-y) $(INC) $(DBG) -c -o $@ $<"; $(CC) $(CFLAGS-y) $(INC) $(DBG) -c -o $@ $<

clean:
	@echo "Cleaning...";
	@echo "$(RM) -r $(BUILDDIR)/*.o $(TARGET)"; $(RM) -r $(BUILDDIR)/*.o $(TARGET)

.PHONY: clean
