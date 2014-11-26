/*
 * histograms.cpp
 *
 *  Created on: Apr 11, 2013
 *      Author: oosode
 */

#include <typeinfo>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>

#include "random.h"
#include "game.h"
#include "team.h"
#include "functions.h"
#include "standing.h"

using std::pair;
using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

void PopulateHists(vector<map<string, Team> > &Teams, map<string, map<string,vector<double> > > &H,double &q,bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PopulateHists starting...\n"); }

	string team;

	//Teams.front().begin()->second.

	vector<double> tmp1(30,0);
	vector<double> tmp2(8,0);
	vector<double> tmp3(83,0);
	vector<double> tmp4(15,0);
	vector<double> tmp5(10,0);
	vector<double> tmp6(17,0);
	vector<double> tmp7(14,0);

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = Teams.front().begin(); iterator != Teams.front().end(); iterator++) {

		team=iterator->second.TeamName;
		double size=Teams.size();

		// initialize
		H.find(team)->second.find("DraftPos")->second=tmp1;
		H.find(team)->second.find("Lottery")->second=tmp1;
		H.find(team)->second.find("Seeds")->second=tmp2;
		H.find(team)->second.find("pWins")->second=tmp6;
		H.find(team)->second.find("pLoss")->second=tmp7;
		H.find(team)->second.find("Wins")->second=tmp3;
		H.find(team)->second.find("Loss")->second=tmp3;
		H.find(team)->second.find("Division")->second=tmp5;
		H.find(team)->second.find("Conference")->second=tmp4;
		H.find(team)->second.find("League")->second=tmp1;
		H.find(team)->second.find("ORanks")->second=tmp1;
		H.find(team)->second.find("DRanks")->second=tmp1;

		for (int i=0; i<(int)Teams.size(); i++) {

			for (it_type iterator1 = Teams.at(i).begin(); iterator1 != Teams.at(i).end(); iterator1++) {

				if (iterator1->second.TeamName==team) {

					// draftpos
					H.find(team)->second.find("DraftPos")->second.at(iterator1->second.DraftPos)+=100.0/size;

					// lottery
					H.find(team)->second.find("Lottery")->second.at(iterator1->second.Lottery)+=100.0/size;

					// seeds
					if (iterator1->second.PlayoffSeed>=0 && iterator1->second.PlayoffSeed<8) {

						H.find(team)->second.find("Seeds")->second.at(iterator1->second.PlayoffSeed)+=100.0/size;

						// playoff wins
						H.find(team)->second.find("pWins")->second.at(iterator1->second.pWin)+=100.0/size;

						// playoff loss
						H.find(team)->second.find("pLoss")->second.at(iterator1->second.pLoss)+=100.0/size;

					}

					// wins
					H.find(team)->second.find("Wins")->second.at(iterator1->second.Win)+=100.0/size;

					// loss
					H.find(team)->second.find("Loss")->second.at(iterator1->second.Loss)+=100.0/size;

					// division
					H.find(team)->second.find("Division")->second.at(iterator1->second.Dstand.back()-1)+=100.0/size;

					// conference
					H.find(team)->second.find("Conference")->second.at(iterator1->second.Cstand.back()-1)+=100.0/size;

					// league
					H.find(team)->second.find("League")->second.at(iterator1->second.Lstand.back()-1)+=100.0/size;

					// oranks
					H.find(team)->second.find("ORanks")->second.at(iterator1->second.OffRtgRank.back()-1)+=100.0 /size;

					// dranks
					H.find(team)->second.find("DRanks")->second.at(iterator1->second.DefRtgRank.back()-1)+=100.0/size;


				}
			}
		}
	}

	if (debug) { printf("PopulateHists exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}


