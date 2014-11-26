/*
 * game.cpp
 *
 *  Created on: Nov 12, 2012
 *      Author: Junior
 */
#include <typeinfo>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>

#include "team.h"
#include "game.h"
#include "random.h"
#include "standing.h"
#include "read.h"
#include "ranking.h"

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::cin;

class Team;

void PerGame(map<string, Team> &TheTeams) {

    // league averages
	double avg4 = 0.0;
	double avgA = 0.0;

	int count = 0;

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		if (abs(iterator->second.avgP4) > 0.0001 && abs(iterator->second.avgPA) > 0.0001) {

		    avg4 += iterator->second.avgP4;
		    avgA += iterator->second.avgPA;

		    count++;

		}
	}

	avg4 = avg4/double(count);
	avgA = avgA/double(count);

	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		iterator->second.avgLeagueP4 = avg4;
		iterator->second.avgLeaguePA = avgA;

	}

	/*
	 *
	 */

	Standing(TheTeams);
	Ranking(TheTeams);

}

Game::Game() {

};
void Game::Load(Team *Ho, Team *Aw, int gameid, time_t gamedate) {

	char buffer [50];
	int t;
	tm *ltm = localtime(&gamedate);

	GameOver = false;

	GameIDint=gameid;

	Home=Ho;
	Away=Aw;

	AwayTeam = Away->TeamName;
	HomeTeam = Home->TeamName;

	GameDate=gamedate;

	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;

	t=sprintf (buffer, "%s.%s.%d-%d-%d", HomeTeam.c_str(),AwayTeam.c_str(),year,month,day);
	GameIDstring=buffer;

	double rv_off[] = {0.000,0.425,0.206,0.630,0.630,1.055,0.836,1.261,-0.617,-0.192,-0.411,0.013,0.013,0.438,0.219};
	double rv_def[] = {0.000,0.364,0.550,0.728,-0.087,0.277,0.463,0.827,1.751,2.115,2.301,2.665,1.751,2.028,2.214};

	vector<double> rvo (rv_off, rv_off + sizeof(rv_off) / sizeof(double) );
	vector<double> rvd (rv_def, rv_def + sizeof(rv_def) / sizeof(double) );

	RestDaysOff = rvo;
	RestDaysDef = rvd;

	Playoff=false;

};
void Game::Load(Team *Ho, Team *Aw, int gameid, time_t gamedate, bool poff) {

	char buffer [50];
	int t;
	tm *ltm = localtime(&gamedate);

	GameOver = false;

	GameIDint=gameid;

	Home=Ho;
	Away=Aw;

	AwayTeam = Away->TeamName;
	HomeTeam = Home->TeamName;

	GameDate=gamedate;

	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;

	t=sprintf (buffer, "%s.%s.%d-%d-%d", HomeTeam.c_str(),AwayTeam.c_str(),year,month,day);
	GameIDstring=buffer;

	double rv_off[] = {0.000,0.425,0.206,0.630,0.630,1.055,0.836,1.261,-0.617,-0.192,-0.411,0.013,0.013,0.438,0.219};
	double rv_def[] = {0.000,0.364,0.550,0.728,-0.087,0.277,0.463,0.827,1.751,2.115,2.301,2.665,1.751,2.028,2.214};

	vector<double> rvo (rv_off, rv_off + sizeof(rv_off) / sizeof(double) );
	vector<double> rvd (rv_def, rv_def + sizeof(rv_def) / sizeof(double) );

	RestDaysOff = rvo;
	RestDaysDef = rvd;

	Playoff=poff;

};
void Game::Sim() {

	int hx, ax;

	if (!GameOver)  {

		double HO,HD,AO,AD,HomeCourt;

		HomeCourt = 3.0;

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

	} else { GameFinished(HomeScore,AwayScore,hx,ax); }

};
void Game::SimPlayoffs(int r) {

	double HO,HD,AO,AD,HomeCourt;

	HO = (Home->OffRtg - Home->avgLeagueP4) + Home->OffRtg;// + tRand();
	HD = (Home->DefRtg - Home->avgLeaguePA) + Home->DefRtg;// + tRand();

	AO = (Away->OffRtg - Home->avgLeagueP4) + Away->OffRtg;// + tRand();
	AD = (Away->DefRtg - Home->avgLeagueP4) + Away->DefRtg;// + tRand();

	HomeCourt = 3.0;

	double HRtg = (HO+AD)/2.0;
	double ARtg = (AO+HD)/2.0 - HomeCourt;

	double HomePoints = HRtg + tRand();
	double AwayPoints = ARtg + tRand();

	int hx, ax;

	GameFinishedPlayoffs(HomePoints,AwayPoints,hx,ax,r);

};

void Game::GameFinished(double HomePoints, double AwayPoints, int &hx, int &ax) {

	GameOver=true;

	AwayScore = AwayPoints;
	HomeScore = HomePoints;

	if ( HomeScore >= AwayScore ) {

		Winner = HomeTeam;
		Loser = AwayTeam;

	} else {

		Winner = AwayTeam;
		Loser = HomeTeam;

	}

	hx = Home->Game(AwayTeam,HomePoints,AwayPoints,GameDate);
	ax = Away->Game(HomeTeam,AwayPoints,HomePoints,GameDate);

	Home->GamesPlayed++;
	Away->GamesPlayed++;

	Home->Calculate();
	Away->Calculate();

};
void Game::GameAlreadyFinished(double HomePoints, double AwayPoints, int &hx, int &ax) {

	GameOver=true;

	AwayScore = AwayPoints;
	HomeScore = HomePoints;

	if ( HomeScore >= AwayScore ) {

		Winner = HomeTeam;
		Loser = AwayTeam;

	} else {

		Winner = AwayTeam;
		Loser = HomeTeam;

	}

	hx = Home->GameAlready(AwayTeam,HomePoints,AwayPoints,GameDate);
	ax = Away->GameAlready(HomeTeam,AwayPoints,HomePoints,GameDate);

	Home->Calculate();
	Away->Calculate();

};
void Game::GameFinishedPlayoffs(double HomePoints, double AwayPoints, int &hx, int &ax, int r) {

	GameOver=true;

	AwayScore = AwayPoints;
	HomeScore = HomePoints;

	if ( HomeScore >= AwayScore ) {

		Winner = HomeTeam;
		Loser = AwayTeam;

	} else {

		Winner = AwayTeam;
		Loser = HomeTeam;

	}

	hx = Home->PlayoffGame(AwayTeam,HomePoints,AwayPoints,r);
	ax = Away->PlayoffGame(HomeTeam,AwayPoints,HomePoints,r);

	Home->CalculatePlayoffs();
	Away->CalculatePlayoffs();

};
double Game::Uncertainty(int gp) {

	return -2.263*log( (double) gp ) + 10.277;

}


