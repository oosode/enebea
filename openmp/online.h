/*
 * online.h
 *
 *  Created on: Jul 15, 2013
 *      Author: oosode
 */

#ifndef ONLINE_H_
#define ONLINE_H_

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include "random.h"
#include "game.h"
#include "read.h"
#include "team.h"
#include "standing.h"
#include "players.h"

class Game;
class Team;
class Player;

string fileToString(const string& filename);
void StripBballRef(string www, double &homertg, double &awayrtg);
void UpdateSchedule(vector<vector<Game> > &G, vector<map<string, Team> > &T, vector<map<string, vector<double> > > &AR,
		            map<string, map<string, vector<double> > > &H, vector<Player> &P,  runparams &parms);
void DownloadSchedule(vector<vector<Game> > &G, vector<map<string, Team> > &T, runparams &parms);
void DownloadPlayers(runparams &parms);
void UpdatePlayers(runparams &parms, vector<Player> &P);
void UpdatePlayersNew(runparams &parms, vector<Player> &P);
void DownloadTeam(runparams &parms, vector<Player> &P);

void TeamWinShares(runparams &parms, vector<Player> &P);
void TeamRating(runparams &parms, vector<Player> &P);
void TeamWinSharesRating(runparams &parms, vector<Player> &P);
void TeamNew(runparams &parms, vector<Player> &P);
//double LeagueAVG(runparams &parms, vector<Player> &P,string stat,int year);
//double SPS(Player &p, string stat, int year, double lmins3, double lmins2, double lmins1, double lstat3, double lstat2, double lstat1);

void RunAnalysis(runparams &parms, vector<vector<Game> > &G, vector<map<string, Team> > &T, vector<map<string, vector<double> > > &AR, map<string, map<string, vector<double> > > &H,vector<Player> &P);
#endif /* ONLINE_H_ */
