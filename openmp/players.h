/*
 * players.h
 *
 *  Created on: Aug 12, 2013
 *      Author: oosode
 */

#ifndef PLAYERS_H_
#define PLAYERS_H_

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <time.h>

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

class Player {

	public:

		Player();

		map<string, map<int,double> > statMap;
		map<string, map<int,string> > infoMap;

		double Info(int year, string stat);
		double Stat(int year, string stat);
		double SPS(double v1, double v2, double v3);

		// personal information
		string LastName;
		string FirstName;
		string FullName;

		string PlayerID;
		string bballref_id;
		string nbacom_id;

		string FirstYear;
		string LastYear;

		string PrimaryPosition;
		//string SecondaryPosition;

		int height;
		int weight;

		string hand;
		string position;

		time_t birthday;

		string HighSchool;
		string College;

		bool active;

		string CurrentTeam;

		// statistics

		// Offensive and Defensive Ratings from past three years
		int ORtg, DRtg;
		//int ORtg1, DRtg1;
		//int ORtg2, DRtg2;

		int Minutes;
		// PER from past three years
		int PER;
		//, PER1, PER2;

		// Win shares / 48 from past three years
		double WS;
		double WS48;

		double DWS,OWS;
		//double WS0, WS1, WS2;

		// Usage rates from past three years
		double Usage; // Usage1, Usage2;

		// shooting
		double TS;
		double eFG;

		// rebounding rates
		double ORB,DRB,TRB;

		double AST,STL,TOV,BLK;

		//age
		map<string,int> age;

		//team
		map<string,string> team;

		//pos
		map<string,string> pos;

		//games
		map<string,int> games;
		map<string,int> games_started;

		map<string,int> points;

		//shooting
		map<string,double> fg;
		map<string,double> fga;
		map<string,double> fgp; // field goal percent

		map<string,double> threeg;
		map<string,double> threega;
		map<string,double> threegp; // three point field goal percent

		map<string,double> twog;
		map<string,double> twoga;
		map<string,double> twogp; // two point field goal percent

		map<string,double> ft;
		map<string,double> fta;
		map<string,double> ftp; // free throw percent

		map<string,double> threegr; // three point rate
		map<string,double> ftr; // free throw rate

		//efg
		map<string,double> efg;
		map<string,double> ts;

		//rebounding
		map<string,double> orb_adv;
		map<string,double> drb_adv;
		map<string,double> trb_adv;

		map<string,double> orb_tot;
		map<string,double> drb_tot;
		map<string,double> trb_tot;

		//other stats
		map<string,double> ast_adv;
		map<string,double> stl_adv;
		map<string,double> blk_adv;
		map<string,double> tov_adv;


		map<string,double> ast_tot;
		map<string,double> stl_tot;
		map<string,double> blk_tot;
		map<string,double> tov_tot;

		map<string,double> foul_tot;

		//usage
		map<string,double> usg;

		//player ratings
		map<string,double> ortg;
		map<string,double> drtg;

		//win shares
		map<string,double> ows;
		map<string,double> dws;
		map<string,double> ws;
		map<string,double> ws48;

		//per
		map<string,double> per;

		//minutes
		map<string,int> mins;

		double ortgavg(string year);
		double drtgavg(string year);
		double ortgreg(string year);
		double drtgreg(string year);

		double owsavg(string year);
		double dwsavg(string year);
		double owsreg(string year);
		double dwsreg(string year);

		double minsavg(string year);
		double minsreg(string year);
		double MinutesReg(int year);

		double OTest();
		double DTest();
};


#endif /* PLAYERS_H_ */
