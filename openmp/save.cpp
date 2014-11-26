/*
 * save.cpp
 *
 *  Created on: Apr 9, 2013
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
#include <sstream>

#include "run.h"


using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;
using std::ofstream;
using std::ios;


void SaveData(string inp, vector<string> fil, string &savedir, double &q, bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("SaveData starting...\n"); }

	int t; char buffer [80];
	time_t now = time(0);
	struct tm* tm = localtime(&now);

	char* cwd=getenv("PWD");
	savedir.append(cwd);
	savedir.append("/");

	string cmd="mkdir -p ";
	string dir="saved/run.";
	int year = 1900 + tm->tm_year;
	int month = 1 + tm->tm_mon;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int min = tm->tm_min;
	int sec = tm->tm_sec;

	t=sprintf(buffer,"%4d",year);
	dir.append(buffer);
	t=sprintf(buffer,"%02d",month);
	dir.append(buffer);
	t=sprintf(buffer,"%02d",day);
	dir.append(buffer);
	t=sprintf(buffer,"%02d",hour);
	dir.append(buffer);
	t=sprintf(buffer,"%02d",min);
	dir.append(buffer);
	t=sprintf(buffer,"%02d",sec);
	dir.append(buffer);

	cmd.append(dir);
	savedir.append(dir);

	int exit=system(cmd.c_str());
	if ( exit!=0 ) {

		fprintf(stderr, "error creating directory: %s\n\n", dir.c_str());

	//return;
	}


	/*
	 *
	 */

	cmd = "mv *conference.csv *league.csv *division.csv average_stands.csv "
			"rating.csv against.csv avgp4rating.csv draft.csv *margins.csv "
			"*hist.csv *offense.csv *defense.csv *differential.csv playoffs.csv "
			"schedule.csv";

	cmd.append(" ");
	cmd.append(dir);

	exit=system(cmd.c_str());
	if ( exit!=0 ) {

		fprintf(stderr, "error moving files: %s\n\n", dir.c_str());

	//return;
	}

	/*
	 *
	 */
	string filename = dir;
	filename.append("/info.inp");
	ofstream ofile(filename.c_str(), ios::trunc);

	string strlist="";
	for (int i=0; i<(int)fil.size(); i++) { strlist.append(fil.at(i)); }

	if (ofile.is_open()) {
		ofile << strlist;
		ofile.close();
	} else cout << "Unable to open file";

	cmd = "cp ";
	cmd.append(inp);
	cmd.append(" ");

	cmd.append(dir);

	exit=system(cmd.c_str());
	if ( exit!=0 ) {

		fprintf(stderr, "error copying input file: %s\n\n", dir.c_str());

	//return;
	}

	if (debug) { printf("SaveData exiting...\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}

void Save(runparams &parms) {

	SaveData(parms.filename,parms.flnm,parms.savedir,parms.tsave,parms.debug);
	printf("     MAIN| output saved to    %60s\n\n",parms.savedir.c_str());

}

