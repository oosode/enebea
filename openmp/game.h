/*
 * game.h
 *
 *  Created on: Nov 10, 2012
 *      Author: Junior
 */

#ifndef GAME_H_
#define GAME_H_

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <time.h>
#include <fstream>

#include "team.h"
#include "read.h"

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::ofstream;
using std::ifstream;

//class Team;

void PerGame(map<string, Team> &TheTeams);
void PerGame(map<string, string> &TheTeams);

class Game {

	public:

		Game();

		string AwayTeam;
		string HomeTeam;

		double AwayScore;
		double HomeScore;
		string Winner;
		string Loser;

		Team *Home;
		Team *Away;

		int GameIDint;
        string GameIDstring;

        bool GameOver;
        bool Playoff;

	    time_t GameDate;

	    vector<double> RestDaysOff;
	    vector<double> RestDaysDef;

	    void Load(Team *Ho, Team *Aw, int gameid, time_t gamedate);
	    void Load(Team *Ho, Team *Aw, int gameid, time_t gamedate, bool poff);
	    void Sim();
	    void SimPlayoffs(int r);
	    void GameFinished(double HomePoints, double AwayPoints, int &hx, int &ax);
	    void GameAlreadyFinished(double HomePoints, double AwayPoints, int &hx, int &ax);
	    void GameFinishedPlayoffs(double HomePoints, double AwayPoints, int &hx, int &ax, int round);
	    double Uncertainty(int gp);
        void read(ifstream *in);
	    void write(ofstream *out);
 
};



#endif /* GAME_H_ */
