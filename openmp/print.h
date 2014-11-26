/*
 * print.h
 *
 *  Created on: Dec 2, 2012
 *      Author: Junior
 */

#ifndef PRINT_H_
#define PRINT_H_

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <time.h>
#include "ranking.h"
#include "standing.h"
#include "run.h"
#include "histograms.h"
#include "game.h"
#include "team.h"

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

class Game;
class Team;
struct runparams;

void PrintLevel(int p,bool &p_margins,bool &p_averages,bool &p_rankings,bool &p_histograms, bool &p_standings,double &t,bool debug);
void PrintLevel(runparams &parms);

void PrintStandings(vector<map<string,Team> > &TheTeams,double &q,bool debug);
void PrintRankings(vector<map<string,Team> > &TheTeams,double &q,bool debug);
void PrintAvgStandings(vector<map<string,Team> > &TheTeams,double &q,bool debug);
void PrintAgainst(vector<map<string, Team> > &T, const vector<vector<vector<double> > > &oppwin,double &q,bool debug);
void PrintSchedule(vector<map<string, Team> > &T, vector<vector<Game> > &Games,double &q, bool debug);
void PrintRefSchedule(vector<map<string, Team> > &T, vector<vector<Game> > &Games,string name,double &q, bool debug);
void PrintAvgRankings(vector<map<string,Team> > &T, map<string, vector<double> > &AvgTeamRanks, double &q, bool debug);
void PrintDraft(vector<map<string, Team> > &T, map<string, vector<double> > &AvgDraftPos,double &q,bool debug);
void PrintHist(map<string, map<string, vector<double> > >&Hist,double &q,bool debug);
void PrintMargins(vector<MarginRankings> &MarginRanks, vector<MarginStandings> &MarginStands,double &q, bool debug);
void PrintPlayoffs(vector<map<string, Team> > &T, double &q, bool debug);

void PrintSimulation(runparams &parms, vector<map<string, Team> > &T, vector<vector<Game> > &G, map<string,map<string, vector<double> > > &Hist);

void PrintHeader(runparams &parms);
void PrintFooter(runparams &parms);

#endif /* PRINT_H_ */
