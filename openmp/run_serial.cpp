/*
 * run.cpp
 *
 *  Created on: Jul 24, 2013
 *      Author: oosode
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
#include <fstream>

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
#include "run.h"
#include "histograms.h"
#include "online.h"
#include "players.h"
#include "run.h"

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
using std::ofstream;
using std::ifstream;

void InitGlobals(runparams &parms, vector<map<string, string> > &T, vector<vector<string> > &G,
		vector<map<string, vector<double> > > &AdjTeamRanks) {

	clock_t starttime = clock();

	if (parms.debug) { printf("InitGlobals starting...\n"); }

	printf("     MAIN| starting initialization of global maps and vectors\n");

	int tsize = abs(T.max_size());
	int gsize = abs(G.max_size());

	if (tsize < parms.nsims && tsize < abs(gsize)) {
		parms.Sim = tsize;
	} else if (gsize < tsize && gsize < parms.nsims) {
		parms.Sim = gsize;
	} else {
		parms.Sim = parms.nsims;
	}

	T.resize(parms.Sim);
	G.resize(parms.Sim);
	AdjTeamRanks.resize(parms.Sim);

	//for (int i=0; i<parms.Sim; i++) {

	//	G.at(i).resize(1230);

	//}

	printf("     MAIN| finished initialization of global maps and vectors\n\n");

	if (parms.debug) { printf("InitGlobals exiting...\n\n"); }

	clock_t endtime=clock();
    parms.tinit=double(endtime-starttime)/CLOCKS_PER_SEC;

}
void UinitGlobals(runparams &parms,vector<map<string, string> > &T, vector<vector<string> > &G,
		vector<map<string, vector<double> > > &AR, map<string, map<string, vector<double> > > &H, vector<Player> &P) {

	clock_t starttime = clock();

	if (parms.debug) { printf("UinitGlobals starting...\n"); }

	printf("     MAIN| starting deallocation of global maps and vectors\n");

	T.clear();
	G.clear();
	AR.clear();
	H.clear();
	P.clear();

	printf("     MAIN| finished deallocation of global maps and vectors\n\n");

	if (parms.debug) { printf("UinitGlobals exiting...\n\n"); }

	clock_t endtime=clock();
    parms.tuinit=double(endtime-starttime)/CLOCKS_PER_SEC;

}
void RunSimulation(runparams &parms, vector<vector<string> > &G, vector<map<string, string> > &T,
		vector<map<string,vector<double> > > &AR, map<string,map<string, vector<double> > > &H, vector<Player> &P) {

    InitGlobals(parms,T,G,AR);
	ReadSimulation(G,T,AR,H,parms);
/*
	clock_t starttime = clock();

	if (parms.debug) { printf("RunSimulation starting...\n"); }

	printf("     MAIN| begin simulation\n\n");

#ifdef _OPENMP
	#pragma omp parallel for
		for (int j=0; j<(int)parms.Sim; j++) {

			double qr;

			time_t date=G.at(j).front().GameDate;
			printf("     SIM| simulating run     %6d\n",j);

			for (int i=0; i<(int)G.at(j).size(); i++) {


				if (date!=G.at(j).at(i).GameDate) {

					PerGame(T.at(j));

				}

				if (i > parms.ratingmin && i % parms.ratingfreq == 0) {

						SimpleRanking(T.at(j),AR.at(j),qr,parms);
						parms.trank+=qr;

				}

				G.at(j).at(i).Sim();
				date=G.at(j).at(i).GameDate;

			}

			double qf,qd,qp;
			FinalStanding(T.at(j),qf,parms.debug);
			Draft(T.at(j),qd,parms.debug);
			Playoffs(G.at(j),T.at(j),qp,parms.debug);

			parms.tfinal+=qf;
			parms.tdraft+=qd;
			parms.tplayoffs+=qp;

			printf("     SIM| end simulating run %6d\n\n",j);

		}

#else
	for (int j=0; j<(int)parms.Sim; j++) {

		double qr;

		time_t date=G.at(j).front().GameDate;
		printf("     SIM| simulating run     %6d\n",j);

		for (int i=0; i<(int)G.at(j).size(); i++) {

			if (date!=G.at(j).at(i).GameDate) {

				PerGame(T.at(j));

			}

			if (i > parms.ratingmin && i % parms.ratingfreq == 0) {

				SimpleRanking(T.at(j),AR.at(j),qr,parms);
				parms.trank+=qr;


			}

			G.at(j).at(i).Sim();
			date=G.at(j).at(i).GameDate;

			char buffer [50];
                	sprintf(buffer,"output.%05d.%04d.chk",j,i);
                	ofstream out(buffer);
                	G.at(j).at(0).write(&out);
                	out.flush();
		}

		double qf,qd,qp;
		FinalStanding(T.at(j),qf,parms.debug);
		Draft(T.at(j),qd,parms.debug);
		Playoffs(G.at(j),T.at(j),qp,parms.debug);

                char buffer [50];
		sprintf(buffer,"output%05d",j);
                ofstream out(buffer);
                G.at(j).at(0).write(&out);
                out.flush();
                
		parms.tfinal+=qf;
		parms.tdraft+=qd;
		parms.tplayoffs+=qp;

		printf("     SIM| end simulating run %6d\n\n",j);
	}
#endif

	if (parms.debug) { printf("RunSimulation exiting...\n\n"); }

	clock_t endtime=clock();
    parms.tsim=double(endtime-starttime)/CLOCKS_PER_SEC;

    PrintSimulation(parms,T,G,H);
    UinitGlobals(parms,T,G,AR,H,P);
*/
}
