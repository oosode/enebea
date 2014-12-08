/*
 ============================================================================
 Name        : season.cpp
 Author      : oosode
 Version     : 
 Date        : Dec 24, 2013
 Description : 
 ============================================================================
 */

#include "nba.h"
//#include "math.h"
#include "season.h"
#include "game.h"
#include "team.h"
#include "run.h"
#include "function.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace NBA_NS;

/*-----------------------------------------------------------------
  Constructor
-----------------------------------------------------------------*/

Season::Season(NBA *nba) : Pointers(nba)
{
  // Basic initializations

  ngames             = 1230;
  nteams	     = 0;

  sprintf(filename, "%s", "season.2015.csv");
  //teams  	     = NULL;
  //games	     = NULL;


}

/*-----------------------------------------------------------------
  Destructor
-----------------------------------------------------------------*/

Season::~Season()
{

}


/*-----------------------------------------------------------------
  Initializer
-----------------------------------------------------------------*/
void Season::init()
{
  // Note: input.cpp read in various MD run parameters already before this point
  //       Also, this is to be called after a RUN_FORCE calculation is completed

  if (nba->master_rank) if (nba->run->debug) printf("season::init starting...\n");

  MPI_Barrier(nba->world);
  init_start = MPI_Wtime();

  // ** Detemine the season parameters ** //
  define();

  // ** Initialize season parameters ** //
  //BUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUG
//  if (teams == NULL) {
//	    teams = new *Team [nteams];
//  }
  //BUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUG
  //if (games == NULL) games = new *Game [ngames];

  init_end = MPI_Wtime();
  init_time = init_end-init_start;
  MPI_Barrier(nba->world);

  if (nba->master_rank) if (nba->run->debug) printf("season::init finished...\n\n");
}

/*-----------------------------------------------------------------
  Define Season Parameters
-----------------------------------------------------------------*/
void Season::define()
{
	if (nba->master_rank) if (nba->run->debug) printf("season::define starting...\n");

	MPI_Barrier(nba->world);
	define_start=MPI_Wtime();

	if (nba->master_rank) {
	struct tm tmlol;
	memset(&tmlol, 0, sizeof(struct tm));

	// Load schedule into finput vector
	std::string line;
	std::vector<std::string> tmp;
	std::ifstream file0(filename);
	int num=0;

	if (file0.is_open())
	{
	    while (file0.good())
	    {
	    	std::getline(file0,line);
	        std::transform(line.begin(),line.end(),line.begin(),::toupper);
	        finput.push_back(line);
	    }
	}
	file0.close();

	// Find year for standings
	// Find number of teams
	// Find number of games
	for (int i=0; i<(int)finput.size(); i++)
	{
		//printf("INPUT LINE:%02d\n",i);
		line=finput[i];
		num+=1;
		if (line.find("DATE")!=std::string::npos)
		{
			if (num==1)
			{
				StringExplode(line,",",&tmp);

				strptime(tmp.at(tmp.size()-3).c_str(), "%Y-%m-%d", &tmlol);
				end = mktime(&tmlol);
				struct tm* tm = localtime(&end);
				year = 1900 + tm->tm_year;

				strptime(tmp.at(1).c_str(), "%Y-%m-%d", &tmlol);
				begin = mktime(&tmlol);
				tm = localtime(&begin);

				for (int j=(int)tmp.size()-1; j>0; j--)
                    if (tmp.at(j).find("DATE")!=std::string::npos) { days=j-1; break; }
			}
			else break;
		}
		else
		{
			nteams+=1;
		}
	}
	}
	define_end = MPI_Wtime();
	define_time = define_end-define_start;
	MPI_Barrier(nba->world);

    MPI_Bcast(&nba->season->nteams, 1, MPI_INT, MASTER_RANK, nba->world);
    MPI_Bcast(&nba->season->days, 1, MPI_INT, MASTER_RANK, nba->world);

	if (nba->master_rank) if (nba->run->debug) printf("season::define finished...\n\n");
}

