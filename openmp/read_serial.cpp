/*
 * read.cpp
 *
 *  Created on: Nov 25, 2012
 *      Author: Junior
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
#include "team.h"
#include "run.h"
#include "players.h"
#include "read.h"

#ifdef _OPENMP
#include "omp.h"
#endif

using std::pair;
using std::make_pair;
using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::transform;

class Game;
class Team;

static const string arr10[] = {"DraftPos","Lottery","Seeds","pWins","pLoss","Wins","Loss",
							   "Division","Conference","League","ORanks","DRanks"};
vector<string> histvals (arr10,arr10 + sizeof(arr10) / sizeof(arr10[0]));

void ReadScheduleNew(runparams &parms, vector<map<string, string> > &TeamM, vector<vector<string> > &AllG,
		vector<map<string, vector<double> > > &AdjTeamRanks, map<string, map<string, vector<double> > > &Histogram, string fname) {

	clock_t starttime=clock();

	if (parms.debug) { printf("ReadSchedule starting...\n"); }

	time_t opening_day,closing_day,end_year;

	bool unique;

	double dif;
	int days,count;
	int id,num,year,month,day;
    char buffer[50];

	struct tm tmlol;
	memset(&tmlol, 0, sizeof(struct tm));

	string line;

	vector<string> tmp;
	vector<string> gm;
	vector<string> scr;

	std::ifstream file0(fname.c_str());
	num=0;
    count=0;

	// Find year for standings
	if (file0.is_open()) {
	    while (file0.good()) {

	    	getline(file0,line);
	    	transform(line.begin(),line.end(),line.begin(),::toupper);

	    	num+=1;
	    	if (line.find("DATE")!=string::npos) {

	    		if (num==1) {

	    		    StringExplode(line,",",&tmp);

	    		    strptime(tmp.at(tmp.size()-3).c_str(), "%Y-%m-%d", &tmlol);
	    		    end_year = mktime(&tmlol);

	    			struct tm* tm = localtime(&end_year);

					year = 1900 + tm->tm_year;
					month = 1 + tm->tm_mon;
					day = tm->tm_mday;

	    		    break;
	    		}
	    	}
	    }
	}
	file0.close();

	map<string, vector<string> > Standings;
	AssignStanding(Standings,year,parms);


	/*
	 *
	 */

	vector<double> temporary;
	map<string, vector<double> > init_hist;
	for (int k=0; k<(int)histvals.size(); k++) {

		init_hist.insert(pair<string, vector<double> >(histvals.at(k),temporary));

	}

	vector<double> rank(4,0.0);

	double hrtg,artg;

	num=0;
	ifstream file1(parms.filename.c_str());

	if (file1.is_open()) {
		while (file1.good()) {

			getline(file1,line);

			transform(line.begin(),line.end(),line.begin(),::toupper);

			if (line.find("DATE")!=string::npos) {
				continue;

			} else {

				StringExplode(line,",",&tmp);
				if (tmp.size() > 2) {

					string team = tmp.at(0);
					string conf;
					string divs;
					//conference

					typedef map<string, vector<string> >::iterator it_type;
					for (it_type iterator = Standings.begin(); iterator != Standings.end(); iterator++) {

						for (int i=0; i<(int)iterator->second.size(); i++) {

							if (iterator->second.at(i)==team) {

								if (iterator->first=="Eastern") {
									conf = "Eastern";
								} else if (iterator->first=="Western") {
									conf = "Western";
								} else {
									divs = iterator->first;
								}
							}
						}
					}

                    
					Histogram.insert(pair<string,map<string, vector<double> > >(team, init_hist));
                    
                    Team temp;
                    temp.Load(team,conf,divs);
                    sprintf(buffer,"buffer.%06d.%02d.chk\n",0,count);
                    ofstream out(buffer);
                    temp.write(&out);
                    out.flush();
                    count++;
                    
					//TeamM.at(0).insert(pair<string, Team>(team, Team()));
					//TeamM.at(0).find(team)->second.Load(team,conf,divs);

					//AdjTeamRanks.at(0).insert(pair<string, vector<double> >(team, rank));


				}
			}
		}
	}
    exit(0);

