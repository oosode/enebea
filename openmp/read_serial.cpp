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

        static const string arr10[] = {"DraftPos","Lottery","Seeds","pWins","pLoss","Wins","Loss",
                                       "Division","Conference","League","ORanks","DRanks"};
        vector<string> histvals (arr10,arr10 + sizeof(arr10) / sizeof(arr10[0]));

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
                    sprintf(buffer,"buffer.%06d.%02d.chk",0,count);
                    ofstream out(buffer);
                    temp.write(&out);
                    out.flush();
                    count++;
                    
					TeamM.at(0).insert(pair<string, string>(team, buffer));
					//TeamM.at(0).find(team)->second.Load(team,conf,divs);

					AdjTeamRanks.at(0).insert(pair<string, vector<double> >(team, rank));


				}
			}
		}
	}

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

/*
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

								AllG.at(q).push_back(Game());
								AllG.at(q).back().Load(&TeamM.at(q).find(homeT)->second,&TeamM.at(q).find(awayT)->second,id,today);
								//cout << AllG.at(q).back().GameIDstring << endl;
							}

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
*/

void ReadRatingRestart(runparams &parms, vector<map<string, string> > &TeamM, vector<map<string, vector<double> > > &AR) {
    
    if (parms.debug) { printf("ReadRatingRestart starting...\n"); }
    
    ifstream file1;
    char buffer[50];
    
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
                    
                    sprintf(buffer,"%s",TeamM.front().find(team)->second);
                    ifstream in(buffer);
                    
                    Team temp;
                    temp.read(&in);
                    
                    temp.OffRtg=atof(off.c_str());
                    temp.DefRtg=atof(def.c_str());
                    
                    temp.startOffRtg = TeamM.front().find(team)->second.OffRtg;
                    temp.startDefRtg = TeamM.front().find(team)->second.DefRtg;
                    
                    temp.write(&out);
                    out.flush();
                    
                }
            }
        }
        
    } else if (parms.ratinginit > 0) {
        
        file1.clear();
        
        typedef map<string, Team>::iterator it_type;
        for (it_type iterator = TeamM.front().begin(); iterator != TeamM.front().end(); iterator++) {
            
            AR.front().insert(pair<string, vector<double> >(iterator->first, rank));
            
            ifstream in(iterator->second);
            Team temp;
            
            temp.read(&in);
            
            temp.OffRtg=parms.ratinginit;
            temp.startOffRtg=parms.ratinginit;
            
            temp.DefRtg=parms.ratinginit;
            temp.startDefRtg=parms.ratinginit;
            
            temp.write(&out);
            out.flush();
            
        }
        
    } else fprintf(stderr, "error: no ratings specified\n\n");
    
    if (parms.debug) { printf("ReadRatingRestart exiting...\n\n"); }
}

void ReadSimulation(vector<vector<string> > &G, vector<map<string, string> > &T, vector<map<string,vector<double> > > &AdjTeamRanks,
					map<string,map<string, vector<double> > > &Histogram, runparams &parms) {

	if (parms.runtype=="default") { ReadScheduleNew(parms,T,G,AdjTeamRanks,Histogram,parms.filename); }

}


