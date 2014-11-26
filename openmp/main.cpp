/*
 * main.cpp
 *
 *  Created on: Nov 10, 2012
 *      Author: Junior
 */


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
#include <stdlib.h>

#include "random.h"
#include "game.h"
#include "read.h"
#include "team.h"
#include "standing.h"
#include "print.h"
#include "functions.h"
#include "ranking.h"
#include "postseason.h"
#include "save.h"
#include "histograms.h"
#include "online.h"
#include "players.h"

#ifdef _OPENMP
#include "omp.h"
#endif

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;
using std::clock;

int main(int argc, char* argv[]) {

//#ifdef WINDOWS
//    #include <direct.h>
//    #define CWD _getcwd
//#else
//    #include <unistd.h>
//    #define CWD getcwd
// #endif
/*
	seed();
	double sa=0,sb=0;

	double win=0;
	for (int i=0; i<1000000; i++) {
		double a = 112.63456 + gaussRand()*(10.80);
		double b =  96.80495 + gaussRand()*(10.80);

		if (a<b) win++;

		sa+=a/1000000;
		sb+=b/1000000;

	}
	cout << win/1000000 << endl;

	cout << sa << " " << sb << endl;
	exit(0);
*/
	runparams parameters;

	//initialize run parameters
	InitParams(parameters);

	//print header information
	PrintHeader(parameters);

	//determine parameters from input file
	ReadInput(parameters);

	//determine print level
	PrintLevel(parameters);

#ifdef _OPENMP

		omp_set_num_threads(parameters.threads);
		printf("     OPENMP| Parallel execution on %d allocated threads.\n\n", parameters.threads);

#endif

	//random number seed
	seed();

	vector<map<string, Team> > Teams;
	vector<vector<Game> > Games;
	vector<map<string, vector<double> > > AdjTeamRanks;
	map<string, map<string, vector<double> > > Hist;
	vector<Player> Players;

	// do specified analysis
	if (parameters.analysis) { RunAnalysis(parameters,Games,Teams,AdjTeamRanks,Hist,Players); }

	//
	//if (parameters.simulation) { RunSimulation(parameters,Games,Teams,AdjTeamRanks,Hist,Players); }
	if (!parameters.runtype.empty()) { RunSimulation(parameters,Games,Teams,AdjTeamRanks,Hist,Players); }

	//
	if (parameters.save) { Save(parameters); }

	//print footer information
	PrintFooter(parameters);

	return 0;

}
