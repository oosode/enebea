/*
 * ranking.cpp
 *
 *  Created on: Dec 29, 2012
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
#include "standing.h"
#include "ranking.h"
#include "cholesky.h"
#include "functions.h"

using std::pair;
using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

#define PI 3.14159

void BestWorstRanking(vector<map<string, Team> > &T, vector<MarginRankings> &BWRank,double &q,bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("MarginRanking starting...\n"); }

	BWRank.resize(T.front().size());
	int count=0;

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = T.front().begin(); iterator != T.front().end(); iterator++) {

		string team=iterator->second.TeamName;
		BWRank.at(count).TeamName=team;

		// Offensive Best
		for (int i=0; i<(int)T.size(); i++) {

			bool ob=true;

			if (!BWRank.at(count).BestOffense.empty()) {

				if (T.at(i).find(team)->second.OffRtgRank.back() < BWRank.at(count).BestOffense.back()) { ob=true; }

				else if (T.at(i).find(team)->second.OffRtgRank.back() == BWRank.at(count).BestOffense.back()) {

					double oldr=AVERAGE(T.at(i).find(team)->second.OffRtgRank);
					double newr=AVERAGE(BWRank.at(count).BestOffense);

					if (newr<oldr) ob=true;

				} else ob=false;

			}

			if (ob) {

				BWRank.at(count).BestOffense=T.at(i).find(team)->second.OffRtgRank;
				BWRank.at(count).BestOff=T.at(i).find(team)->second.OffRtg;

			}

		}

		// Offensive Worst
		for (int i=0; i<(int)T.size(); i++) {

			bool ob=true;

			if (!BWRank.at(count).WorstOffense.empty()) {

				if (T.at(i).find(team)->second.OffRtgRank.back() > BWRank.at(count).WorstOffense.back()) { ob=true; }

				else if (T.at(i).find(team)->second.OffRtgRank.back() == BWRank.at(count).WorstOffense.back()) {

					double oldr=AVERAGE(T.at(i).find(team)->second.OffRtgRank);
					double newr=AVERAGE(BWRank.at(count).WorstOffense);

					if (newr>oldr) ob=true;

				} else ob=false;

			}

			if (ob) {

				BWRank.at(count).WorstOffense=T.at(i).find(team)->second.OffRtgRank;
				BWRank.at(count).WorstOff=T.at(i).find(team)->second.OffRtg;

			}

		}

		// Defensive Best
		for (int i=0; i<(int)T.size(); i++) {

			bool ob=true;

			if (!BWRank.at(count).BestDefense.empty()) {

				if (T.at(i).find(team)->second.DefRtgRank.back() < BWRank.at(count).BestDefense.back()) { ob=true; }

				else if (T.at(i).find(team)->second.DefRtgRank.back() == BWRank.at(count).BestDefense.back()) {

					double oldr=AVERAGE(T.at(i).find(team)->second.DefRtgRank);
					double newr=AVERAGE(BWRank.at(count).BestDefense);

					if (newr<oldr) ob=true;

				} else ob=false;

			}

			if (ob) {

				BWRank.at(count).BestDefense=T.at(i).find(team)->second.DefRtgRank;
				BWRank.at(count).BestDef=T.at(i).find(team)->second.DefRtg;

			}

		}

		// Defensive Worst
		for (int i=0; i<(int)T.size(); i++) {

			bool ob=true;

			if (!BWRank.at(count).WorstDefense.empty()) {

				if (T.at(i).find(team)->second.DefRtgRank.back() > BWRank.at(count).WorstDefense.back()) { ob=true; }

				else if (T.at(i).find(team)->second.DefRtgRank.back() == BWRank.at(count).WorstDefense.back()) {

					double oldr=AVERAGE(T.at(i).find(team)->second.DefRtgRank);
					double newr=AVERAGE(BWRank.at(count).WorstDefense);

					if (newr>oldr) ob=true;

				} else ob=false;

			}

			if (ob) {

				BWRank.at(count).WorstDefense=T.at(i).find(team)->second.DefRtgRank;
				BWRank.at(count).WorstDef=T.at(i).find(team)->second.DefRtg;

			}

		}

		// Differential Best
		for (int i=0; i<(int)T.size(); i++) {

			bool ob=true;
			double diff=T.at(i).find(team)->second.RtgDiff;

			if (!BWRank.at(count).BestDifferential.empty()) {

				if (diff > BWRank.at(count).BestDiff) { ob=true; }

				else ob=false;

			}

			if (ob) {

				BWRank.at(count).BestDifferential=T.at(i).find(team)->second.RtgDiffRank;
				BWRank.at(count).BestDiff=diff;

			}

		}

		// Differential Worst
		for (int i=0; i<(int)T.size(); i++) {

			bool ob=true;
			double diff=T.at(i).find(team)->second.RtgDiff;

			if (!BWRank.at(count).WorstDifferential.empty()) {

				if (diff < BWRank.at(count).WorstDiff) { ob=true; }

				else ob=false;

			}

			if (ob) {

				//BUGBUGBUGBUGBUG
				BWRank.at(count).WorstDifferential=T.at(i).find(team)->second.RtgDiffRank;
				BWRank.at(count).WorstDiff=diff;

			}

		}

		count+=1;
	}

	if (debug) { printf("MarginRanking exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}


void AverageRanking(vector<map<string, Team> > &T, map<string, vector<double> > &AvgTeamRanks, double &q, bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("AverageRanking starting...\n"); }

	double denom = double(T.size());
	vector<double> rank(6,0.0);


	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = T.front().begin(); iterator != T.front().end(); iterator++) {

		AvgTeamRanks.insert(pair<string, vector<double> >(iterator->second.TeamName, rank));

	}

	for (int i=0; i<(int)T.size(); i++) {

		for (it_type iterator = T.at(i).begin(); iterator != T.at(i).end(); iterator++) {

			AvgTeamRanks.find(iterator->second.TeamName)->second.at(0) += iterator->second.OffRtg/denom;
			AvgTeamRanks.find(iterator->second.TeamName)->second.at(1) += iterator->second.DefRtg/denom;
			AvgTeamRanks.find(iterator->second.TeamName)->second.at(2) += (iterator->second.OffRtg-iterator->second.DefRtg)/denom;

			AvgTeamRanks.find(iterator->second.TeamName)->second.at(3) += iterator->second.avgP4/denom;
			AvgTeamRanks.find(iterator->second.TeamName)->second.at(4) += iterator->second.avgPA/denom;
			AvgTeamRanks.find(iterator->second.TeamName)->second.at(5) += (iterator->second.avgP4-iterator->second.avgPA)/denom;

		}
	}

	if (debug) { printf("AverageRanking exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}

void SimpleRanking(map<string, Team> &TheTeams, map<string, vector<double> > &AdjTeamRanks, double &q, runparams &parms) {

	clock_t starttime=clock();

	if (parms.debug) { printf("SimpleRanking starting...\n"); }

	double LeagueAvg = TheTeams.begin()->second.avgLeagueP4;
	double tol = 0.050;
	int memory;

    map<string, vector<double> > Margins;

    /*
     *
     */
    // Margins
	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		if (iterator->second.avgP4 > 1.0) {
			//cout << iterator->first << iterator->second.avgP4 << " " << iterator->second.avgPA << endl;

			int totalgames = iterator->second.HomeGames + iterator->second.AwayGames;
			double homepercent = double(iterator->second.HomeGames)/double(totalgames);

			vector<double> marg(2,0.0);

			string team = iterator->second.TeamName;

			Margins.insert(pair<string, vector<double> >(team,marg));

			double OffMar = iterator->second.avgP4 - LeagueAvg;
			double DefMar = iterator->second.avgPA - LeagueAvg;

			// Adjusted Margins

			Margins.find(team)->second.at(0) = OffMar - homepercent*3.0/2;
			Margins.find(team)->second.at(1) = DefMar + homepercent*3.0/2;

			//cout << iterator->second.TeamName << " " << homepercent << " " << OffMar << " " << Margins.find(team)->second.at(0) << endl;
			//cout << iterator->second.TeamName << " " << homepercent << " " << DefMar << " " << Margins.find(team)->second.at(1) << endl;

		}
	}

	bool converged = false;

	double count = 0;
	while (!converged) {


		/*
		 *
		 */

		// reinitialize
		typedef map<string, vector<double> >::iterator it_type;
		for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

			iterator->second.at(2) = iterator->second.at(0); // saving old offensive Team Ranks
			iterator->second.at(3) = iterator->second.at(1); // saving old defensive Team Ranks

		}

		typedef map<string, vector<double> >::iterator it_type;
		for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

			string team =  iterator->first;

			double den = 0.0;
			double numo = 0.0;
			double numd = 0.0;

			memory=0;

			for (int i=0; i<(int)TheTeams.find(team)->second.Schedule.size(); i++) {

				if (TheTeams.find(team)->second.Schedule.at(i).Ratings.empty()) {

					break;

			    } else if (abs(TheTeams.find(team)->second.Schedule.at(i).Ratings.at(0)) > 0.0001) {

			    	if (memory <= parms.ratingmemory) {

						string opp = TheTeams.find(team)->second.Schedule.at(i).Opponent;

						// Offense
						numo += AdjTeamRanks.find(opp)->second.at(1);

						// Defense
						numd += AdjTeamRanks.find(opp)->second.at(0);

						den += 1.0;

						memory++;

			    	}
				}
			}

			AdjTeamRanks.find(team)->second.at(0) = -numo/den + Margins.find(team)->second.at(0);
			AdjTeamRanks.find(team)->second.at(1) = numd/den + -Margins.find(team)->second.at(1);

			//if (team == "WAS") {
			    //cout << team << " SOS: " << -numo/den << " MOV: " << Margins.find(team)->second.at(0) << " SRS: " << AdjTeamRanks.find(team)->second.at(0) << endl;
			    //cout << team << " SOS: " << numd/den << " MOV: " << -Margins.find(team)->second.at(1) << " SRS: " << AdjTeamRanks.find(team)->second.at(1) << endl;
			//}
		}

		double conv = 0.0;

		bool check = true;

		typedef map<string, vector<double> >::iterator it_type;
		for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

			conv = fabs(iterator->second.at(2) - iterator->second.at(0));

			if (conv > tol) {

				check = false;
				break;

			}

			conv = fabs(iterator->second.at(3) - iterator->second.at(1));

			if (conv > tol) {

				check = false;
				break;

			}
		}

		if (check) {

			converged = true;

			//typedef map<string, vector<double> >::iterator it_type;
			//for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++)
			for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

				TheTeams.find(iterator->first)->second.OffRtg = LeagueAvg + iterator->second.at(0);
				TheTeams.find(iterator->first)->second.DefRtg = LeagueAvg - iterator->second.at(1);
				TheTeams.find(iterator->first)->second.RtgDiff = TheTeams.find(iterator->first)->second.OffRtg -
																 TheTeams.find(iterator->first)->second.DefRtg;

				//cout << TheTeams.find(iterator->first)->second.OffRtg << " " <<
				//		TheTeams.find(iterator->first)->second.DefRtg << endl;


			}

		}

		count += 1;

		//cout << count << endl;

		if (count > 10) {

			typedef map<string, vector<double> >::iterator it_type;
			for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

				TheTeams.find(iterator->first)->second.OffRtg = LeagueAvg + iterator->second.at(0);
				TheTeams.find(iterator->first)->second.DefRtg = LeagueAvg - iterator->second.at(1);
				TheTeams.find(iterator->first)->second.RtgDiff = TheTeams.find(iterator->first)->second.OffRtg -
																 TheTeams.find(iterator->first)->second.DefRtg;


				//cout << TheTeams.find(iterator->first)->second.OffRtg << " " <<
				//		TheTeams.find(iterator->first)->second.DefRtg << endl;

			}

			break;
		}

	}

	if (parms.debug) { printf("SimpleRanking exiting...\n\n"); }

	clock_t endtime=clock();
    q=double(endtime-starttime)/CLOCKS_PER_SEC;
}