/*

	ReadRatingRestart(parms,TeamM,AdjTeamRanks);

#ifdef _OPENMP

	#pragma omp parallel for

		for (int i=1; i<(int)TeamM.size(); i++) {

			TeamM.at(i) = TeamM.front();
			AdjTeamRanks.at(i) = AdjTeamRanks.front();

		}
#else

	for (int i=1; i<(int)TeamM.size(); i++) {

		TeamM.at(i) = TeamM.front();
		AdjTeamRanks.at(i) = AdjTeamRanks.front();

	}
#endif

	file1.close();
	ifstream file2(parms.filename.c_str());


	if (file2.is_open()) {
	    while (file2.good()) {

	    	getline(file2,line);
	    	transform(line.begin(),line.end(),line.begin(),::toupper);

	    	num+=1;
	    	if (line.find("DATE")!=string::npos) {

	    		printf("     READING| initializing dates\n");

	    		if (num==1) {

	    		    StringExplode(line,",",&tmp);
	    		    strptime(tmp.at(1).c_str(), "%Y-%m-%d", &tmlol);
	    		    opening_day = mktime(&tmlol);

	    		    for (int i=1; i<(int)tmp.size(); i++ ) {

	    		    	if (tmp.at(i).find("DATE")!=string::npos) {

	    		    		strptime(tmp.at(i-1).c_str(), "%Y-%m-%d", &tmlol);
	    		    		closing_day = mktime(&tmlol);

	    		    		dif = difftime(closing_day,opening_day);
	    		    		days = i;

	    		    	}
	    		    }

	    		} else {

	    			break;

	    		}

	    	} else {

	    		StringExplode(line,",",&tmp);

	    		string team = tmp.at(0);

	    		printf("     READING| initializing games for team %48s\n",team.c_str());

	    		for (int i=1; i<days; i++) {

	    			string gmtm = tmp.at(i);

	    			if (gmtm.empty()) {


	    		    } else if (gmtm.find("@")!=string::npos) { // team is away

	    		    	StringExplode(gmtm," ",&gm);

						if (gm.at(0)=="W") {

							struct tm* tm = localtime(&opening_day);
							tm->tm_mday += i-1;
							time_t today = mktime(tm);

							string awayT = team;
							string homeT = gm.at(2);

							hrtg = -0.00001;
							artg =  0.00001;

							if (gm.size() > 3) {

								StringExplode(gm.at(3),"-",&scr);

								artg = atof(scr.at(0).c_str());
								hrtg = atof(scr.at(1).c_str());

								if (hrtg > artg) {

									fprintf(stderr, "error invalid input %s\n\n", gmtm.c_str());
									exit(1);

								}
							}

							DayInfo dnf;
							dnf.Date = today;
							dnf.Opponent = homeT;
							dnf.IsHome = false;

							for (int q=0; q<(int)TeamM.size(); q++) {

								dnf.Opp = &TeamM.at(q).find(homeT)->second;
								TeamM.at(q).find(team)->second.Schedule.push_back(dnf);

							}
//#endif

							unique=true;
							for (int g=0; g<(int)AllG.front().size(); g++) {


								if (AllG.front().at(g).HomeTeam==homeT && AllG.front().at(g).AwayTeam==awayT && AllG.front().at(g).GameDate==today) {
									unique=false;
									break;
								}

							}

							if (unique) {

								for (int q=0; q<(int)AllG.size(); q++) {

									//AllG.at(q).at(id)=Game(); cout << id%82 << endl;
									AllG.at(q).push_back(Game());
									AllG.at(q).back().Load(&TeamM.at(q).find(homeT)->second,&TeamM.at(q).find(awayT)->second,id,today);
									AllG.at(q).back().GameOver=true; AllG.at(q).back().HomeScore=hrtg; AllG.at(q).back().AwayScore=artg;

								}
								id += 1;

							}

						} else if (gm.at(0)=="L") {

							struct tm* tm = localtime(&opening_day);
							tm->tm_mday += i-1;
							time_t today = mktime(tm);

							string awayT = team;
							string homeT = gm.at(2);

							hrtg =  0.00001;
							artg = -0.00001;

							if (gm.size() > 3) {

								StringExplode(gm.at(3),"-",&scr);
								//hrtg = atof(scr.at(0).c_str());
								//artg = atof(scr.at(1).c_str());
								artg = atof(scr.at(0).c_str());
								hrtg = atof(scr.at(1).c_str());

								if (artg > hrtg) {

									fprintf(stderr, "error invalid input %s\n\n", gmtm.c_str());
									exit(1);

								}
							}

							DayInfo dnf;
							dnf.Date = today;
							dnf.Opponent = homeT;
							dnf.IsHome = false;
							//dnf.DidWin = false;
							//double rtngs[] = {artg,hrtg};
							//vector<double> rtng(rtngs,rtngs+sizeof(rtngs)/sizeof(double));
							//dnf.Ratings = rtng;


							for (int q=0; q<(int)TeamM.size(); q++) {

								dnf.Opp = &TeamM.at(q).find(homeT)->second;
								TeamM.at(q).find(team)->second.Schedule.push_back(dnf);

							}


							unique=true;
							for (int g=0; g<(int)AllG.front().size(); g++) {

								if (AllG.front().at(g).HomeTeam==homeT && AllG.front().at(g).AwayTeam==awayT && AllG.front().at(g).GameDate==today) {
									unique=false;
									break;
								}
							}

							if (unique) {

								for (int q=0; q<(int)AllG.size(); q++) {

									//AllG.at(q).at(id)=Game(); cout << id%82 << endl;
									AllG.at(q).push_back(Game());
									AllG.at(q).back().Load(&TeamM.at(q).find(homeT)->second,&TeamM.at(q).find(awayT)->second,id,today);
									AllG.at(q).back().GameOver=true; AllG.at(q).back().HomeScore=hrtg; AllG.at(q).back().AwayScore=artg;

								}
								id += 1;

							}



						} else {

							struct tm* tm = localtime(&opening_day);
							tm->tm_mday += i-1;
							time_t today = mktime(tm);

							string awayT = team;
							string homeT = gm.at(1);

							DayInfo dnf;
							dnf.Date = today;
							dnf.Opponent = homeT;
							dnf.IsHome = false;


							for (int q=0; q<(int)TeamM.size(); q++) {

								dnf.Opp = &TeamM.at(q).find(homeT)->second;
								TeamM.at(q).find(team)->second.Schedule.push_back(dnf);

							}


							unique=true;
							for (int g=0; g<(int)AllG.front().size(); g++) {

								if (AllG.front().at(g).HomeTeam==homeT && AllG.front().at(g).AwayTeam==awayT && AllG.front().at(g).GameDate==today) {
									unique=false;
									break;
								}

							}

							if (unique) {

								for (int q=0; q<(int)AllG.size(); q++) {

									//AllG.at(q).at(id)=Game(); cout << id%82 << endl;
									AllG.at(q).push_back(Game());
									AllG.at(q).back().Load(&TeamM.at(q).find(homeT)->second,&TeamM.at(q).find(awayT)->second,id,today);

								}
								id += 1;

							}
						}

	    			} else { // team is home

	    				StringExplode(gmtm," ",&gm);

	    				if (gm.at(0)=="W") {

	    					struct tm* tm = localtime(&opening_day);
							tm->tm_mday += i-1;
							time_t today = mktime(tm);

	    					string homeT = team;
							string awayT = gm.at(1);

							hrtg =  0.00001;
							artg = -0.00001;

							if (gm.size() > 2) {

								StringExplode(gm.at(2),"-",&scr);
								hrtg = atof(scr.at(0).c_str());
								artg = atof(scr.at(1).c_str());

								if (hrtg <= artg) {

									fprintf(stderr, "error invalid input %s\n\n", gmtm.c_str());
									exit(1);

								}
							}

							DayInfo dnf;
							dnf.Date = today;
							dnf.Opponent = awayT;
							dnf.IsHome = true;
							//dnf.DidWin = true;
							//double rtngs[] = {hrtg,artg};
							//vector<double> rtng(rtngs,rtngs+sizeof(rtngs)/sizeof(double));
							//dnf.Ratings = rtng;

							for (int q=0; q<(int)TeamM.size(); q++) {

								dnf.Opp = &TeamM.at(q).find(awayT)->second;
								TeamM.at(q).find(team)->second.Schedule.push_back(dnf);

							}


							unique=true;
							for (int g=0; g<(int)AllG.front().size(); g++) {

								if (AllG.front().at(g).HomeTeam==homeT && AllG.front().at(g).AwayTeam==awayT && AllG.front().at(g).GameDate==today) {
									unique=false;
									break;
								}

							}

							if (unique) {

								for (int q=0; q<(int)AllG.size(); q++) {

									//AllG.at(q).at(id)=Game(); cout << id%82 << endl;
									AllG.at(q).push_back(Game());
									AllG.at(q).back().Load(&TeamM.at(q).find(homeT)->second,&TeamM.at(q).find(awayT)->second,id,today);
									AllG.at(q).back().GameOver=true; AllG.at(q).back().HomeScore=hrtg; AllG.at(q).back().AwayScore=artg;

								}
								id += 1;

							}

	    				} else if (gm.at(0)=="L") {

	    					struct tm* tm = localtime(&opening_day);
	    					tm->tm_mday += i-1;
	    					time_t today = mktime(tm);

	    					string homeT = team;
	    					string awayT = gm.at(1);

	    					hrtg = -0.00001;
	    					artg =  0.00001;
	    					if (gm.size() > 2) {

								StringExplode(gm.at(2),"-",&scr);
								hrtg = atof(scr.at(0).c_str());
								artg = atof(scr.at(1).c_str());

								if (artg <= hrtg) {

									fprintf(stderr, "error invalid input %s\n\n", gmtm.c_str());
									exit(1);

								}

	    					}

							DayInfo dnf;
							dnf.Date = today;
							dnf.Opponent = awayT;
							dnf.IsHome = true;
							//dnf.DidWin = false;
							//double rtngs[] = {hrtg,artg};
							//vector<double> rtng(rtngs,rtngs+sizeof(rtngs)/sizeof(double));
							//dnf.Ratings = rtng;

							for (int q=0; q<(int)TeamM.size(); q++) {

								dnf.Opp = &TeamM.at(q).find(awayT)->second;
								TeamM.at(q).find(team)->second.Schedule.push_back(dnf);

							}

							unique=true;
							for (int g=0; g<(int)AllG.front().size(); g++) {

								if (AllG.front().at(g).HomeTeam==homeT && AllG.front().at(g).AwayTeam==awayT && AllG.front().at(g).GameDate==today) {
									unique=false;
									break;
								}

							}

							if (unique) {

								for (int q=0; q<(int)AllG.size(); q++) {

									//AllG.at(q).at(id)=Game(); cout << id%82 << endl;
									AllG.at(q).push_back(Game());
									AllG.at(q).back().Load(&TeamM.at(q).find(homeT)->second,&TeamM.at(q).find(awayT)->second,id,today);
									AllG.at(q).back().GameOver=true; AllG.at(q).back().HomeScore=hrtg; AllG.at(q).back().AwayScore=artg;

								}
								id += 1;

							}

	    				} else {

	    					struct tm* tm = localtime(&opening_day);
							tm->tm_mday += i-1;
							time_t today = mktime(tm);

							string homeT = team;
							string awayT = gm.at(0);

							DayInfo dnf;
							dnf.Date = today;
							dnf.Opponent = awayT;
							dnf.IsHome = true;


							for (int q=0; q<(int)TeamM.size(); q++) {

								dnf.Opp = &TeamM.at(q).find(awayT)->second;
								TeamM.at(q).find(team)->second.Schedule.push_back(dnf);

							}

							unique=true;
							for (int g=0; g<(int)AllG.front().size(); g++) {


								if (AllG.front().at(g).HomeTeam==homeT && AllG.front().at(g).AwayTeam==awayT && AllG.front().at(g).GameDate==today) {
									unique=false;
									break;
								}

							}

							if (unique) {

								for (int q=0; q<(int)AllG.size(); q++) {

									//AllG.at(q).at(id)=Game(); cout << id%82 << endl;
									AllG.at(q).push_back(Game());
									AllG.at(q).back().Load(&TeamM.at(q).find(homeT)->second,&TeamM.at(q).find(awayT)->second,id,today);

								}
								id += 1;
							}


	    				}
	    			}
	    		}
	    	}
	    }
	}

	struct tm* tm = localtime(&opening_day);

	vector<vector<Game> > UnsortedGames=AllG;

#ifdef _OPENMP
	#pragma omp parallel for

		for (int i=0; i<(int)AllG.size(); i++) {

			AllG.at(i).clear();
		}
#else
	for (int i=0; i<(int)AllG.size(); i++) {

		AllG.at(i).clear();
	}
#endif

	printf("\n");
	printf("     READING| total number of days %55d\n\n",days-1);
	int gameidx=0;
	for (int i=0; i<days-1; i++) {

		time_t today = mktime(tm);

		for (int j=(int)UnsortedGames.front().size()-1; j>=0; j--) {

			if (UnsortedGames.front().at(j).GameDate==today) {
#ifdef _OPENMP
				#pragma omp parallel for
					for (int q=0; q<(int)AllG.size(); q++) {

						//AllG.at(q).at(gameidx)=UnsortedGames.at(q).at(j);
						AllG.at(q).push_back(UnsortedGames.at(q).at(j));
						//AllG.at(q).insert(AllG.at(q).end(),UnsortedGames.at(q).at(j));
						UnsortedGames.at(q).erase(UnsortedGames.at(q).begin()+j);

					}
#else

					for (int q=0; q<(int)AllG.size(); q++) {

						AllG.at(q).push_back(UnsortedGames.at(q).at(j));
						UnsortedGames.at(q).erase(UnsortedGames.at(q).begin()+j);

					}
#endif
				gameidx++;
			}
		}
		printf("     READING| day %3d \n",i);

		tm->tm_mday++;

	}
    printf("\n");
*/

	if (parms.debug) { printf("ReadSchedule exiting...\n\n"); }

	clock_t endtime=clock();
    parms.tschedule=double(endtime-starttime)/CLOCKS_PER_SEC;

	return;
}

