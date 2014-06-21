/*
 ============================================================================
 Name        : game.cpp
 Author      : oosode
 Version     : 
 Date        : Dec 24, 2013
 Description : 
 ============================================================================
 */

#include "nba.h"
#include "game.h"
#include "team.h"

using namespace NBA_NS;

#define MAX_LENGTH 1024

/*-----------------------------------------------------------------
  Constructor
-----------------------------------------------------------------*/

Game::Game(NBA *nba) : Pointers(nba)
{
   // Set defaults
   gametype   = SEASON_GAME;
   gameover = false;

   double rv_off[] = {0.000,0.425,0.206,0.630,0.630,1.055,0.836,1.261,-0.617,-0.192,-0.411,0.013,0.013,0.438,0.219};
   double rv_def[] = {0.000,0.364,0.550,0.728,-0.087,0.277,0.463,0.827,1.751,2.115,2.301,2.665,1.751,2.028,2.214};

   std::vector<double> rvo (rv_off, rv_off + sizeof(rv_off) / sizeof(double) );
   std::vector<double> rvd (rv_def, rv_def + sizeof(rv_def) / sizeof(double) );

   restoff = rvo;
   restdef = rvd;
/*
   n_monomers = 0;
   n_dimers   = 0;
   fmo_energies      = NULL;
   monomer_energies  = NULL;
   dimer_energies    = NULL;
   fmo_gradients     = NULL;
   monomer_gradients = NULL;
   dimer_gradients   = NULL;
*/
}

/*-----------------------------------------------------------------
  Destructor
-----------------------------------------------------------------*/

Game::~Game()
{
/*
  if (fmo_energies      != NULL) delete [] fmo_energies;
  if (monomer_energies  != NULL) delete [] monomer_energies;
  if (dimer_energies    != NULL) delete [] dimer_energies;
  if (fmo_gradients     != NULL) delete [] fmo_gradients;
  if (monomer_gradients != NULL) delete [] monomer_gradients;
  if (dimer_gradients   != NULL) delete [] dimer_gradients;
*/
}

void Game::load(Team* Ho, Team* Aw, int gamenum, time_t date) {

	tm *ltm = localtime(&date);

	gamenumber=gamenum;

	home=Ho;
	away=Aw;

	sprintf (awayteam, "%s", away->name);
	sprintf (hometeam, "%s", home->name);

	gamedate=date;

	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;

	sprintf (gameid, "%s.%s.%d-%d-%d", hometeam,awayteam,year,month,day);
};

void Game::sim() {

	printf("game::sim on rank %d\n",nba->my_rank);

	if (!gameover)  {

/*
		int k = (Home->GamesPlayed+1 + Away->GamesPlayed+1)/2.0;
		double sig = Uncertainty(k); // uncertainty
		//double nrm = Uncertainty(1); // normal distribution of points
		double nrm=10.8;

		int HRest = Home->Rest(GameDate);
		int ARest = Away->Rest(GameDate);

		HO = (Home->OffRtg - Home->avgLeagueP4) + Home->OffRtg + RestDaysOff.at(HRest);// + tRand();
		HD = (Home->DefRtg - Home->avgLeaguePA) + Home->DefRtg + RestDaysDef.at(HRest);// + tRand();

		AO = (Away->OffRtg - Home->avgLeagueP4) + Away->OffRtg + RestDaysOff.at(ARest);// + tRand();
		AD = (Away->DefRtg - Home->avgLeagueP4) + Away->DefRtg + RestDaysDef.at(ARest);// + tRand();

		double HRtg = (HO+AD)/2.0 + HomeCourt/2.0;
		double ARtg = (AO+HD)/2.0 - HomeCourt/2.0;


		//if (Home->TeamName=="OKC" && Away->TeamName=="ORL") { cout << HRtg << " " << ARtg << endl; }

		//double HRtg = (HO+AD)/2.0;
		//double ARtg = (AO+HD)/2.0;

		//double HomePoints = HRtg + tRand();
		//double AwayPoints = ARtg + tRand();

		double HomePoints = HRtg + gaussRand()*(sig+nrm);
		double AwayPoints = ARtg + gaussRand()*(sig+nrm);

		//cout << sig+nrm << endl;

		GameFinished(HomePoints,AwayPoints,hx,ax);
*/
	} //else { GameFinished(HomeScore,AwayScore,hx,ax); }

};