void SimpleRankingLast10(map<string, Team> &TheTeams, map<string, vector<double> > &AdjTeamRanks) {

	double LeagueAvg = TheTeams.begin()->second.avgLeagueP4;
	double tol = 0.10;

    map<string, vector<double> > Margins;

    /*
     *
     */

    // Margins
	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		if (iterator->second.avgP4Last10 > 0.01) {

			//cout << "hello" << endl;
			//cout << iterator->second.avgP4Last10 << endl;

			int totalgames = iterator->second.HomeGamesLast10 + iterator->second.AwayGamesLast10;
			double homepercent = double(iterator->second.HomeGamesLast10)/double(totalgames);

			vector<double> marg(2,0.0);

			string team = iterator->second.TeamName;

			Margins.insert(pair<string, vector<double> >(team,marg));

			double OffMar = iterator->second.avgP4Last10 - LeagueAvg;
			double DefMar = iterator->second.avgPALast10 - LeagueAvg;

			// Adjusted Margins
			Margins.find(team)->second.at(0) = OffMar - homepercent*3.0/2;
			Margins.find(team)->second.at(1) = DefMar + homepercent*3.0/2;

		}
	}

	bool converged = false;

	double count = 0;
	while (!converged) {

		/*
		 *
		 */

		// reinitialize
		typedef map<string, vector<double> >::iterator it_type;
		for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

			iterator->second.at(2) = iterator->second.at(0); // saving old offensive Team Ranks
			iterator->second.at(3) = iterator->second.at(1); // saving old defensive Team Ranks

		}

		typedef map<string, vector<double> >::iterator it_type;
		for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

			string team = iterator->first;

			double den = 0.0;
			double numo = 0.0;
			double numd = 0.0;

			int care=0;

			for (int i=(int)TheTeams.find(team)->second.Schedule.size()-1; i>=0; i--) {

				if (TheTeams.find(team)->second.Schedule.at(i).Ratings.empty()) {

					continue;

			    } else if (abs(TheTeams.find(team)->second.Schedule.at(i).Ratings.at(0)) > 0.0001) {
			    	//cout << TheTeams.find(team)->second.Schedule.at(i).Ratings.at(0) << endl;
			    	if (care < 10) {

						string opp = TheTeams.find(team)->second.Schedule.at(i).Opponent;

						// Offense
						numo += AdjTeamRanks.find(opp)->second.at(1);

						// Defense
						numd += AdjTeamRanks.find(opp)->second.at(0);

						den += 1.0;

						care++;


			    	} else {

			    		break;

			    	}
				}
			}

			AdjTeamRanks.find(team)->second.at(0) = -numo/den + Margins.find(team)->second.at(0);
			AdjTeamRanks.find(team)->second.at(1) = numd/den + -Margins.find(team)->second.at(1);


		}

		double conv = 0.0;

		bool check = true;
		for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

			conv = fabs(iterator->second.at(2) - iterator->second.at(0));

			if (conv > tol) {

				check = false;
				break;

			}

			conv = fabs(iterator->second.at(3) - iterator->second.at(1));

			if (conv > tol) {

				check = false;
				break;

			}
		}

		if (check) {

			converged = true;

			typedef map<string, vector<double> >::iterator it_type;
			for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

				TheTeams.find(iterator->first)->second.OffRtg = LeagueAvg + iterator->second.at(0);
				TheTeams.find(iterator->first)->second.DefRtg = LeagueAvg - iterator->second.at(1);
				TheTeams.find(iterator->first)->second.RtgDiff = TheTeams.find(iterator->first)->second.OffRtg -
																 TheTeams.find(iterator->first)->second.DefRtg;

			}
		}

		count++;
		if (count > 10) {

			typedef map<string, vector<double> >::iterator it_type;
			for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

				TheTeams.find(iterator->first)->second.OffRtg = LeagueAvg + iterator->second.at(0);
				TheTeams.find(iterator->first)->second.DefRtg = LeagueAvg - iterator->second.at(1);
				TheTeams.find(iterator->first)->second.RtgDiff = TheTeams.find(iterator->first)->second.OffRtg -
																 TheTeams.find(iterator->first)->second.DefRtg;

			}

			break;
		}
	}
}

