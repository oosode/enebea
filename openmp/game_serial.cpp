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

void PerGame(map<string, string> &TheTeams) {

    // league averages
	double avg4 = 0.0;
	double avgA = 0.0;

	int count = 0;

	typedef map<string, string>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {
        
        ifstream in(iterator->second.c_str());
        Team temp;
        temp.read(&in);
        
		if (abs(temp.avgP4) > 0.0001 && abs(temp.avgPA) > 0.0001) {

		    avg4 += temp.avgP4;
		    avgA += temp.avgPA;

		    count++;

		}
        
        ofstream out(iterator->second.c_str());
        temp.write(&out);
        out.flush();
	}

	avg4 = avg4/double(count);
	avgA = avgA/double(count);

	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {
        
        ifstream in(iterator->second.c_str());
        Team temp;
        temp.read(&in);

		temp.avgLeagueP4 = avg4;
		temp.avgLeaguePA = avgA;
        
        ofstream out(iterator->second.c_str());
        temp.write(&out);
        out.flush();

	}

	/*
	 *
	 */

	Standing(TheTeams);
	Ranking(TheTeams);

}
