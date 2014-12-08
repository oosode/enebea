/* 
 ============================================================================
 Name        : season.h
 Author      : oosode
 Version     : 
 Date        : Dec 07, 2014
 Description : 
 ============================================================================
 */
#ifndef STANDING_H_
#define STANDING_H_

#include <map>
#include <vector>
#include <string>
//#include <cmath>
//#include <map>
//#include <vector>
//#include <iostream>
//#include <time.h>
//#include "run.h"
//#include "read.h"
#include "pointers.h"

namespace NBA_NS {


struct runparams;

struct MarginStandings {

	string TeamName;

	vector<int> BestLStanding;
	vector<int> BestCStanding;
	vector<int> BestDStanding;

	vector<int> WorstLStanding;
	vector<int> WorstCStanding;
	vector<int> WorstDStanding;

	int BestWin;
	int BestLoss;
	int BestWinC;
	int BestLossC;
	int BestWinD;
	int BestLossD;

	int WorstWin;
	int WorstLoss;
	int WorstWinC;
	int WorstLossC;
	int WorstWinD;
	int WorstLossD;

};
void AssignStanding(map<string, vector<string> > &Standings, int year, runparams &parms);
bool TieBreak(Team &TA, Team &TB);
bool PlayoffTieBreak(Team &TA, Team &TB);
double GamesBack(int W, int L, int FirstW, int FirstL);
void Standing(map<string, Team> &TheTeams);
void FinalStanding(map<string, Team> &TheTeams,double &q,bool debug);
void WinsAgainst(vector<map<string, Team> > &T, vector<vector<vector<double> > > &oppwin, double &t, bool debug);
void BestWorstStanding(vector<map<string, Team> > &T, vector<MarginStandings> &MarginStands,double &q, bool debug);

#endif /* STANDING_H_ */