void SimpleRankingQuarter(map<string, Team> &TheTeams, map<string, vector<double> > &AdjTeamRanks) {

	double LeagueAvg = TheTeams.begin()->second.avgLeagueP4;
	double tol = 0.10;

    map<string, vector<double> > Margins;

    /*
     *
     */

    // Margins
	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		if (iterator->second.avgP4Quarter > 0.01) {

			int totalgames = iterator->second.HomeGamesQuarter + iterator->second.AwayGamesQuarter;
			double homepercent = double(iterator->second.HomeGamesQuarter)/double(totalgames);

			vector<double> marg(2,0.0);

			string team = iterator->second.TeamName;

			Margins.insert(pair<string, vector<double> >(team,marg));

			double OffMar = iterator->second.avgP4Quarter - LeagueAvg;
			double DefMar = iterator->second.avgPAQuarter - LeagueAvg;

			// Adjusted Margins
			Margins.find(team)->second.at(0) = OffMar - homepercent*3.0/2;
			Margins.find(team)->second.at(1) = DefMar + homepercent*3.0/2;

		}
	}

	bool converged = false;

	double count = 0;
	while (!converged) {

		/*
		 *
		 */

		// reinitialize
		typedef map<string, vector<double> >::iterator it_type;
		for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

			iterator->second.at(2) = iterator->second.at(0); // saving old offensive Team Ranks
			iterator->second.at(3) = iterator->second.at(1); // saving old defensive Team Ranks

		}

		typedef map<string, vector<double> >::iterator it_type;
		for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

			string team = iterator->first;

			double den = 0.0;
			double numo = 0.0;
			double numd = 0.0;

			int care=0;

			for (int i=(int)TheTeams.find(team)->second.Schedule.size()-1; i>=0; i--) {

				if (TheTeams.find(team)->second.Schedule.at(i).Ratings.empty()) {

					continue;

			    } else if (abs(TheTeams.find(team)->second.Schedule.at(i).Ratings.at(0)) > 0.0001) {

			    	if (care < 10) {

						string opp = TheTeams.find(team)->second.Schedule.at(i).Opponent;

						// Offense
						numo += AdjTeamRanks.find(opp)->second.at(1);

						// Defense
						numd += AdjTeamRanks.find(opp)->second.at(0);

						den += 1.0;

						care++;


			    	} else {

			    		break;

			    	}
				}
			}

			AdjTeamRanks.find(team)->second.at(0) = -numo/den + Margins.find(team)->second.at(0);
			AdjTeamRanks.find(team)->second.at(1) = numd/den + -Margins.find(team)->second.at(1);


		}

		double conv = 0.0;

		bool check = true;
		for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

			conv = fabs(iterator->second.at(2) - iterator->second.at(0));

			if (conv > tol) {

				check = false;
				break;

			}

			conv = fabs(iterator->second.at(3) - iterator->second.at(1));

			if (conv > tol) {

				check = false;
				break;

			}
		}

		if (check) {

			converged = true;

			typedef map<string, vector<double> >::iterator it_type;
			for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

				TheTeams.find(iterator->first)->second.OffRtg = LeagueAvg + iterator->second.at(0);
				TheTeams.find(iterator->first)->second.DefRtg = LeagueAvg - iterator->second.at(1);
				TheTeams.find(iterator->first)->second.RtgDiff = TheTeams.find(iterator->first)->second.OffRtg -
																 TheTeams.find(iterator->first)->second.DefRtg;

			}
		}

		count++;
		if (count > 10) {

			typedef map<string, vector<double> >::iterator it_type;
			for (it_type iterator = AdjTeamRanks.begin(); iterator != AdjTeamRanks.end(); iterator++) {

				TheTeams.find(iterator->first)->second.OffRtg = LeagueAvg + iterator->second.at(0);
				TheTeams.find(iterator->first)->second.DefRtg = LeagueAvg - iterator->second.at(1);
				TheTeams.find(iterator->first)->second.RtgDiff = TheTeams.find(iterator->first)->second.OffRtg -
																 TheTeams.find(iterator->first)->second.DefRtg;

			}

			break;
		}
	}
}


