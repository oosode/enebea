/*
 ============================================================================
 Name        : nba.h
 Author      : oosode
 Version     :
 Date        : Nov 09, 2013
 Description :
 ============================================================================
 */

#ifndef NBA_H_
#define NBA_H_

#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "nba.h"

namespace NBA_NS {

#define FLERR __FILE__,__LINE__
#define MASTER_RANK 0

class NBA {
 public:

  // ** Constructor/destructor ** //
  NBA(int, char **, MPI_Comm);
  ~NBA();

  // ** MPI business ** //
  MPI_Comm world;               // MPI communicator for world
  int world_size;               // Size of world
  int my_rank;                  // My rank in world

  // ** Class pointers ** //
  class Input *input;           // Handles input file and atoms file
  class Run *run;               // Handles run specs and manages calculations
  class Game *game;
  class Team *team;
  class Season *season;
  class Playoff *playoff;
  //class Math *math;         // Handles Hamiltonian matrix, etc.

  // ** Variables ** //
  int master_rank;
  int print_level;

  // ** Functions ** //
  void parse_command_line(int, char **);
  void execute();                              // Executes the calculation
  void error(const char *, int, const char *); // Controlled error crash

};

}

#endif /* NBA_H_ */
