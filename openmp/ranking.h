/*
 * ranking.h
 *
 *  Created on: Dec 29, 2012
 *      Author: Junior
 */

#ifndef RANKING_H_
#define RANKING_H_

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <time.h>

#include "run.h"

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

struct runparams;

struct MarginRankings {

	string TeamName;

	vector<int> BestOffense;
	vector<int> BestDefense;
	vector<int> BestDifferential;

	vector<int> WorstOffense;
	vector<int> WorstDefense;
	vector<int> WorstDifferential;

	double BestOff;
	double BestDef;
	double BestDiff;

	double WorstOff;
	double WorstDef;
	double WorstDiff;

};

void BestWorstRanking(vector<map<string, Team> > &T, vector<MarginRankings> &BWRank,double &q,bool debug);
void AverageRanking(vector<map<string, Team> > &T, map<string, vector<double> > &AvgTeamRanks,double &q,bool debug);
//void SimpleRanking(map<string, Team> &TheTeams, map<string, vector<double> > &AdjTeamRanks, double &q, bool debug);
void SimpleRanking(map<string, Team> &TheTeams, map<string, vector<double> > &AdjTeamRanks, double &q, runparams &parms);
//void SimpleRanking(map<string, Team> &TheTeams, map<string, vector<double> > &AdjTeamRanks);
void SimpleRankingLast10(map<string, Team> &TheTeams, map<string, vector<double> > &AdjTeamRanks);
void SimpleRankingQuarter(map<string, Team> &TheTeams, map<string, vector<double> > &AdjTeamRanks);
void ColleyRanking(map<string, Team> &TheTeams, map<string,vector<double> > &AdjTeamRanks);
void Ranking(map<string, Team> &TheTeams);



#endif /* RANKING_H_ */
