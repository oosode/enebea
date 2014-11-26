/*
 * projection.h
 *
 *  Created on: Oct 23, 2013
 *      Author: oosode
 */

#ifndef PROJECTION_H_
#define PROJECTION_H_

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

double SPS(Player &p,string stat, int year, double lmins3, double lmins2, double lmins1,
										    double lstat3, double lstat2, double lstat1);

double LeagueAVG(runparams &parms, vector<Player> &P, string stat, int year);

void PlayerProjection(runparams&,vector<Player>&,Player&,int);
void TeamProjection(runparams &parms, vector<Player> &P);
#endif /* PROJECTION_H_ */
