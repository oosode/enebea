/*
 * team.h
 *
 *  Created on: Nov 10, 2012
 *      Author: Junior
 */

#ifndef TEAM_H_
#define TEAM_H_

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <time.h>
#include <fstream>

#include "team.h"
#include "players.h"

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::ofstream;
using std::ifstream;

class Team;

struct DayInfo {

	string Opponent;
	Team *Opp;

	// 0 = Loss, 1 = Win result for the current team
	 bool DidWin;

	 bool IsHome;

	// offensive, defensive ratings
	vector<double> Ratings;

	// distance from last game, if last game was less than three days ago
	double Distance;

	time_t Date;

};

class Team {

	public:

		Team();

		string TeamName;

		string Division;
		string Conference;

		vector<int> Lstand;
		vector<int> Cstand;
		vector<int> Dstand;

		vector<DayInfo> Schedule;
		vector<DayInfo> PlayoffSchedule;

		int Win;
		int Loss;

		int DivWin;
		int DivLoss;

		int ConfWin;
		int ConfLoss;

		int hBestConfWin;
		int hBestConfLoss;

		int aBestConfWin;
		int aBestConfLoss;

		int eWin;
		int eLoss;

		int HomeGames;
		int AwayGames;

		int HomeGamesLast10;
		int AwayGamesLast10;

		int HomeGamesQuarter;
		int AwayGamesQuarter;

		double WinPercent;
		double LossPercent;

		double DivWinPercent;
		double DivLossPercent;

		double ConfWinPercent;
		double ConfLossPercent;

		double hBestConfWinPercent;
		double hBestConfLossPercent;

		double aBestConfLossPercent;
		double aBestConfWinPercent;

		double Over500;
		double eOver500;
		double eWinPercent;
		double eLossPercent;

		double GamesBehindL; // Games Back in League
		double GamesBehindC; // Games Back in Conference
		double GamesBehindD; // Games Back in Division

		double OffRtg;
		double DefRtg;
		double RtgDiff;

		double startOffRtg;
		double startDefRtg;
		double startRtgDiff;

		vector<int> OffRtgRank;
		vector<int> DefRtgRank;
		vector<int> RtgDiffRank;

		double avgP4;
		double avgPA;

		double avgP4Last10;
		double avgPALast10;

		double avgP4Quarter;
		double avgPAQuarter;

		double avgLeagueP4;
		double avgLeaguePA;

		double Age;

		int GamesPlayed;

		vector<Player> Roster;

		/*
		 *
		 */

		// Playoff variables
		int PlayoffSeed;

		int pWin;
		int pLoss;

		int oneWin; // round one wins
		int oneLoss; // round one losses

		int twoWin; // conference semifinal wins
		int twoLoss; // conference semifinal losses

		int threeWin; // conference final wins
		int threeLoss; // conference final losses

		int fourWin; // championship wins
		int fourLoss; // championship loss

		double pWinPercent;
		double pLossPercent;

		double oneWinPercent; // round one win percentage
		double oneLossPercent; // round one loss percentage

		double twoWinPercent; // conference semifinal win percentage
		double twoLossPercent; // conference semifinal loss percentage

		double threeWinPercent; // conference final win percentage
		double threeLossPercent; // conference final loss percentage

		double fourWinPercent; // championship win percentage
		double fourLossPercent; // championship loss percentage

		double pavgP4;
		double pavgPA;

		int epWin;
		int epLoss;

		double epWinPercent;
		double epLossPercent;

		int pConfWin;
		int pConfLoss;

		double pConfWinPercent;
		double pConfLossPercent;

		double pOver500;
		double epOver500;

		/*
		 *
		 */

		int Lottery;
		int DraftPos;

		string secondround;
		string conffinals;
		string finals;

		void Load(string name, string conf, string divs);
		void Load(string name);
		int Game(string opp, double off, double def, time_t date);
		int GameAlready(string opp, double off, double def, time_t date);
		int PlayoffGame(string opp, double off, double def, int r);
		void CalcPercent();
		void PlayoffCalcPercent();
		void CalcRatg1(int g);
		void CalcRatg2(int g);
		void CalcRatg3(int g);
		void TeamWin();
		void TeamLoss();
		void Shock();
		void Calculate(int tx);
		void CalculatePlayoffs();
		void Calculate();
		void Average();
		void PlayoffAverage();
		void CalcBestPercent();
		int Rest(const time_t dat);
		void Distance(double lat1, double lat2, double lon1, double lon2, int i);
        void read(ifstream *in);
        void write(ofstream *out);

};


#endif /* TEAM_H_ */
