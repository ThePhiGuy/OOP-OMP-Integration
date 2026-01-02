# Originally created by Joel Adams, Calvin University
# Modified by Steven McKelvey, Calvin University
# Re-Utilized by Ryan Deaton, Calvin University for Integration Monte Carlo
# To build, enter: make

# name of the binary
PROGRAM   = integration

# source files
SRCS      = ooint.cpp main.cpp

# object files from source files
OBJS      = $(SRCS:.cpp=.o)

# which compiler to use
CC        = g++

# flags for compilation and linking 
CFLAGS    = -Wall -fPIE -fopenmp
LFLAGS    = -lm -fopenmp -fPIE

# Rules
.PHONY: clean

# valid file suffixes 
.SUFFIXES: .c .o .cpp

# Link object files
$(PROGRAM): $(OBJS)
	@echo "Linking $@..."
	@$(CC) $^ $(LFLAGS) -o $@ \
	|| { echo "Linking failed for $@"; exit 1; }
	@echo "Finished building $@"
	@echo " "

# command to build .o files from .c files
%.o: %.cpp
	@echo "Compiling $< to $@..."
	@$(CC) $(CFLAGS) -c $< -o $@ \
	|| { echo "Compiliation failed for $<"; exit 1; }
	@echo "Finished compiling $<"
	@echo " "


clean:
	/bin/rm -f $(OBJS) $(PROGRAM) *~ *#

