# Alien Attack - Project makefile.

# Executable name.
EXE = alien-attack

# Compiler name, source file extension and compilation data (flags and libs).
CC = g++
CFLAGS = -Wall -g -I $(IDIR) -std=c++17
LIBS =

# Project paths.
IDIR = include
ODIR = src/obj
SDIR = src

# Project extensions.
IEXT = hpp
OEXT = o
SEXT = cpp

# Project main.
MAIN = main

# Project classes.
MODULES =

# Makefile function definitions.
FULL_PATH = $(patsubst %,$(2)/%.$(3),$(1))

# Joining file names with their respective paths.
DEPS = $(call FULL_PATH,$(MODULES),$(IDIR),$(IEXT))
OBJ = $(call FULL_PATH,$(MODULES) $(MAIN),$(ODIR),$(OEXT))
# SRC = $(call FULL_PATH,$(MODULES) $(MAIN),$(SDIR),$(SEXT))

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