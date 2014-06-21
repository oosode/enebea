/*
 ============================================================================
 Name        : pointers.h
 Author      : oosode
 Version     : 
 Date        : Nov 9, 2013
 Description : 
 ============================================================================
 */
#ifndef POINTERS_H_
#define POINTERS_H_

#include "nba.h"

namespace NBA_NS {

class Pointers {
 public:
  Pointers(NBA *ptr) :
   nba(ptr),
   input(ptr->input),
   run(ptr->run),
   game(ptr->game),
   team(ptr->team),
   season (ptr->season) {}
   //playoff (ptr->playoff) {}
  virtual ~Pointers() {}

 protected:
  NBA *nba;
  Input *&input;
  Run *&run;
  Game *&game;
  Team *&team;
  Season *&season;
  //Playoff *&playoff;
  //Matrix *&matrix;
  //State *&state;
  //Dynamics *&dynamics;

};

}

#endif /* POINTERS_H_ */
