/*
 * read.h
 *
 *  Created on: Nov 25, 2012
 *      Author: Junior
 */

#ifndef READ_H_
#define READ_H_

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <stdio.h>

#include "random.h"
#include "game.h"
#include "read.h"
#include "team.h"
#include "standing.h"
#include "print.h"
#include "functions.h"
#include "omp.h"
#include "run.h"
#include "ranking.h"
#include "histograms.h"
#include "players.h"

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;

class Game;
class Team;

void ReadInput(vector<string> inp,string &filename,int &nsims,string &runtype,
			   int &nthreads,bool &save,int &pval,string &start, string &end, bool &dbg,double &t);

void ReadInput(runparams &parms);

void ReadRatingRestart(runparams &parms, vector<map<string, Team> > &TeamM, vector<map<string, vector<double> > > &AdjTeamRanks);
void ReadRatingRestart(runparams &parms, vector<map<string, string> > &TeamM, vector<map<string, vector<double> > > &AR);

void ReadPlayerRestart(runparams &parms, vector<Player> &P, string fname);
void ReadPlayerRestartNew(runparams &parms, vector<Player> &P, string fname);
void ReadScheduleNew(runparams &parms, vector<map<string, Team> > &TeamM, vector<vector<Game> > &AllG,
		vector<map<string, vector<double> > > &AdjTeamRanks, map<string, map<string, vector<double> > > &Histogram, string fname);

void ReadScheduleClearNew(runparams &parms, vector<map<string, Team> > &TeamM, vector<vector<Game> > &AllG,
		vector<map<string, vector<double> > > &AdjTeamRanks, map<string, map<string, vector<double> > > &Histogram, string fname);

void ReadSimulation(vector<vector<Game> > &G, vector<map<string, Team> > &T, vector<map<string,vector<double> > > &AdjTeamRanks,
					map<string,map<string, vector<double> > > &Histogram, runparams &parms);

void ReadSimulation(vector<vector<string> > &G, vector<map<string, string> > &T, vector<map<string,vector<double> > > &AdjTeamRanks, map<string,map<string, vector<double> > > &Histogram, runparams &parms);

void ReadScheduleNew(runparams &parms, vector<map<string, string> > &TeamM, vector<vector<string> > &AllG,
                     vector<map<string, vector<double> > > &AdjTeamRanks, map<string, map<string, vector<double> > > &Histogram, string fname);

#endif /* READ_H_ */
