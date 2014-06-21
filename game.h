/*
 ============================================================================
 Name        : game.h
 Author      : oosode
 Version     : 
 Date        : Dec 24, 2013
 Description : 
 ============================================================================
 */
#ifndef GAME_H_
#define GAME_H_

// Read options
#define SEASON_GAME  0
#define PLAYOFF_GAME 1

#include "pointers.h"
#include <vector>

namespace NBA_NS {

class Game : protected Pointers {
 public:

   // ** Constructor/destructor ** //
   Game(NBA *);
   ~Game();

   // ** Variables ** //
   char awayteam[64];               // Away team name
   char hometeam[64];	            // Home team name
   double awayscore;				// Away team score
   double homescore;				// Home team score
   double pace;					    // Number of possessions
   double awayrating;				// Away team pace adjusted score
   double homerating;				// Home team pace adjusted score
   char winner[64];					// String of winning team name
   char loser[64];					// String of losing team name
   Team* home;
   Team* away;
   char gameid[64];					// Game ID string
   int gamenumber;					// Game ID int
   bool gameover;					// Has game already been simulated or played?
   int gametype;					// Season or playoff game
   time_t gamedate;                 // Day of scheduled game
   std::vector<double> restoff;     // Offensive rest days array
   std::vector<double> restdef;     // Defensive rest days array

   // ** Functions ** //
   void init();                   // Initializer function, calls others to set up MD run
   void load(Team*,Team*,int,time_t);
   void sim();

};

}

#endif /* GAME_H_ */