void ReadScheduleClearNew(runparams &parms, vector<map<string, Team> > &TeamM, vector<vector<Game> > &AllG,
		vector<map<string, vector<double> > > &AdjTeamRanks, map<string, map<string, vector<double> > > &Histogram, string fname) {

	clock_t starttime=clock();

	if (parms.debug) { printf("ReadScheduleClear starting...\n"); }

	time_t opening_day,closing_day;

	bool unique;

	double dif;
	int days;
	int id;

	int num;
    int year;

	struct tm tmlol;
	memset(&tmlol, 0, sizeof(struct tm));

	vector<string> tmp;
	vector<string> gm;
	vector<string> scr;

	string line;

	ifstream file0(fname.c_str());
	num=0;

	// Find year for standings
	if (file0.is_open()) {
	    while (file0.good()) {

	    	getline(file0,line);
	    	transform(line.begin(),line.end(),line.begin(),::toupper);

	    	num+=1;
	    	if (line.find("DATE")!=string::npos) {

	    		if (num==1) {

	    		    StringExplode(line,",",&tmp);

	    		    strptime(tmp.at(tmp.size()-3).c_str(), "%Y-%m-%d", &tmlol);
	    		    time_t end_year = mktime(&tmlol);

	    			struct tm* tm = localtime(&end_year);

					year = 1900 + tm->tm_year;

	    		    break;
	    		}
	    	}
	    }
	}
	file0.close();

	map<string, vector<string> > Standings;
	AssignStanding(Standings,year,parms);

	vector<double> temporary;
	map<string, vector<double> > init_hist;
	for (int k=0; k<(int)histvals.size(); k++) {

		init_hist.insert(pair<string, vector<double> >(histvals.at(k),temporary));

	}

	vector<double> rank(4,0.0);

	num=0;
	ifstream file1(fname.c_str());

	if (file1.is_open()) {
		while (file1.good()) {

			getline(file1,line);

			transform(line.begin(),line.end(),line.begin(),::toupper);

			if (line.find("DATE")!=string::npos) {
				continue;

			} else {

				StringExplode(line,",",&tmp);
				if (tmp.size() > 2) {

					string team = tmp.at(0);
					string conf;
					string divs;
					//conference

					typedef map<string, vector<string> >::iterator it_type;
					for (it_type iterator = Standings.begin(); iterator != Standings.end(); iterator++) {

						for (int i=0; i<(int)iterator->second.size(); i++) {

							if (iterator->second.at(i)==team) {

								if (iterator->first=="Eastern") {
									conf = "Eastern";
								} else if (iterator->first=="Western") {
									conf = "Western";
								} else {
									divs = iterator->first;
								}
							}
						}
					}

					Histogram.insert(pair<string, map<string, vector<double> > >(team, init_hist));
					TeamM.at(0).insert(pair<string, Team>(team, Team()));
					TeamM.at(0).find(team)->second.Load(team,conf,divs);

				}
			}
		}
	}

	ReadRatingRestart(parms,TeamM,AdjTeamRanks);

#ifdef _OPENMP

	#pragma omp parallel for

		for (int i=1; i<(int)TeamM.size(); i++) {

			TeamM.at(i) = TeamM.front();
			AdjTeamRanks.at(i) = AdjTeamRanks.front();

		}

#else

	for (int i=1; i<(int)TeamM.size(); i++) {

		TeamM.at(i) = TeamM.front();
		AdjTeamRanks.at(i) = AdjTeamRanks.front();

	}

#endif

	file1.close();
	ifstream file2(fname.c_str());

	if (file2.is_open()) {
	    while (file2.good()) {

	    	getline(file2,line);
	    	transform(line.begin(),line.end(),line.begin(),::toupper);

	    	num+=1;
	    	if (line.find("DATE")!=string::npos) {

		    	printf("     READING| initializing date\n");

	    		if (num==1) {

	    		    StringExplode(line,",",&tmp);

	    		    strptime(tmp.at(1).c_str(), "%Y-%m-%d", &tmlol);
	    		    opening_day = mktime(&tmlol);

	    		    for (int i=1; i<(int)tmp.size(); i++ ) {

	    		    	if (tmp.at(i).find("DATE")!=string::npos) {


	    		    		strptime(tmp.at(i-1).c_str(), "%Y-%m-%d", &tmlol);
	    		    		closing_day = mktime(&tmlol);

	    		    		dif = difftime(closing_day,opening_day);
	    		    		days = i;

	    		    	}
	    		    }
	    		} else {

	    			break;

	    		}

	    	} else {

	    		StringExplode(line,",",&tmp);

	    		string team = tmp.at(0);

		    	printf("     READING| initializing games for team %48s\n",team.c_str());

	    		for (int i=1; i<days; i++) {

	    			string gmtm = tmp.at(i);

	    			if (gmtm.empty()) {


	    		    } else if (gmtm.find("@")!=string::npos) { // team is away

	    		    	StringExplode(gmtm," ",&gm);

						struct tm* tm = localtime(&opening_day);
						tm->tm_mday += i-1;
						time_t today = mktime(tm);

						//struct tm* oz = localtime(&today);

						string awayT = team;
						string homeT;

						if (gm.size()==2){

							homeT = gm.at(1);

						} else homeT = gm.at(2);

						DayInfo dnf;
						dnf.Date = today;
						dnf.Opponent = homeT;
						dnf.IsHome = false;

						for (int q=0; q<(int)TeamM.size(); q++) {

							dnf.Opp = &TeamM.at(q).find(homeT)->second;
							TeamM.at(q).find(team)->second.Schedule.push_back(dnf);

						}

						unique=true;
						for (int g=0; g<(int)AllG.front().size(); g++) {

							if (AllG.front().at(g).HomeTeam==homeT && AllG.front().at(g).AwayTeam==awayT && AllG.front().at(g).GameDate==today) {
								unique=false;
								break;
							}
						}

						if (unique) {

							for (int q=0; q<(int)AllG.size(); q++) {

								AllG.at(q).push_back(Game());
								AllG.at(q).back().Load(&TeamM.at(q).find(homeT)->second,&TeamM.at(q).find(awayT)->second,id,today);

							}

						}
						id += 1;

	    			} else { // team is home

	    				StringExplode(gmtm," ",&gm);

						struct tm* tm = localtime(&opening_day);
						tm->tm_mday += i-1;
						time_t today = mktime(tm);

						string homeT = team;
						string awayT;

						if (gm.size()==1){

							awayT = gm.at(0);

						} else awayT = gm.at(1);

						DayInfo dnf;
						dnf.Date = today;
						dnf.Opponent = awayT;
						dnf.IsHome = true;
						/*
#ifdef _OPENMP
						#pragma omp parallel for

							for (int q=0; q<(int)TeamM.size(); q++) {

								dnf.Opp = &TeamM.at(q).find(awayT)->second;
								TeamM.at(q).find(team)->second.Schedule.push_back(dnf);

							}
#else
*/
						for (int q=0; q<(int)TeamM.size(); q++) {

							dnf.Opp = &TeamM.at(q).find(awayT)->second;
							TeamM.at(q).find(team)->second.Schedule.push_back(dnf);

						}
//#endif
						unique=true;
						for (int g=0; g<(int)AllG.front().size(); g++) {

							if (AllG.front().at(g).HomeTeam==homeT && AllG.front().at(g).AwayTeam==awayT && AllG.front().at(g).GameDate==today) {
								unique=false;
								break;
							}

						}

						if (unique) {
/*#ifdef _OPENMP
							#pragma omp parallel for

								for (int q=0; q<(int)AllG.size(); q++) {

									AllG.at(q).push_back(Game());
									AllG.at(q).back().Load(&TeamM.at(q).find(homeT)->second,&TeamM.at(q).find(awayT)->second,id,today);

								}
#else*/
							for (int q=0; q<(int)AllG.size(); q++) {

								AllG.at(q).push_back(Game());
								AllG.at(q).back().Load(&TeamM.at(q).find(homeT)->second,&TeamM.at(q).find(awayT)->second,id,today);
								//cout << AllG.at(q).back().GameIDstring << endl;
							}
//#endif
						}
						id += 1;
	    			}
	    		}
	    	}
	    }
	}

	struct tm* tm = localtime(&opening_day);

	vector<vector<Game> > UnsortedGames=AllG;

#ifdef _OPENMP
	#pragma omp parallel for

		for (int i=0; i<(int)AllG.size(); i++) {

			AllG.at(i).clear();
		}
#else
	for (int i=0; i<(int)AllG.size(); i++) {

		AllG.at(i).clear();
	}
#endif

	printf("\n");
	printf("     READING| total number of days %55d\n\n",days-1);
	for (int i=0; i<days-1; i++) {

		time_t today = mktime(tm);

		for (int j=(int)UnsortedGames.front().size()-1; j>=0; j--) {

			if (UnsortedGames.front().at(j).GameDate==today) {
#ifdef _OPENMP
				#pragma omp parallel for

					for (int q=0; q<(int)AllG.size(); q++) {

						//AllG.at(q).push_back(UnsortedGames.at(q).at(j));
						AllG.at(q).insert(AllG.at(q).end(),UnsortedGames.at(q).at(j));
						UnsortedGames.at(q).erase(UnsortedGames.at(q).begin()+j);

					}
#else
					for (int q=0; q<(int)AllG.size(); q++) {

						AllG.at(q).push_back(UnsortedGames.at(q).at(j));
						UnsortedGames.at(q).erase(UnsortedGames.at(q).begin()+j);

					}
#endif
			}
		}
		printf("     READING| day %3d \n",i);

		tm->tm_mday++;

	}
	printf("\n");


	if (parms.debug) { printf("ReadScheduleClear exiting...\n\n"); }

	clock_t endtime=clock();
    parms.tschedule=double(endtime-starttime)/CLOCKS_PER_SEC;

	return;
}
void ReadRatingRestart(runparams &parms, vector<map<string, Team> > &TeamM, vector<map<string, vector<double> > > &AR) {

	if (parms.debug) { printf("ReadRatingRestart starting...\n"); }

	ifstream file1;

	vector<string> tmp,tmp0;
	string line; vector<double> rank(4,0.0);

	if (!parms.ratingrestart.empty()) {

		ifstream file1(parms.ratingrestart.c_str());

		if (file1.is_open()) {
			while (file1.good()) {

				getline(file1,line);
				transform(line.begin(),line.end(),line.begin(),::toupper);

				StringExplode(line,"\n",&tmp0);
				StringExplode(tmp0.at(0),",",&tmp);

				if (tmp.size() > 3) {

					string team = tmp.at(0);
					string off = tmp.at(1);
					string def = tmp.at(2);

					AR.front().insert(pair<string, vector<double> >(team, rank));

					TeamM.front().find(team)->second.OffRtg=atof(off.c_str());
					TeamM.front().find(team)->second.DefRtg=atof(def.c_str());

					TeamM.front().find(team)->second.startOffRtg = TeamM.front().find(team)->second.OffRtg;
					TeamM.front().find(team)->second.startDefRtg = TeamM.front().find(team)->second.DefRtg;

					//cout <<  team << " " << TeamM.front().find(team)->second.DefRtg << endl;

				} //else { fprintf(stderr, "error: wrong number of input parameters\n\n"); }
			}
		}

	} else if (parms.ratinginit > 0) {

		file1.clear();

		typedef map<string, Team>::iterator it_type;
		for (it_type iterator = TeamM.front().begin(); iterator != TeamM.front().end(); iterator++) {

			AR.front().insert(pair<string, vector<double> >(iterator->second.TeamName, rank));

			iterator->second.OffRtg=parms.ratinginit;
			iterator->second.startOffRtg=parms.ratinginit;

			iterator->second.DefRtg=parms.ratinginit;
			iterator->second.startDefRtg=parms.ratinginit;

			//cout << iterator->second.TeamName << " " << iterator->second.DefRtg << endl;

		}

	} else fprintf(stderr, "error: no ratings specified\n\n");

	if (parms.debug) { printf("ReadRatingRestart exiting...\n\n"); }
}
void ReadPlayerRestart(runparams &parms, vector<Player> &P, string fname) {

	if (parms.debug) { printf("ReadPlayerRestart starting...\n"); }

	//int games,age,active;
	int mp,ortg,drtg;
	double ts,efg,orb,drb,trb;
	double ast,stl,blk,tov,usg;
	double ows,dws,ws,ws48,per;

	struct tm tmlol;
	memset(&tmlol, 0, sizeof(struct tm));

	time_t birthday;

	char name [80];

	FILE * pFile;
	pFile = fopen (fname.c_str(),"r");

	char line[1024]; vector<string> inp,tmp;

	while (fgets(line, sizeof(line), pFile)) { inp.push_back(line);	}

	for (int i=0; i<(int)inp.size(); i++) {

		StringExplode(inp.at(i),",",&tmp);

		if (tmp.at(0)=="LASTNAME") { continue; }

		else {

			Player p;

			//fprintf(oFile,"LASTNAME,FIRSTNAME,PID,FIRSTYR,LASTYR,POSITION,HANDED,HEIGHT,WEIGHT,BIRTHDATE,SCHOOL,");
			//fprintf(oFile,"ACTIVE,TEAM,EFG,TS,DRB,ORB,TRB,AST,STL,BLK,TOV,USG,ORTG,DRTG,OWS,DWS,WS48,WS,\n");

			sprintf(name,"%s %s",tmp.at(1).c_str(),tmp.at(0).c_str());

			p.FullName=name; p.LastName=tmp.at(0); p.FirstName=tmp.at(1);

		    strptime(tmp.at(9).c_str(), "%Y-%m-%d", &tmlol);
		    birthday = mktime(&tmlol);

		    p.birthday=birthday;

		    p.bballref_id=tmp.at(2);

		    p.FirstYear=tmp.at(3);
		    p.LastYear=tmp.at(4);

			p.height=atoi(tmp.at(7).c_str()); p.height=atoi(tmp.at(8).c_str()); p.hand=tmp.at(6); p.position=tmp.at(5);

			p.College=tmp.at(10);

			p.active=false;
			if (tmp.at(11)=="1") p.active=true;

			p.CurrentTeam=tmp.at(12);

			mp=atoi(tmp.at(13).c_str());
			efg=atof(tmp.at(14).c_str());
			ts=atof(tmp.at(15).c_str());
			drb=atof(tmp.at(16).c_str());
			orb=atof(tmp.at(17).c_str());
			trb=atof(tmp.at(18).c_str());
			ast=atof(tmp.at(19).c_str());
			stl=atof(tmp.at(20).c_str());
			blk=atof(tmp.at(21).c_str());
			tov=atof(tmp.at(22).c_str());
			usg=atof(tmp.at(23).c_str());
			ortg=atof(tmp.at(24).c_str());
			drtg=atof(tmp.at(25).c_str());
			ows=atof(tmp.at(26).c_str());
			dws=atof(tmp.at(27).c_str());
			ws48=atof(tmp.at(28).c_str());
			ws=atof(tmp.at(29).c_str());
			per=atof(tmp.at(30).c_str());

			//stats
			p.eFG=efg; p.TS=ts; p.Minutes=mp;

			p.DRB=drb; p.ORB=orb; p.TRB=trb;

			p.AST=ast; p.STL=stl; p.BLK=blk; p.TOV=tov;

			p.Usage=usg;

			p.ORtg=ortg; p.DRtg=drtg;

			p.OWS=ows; p.DWS=dws;
			p.WS48=ws48; p.WS=ws;

			p.PER=per;

			printf("     READING| loading player        %55s\n",p.FullName.c_str());

			P.push_back(p);

		}
	}
	printf("\n");

	if (parms.debug) { printf("ReadPlayerRestart exiting...\n\n"); }
}
void ReadPlayerRestartNew(runparams &parms, vector<Player> &P, string fname) {

	if (parms.debug) { printf("ReadPlayerRestart starting...\n"); }

	struct tm tmlol;
	memset(&tmlol, 0, sizeof(struct tm));

	char name [80];

	FILE * pFile;
	pFile = fopen (fname.c_str(),"r");

	char line[1048576]; vector<string> inp,tmp,val,split;

	string stat, value;
	int year;

	while (fgets(line, sizeof(line), pFile)) { inp.push_back(line);	}

	for (int i=0; i<(int)inp.size(); i++) {

		StringExplode(inp.at(i),",",&tmp);

		Player p;

		for (int j=0; j<(int)tmp.size(); j++) {

			if (tmp.at(j).find("=")!=string::npos) {

				year=1900;
				StringExplode(tmp.at(j),"=",&val);
				StringExplode(val.at(0),".",&split);

				stat=split.at(0);
				if (split.size()>1) { year=atof(split.at(1).c_str()); }

				if (val.size()>1 ) { value=val.at(1); }

				if (stat=="lastname") { p.LastName=value; continue; }
				if (stat=="firstname") { p.FirstName=value; continue; }

				if (stat=="bballref") { p.bballref_id=value; continue; }

				if (stat=="hand") { p.hand=value; continue; }
				if (stat=="height") { p.height=atoi(value.c_str()); continue; }
				if (stat=="weight") { p.weight=atoi(value.c_str()); continue; }
/*
				if (stat=="age") { p.age.insert(pair<string,int>(year,atoi(value.c_str()))); }

				if (stat=="team") { p.team.insert(pair<string,string>(year,value)); }

				if (stat=="pos") { p.pos.insert(pair<string,string>(year,value)); }

				if (stat=="games") { p.games.insert(pair<string,int>(year,atoi(value.c_str()))); }
				if (stat=="games_started") { p.games_started.insert(pair<string,int>(year,atoi(value.c_str()))); }

				if (stat=="points") { p.points.insert(pair<string,double>(year,atof(value.c_str()))); }


				if (stat=="fg") { p.fg.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="fga") { p.fga.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="fgp") { p.fgp.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="threeg") { p.threeg.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="threega") { p.threega.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="threegp") { p.threegp.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="twog") { p.twog.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="twoga") { p.twoga.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="twogp") { p.twogp.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="ft") { p.ft.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="fta") { p.fta.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="ftp") { p.ftp.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="threegr") { p.threegr.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="ftr") { p.ftr.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="efg") { p.efg.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="ts") { p.ts.insert(pair<string,double>(year,atof(value.c_str()))); }


				if (stat=="orb_adv") { p.orb_adv.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="drb_adv") { p.drb_adv.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="trb_adv") { p.trb_adv.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="orb_tot") { p.orb_tot.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="drb_tot") { p.drb_tot.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="trb_tot") { p.trb_tot.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="ast_adv") { p.ast_adv.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="stl_adv") { p.stl_adv.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="blk_adv") { p.blk_adv.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="tov_adv") { p.tov_adv.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="ast_tot") { p.ast_tot.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="stl_tot") { p.stl_tot.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="blk_tot") { p.blk_tot.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="tov_tot") { p.tov_tot.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="foul_tot") { p.foul_tot.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="usg") { p.usg.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="ortg") {	p.ortg.insert(pair<string,int>(year,atoi(value.c_str()))); }
				if (stat=="drtg") { p.drtg.insert(pair<string,int>(year,atoi(value.c_str()))); }

				if (stat=="ows") { p.ows.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="dws") { p.dws.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="ws") { p.ws.insert(pair<string,double>(year,atof(value.c_str()))); }
				if (stat=="ws48") { p.ws48.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="per") { p.per.insert(pair<string,double>(year,atof(value.c_str()))); }

				if (stat=="mins") { p.mins.insert(pair<string,int>(year,atoi(value.c_str()))); }
*/
				if (stat=="pos" || stat=="team") {
					p.infoMap[stat].insert(make_pair(year,value));
				} else {
					p.statMap[stat].insert(make_pair(year,atof(value.c_str())));
				}
			}

		}

		sprintf(name,"%s %s",p.FirstName.c_str(),p.LastName.c_str());
		printf("     READING| loading player       %55s\n",name);
		P.push_back(p);

	}


	printf("\n");

	if (parms.debug) { printf("ReadPlayerRestart exiting...\n\n"); }
}
void ReadInput(runparams &parms) {

	clock_t starttime=clock();

	string temp;
	vector<string> tmp;
	vector<string> tmp0;

	char line[1024];

	while (fgets(line, sizeof(line), stdin)) {
		parms.flnm.push_back(line);
	}

	for (int i=0; i<(int)parms.flnm.size(); i++) {

		if (parms.flnm.at(i).find("&filename")!=string::npos) {

			StringExplode(parms.flnm.at(i+1),"\n",&tmp);
			parms.filename=tmp.at(0);
			continue;

		} else if (parms.flnm.at(i).find("&analysis")!=string::npos) {

			for (int x=i; x<100+i; x++) {

				StringExplode(parms.flnm.at(x+1),"\n",&tmp);
				vector<string> tmp2;
				StringExplode(tmp.at(0)," ",&tmp2);

				if (tmp.at(0).empty()) continue;

				if (tmp2.at(0)== "/") break;

				if (tmp2.at(0)=="team") parms.analysis=true;

				else if (tmp2.at(0)=="player") parms.analysis=true;

				else if (tmp2.at(0)=="season") parms.analysis=true;

				else if (tmp2.at(0)=="website") { parms.website=tmp2.at(1); }

				//
				//player analysis
				if (tmp2.at(0)=="player") {

					if (tmp2.size()>=4) {

						if (tmp2.at(1)=="analysis") {

							parms.player_analysis=true;

							if (tmp2.at(2)=="print") parms.print_player_analysis=tmp2.at(3);

							else if (tmp2.at(2)=="read") parms.read_player_analysis=tmp2.at(3);

							else if (tmp2.at(2)=="stat") parms.player_analysis_stat=tmp2.at(3);

							else if (tmp2.at(2)=="begin") parms.begin_player_analysis=atoi(tmp2.at(3).c_str());

							else if (tmp2.at(2)=="end") parms.end_player_analysis=atoi(tmp2.at(3).c_str());

						} else if (tmp2.at(1)=="update") {

							parms.player_update=true;

							if (tmp2.at(2)=="print") parms.print_player_update=tmp2.at(3);

							else if (tmp2.at(2)=="read") parms.read_player_update=tmp2.at(3);

							else if (tmp2.at(2)=="year") parms.player_update_year=atoi(tmp2.at(3).c_str());

						} else if (tmp2.at(1)=="download") {

							parms.player_download=true;

							if (tmp2.at(2)=="print") parms.print_player_download=tmp2.at(3);

						}

					} else if (tmp2.size()>=2) {

						if (tmp2.at(1)=="update") { parms.player_update=true; }

						else if (tmp2.at(1)=="download") { parms.player_download=true; }

					} else { fprintf(stderr, "error: incorrect number of player analysis parameters\n\n");	}


				//team analysis
				} else if (tmp2.at(0)=="team") {

					if (tmp2.size()>=4) {

						if (tmp2.at(1)=="download") {

							parms.team_download=true;

							if (tmp2.at(2)=="print") parms.print_team_download=tmp2.at(3);

							else if (tmp2.at(2)=="year") parms.team_download_year=atoi(tmp2.at(3).c_str());

							else if (tmp2.at(2)=="read") parms.read_team_download=tmp2.at(3);

						} else if (tmp2.at(1)=="update") {

							parms.team_update=true;

							if (tmp2.at(2)=="print") parms.print_team_update=tmp2.at(3);

							else if (tmp2.at(2)=="year") parms.team_update_year=atoi(tmp2.at(3).c_str());

							else if (tmp2.at(2)=="type") parms.team_update_type=tmp2.at(3);

							else if (tmp2.at(2)=="read") {

								if (tmp2.at(3)=="team") parms.read_team_update_team=tmp2.at(4);

								else if (tmp2.at(3)=="player") parms.read_team_update_player=tmp2.at(4);
							}
						}

					} else if (tmp2.size()>=2) {

						if (tmp2.at(1)=="download") { parms.team_download=true; }

						else if (tmp2.at(1)=="update") { parms.team_update=true; }

					} else { fprintf(stderr, "error: incorrect number of team analysis parameters\n\n"); }

				//season analysis
				} else if (tmp2.at(0)=="season") {

					if (tmp2.size()>=4) {

						if (tmp2.at(1)=="update") {

							parms.season_update=true;

							if (tmp2.at(2)=="print") parms.print_season_update=tmp2.at(3);

							else if (tmp2.at(2)=="begin") parms.begin_season_update=tmp2.at(3);

							else if (tmp2.at(2)=="end") parms.finish_season_update=tmp2.at(3);

							else if (tmp2.at(2)=="read") parms.read_season_update=tmp2.at(3);

						} else if (tmp2.at(1)=="download") {

							parms.season_download=true;

							if (tmp2.at(2)=="print") parms.print_season_download=tmp2.at(3);

							else if (tmp2.at(2)=="year") parms.season_download_year=atoi(tmp2.at(3).c_str());

						}

					} else if (tmp2.size()==2) {

						if (tmp2.at(1)=="update") { parms.season_update=true; }

						else if (tmp2.at(1)=="download") { parms.season_download=true; }

					} else { fprintf(stderr, "error: incorrect number of season analysis parameters\n\n"); }
				}
			}
			continue;

		} else if (parms.flnm.at(i).find("&simulation")!=string::npos) {

			for (int x=i; x<100+i; x++) {

				StringExplode(parms.flnm.at(x+1),"\n",&tmp);
				vector<string> tmp2;
				StringExplode(tmp.at(0)," ",&tmp2);

				if (tmp.at(0).empty()) continue;

				if (tmp2.at(0)== "/") break;

				if (tmp2.at(0)=="run") parms.simulation=true;

				//
				if (tmp2.at(0)=="run") {

					if (tmp2.size()>=3) {

						if (tmp2.at(1)=="runtype") parms.runtype=tmp2.at(2);

						else if (tmp2.at(1)=="read") parms.filename=tmp2.at(2);

						else if (tmp2.at(1)=="ratingrestart") parms.ratingrestart=tmp2.at(2);

						else if (tmp2.at(1)=="ratingmin") parms.ratingmin=atoi(tmp2.at(2).c_str());

						else if (tmp2.at(1)=="ratingmemory") parms.ratingmemory=atoi(tmp2.at(2).c_str());

						else if (tmp2.at(1)=="ratinginit") parms.ratinginit=atoi(tmp2.at(2).c_str());

						else if (tmp2.at(1)=="ratingfreq") parms.ratingfreq=atoi(tmp2.at(2).c_str());

						else if (tmp2.at(1)=="nsims") parms.nsims=atoi(tmp2.at(2).c_str());

					} else { fprintf(stderr, "error: incorrect number of player analysis parameters\n\n");	}

				}
			}
/*
		} else if (parms.flnm.at(i).find("&nsims")!=string::npos) {

			StringExplode(parms.flnm.at(i+1),"\n",&tmp);
			parms.nsims=atoi(tmp.at(0).c_str());
			continue;
*/
		} else if (parms.flnm.at(i).find("&parallel")!=string::npos) {

			StringExplode(parms.flnm.at(i+1),"\n",&tmp);
			parms.threads=atoi(tmp.at(0).c_str());
			continue;

		} else if (parms.flnm.at(i).find("&save")!=string::npos) {

			StringExplode(parms.flnm.at(i+1),"\n",&tmp);
			if (tmp.at(0)=="true" || tmp.at(0)=="True") { parms.save=true; continue; }

			else if (tmp.at(0) =="false" || tmp.at(0)=="False") { parms.save=false; continue; }

		} else if (parms.flnm.at(i).find("&print")!=string::npos) {

			parms.pl=0;
			int iter=1;

			while (parms.flnm.at(i+iter).find("/")==string::npos) {

				StringExplode(parms.flnm.at(i+iter),"\n",&tmp);
				if (tmp.at(0)=="standings") parms.pl += 1;

				else if (tmp.at(0)=="histograms") parms.pl += 2;

				else if (tmp.at(0)=="rankings") parms.pl += 4;

				else if (tmp.at(0)=="averages") parms.pl += 8;

				else if (tmp.at(0)=="margins") parms.pl += 16;

				iter+=1;
			}

		} else if (parms.flnm.at(i).find("&debug")!=string::npos) {

			parms.debug=false;
			StringExplode(parms.flnm.at(i+1),"\n",&tmp);
			if (tmp.at(0)=="true" || tmp.at(0)=="True") { parms.debug=true; continue; }

		}

	}

	if (parms.filename.size()==0) {

		fprintf(stderr, "error: no filename\n\n");
		//exit(1);

	}

	if (parms.simulation) {

		printf("     INPUT| filename               %55s\n",parms.filename.c_str());
		printf("     INPUT| runtype                %55s\n",parms.runtype.c_str());
		printf("     INPUT| number of sims         %55d\n",parms.nsims);

		if (parms.save) printf("     INPUT| save                   %55s\n","true");
		else printf("     INPUT| save                   %55s\n","false");

		printf("     INPUT| number of threads      %55d\n",parms.threads);
		printf("     INPUT| print level            %55d\n",parms.pl);
		printf("     INPUT| rating update frequency %54d\n",parms.ratingfreq);
		printf("     INPUT| rating update minimum  %55d\n",parms.ratingmin);
		printf("     INPUT| rating memory          %55d\n",parms.ratingmemory);
		if (!parms.ratingrestart.empty()) printf("     INPUT| rating restart file    %55s\n",parms.ratingrestart.c_str());
		if (parms.ratinginit>0 && parms.ratingrestart.empty()) printf("     INPUT| rating initial value   %55f\n",parms.ratinginit);

	}


	if (parms.analysis) {

		if (!parms.website.empty()) { printf("\n"); printf("     INPUT| analysis website       %55s\n",parms.website.c_str()); }

		if (parms.player_download) {

			printf("\n");
			printf("     INPUT| analysis player download print %47s\n",parms.print_player_download.c_str());

		}
		if (parms.player_update) {

			printf("\n");
			printf("     INPUT| analysis player update print %49s\n",parms.print_player_update.c_str());
			printf("     INPUT| analysis player update read  %49s\n",parms.read_player_update.c_str());
			printf("     INPUT| analysis player update year  %49d\n",parms.player_update_year);

		}
		if (parms.team_download) {

			printf("\n");
			printf("     INPUT| analysis team download print %49s\n",parms.print_team_download.c_str());
			printf("     INPUT| analysis team download read  %49s\n",parms.read_team_download.c_str());
			printf("     INPUT| analysis team download year  %49d\n",parms.team_download_year);

		}
		if (parms.team_update) {

			printf("\n");
			printf("     INPUT| analysis team update print   %49s\n",parms.print_team_update.c_str());
			printf("     INPUT| analysis team update read team   %45s\n",parms.read_team_update_team.c_str());
			printf("     INPUT| analysis team update read player %45s\n",parms.read_team_update_player.c_str());

		}
		if (parms.season_download) {

			printf("\n");
			printf("     INPUT| analysis season download print %47s\n",parms.print_season_download.c_str());
			printf("     INPUT| analysis season download year  %47d\n",parms.season_download_year);

		}
		if (parms.season_update) {

			printf("\n");
			printf("     INPUT| analysis season update print %49s\n",parms.print_season_update.c_str());
			printf("     INPUT| analysis season update read  %49s\n",parms.read_season_update.c_str());
			printf("     INPUT| analysis season update begin %49s\n",parms.begin_season_update.c_str());
			printf("     INPUT| analysis season update end   %49s\n",parms.finish_season_update.c_str());

		}
	}

	printf("\n");

	clock_t endtime=clock();
    parms.tread=double(endtime-starttime)/CLOCKS_PER_SEC;
}
void ReadSimulation(vector<vector<string> > &G, vector<map<string, string> > &T, vector<map<string,vector<double> > > &AdjTeamRanks,
					map<string,map<string, vector<double> > > &Histogram, runparams &parms) {

	if (parms.runtype=="default") { ReadScheduleNew(parms,T,G,AdjTeamRanks,Histogram,parms.filename); }

	//else if (parms.runtype=="clear") { ReadScheduleClearNew(parms,T,G,AdjTeamRanks,Histogram,parms.filename); }

}