/*-----------------------------------------------------------------
  Load Season Teams and Games
-----------------------------------------------------------------*/
void Season::load()
{
	if (nba->master_rank) if (nba->run->debug) printf("season::load starting...\n");

	MPI_Barrier(nba->world);
	load_start=MPI_Wtime();

	std::string line;
	std::vector<std::string> tmp;
	int num;

/*
	std::map<std::string, std::vector<std::string> > Standings;
	AssignStanding(Standings,year,parms);

	vector<double> temporary;
	map<string, vector<double> > init_hist;
	for (int k=0; k<(int)histvals.size(); k++) {

		init_hist.insert(pair<string, vector<double> >(histvals.at(k),temporary));

	}
*/

	//std::vector<double> rank(4,0.0);
	//double hrtg,artg;

	num = 0;

	for (int i=0; i<(int)finput.size(); i++)
	{
		line=finput[i];
		if (line.find("DATE")!=std::string::npos) continue;
		else
		{
			StringExplode(line,",",&tmp);
			if (tmp.size() > 2) {

				std::string team = tmp.at(0);

				/*
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
				*/
				//teams[num].name=team;
				//TeamM.at(0).insert(pair<string, Team>(team, Team()));
				//					TeamM.at(0).find(team)->second.Load(team,conf,divs);
			    num+=1;
			}
		}



	}
	num=0;
	//std::ifstream file1(nba->input->season_name);
	//BUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUG
	//hard-coded value
	std::ifstream file1(filename);
	//BUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUG
	if (file1.is_open()) {
		while (file1.good()) {

			getline(file1,line);

			transform(line.begin(),line.end(),line.begin(),::toupper);

			if (line.find("DATE")!=std::string::npos) {
				continue;

			} else {

				StringExplode(line,",",&tmp);
				if (tmp.size() > 2) {

					std::string team = tmp.at(0);
					std::string conf;
					std::string divs;
					
//conference

					/*
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
					*/


					//Histogram.insert(pair<string,map<string, vector<double> > >(team, init_hist));
					//TeamM.at(0).insert(pair<string, Team>(team, Team()));
					//TeamM.at(0).find(team)->second.Load(team,conf,divs);


				}
			}
		}
	}

	load_end  = MPI_Wtime();
	load_time = load_end - load_start;

	if (nba->master_rank) if (nba->run->debug) printf("season::load finished...\n\n");

	return;
}
/*
	ReadRatingRestart(parms,TeamM,AdjTeamRanks);

	for (int i=1; i<(int)TeamM.size(); i++) {

		TeamM.at(i) = TeamM.front();
		AdjTeamRanks.at(i) = AdjTeamRanks.front();

	}

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
									AllG.at(q).back().GameOver=true; AllG.at(q).back().HomeScore=hrtg; AllG.at(q).back().AwayScore=artg;

								}
								id += 1;

							}

						} else if (gm.at(0)=="L") {

							struct tm* tm = localtime(&opening_day);
							tm->tm_mday += i-1;
							time_t today = mktime(tm);

							std::string awayT = team;
							std::string homeT = gm.at(2);

							hrtg =  0.00001;
							artg = -0.00001;

							if (gm.size() > 3) {

								StringExplode(gm.at(3),"-",&scr);
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

	for (int i=0; i<(int)AllG.size(); i++) {

		AllG.at(i).clear();
	}

	printf("\n");
	printf("     READING| total number of days %55d\n\n",days-1);
	int gameidx=0;
	for (int i=0; i<days-1; i++) {

		time_t today = mktime(tm);

		for (int j=(int)UnsortedGames.front().size()-1; j>=0; j--) {

			if (UnsortedGames.front().at(j).GameDate==today) {

				for (int q=0; q<(int)AllG.size(); q++) {

					AllG.at(q).push_back(UnsortedGames.at(q).at(j));
					UnsortedGames.at(q).erase(UnsortedGames.at(q).begin()+j);

				}

				gameidx++;
			}
		}
		printf("     READING| day %3d \n",i);

		tm->tm_mday++;

	}
	printf("\n");

}
*/
void Season::run()
{
  nba->game->sim();
}


