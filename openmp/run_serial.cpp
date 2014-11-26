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

void InitParams(runparams &parms) {

	parms.analysis=false;

	//player analysis
	parms.player_update=false;
	parms.player_update_year=2013;
	//parms.print_player_update;
	//string read_player_update;

	parms.player_analysis=false;
	//parms.print_player_analysis;
	//parms.read_player_analysis;
	//parms.player_analysis_stat;
	parms.begin_player_analysis=0;
	parms.end_player_analysis=20;

	parms.player_download=false;
	//print_player_download;

	//team analysis
	parms.team_download=false;
	parms.team_download_year=2013;
	//string print_team_download;

	//season analysis
	parms.season_update=false;
	parms.begin_season_update="2012-10-01";
	parms.finish_season_update="2013-08-01";
	//string print_season_update;
	//string read_season_update;

	parms.season_download=false;
	parms.season_download_year=2013;
	//print_season_download;

	parms.website="basketball-reference.com";

	/*
	 *
	 *
	 *
	 */

	parms.simulation=false;

	parms.debug=false;
	parms.save=false;

	parms.pl=4;

	parms.nsims=0; // number of simulations
	parms.Sim=0;

	//print info
	parms.p_histograms=false;
	parms.p_standings=false;
	parms.p_margins=false;
	parms.p_averages=false;
	parms.p_rankings=false;

	//
	parms.tprint=0.0;
	parms.tfinal=0.0;
	parms.tdraft=0.0;
	parms.tagainst=0.0;
	parms.tdaverage=0.0;
	parms.traverage=0.0;
	parms.thist=0.0;
	parms.trmargin=0.0;
	parms.tsmargin=0.0;
	parms.tupdate=0.0;
	parms.tschedule=0.0;
	parms.tsim=0.0;
	parms.tsave=0.0;
	parms.tread=0.0;
	parms.trank=0.0;
	parms.tplayers=0.0;

	//
	parms.tpstands=0.0;
	parms.tpranks=0.0;
	parms.tpagainst=0.0;
	parms.tpdraft=0.0;
	parms.tpplayoffs=0.0;
	parms.tplayoffs=0.0;
	parms.tphist=0.0;
	parms.tpmargin=0.0;
	parms.tpschedule=0.0;
	parms.tpsaverage=0.0;
	parms.tpraverage=0.0;

	parms.wallclock=0.0;
    parms.startwallclock=clock();

	parms.cpuclock=0.0;


	parms.ratingfreq=5;
	parms.ratingmin=300;
	parms.ratinginit=NULL;
	parms.ratingmemory=1000;

	parms.threads=1;

}
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