void ColleyRanking(map<string, Team> &TheTeams, map<string,vector<double> > &AdjTeamRanks) {

	double LeagueAvg = TheTeams.begin()->second.avgLeagueP4;
	int nteams = TheTeams.size();

    vector<vector<double> > Colley(nteams, vector<double>(nteams,0.0));

    /*
     *
     */

    int row=0;
    int col=0;
    int ngames=0;

    // Generate Colley Matrix
	typedef map<string, Team>::iterator it_type;
	for (it_type iterator1 = TheTeams.begin(); iterator1 != TheTeams.end(); iterator1++) {

		col = 0;
		for (it_type iterator2 = TheTeams.begin(); iterator2 != TheTeams.end(); iterator2++) {

			if (iterator1->second.TeamName == iterator2->second.TeamName) {

				Colley[row][col] = 2.0 + iterator1->second.AwayGames + iterator1->second.HomeGames;

			} else {

				ngames = 0;
				for (int i=(int)iterator1->second.Schedule.size()-1; i>=0; i--) {

					if (iterator1->second.Schedule.at(i).Ratings.empty()) {

						continue;

					 } else if (abs(iterator1->second.Schedule.at(i).Ratings.at(0)) > 0.0001) {

						if (iterator1->second.Schedule.at(i).Opponent == iterator2->second.TeamName) {

							ngames++;

						}
					}
				}
				Colley[row][col] = -ngames;
			}
			col++;
		}
		row++;
	}

	int OvrOff;
	int UndOff;
	int OvrDef;
	int UndDef;

	vector<double> OffensiveScores(nteams, 0.0);
	vector<double> DefensiveScores(nteams, 0.0);

	row = 0;

	// Generate Offensive and Defensive wins
	for (it_type iterator1 = TheTeams.begin(); iterator1 != TheTeams.end(); iterator1++) {

		OvrOff = 0;
		UndOff = 0;
		OvrDef = 0;
		UndDef = 0;

		for (int i=(int)iterator1->second.Schedule.size()-1; i>=0; i--) {

			if (iterator1->second.Schedule.at(i).Ratings.empty()) {

				continue;

			 } else if (abs(iterator1->second.Schedule.at(i).Ratings.at(0)) > 0.0001) {

				if (iterator1->second.Schedule.at(i).Ratings.at(0) >= LeagueAvg) OvrOff++;

				else UndOff++;

				//if (iterator1->second.Schedule.at(i).Ratings.at(1) > LeagueAvg) OvrDef++;
				if (iterator1->second.Schedule.at(i).Ratings.at(1) <= LeagueAvg) OvrDef++;

				else UndDef++;

			}
		}

		OffensiveScores.at(row) = 1.0 + double(OvrOff-UndOff)/2.0;
		DefensiveScores.at(row) = 1.0 + double(OvrDef-UndDef)/2.0;
		row++;

	}

	// Cholesky Decomposition

	//PrintMatrix(Colley);

	vector<vector<double> > ColleyO = Colley;
	vector<vector<double> > ColleyD = Colley;

	vector<double> DRanks(nteams);
	vector<double> ORanks(nteams);

	vector<double> diagonal(nteams);

	choldc(Colley,nteams,diagonal);
	cholsl(Colley,nteams,diagonal,OffensiveScores,DRanks);
	cholsl(Colley,nteams,diagonal,DefensiveScores,ORanks);


	int count = 0;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		TheTeams.find(iterator->first)->second.OffRtg = LeagueAvg + 50*atan((ORanks.at(count)-0.5)*5.0)/(2*PI);
		TheTeams.find(iterator->first)->second.DefRtg = LeagueAvg - 50*atan((DRanks.at(count)-0.5)*5.0)/(2*PI);
		cout << TheTeams.find(iterator->first)->second.TeamName << " ";
		cout << TheTeams.find(iterator->first)->second.OffRtg << " ";
		cout << TheTeams.find(iterator->first)->second.DefRtg << " ";
		cout << TheTeams.find(iterator->first)->second.WinPercent << " ";
		cout << ORanks.at(count) << " " << DRanks.at(count) << endl;

		count++;
	}

	cout << LeagueAvg << endl;
	cout << "Finished" << endl;
    //exit(1);
}


