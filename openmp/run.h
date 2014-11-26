/*
 * run.h
 *
 *  Created on: Jul 24, 2013
 *      Author: oosode
 */

#ifndef RUN_H_
#define RUN_H_

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <time.h>

#include "team.h"
#include "run.h"
#include "game.h"
#include "postseason.h"
#include "players.h"

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

class Game;


struct runparams {

	bool analysis;

	//player analysis
	bool   player_update;
	int    player_update_year;
	string print_player_update;
	string read_player_update;

	bool player_download;
	string print_player_download;

	bool player_analysis;
	string print_player_analysis;
	string read_player_analysis;
	string player_analysis_stat;
	int    begin_player_analysis;
	int    end_player_analysis;

	//team analysis
	bool   team_download;
	int    team_download_year;
	string print_team_download;
	string read_team_download;

	bool   team_update;
	string print_team_update;
	string read_team_update_team;
	string read_team_update_player;
	int    team_update_year;
	string team_update_type;

	//season analysis
	bool   season_update;
	string begin_season_update;
	string finish_season_update;
	string print_season_update;
	string read_season_update;

	bool   season_download;
	int    season_download_year;
	string print_season_download;


	string update;
	string download;

	int download_year;

	int player_year;
	string playerrestart;

	string teamrestart;

	string begin_update;
	string finish_update;

	string website;

	/*
	 *
	 *
	 */

	bool simulation;




	string runtype;

	//ratings
	int ratingfreq;
	int ratingmin;
	string ratingrestart;
	double ratinginit;
	int ratingmemory;

	string filename;
	string savedir;
	string stime;
	string etime;

	vector<string> flnm;

	bool debug;
	bool save;

	int pl;

	int nsims; // number of simulations
	int Sim;

	//print info
	bool p_histograms;
	bool p_standings;
	bool p_margins;
	bool p_averages;
	bool p_rankings;

	//
	double tprint;
	double tfinal;
	double tdraft;
	double tagainst;
	double tdaverage;
	double traverage;
	double thist;
	double trmargin;
	double tsmargin;
	double tupdate;
	double tschedule;
	double tsim;
	double tsave;
	double tread;
	double tinit;
	double tuinit;
	double trank;
	double tplayers;
	double tuplayers;

	//
	double tpstands;
	double tpranks;
	double tpagainst;
	double tpdraft;
	double tpplayoffs;
	double tplayoffs;
	double tphist;
	double tpmargin;
	double tpschedule;
	double tpsaverage;
	double tpraverage;

	double wallclock;
	double startwallclock;
	double stopwallclock;

	double cpuclock;

	char* cwd;
	char* uname;
	char* hostname;

	int threads;

};
void InitParams(runparams &parms);
void InitGlobals(runparams &parms,vector<map<string, Team> > &T, vector<vector<Game> > &G,
		vector<map<string, vector<double> > > &AdjTeamRanks);
void UinitGlobals(runparams &parms,vector<map<string, Team> > &T, vector<vector<Game> > &G,
		vector<map<string, vector<double> > > &AdjTeamRanks,map<string, map<string, vector<double> > > &Hist, vector<Player> &P);

void RunSimulation(runparams &parms, vector<vector<Game> > &G, vector<map<string, Team> > &T,
		vector<map<string,vector<double> > > &AdjTeamRanks,map<string,map<string, vector<double> > > &Histogram, vector<Player> &P);
/*
void InitGlobals(runparams &parms, vector<map<string, string> > &T, vector<vector<string> > &G,
                 vector<map<string, vector<double> > > &AdjTeamRanks);

void UinitGlobals(runparams &parms,vector<map<string, string> > &T, vector<vector<string> > &G,
                  vector<map<string, vector<double> > > &AR, map<string, map<string, vector<double> > > &H, vector<Player> &P);

void RunSimulation(runparams &parms, vector<vector<string> > &G, vector<map<string, string> > &T,
                   vector<map<string,vector<double> > > &AR, map<string,map<string, vector<double> > > &H, vector<Player> &P);
 */
#endif /* RUN_H_ */
