/*
 ============================================================================
 Name        : team.h
 Author      : oosode
 Version     : 
 Date        : Dec 26, 2013
 Description : 
 ============================================================================
 */
#ifndef TEAM_H_
#define TEAM_H_

#include "pointers.h"
#include <vector>

namespace NBA_NS {

class Team : protected Pointers {
 public:

   // ** Constructor/destructor ** //
   Team(NBA *);
   ~Team();

   // ** Variables ** //
   char   name[64];
   char   conference[64];
   char   division[64];
   int    nhomegames;
   int    nawaygames;
   double offrtg;
   double defrtg;
   double init_offrtg;
   double init_defrtg;
   double pace;
   int    win;
   int    loss;
   double winpercent;
   double ewin;
   double eloss;
   double ewinpercent;
   int    divisionwin;
   int    divisionloss;
   double divisionwinpercent;
   int    conferencewin;
   int    conferenceloss;
   double conferencewinpercent;
   int    homebestconferencewin;
   int    homebestconferenceloss;
   double homebestconferencepercent;
   int    awaybestconferencewin;
   int    awaybestconferenceloss;
   double awaybestconferencepercent;
   double average_p4;
   double average_pA;
   double average_league_p4;
   double average_league_pA;
   int    playoff_win;
   int    playoff_loss;
   double playoff_winpercent;
   double playoff_ewin;
   double playoff_eloss;
   double playoff_ewinpercent;
   int    gamesplayed;
   double playoff_average_p4;
   double playoff_average_pA;
   int    lottery;
   int    draftposition;
   std::vector<int> offrank;
   std::vector<int> defrank;
   std::vector<int> diffrank;
   std::vector<int> league_stand;
   std::vector<int> conference_stand;
   std::vector<int> division_stand;

   // ** Functions ** //
   void init();

};

}




#endif /* TEAM_H_ */
