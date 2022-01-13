# Alien Attack - Project makefile.

# Executable name.
EXE = alien-attack

# Compiler name, source file extension and compilation data (flags and libs).
CC = g++
CFLAGS = -Wall -g -I $(IDIR)
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer

# Project paths.
IDIR = include
ODIR = src/obj
SDIR = src

# Project extensions.
IEXT = hpp
OEXT = o
SEXT = cpp

# Project components.
MAIN = main
CLASSES = Game Music Sprite State
TEMPLATES = ErrorDescriptionTemplate 

# Makefile function definitions.
FULL_PATH = $(patsubst %,$(2)/%.$(3),$(1))

# Joining file names with their respective paths.
DEPS = $(call FULL_PATH,$(CLASSES) $(TEMPLATES),$(IDIR),$(IEXT))
OBJ = $(call FULL_PATH,$(CLASSES) $(MAIN),$(ODIR),$(OEXT))
# SRC = $(call FULL_PATH,$(CLASSES) $(MAIN),$(SDIR),$(SEXT))

# Project executable compilation rule.
$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Object files compilation rule.
$(ODIR)/%.$(OEXT): $(SDIR)/%.$(SEXT) $(DEPS)
	@if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi
	$(CC) -c -o $@ $< $(CFLAGS)

# List of aditional makefile commands.
.PHONY: all
.PHONY: clean

# Generate all available targets.
all: $(EXE)

# Command to clean object files and project executable.
clean:
	@rm -f $(ODIR)/*.o *~ core
	@if [ -f $(EXE) ]; then \
		rm -i $(EXE); \
	fi