void Ranking(map<string, Team> &TheTeams) {

	vector<string> Offensive;
	vector<string> Defensive;
	vector<string> Differential;

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		// Offensive
		bool ofound = false;
		for (int i=0; i<(int)Offensive.size(); i++) {

			if (iterator->second.OffRtg >= TheTeams.find(Offensive.at(i))->second.OffRtg) {

				Offensive.insert(Offensive.begin()+i,iterator->second.TeamName);
				ofound = true;
				break;

			}

		}
		if (!ofound) {

			Offensive.push_back(iterator->second.TeamName);
		}

		/*
		 *
		 */

		// Defensive
		bool dfound = false;
		for (int i=0; i<(int)Defensive.size(); i++) {

			if (iterator->second.DefRtg <= TheTeams.find(Defensive.at(i))->second.DefRtg) {

				Defensive.insert(Defensive.begin()+i,iterator->second.TeamName);
				dfound = true;
				break;

			}

		}
		if (!dfound) {

			Defensive.push_back(iterator->second.TeamName);
		}

		/*
		 *
		 */

		// Differential
		bool efound = false;
		for (int i=0; i<(int)Differential.size(); i++) {

			if (iterator->second.RtgDiff >= TheTeams.find(Defensive.at(i))->second.RtgDiff) {

				Differential.insert(Differential.begin()+i,iterator->second.TeamName);
				efound = true;
				break;

			}

		}
		if (!efound) {

			Differential.push_back(iterator->second.TeamName);
		}

	}

	for (int i=0; i<(int)Offensive.size(); i++) {

		TheTeams.find(Offensive.at(i))->second.OffRtgRank.push_back(i+1);

	}
	for (int i=0; i<(int)Defensive.size(); i++) {

		TheTeams.find(Defensive.at(i))->second.DefRtgRank.push_back(i+1);

	}
	for (int i=0; i<(int)Differential.size(); i++) {

		TheTeams.find(Differential.at(i))->second.RtgDiffRank.push_back(i+1);

	}

}

