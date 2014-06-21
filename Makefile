# ----------------------------------------------- #
# ** Makefile for FMR code **
# ----------------------------------------------- #


# ----------------------------------------------- #
# ** User defined variables **
# ----------------------------------------------- #
# MPI C++ compiler
CXX = mpicxx

# Debugging flags
#DEBUG = -g -DFMR_DEBUG
DEBUG = -g 

# Compiler flags
CFLAGS = -O3 $(DEBUG) -DMPICH_IGNORE_CXX_SEEK

# Libraries, if any
LIBDIR = -L/usr/lib
LIB = -lm -llapack

# ----------------------------------------------- #
# Compilation instructions
# ----------------------------------------------- #

SRC = $(wildcard *.cpp)
INC = $(wildcard *.h)
OBJ = $(SRC:.cpp=.o)

install: $(OBJ)
	$(CXX) $(OBJ) $(LIB) -o enebea.exe

clean: 
	rm -f *.o enebea.exe

%.o:%.cpp
	$(CXX) $(CFLAGS) -c $<
