# Alien Attack - Project makefile.

# Executable name.
EXE = alien-attack

# Project paths.
INC_DIR = include
OBJ_DIR = src/obj
SRC_DIR = src
TPL_DIR = include/templates

# Project extensions.
INC_EXT = hpp
OBJ_EXT = o
SRC_EXT = cpp
TPL_EXT = hpp

# Project components.
MAIN = main
CLASSES = Face Game GameObject Music Rectangle Sound Sprite State Texture \
	Tileset VectorR2
TEMPLATES = ErrorDescription RuntimeException

# Compiler name, source file extension and compilation data (flags and libs).
CC = g++
CFLAGS = -Wall -g -I $(INC_DIR)
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer

# Makefile function definitions.
FULL_PATH = $(patsubst %,$(2)/%.$(3),$(1))

# Joining file names with their respective paths.
DEPS = $(call FULL_PATH,$(CLASSES),$(INC_DIR),$(INC_EXT)) \
	$(call FULL_PATH,$(TEMPLATES),$(TPL_DIR),$(TPL_EXT))
OBJ = $(call FULL_PATH,$(CLASSES) $(MAIN),$(OBJ_DIR),$(OBJ_EXT))

# Project executable compilation rule.
$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Object files compilation rule.
$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT) $(DEPS)
	@if [ ! -d $(OBJ_DIR) ]; then \
		mkdir $(OBJ_DIR); \
	fi
	$(CC) -c -o $@ $< $(CFLAGS)

# List of aditional makefile commands.
.PHONY: all
.PHONY: clean

# Generate all available targets.
all: $(EXE)

# Command to clean object files and project executable.
clean:
	@rm -f $(OBJ_DIR)/*.o *~ core
	@if [ -f $(EXE) ]; then \
		rm -i $(EXE); \
	fi
