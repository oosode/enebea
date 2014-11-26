/*
 * online.cpp
 *
 *  Created on: Jul 14, 2013
 *      Author: oosode
 */

#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <algorithm>
#include <unistd.h>

#include "random.h"
#include "game.h"
#include "read.h"
#include "team.h"
#include "standing.h"
#include "functions.h"
#include "online.h"
#include "players.h"
#include "projection.h"

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::pair;
using std::istreambuf_iterator;
using namespace std;

class Game;
class Team;
class Player;

# define NONNUMBER -13982934874

# define TEAMAVGMPG 241.85
# define TEAMAVGMIN TEAMAVGMPG*82

string fileToString(const string& filename)
{

    ifstream file(filename.c_str());
    if (!file) return "";
    string str(istreambuf_iterator<char>(file),
               (istreambuf_iterator<char>()));
    return str;

}
void StripBballRef(string www, double &homertg, double &awayrtg) {

	string html=fileToString(www);
	if (html=="") { homertg=0.0; awayrtg=0.0; return; }

	size_t four=html.find("Four Factors");
	size_t start=html.find("<tbody>",four);
	size_t end=html.find("</tbody>",start);

	string sub=html.substr(start,end-start);

	size_t last=sub.find("</tr>"); string str2=sub.substr(0,last);
	end=str2.find_last_of("</td>"); string str3=sub.substr(0,end-4);
	start=str3.find_last_of(">"); string str4=str3.substr(start+1);

	awayrtg=atof(str4.c_str());

	last=sub.find_last_of("</tr>");	str2=sub.substr(0,last);
	end=str2.find_last_of("</td>"); str3=sub.substr(0,end-4);
	start=str3.find_last_of(">"); str4=sub.substr(start+1);

	homertg=atof(str4.c_str());

}
void UpdateSchedule(vector<vector<Game> > &G, vector<map<string, Team> > &T, vector<map<string, vector<double> > > &AR,
		            map<string, map<string, vector<double> > > &H, vector<Player> &P,  runparams &parms) {

	clock_t starttime=clock();

	if (parms.debug) { printf("UpdateSchedule starting...\n"); }

	int t; char buffer [80]; string strlist;
	time_t today; int y,m,d; string home;

	double hrtg,artg;

    //Reading schedule dates
	ReadScheduleClearNew(parms,T,G,AR,H,parms.read_season_update);

	//Setting beginning and end dates
	struct tm tmlol;
	memset(&tmlol, 0, sizeof(struct tm));

    strptime(parms.begin_season_update.c_str(), "%Y-%m-%d", &tmlol);
    time_t begin = mktime(&tmlol);

    strptime(parms.finish_season_update.c_str(), "%Y-%m-%d", &tmlol);
    time_t end = mktime(&tmlol);

    //looping through games
	for (int i=0; i<(int)G.front().size(); i++) {

		if (parms.website=="basketball-reference.com") {

			today = G.front().at(i).GameDate;

			if (begin <= today && today <= end) {

				struct tm* oz = localtime(&today);

				y = 1900 + oz->tm_year;
				m = 1 + oz->tm_mon;
				d = oz->tm_mday;

				home=G.front().at(i).HomeTeam; if (home=="BKN") home="BRK";  else if (home=="NOR") home="NOH";

				//download webpage setup
				strlist="curl -s -O http://www.basketball-reference.com/boxscores/";
				t=sprintf(buffer,"%4d%02d%02d0%3s.html",y,m,d,home.c_str());
				strlist.append(buffer);

				printf("     ANALYSIS| Downloading schedule %54s\n", buffer);

				//download webpage
				ifstream ifile(buffer);
				if (!ifile) { usleep(100000); system(strlist.c_str()); }

				StripBballRef(buffer,hrtg,artg);

				if (hrtg==0.0 && artg==0.0) {
					printf("     ANALYSIS| ERROR: No schedule   %54s\n", buffer);
					continue;
				}

				int h,a;
				G.front().at(i).GameFinished(hrtg,artg,h,a);

			}

		} else if (parms.website=="nba.com") {


		}
	}

	printf("\n");

	//output schedule name
	char name [80];
	sprintf(name,"ref.update.%s.%s.csv",parms.begin_season_update.c_str(),parms.finish_season_update.c_str());
	if (!parms.print_season_update.empty()) sprintf(name,"%s",parms.print_season_update.c_str());

	//print updated schedule
	PrintRefSchedule(T,G,name,parms.tpschedule,parms.debug);

	if (parms.debug) { printf("UpdateSchedule exiting...\n\n"); }

	clock_t endtime=clock();
	parms.tpschedule=double(endtime-starttime)/CLOCKS_PER_SEC;

	return;

}
void DownloadSchedule(vector<vector<Game> > &G, vector<map<string, Team> > &T, runparams &parms) {

	clock_t starttime=clock();

	if (parms.debug) { printf("DownloadSchedule starting...\n"); }

	struct tm tmlol;
	memset(&tmlol, 0, sizeof(struct tm));

	time_t game_day;

	int t,id; char buffer [80]; string strlist;

	string game;
	vector<string> v;
	string home, away;
	size_t pos,end;

	if (parms.website=="basketball-reference.com") {

		//download webpage setup
		strlist.append("curl -s -O http://www.basketball-reference.com/leagues/");
		t=sprintf(buffer,"NBA_%d_games.html",parms.season_download_year);
		strlist.append(buffer);

		printf("     ANALYSIS| Downloading schedule %54s\n\n", buffer);

		//download webpage
		ifstream ifile(buffer);
		if (!ifile) system(strlist.c_str());

		//convert page to single string
		string html=fileToString(buffer);

		for (int i=0; i<4000; i++) {

			pos=999999999;
			end=999999999;

			if (i>0) {

				size_t stop=html.find("Playoffs");
				size_t chck=html.find("csk=");

				//stop at playoffs
				if (stop<chck) { break; }

			}

			//away game
			if (i%3==1) {

				pos = html.find("csk=");
				end=html.find(">",pos);

				if (pos > html.length() || end > html.length()) break;

				game=html.substr(pos+5,end-pos-6);
				html=html.substr(pos+20);

				StringExplode(game,".",&v);
				away=v.at(0); //if (away=="BRK") away="BKN"; else if (away=="NOR") away="NOH";

				game=v.at(1).substr(0,7);
				strptime(v.at(1).c_str(), "%Y%m%d", &tmlol);
				game_day = mktime(&tmlol);

				home=v.at(1).substr(9);// if (home=="BRK") home="BKN"; else if (home=="NOR") home="NOH";

				//if team hasn't been initialized
				if (T.front().find(away) == T.front().end()) {

					T.front().insert(pair<string, Team>(away, Team()));
					T.front().find(away)->second.Load(away,"","");

				}

				//game info
				DayInfo dnf;
				dnf.Date = game_day;
				dnf.Opponent = home;
				dnf.IsHome = false;

				T.front().find(away)->second.Schedule.push_back(dnf);

			//home game
			} else if (i%3==2) {

				pos = html.find("csk=");
				end=html.find(">",pos);

				if (pos > html.length() || end > html.length()) break;

				game=html.substr(pos+5,end-pos-6);
				html=html.substr(pos+20);

				StringExplode(game,".",&v);
				home=v.at(0);// if (home=="BRK") home="BKN"; else if (home=="NOR") home="NOH";

				game=v.at(1).substr(0,7);
				strptime(v.at(1).c_str(), "%Y%m%d", &tmlol);
				game_day = mktime(&tmlol);

				//if team hasn't been initialized
				if (T.front().find(home) == T.front().end() ) {

					T.front().insert(pair<string, Team>(home, Team()));
					T.front().find(home)->second.Load(home,"","");

				}

				//game info
				DayInfo dnf;
				dnf.Date = game_day;
				dnf.Opponent = away;
				dnf.IsHome = true;

				T.front().find(home)->second.Schedule.push_back(dnf);

				G.front().push_back(Game());
				G.front().back().Load(&T.front().find(home)->second,&T.front().find(away)->second,id,game_day);
				id+=1;


			} else if (i%3==0) {

				pos = html.find("csk=");
				html=html.substr(pos+20);

			}
		}

	} else if (parms.website=="nba.com") {



	}

	/*
	 *
	 */

	//name schedule file
	char name [80];
	sprintf(name,"ref.%4d.csv",parms.season_download_year);
	if (!parms.print_season_download.empty()) sprintf(name,"%s",parms.print_season_download.c_str());

	//print schedule
	PrintRefSchedule(T,G,name,parms.tpschedule,parms.debug);

	if (parms.debug) { printf("DownloadSchedule exiting...\n\n"); }

	clock_t endtime=clock();
	parms.tupdate=double(endtime-starttime)/CLOCKS_PER_SEC;

	return;

}
void DownloadPlayers(runparams &parms) {

	clock_t starttime=clock();

	if (parms.debug) { printf("DownloadPlayers starting...\n"); }

	//char name [32];
	FILE * pFile;
	pFile = fopen ("players.csv","w");
	if (!parms.print_player_download.empty()) pFile = fopen(parms.print_player_download.c_str(),"w");

	struct tm tmlol;
	memset(&tmlol, 0, sizeof(struct tm));

	time_t game_day;

	int t; char buffer [280]; string strlist;

	string game;
	vector<string> v;
	string home, away; size_t pos,f,g,h;

	if (parms.website=="basketball-reference.com") {

		//no players with last name beginning in x
		string alpha="abcdefghijklmnopqrstuvwyz";
		string val;

		string lastname,firstname;
		string playerid;
		int first_year,last_year;
		string position;
		int height,weight;
		string birthday,school;
		int year,month,day;
		int active;

		int feet,inches;

		for (int abc=0; abc<(int)alpha.size(); abc++) {

			val=alpha.at(abc);

			strlist="";

			t=sprintf(buffer,"curl -s http://www.basketball-reference.com/players/%s/ > ",val.c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%s.html",val.c_str());
			strlist.append(buffer);

			printf("     ANALYSIS| Downloading players  %54s\n", val.c_str());

			ifstream ifile(buffer);
			//if (!ifile) system(strlist.c_str());
			system(strlist.c_str());

			string html=fileToString(buffer);
			pos = html.find("tr  class=");

			while (pos!=string::npos) {

				lastname="NULL";
				firstname="NULL";
				playerid="null00";
				first_year=1900;
				last_year=1900;
				position="NULL";
				height=0;
				weight=0;
				birthday="1900-01-01";
				school="NULL";

				//notice different string identifier than before
				f = html.find("<td align=",pos);
				pos = html.find("<tr  class=",pos);

				//active
				active=0;
				g = html.find("<strong>",f);
				if (g<pos) {

					if (g!=std::string::npos) active=1;

				}

				//playerid
				if (f<pos) {

					f = html.find("/players/",f);
					g = html.find(".html",f);
					playerid = html.substr(f+11,g-f-11);

				}

				//player name
				if (f<pos) {

					f = html.find(".html",f);
					g = html.find("</a>",f);
					string name = html.substr(f+7,g-f-7);
					StringExplode(name," ",&v);
					firstname = v.at(0);
					lastname = "";
					for (int rr=1; rr<(int)v.size(); rr++) { lastname.append(v.at(rr)); lastname.append(" "); }

					lastname.erase(lastname.size()-1);

				}


				// first_year
				f = html.find("<td align",f);
				if (f<pos) {

					f = html.find(">",f);
					g = html.find("</td>",f);
					first_year = atoi(html.substr(f+1,g-f-1).c_str());

				}

				// last_year
				f = html.find("<td align",f);
				if (f<pos) {

					f = html.find(">",f);
					g = html.find("</td>",f);
					last_year = atoi(html.substr(f+1,g-f-1).c_str());

				}

				// position
				f = html.find("<td align",f);
				if (f<pos) {

					f = html.find(">",f);
					g = html.find("</td>",f);
					position = html.substr(f+1,g-f-1);

				}

				// height
				f = html.find("<td align",f);
				if (f<pos) {

					f = html.find(">",f);
					g = html.find("</td>",f);
					string tmpheight = html.substr(f+1,g-f-1);
					StringExplode(tmpheight,"-",&v);
					feet = atoi(v.at(0).c_str())*12;
					inches = atoi(v.at(1).c_str());
					height = feet+inches;

				}

				// weight

				f = html.find("<td align",f);
				if (f<pos) {

					f = html.find(">",f);
					g = html.find("</td>",f);
					weight = atoi(html.substr(f+1,g-f-1).c_str());

				}

				// birthday
				f = html.find("<td align",f);
				if (html.find("/friv/birthdays",f)<pos) {

					f = html.find("<a href=",f);f = html.find(">",f);
					g = html.find("</a>",f);
					birthday = html.substr(f+1,g-f-1);
					strptime(birthday.c_str(),"%B %d, %Y", &tmlol);
					game_day = mktime(&tmlol);

					struct tm* tm = localtime(&game_day);
					year = 1900 + tm->tm_year;
					month = 1 + tm->tm_mon;
					day = tm->tm_mday;

				}


				// school
				f = html.find("<td align",f); //f = html.find("/friv/colleges",f);
				if (html.find("/friv/colleges",f)<pos) {

					//f = html.find("<a href=",f);
					f = html.find("/friv/colleges",f);
					f = html.find(">",f);
					g = html.find("</a>",f);
					school = html.substr(f+1,g-f-1);
					h = school.find(","); if (h!=string::npos) school = school.replace(h,1,"");

				}

				pos = html.find("tr  class=",f);

				fprintf(pFile,"%s,%s,%s,%d,%d,%s,%d,%d,%d-%d-%d,%s,%d,\n",lastname.c_str(),firstname.c_str(),playerid.c_str(),
																		  first_year,last_year,position.c_str(),
																		  height,weight,year,month,day,
																		  school.c_str(),active);

			}
		}

	} else if (parms.website=="nba.com") {



	}

	fclose(pFile);
	printf("\n");

	if (parms.debug) { printf("DownloadPlayers exiting...\n\n"); }

	clock_t endtime=clock();
    parms.tplayers=double(endtime-starttime)/CLOCKS_PER_SEC;

	return;

}
void UpdatePlayers(runparams &parms, vector<Player> &P) {

	clock_t starttime=clock();

	if (parms.debug) { printf("UpdatePlayers starting...\n"); }

	vector<string> inp;
	vector<string> tmp;

	FILE * pFile;
	pFile = fopen ("players.csv","r");
	if (!parms.read_player_update.empty()) { pFile = fopen (parms.read_player_update.c_str(),"r"); }

	FILE * oFile = fopen ("players.update.csv","w");
	if (!parms.print_player_update.empty()) { oFile = fopen (parms.print_player_update.c_str(),"w"); }

	char line[1024];
	char buffer[128];
	char name[128];
	char adv_string[128];

	string html;
	size_t pos,f,g;

	string pid;

	string playername,lname,fname,position,hand,team;

	//stats
	int games,mp,age,ortg,drtg,active;
	double per,ts,efg,orb,drb,trb;
	double ast,stl,blk,tov,usg;
	double ows,dws,ws,ws48;

	ifstream ifile;

	while (fgets(line, sizeof(line), pFile)) {
		inp.push_back(line);
	}

	for (int i=0; i<(int)inp.size(); i++) {

		// first line contains header info
		//if (i==0) continue;

		StringExplode(inp.at(i),",",&tmp);

		if (tmp.at(2).find("NULL")!=string::npos) {

			fprintf(stderr, "error: no playerid. skipping player.\n\n");
			continue;
		}

		if (i%15==1) {

			fprintf(oFile,"LASTNAME,FIRSTNAME,PID,FIRSTYR,LASTYR,POSITION,HANDED,HEIGHT,WEIGHT,BIRTHDATE,SCHOOL,");
			fprintf(oFile,"ACTIVE,TEAM,MINUTES,EFG,TS,DRB,ORB,TRB,AST,STL,BLK,TOV,USG,ORTG,DRTG,OWS,DWS,WS48,WS,PER,\n");

		}

		pid=tmp.at(2);
		string alpha=pid.substr(0,1);

		sprintf(name,"%s %s",tmp.at(1).c_str(),tmp.at(0).c_str());
		printf("     ANALYSIS| Updating player       %53s\n", name);

		sprintf(buffer,"curl -s -O http://www.basketball-reference.com/players/%s/%s.html",alpha.c_str(),pid.c_str());

		usleep(1);

		pid = pid.append(".html");
		ifstream ifile(pid.c_str());

		if (!ifile) { usleep(100000); system(buffer); }

		html=fileToString(pid);

		// player name
		pos = html.find("<h1>");
		f = html.find("</h1>",pos);
		playername = html.substr(pos+4,f-pos-4);

		// position
		pos = html.find("Position:",pos);
		pos = html.find("</span> ",pos);
		g = html.find("&nbsp;&#9642;&nbsp;",pos);
		position = html.substr(pos+8,g-pos-8);

		// handed
		pos = html.find("Shoots:",pos);
		pos = html.find("</span> ",pos);
		g = html.find("<br>",pos);
		hand = html.substr(pos+8,g-pos-8);

		/*advanced stats*/

		//
		pos = html.find("Advanced</h2>",pos);

		// initialize position of advanced stats positions
		sprintf(adv_string,"advanced.%d",parms.player_update_year);

		active = 0;
		if (html.find(adv_string)!=string::npos) {

			pos = html.find(adv_string,pos);
			pos = html.find("</a></td>",pos);
			active = 1;

		}

		// if no stats for year do career instead
		else pos = html.find("Career",pos);


		// scrub for advanced stats

		// age
		pos = html.find("<td align=",pos);
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		age = atoi(html.substr(f+1,g-f-1).c_str());

		pos = g;

		// team
		g = html.find("</td>",pos+1);
		if (html.rfind("</a>",g,4)==g-4) g = html.rfind("</a>",g,4);
		f = html.rfind(">",g);
		team = html.substr(f+1,g-f-1);
		pos = g;

		// league
		pos = html.find("<td align=",pos);
		pos = html.find("</td>",pos);

		// position
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		position = html.substr(f+1,g-f-1);
		pos = g;

		// games
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		games = atoi(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// minutes played
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		mp = atoi(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// per
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		per = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// true shooting percentage
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		ts = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// effective field goal percentage
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		efg = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// offensive rebounding rate
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		orb = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// defensive rebounding rate
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		drb = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// total rebounding rate
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		trb = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// assist rate percentage
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		ast = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// steal rate percentage
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		stl = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// block rate percentage
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		blk = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// turnover rate percentage
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		tov = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// usage rate percentage
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		usg = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// offensive rating
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		ortg = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// defensive rating
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		drtg = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// offensive win shares
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		ows = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// defensive win shares
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		dws = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// win shares
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		ws = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		// win shares per 48
		g = html.find("</td>",pos+1);
		f = html.rfind(">",g);
		ws48 = atof(html.substr(f+1,g-f-1).c_str());
		pos = g;

		Player p;

		p.FullName=playername;

		p.CurrentTeam=team;

		p.eFG=efg; p.TS=ts; p.Minutes=mp;

		p.DRB=drb; p.ORB=orb; p.TRB=trb;

		p.AST=ast; p.STL=stl; p.BLK=blk; p.TOV=tov;

		p.Usage=usg;

		p.ORtg=ortg; p.DRtg=drtg;

		p.OWS=ows; p.DWS=dws;
		p.WS48=ws48; p.WS=ws;

		P.push_back(p);

		//fprintf(oFile,"LASTNAME,FIRSTNAME,PID,FIRSTYR,LASTYR,POSITION,HANDED,HEIGHT,WEIGHT,BIRTHDATE,SCHOOL,");
		//fprintf(oFile,"ACTIVE,TEAM,EFG,TS,DRB,ORB,TRB,AST,STL,BLK,TOV,USG,ORTG,DRTG,OWS,DWS,WS48,WS,\n");

		fprintf(oFile,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",
				tmp.at(0).c_str(),tmp.at(1).c_str(),tmp.at(2).c_str(),tmp.at(3).c_str(),tmp.at(4).c_str(),position.c_str(),
				hand.substr(0,1).c_str(),tmp.at(6).c_str(),tmp.at(7).c_str(),tmp.at(8).c_str(),tmp.at(9).c_str());

		fprintf(oFile,"%d,%s,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%f,%f,%f,%f,%f,\n",
				active,team.c_str(),mp,efg,ts,drb,orb,trb,ast,stl,blk,tov,
				usg,ortg,drtg,ows,dws,ws48,ws,per);

	}
	printf("\n");

	fclose(oFile);
	fclose(pFile);

	if (parms.debug) { printf("UpdatePlayers exiting...\n\n"); }

	clock_t endtime=clock();
    parms.tuplayers=double(endtime-starttime)/CLOCKS_PER_SEC;

	return;

}
void UpdatePlayersNew(runparams &parms, vector<Player> &P) {

	clock_t starttime=clock();

	if (parms.debug) { printf("UpdatePlayers starting...\n"); }

	vector<string> inp;
	vector<string> tmp;

	FILE * pFile;
	pFile = fopen ("players.csv","r");
	if (!parms.read_player_update.empty()) { pFile = fopen (parms.read_player_update.c_str(),"r"); }

	FILE * oFile = fopen ("players.update.csv","w");
	if (!parms.print_player_update.empty()) { oFile = fopen (parms.print_player_update.c_str(),"w"); }

	char line[1024];
	char buffer[128];
	char name[128];
	//char adv_string[128];
	char yr[32];

	string html;
	size_t pos,f,g,car;

	string pid;
	string year;

	string playername,lname,fname,position,hand,team;

	//stats
	int games,gs,mp,age,ortg,drtg;//active;
	double per,ts,efg,orb,drb,trb;
	double ast,stl,blk,tov,usg;
	double ows,dws,ws,ws48;

	double fg,fga,fgp;
	double ft,fta,ftp,ftr;
	double threeg,threega,threegp,threegr;
	double twog,twoga,twogp;
	double fouls,points;

	ifstream ifile;

	while (fgets(line, sizeof(line), pFile)) {
		inp.push_back(line);
	}

	for (int i=0; i<(int)inp.size(); i++) {

		// first line contains header info
		//if (i==0) continue;

		StringExplode(inp.at(i),",",&tmp);

		if (tmp.at(2).find("NULL")!=string::npos) {

			fprintf(stderr, "error: no playerid. skipping player.\n\n");
			continue;
		}

		pid=tmp.at(2);
		string alpha=pid.substr(0,1);

		sprintf(name,"%s %s",tmp.at(1).c_str(),tmp.at(0).c_str());
		printf("     ANALYSIS| Updating player       %53s\n", name);

		sprintf(buffer,"curl -s -O http://www.basketball-reference.com/players/%s/%s.html",alpha.c_str(),pid.c_str());

		usleep(1);

		pid = pid.append(".html");
		ifstream ifile(pid.c_str());

		if (!ifile) { usleep(100000); system(buffer); }
		//usleep(100000); system(buffer);

		html=fileToString(pid);

		// player name
		pos = html.find("<h1>");
		f = html.find("</h1>",pos);
		playername = html.substr(pos+4,f-pos-4);

		// position
		pos = html.find("Position:",pos);
		pos = html.find("</span> ",pos);
		g = html.find("&nbsp;&#9642;&nbsp;",pos);
		position = html.substr(pos+8,g-pos-8);

		// handed
		pos = html.find("Shoots:",pos);
		pos = html.find("</span> ",pos);
		g = html.find("<br>",pos);
		hand = html.substr(pos+8,g-pos-8);

		//fprintf(oFile,"LASTNAME,FIRSTNAME,PID,FIRSTYR,LASTYR,POSITION,HANDED,HEIGHT,WEIGHT,BIRTHDATE,SCHOOL,");
		fprintf(oFile,"lastname=%s,firstname=%s,bballref=%s,hand=%s,height=%s,weight=%s,",
				tmp.at(0).c_str(),tmp.at(1).c_str(),tmp.at(2).c_str(),hand.substr(0,1).c_str(),
				tmp.at(6).c_str(),tmp.at(7).c_str());

		// ** total stats **//
		pos = html.find("Totals</h2>",pos);
		pos = html.find("totals.",pos);

		while (pos!=string::npos && pos<html.find(">Per Game</h2>")) {

			//cout << pos << " " << html.find(">Per Game</h2>") << endl;

			f = pos+7;
			g = f+4;
			year = html.substr(f,4);
			sprintf(yr,"%s",year.c_str());

			//cout << year << endl;
			//skip ahead
			pos = g;
			//pos = html.find("</a></td>",pos);
			pos = html.find("</td>",pos);

			//age
			pos = html.find("<td align=",pos);
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			age = atoi(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"age.%s=%d,",yr,age);

			pos = g;

			// team
			g = html.find("</td>",pos+1);
			if (html.rfind("</a>",g,4)==g-4) g = html.rfind("</a>",g,4);
			f = html.rfind(">",g);
			team = html.substr(f+1,g-f-1);
			fprintf(oFile,"team.%s=%s,",yr,team.c_str());

			pos = g;

			// league
			pos = html.find("<td align=",pos);
			pos = html.find("</td>",pos);

			// position
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			position = html.substr(f+1,g-f-1);
			fprintf(oFile,"pos.%s=%s,",yr,position.c_str());

			pos = g;

			// games
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			games = atoi(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"games.%s=%d,",yr,games);

			pos = g;

			// games started
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			gs = atoi(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"games_started.%s=%d,",yr,gs);

			pos = g;

			// minutes played
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			mp = atoi(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"mins.%s=%d,",yr,mp);

			pos = g;

			// field goals
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			fg = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"fg.%s=%f,",yr,fg);

			pos = g;

			// field goals attempts
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			fga = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"fga.%s=%f,",yr,fga);

			pos = g;

			// field goal percentage
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			fgp = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"fgp.%s=%f,",yr,fgp);

			pos = g;

			// three point field goals
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			threeg = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"threeg.%s=%f,",yr,threeg);

			pos = g;

			// three point field goal attempts
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			threega = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"threega.%s=%f,",yr,threega);

			pos = g;

			// three point field goal percentage
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			threegp = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"threegp.%s=%f,",yr,threegp);

			pos = g;

			// two point field goals
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			twog = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"twog.%s=%f,",yr,twog);

			pos = g;

			// two point field goal attempts
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			twoga = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"twoga.%s=%f,",yr,twoga);

			pos = g;

			// two point field goals percentage
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			twogp = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"twogp.%s=%f,",yr,twogp);

			pos = g;

			// free throws
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			ft = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"ft.%s=%f,",yr,ft);

			pos = g;

			// free throw attempts
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			fta = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"fta.%s=%f,",yr,fta);

			pos = g;

			// free throw percentage
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			ftp = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"ftp.%s=%f,",yr,ftp);

			pos = g;

			// offensive rebounds
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			orb = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"orb_tot.%s=%f,",yr,orb);

			pos = g;

			// defensive rebounds
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			drb = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"drb_tot.%s=%f,",yr,drb);

			pos = g;

			// total rebounds
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			trb = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"trb_tot.%s=%f,",yr,trb);

			pos = g;

			// assists
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			ast = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"ast_tot.%s=%f,",yr,ast);

			pos = g;

			// steals
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			stl = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"stl_tot.%s=%f,",yr,stl);

			pos = g;

			// blocks
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			blk = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"blk_tot.%s=%f,",yr,blk);

			pos = g;

			// turnovers
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			tov = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"tov_tot.%s=%f,",yr,tov);

			pos = g;

			// fouls
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			fouls = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"foul_tot.%s=%f,",yr,fouls);

			pos = g;

			// points
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			points = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"points.%s=%f,",yr,points);

			pos = g;

			car = html.find(">Career</td>",pos);
			pos = html.find("totals.",pos);

			if (pos>car) { pos=car; break; }

		}


		// ** advanced stats **//
		pos = html.find("Advanced</h2>",pos);
		pos = html.find("advanced.",pos);

		while (pos!=string::npos && pos<html.find(">Playoffs Advanced</h2>")) {

			//cout << pos << " " << html.find(">Playoffs Advanced</h2>") << endl;

			f = pos+9;
			g = f+4;
			year = html.substr(f,4);
			sprintf(yr,"%s",year.c_str());

			//cout << year << endl;
			//skip ahead
			pos = g;
			//pos = html.find("</a></td>",pos);
			pos = html.find("</td>",pos);

			//age
			pos = html.find("<td align=",pos);
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			age = atoi(html.substr(f+1,g-f-1).c_str());
			//fprintf(oFile,"age.%s=%d,",yr,age);

			pos = g;

			// team
			g = html.find("</td>",pos+1);
			if (html.rfind("</a>",g,4)==g-4) g = html.rfind("</a>",g,4);
			f = html.rfind(">",g);
			team = html.substr(f+1,g-f-1);
			fprintf(oFile,"team.%s=%s,",yr,team.c_str());

			pos = g;

			// league
			pos = html.find("<td align=",pos);
			pos = html.find("</td>",pos);

			// position
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			position = html.substr(f+1,g-f-1);
			//fprintf(oFile,"pos.%s=%s,",yr,position.c_str());

			pos = g;

			// games
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			games = atoi(html.substr(f+1,g-f-1).c_str());
			//fprintf(oFile,"games.%s=%d,",yr,games);

			pos = g;

			// minutes played
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			mp = atoi(html.substr(f+1,g-f-1).c_str());
			//fprintf(oFile,"mins.%s=%d,",yr,mp);

			pos = g;

			// per
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			per = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"per.%s=%f,",yr,per);

			pos = g;

			// true shooting percentage
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			ts = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"ts.%s=%f,",yr,ts);

			pos = g;

			// effective field goal percentage
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			efg = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"efg.%s=%f,",yr,efg);

			pos = g;

			// free throw rate
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			efg = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"ftr.%s=%f,",yr,efg);

			pos = g;

			// three point rate
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			efg = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"threegr.%s=%f,",yr,efg);

			pos = g;

			// offensive rebounding rate
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			orb = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"orb_adv.%s=%f,",yr,orb);

			pos = g;

			// defensive rebounding rate
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			drb = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"drb_adv.%s=%f,",yr,drb);

			pos = g;

			// total rebounding rate
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			trb = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"trb_adv.%s=%f,",yr,trb);

			pos = g;

			// assist rate percentage
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			ast = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"ast_adv.%s=%f,",yr,ast);

			pos = g;

			// steal rate percentage
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			stl = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"stl_adv.%s=%f,",yr,stl);

			pos = g;

			// block rate percentage
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			blk = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"blk_adv.%s=%f,",yr,blk);

			pos = g;

			// turnover rate percentage
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			tov = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"tov_adv.%s=%f,",yr,tov);

			pos = g;

			// usage rate percentage
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			usg = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"usg.%s=%f,",yr,usg);

			pos = g;

			// offensive rating
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			ortg = atoi(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"ortg.%s=%d,",yr,ortg);

			pos = g;

			// defensive rating
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			drtg = atoi(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"drtg.%s=%d,",yr,drtg);

			pos = g;

			// offensive win shares
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			ows = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"ows.%s=%f,",yr,ows);

			pos = g;

			// defensive win shares
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			dws = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"dws.%s=%f,",yr,dws);

			pos = g;

			// win shares
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			ws = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"ws.%s=%f,",yr,ws);

			pos = g;

			// win shares per 48
			g = html.find("</td>",pos+1);
			f = html.rfind(">",g);
			ws48 = atof(html.substr(f+1,g-f-1).c_str());
			fprintf(oFile,"ws48.%s=%f,",yr,ws48);

			pos = g;

			car = html.find(">Career</td>",pos);
			pos = html.find("advanced.",pos);

			if (pos>car) { pos=car; break; }

		}

		fprintf(oFile,"\n");

	}
	printf("\n");

	fclose(oFile);
	fclose(pFile);

	if (parms.debug) { printf("UpdatePlayers exiting...\n\n"); }

	clock_t endtime=clock();
    parms.tuplayers=double(endtime-starttime)/CLOCKS_PER_SEC;

	return;

}

void AnalysisPlayers(runparams &parms, vector<Player> &P) {

	clock_t starttime=clock();

	if (parms.debug) { printf("AnalysisPlayers starting...\n"); }

	double s;
	int count;

	FILE * oFile = fopen ("players.analysis.csv","w");
	if (!parms.print_player_analysis.empty()) { oFile = fopen (parms.print_player_analysis.c_str(),"w"); }

	ReadPlayerRestartNew(parms, P, parms.read_player_analysis);

	for (int i=0; i<(int)P.size(); i++) {

		fprintf(oFile,"%15s,%15s,",P.at(i).LastName.c_str(),P.at(i).FirstName.c_str());
		count=0;

		for (int y=1900; y<=2014; y++) {

			s=P.at(i).Stat(y,parms.player_analysis_stat);

			if (s!=NONNUMBER) {

				if (count>=parms.begin_player_analysis && count<=parms.end_player_analysis) {

					cout << "----------------------------- " << s << endl;
					fprintf(oFile,"%15.10f,",s);

				}
				count++;
			}
		}
		fprintf(oFile,"\n");
	}

	printf("\n");

	fclose(oFile);

	if (parms.debug) { printf("AnalysisPlayers exiting...\n\n"); }

	clock_t endtime=clock();
    parms.tuplayers=double(endtime-starttime)/CLOCKS_PER_SEC;

	return;

}

void DownloadTeam(runparams &parms, vector<Player> &P) {

	clock_t starttime=clock();

	if (parms.debug) { printf("DownloadTeam starting...\n"); }

	vector<string> inp;
	vector<string> tmp;

	if (parms.read_team_download.empty()) { parms.read_team_download="players.csv"; }

	FILE * oFile = fopen ("teams.csv","w");
	if (!parms.print_team_download.empty()) { oFile = fopen (parms.print_team_download.c_str(),"w"); }

	char buffer[128];

	char yr[32];
	char nm[128];
	char mm[32];

	string html,teamhtml;
	size_t pos,f,g;
	size_t tpos,tf,tg;

	string pid;
	string team;

	int i;

	//read players
	ReadPlayerRestartNew(parms, P, parms.read_team_download);

	if (parms.website=="basketball-reference.com") {

		sprintf(buffer,"curl -s -O http://www.basketball-reference.com/leagues/NBA_%d.html",parms.team_download_year);
		system(buffer);

		sprintf(buffer,"NBA_%d.html",parms.team_download_year);
		html=fileToString(buffer);

		pos = html.find("Team Stats</h2>");
		pos = html.find("<td align=",pos);

		while (pos<html.find("Opponent Stats</h2>")) {

			sprintf(yr,"/%d.html",parms.team_download_year);
			g = html.find(yr,pos);
			f = html.rfind("/teams/",g);
			team = html.substr(f+7,g-f-7);

			sprintf(nm,"curl -s http://www.basketball-reference.com/teams/%s/%d.html > %s%d.html",team.c_str(),parms.team_download_year,team.c_str(),parms.team_download_year);
	     	sprintf(mm,"%s%d.html",team.c_str(),parms.team_download_year);

	     	printf("     ANALYSIS| Downloading team      %53s\n", team.c_str());

			ifstream ifile(mm);
			if (!ifile) { usleep(1000000); system(nm); }


			fprintf(oFile,"team,%s,\n",team.c_str());
			teamhtml=fileToString(mm);

			tpos = teamhtml.find("Roster</h2>");

			while (tpos<teamhtml.find("Team and Opponent Stats</h2>")) {

				tg = teamhtml.find(".html",tpos);
				tf = teamhtml.rfind("/players/",tg);
				//cout << tg << " " << tf << endl;

				pid = teamhtml.substr(tf+11,tg-tf-11);

				for (i=0; i<(int)P.size(); i++) {

					//printf("%s %s\n", pid.c_str(),P.at(i).bballref_id.c_str());
					if (pid==P.at(i).bballref_id) 	{

						fprintf(oFile,"player,%s,%s,%s\n",P.at(i).LastName.c_str(),P.at(i).FirstName.c_str(),pid.c_str());
						//printf("%s,%s,%s\n",P.at(i).LastName.c_str(),P.at(i).FirstName.c_str(),pid.c_str());
						tpos = teamhtml.find(".html",tg+1);
						break;
					}
				}
			}

			fprintf(oFile,"\n");

			pos = html.find(yr,g+1);
		}


	}
	printf("\n");

	fclose(oFile);

	if (parms.debug) { printf("DownloadTeam exiting...\n\n"); }

	clock_t endtime=clock();
    parms.tuplayers=double(endtime-starttime)/CLOCKS_PER_SEC;
    exit(0);
	return;

}
void UpdateTeam(runparams &parms, vector<Player> &P) {

	clock_t starttime=clock();

	if (parms.debug) { printf("UpdateTeam starting...\n"); }

	TeamProjection(parms,P);

	//if (parms.team_update_type=="ws") TeamWinShares(parms,P);
	//else if (parms.team_update_type=="rating") TeamRating(parms,P);
	//else if (parms.team_update_type=="ws_rating") TeamWinSharesRating(parms,P);

	if (parms.debug) { printf("UpdateTeam exiting...\n\n"); }

	clock_t endtime=clock();
    parms.tuplayers=double(endtime-starttime)/CLOCKS_PER_SEC;

	return;

}
void TeamWinShares(runparams &parms, vector<Player> &P) {

	if (parms.read_team_update_team.empty()) { parms.read_team_update_team="teams.csv"; }

	FILE * oFile = fopen ("teams.update.csv","w");
	if (!parms.print_team_update.empty()) { oFile = fopen (parms.print_team_update.c_str(),"w"); }

	ReadPlayerRestartNew(parms, P, parms.read_team_update_player);

	map<string,vector<double> > teams;

	vector<double> vals(2,0.0);
	vector<string> tmp;
	string line;

	double minutes;
	double offrtg;
	double defrtg;

	double pmins;
	double poff;
	double pdef;

	char year[8];
	sprintf(year,"%d",parms.team_update_year);

	int num;

	ifstream file0(parms.read_team_update_team.c_str());

	// Find year for standings
	if (file0.is_open()) {
	    while (file0.good()) {

	    	getline(file0,line);
	    	StringExplode(line,",",&tmp);

	    	if (tmp.at(0)=="team") {

	    		string team = tmp.at(1);
	    		printf("     ANALYSIS| Updating team         %53s\n", team.c_str());

	    		getline(file0,line);
	    		StringExplode(line,",",&tmp);

	    		offrtg=0.0;
	    		defrtg=0.0;
	    		minutes=0;

	    		num=0;

	    		vals[0]=0.0;
	    		vals[1]=0.0;

	    		while (tmp.at(0)=="player") {

	    			string pid=tmp.at(3);

	    			pmins=0.0;
	    			poff=0.0;
	    			pdef=0.0;

	    			for (int i=0; i<(int)P.size(); i++) {

	    				if (P.at(i).bballref_id==pid) {

	    					pmins=P.at(i).minsreg(year);
	    					poff=P.at(i).owsreg(year);
	    					pdef=P.at(i).dwsreg(year);

	    					printf("%15s %15.10f %15.10f %15.10f\n",P.at(i).LastName.c_str(),pmins,poff,pdef);

	    					if (pmins==0) { pmins=500; //poff=0.1; pdef=0.1;

	    					}

	    					minutes+=pmins;
	    					offrtg+=poff;///pmins;
	    					defrtg+=pdef;///pmins;

	    					break;
	    				}
	    			}

	    			getline(file0,line);
	    			StringExplode(line,",",&tmp);

	    		}

	    		vals[0]=offrtg*48*82*5/minutes;
	    		vals[1]=defrtg*48*82*5/minutes;

	    		printf("%10.5f %10.5f\n\n",offrtg,defrtg);

	    		teams.insert(pair<string,vector<double> >(team,vals));

	    	}
	    }
	}

	double average_off=0.0;
	double average_def=0.0;

	int count=0;

	typedef map<string, vector<double> >::iterator it_type;
	for (it_type iterator = teams.begin(); iterator != teams.end(); iterator++) {

		average_off += iterator->second[0];
		average_def += iterator->second[1];

		count += 1;

	}

	average_off = average_off/double(count);
	average_def = average_def/double(count);

	typedef map<string, vector<double> >::iterator it_type;
	for (it_type iterator = teams.begin(); iterator != teams.end(); iterator++) {

		printf("%s,%15.10f,%15.10f,%15.10f,\n",iterator->first.c_str(),iterator->second[0],iterator->second[1],iterator->second[0]-iterator->second[1]);
		iterator->second[0] -= average_off;
		iterator->second[1] -= average_def;

		if (iterator->second[0]>=0.0) { iterator->second[0] = pow(iterator->second[0],0.60); }
		else { iterator->second[0] = -1*pow(-1*iterator->second[0],0.60); }

		if (iterator->second[1]>=0.0) { iterator->second[1] = pow(iterator->second[1],0.60); }
		else { iterator->second[1] = -1*pow(-1*iterator->second[1],0.60); }

		iterator->second[0] += 105.0;
		iterator->second[1] = 105.0 - iterator->second[1];

		double offr = iterator->second[0];
		double defr = iterator->second[1];
		double diff = offr-defr;

		fprintf(oFile,"%s,%15.10f,%15.10f,%15.10f,\n",iterator->first.c_str(),offr,defr,diff);
	}

	printf("\n");

	fclose(oFile);

}
void TeamRating(runparams &parms, vector<Player> &P) {

	if (parms.read_team_update_team.empty()) { parms.read_team_update_team="teams.csv"; }

	FILE * oFile = fopen ("teams.update.csv","w");
	if (!parms.print_team_update.empty()) { oFile = fopen (parms.print_team_update.c_str(),"w"); }

	ReadPlayerRestartNew(parms, P, parms.read_team_update_player);

	map<string,vector<double> > teams;

	vector<string> tmp;
	string line;

	double minutes;
	double offrtg;
	double defrtg;

	double pmins;
	double poff;
	double pdef;

	char year[8];
	sprintf(year,"%d",parms.team_update_year);

	int num;

	ifstream file0(parms.read_team_update_team.c_str());

	// Find year for standings
	if (file0.is_open()) {
	    while (file0.good()) {

	    	getline(file0,line);
	    	StringExplode(line,",",&tmp);

	    	if (tmp.at(0)=="team") {

	    		string team = tmp.at(1);
	    		printf("     ANALYSIS| Updating team         %53s\n", team.c_str());

	    		getline(file0,line);
	    		StringExplode(line,",",&tmp);

	    		offrtg=0.0;
	    		defrtg=0.0;
	    		minutes=0;

	    		num=0;

	    		while (tmp.at(0)=="player") {

	    			string pid=tmp.at(3);

	    			pmins=0.0;
	    			poff=0.0;
	    			pdef=0.0;

	    			for (int i=0; i<(int)P.size(); i++) {

	    				if (P.at(i).bballref_id==pid) {

	    					pmins=P.at(i).minsreg(year);
	    					poff=P.at(i).ortgreg(year);
	    					pdef=P.at(i).drtgreg(year);

	    					printf("%20s %20.10f %20.10f\n",P.at(i).LastName.c_str(),poff,pdef);

	    					if (pmins<=0.0) { pmins=500; poff=100; pdef=110; }

	    					//offrtg+=poff;
	    					//defrtg+=pdef;

	    					minutes+=pmins;
	    					offrtg+=poff*pmins;
	    					defrtg+=pdef*pmins;

	    					break;
	    				}
	    			}

	    			getline(file0,line);
	    			StringExplode(line,",",&tmp);

	    		}

	    		double offr=offrtg/minutes;
	    		double defr=defrtg/minutes;
	    		double diff=offr-defr;

	    		fprintf(oFile,"%s,%15.10f,%15.10f,%15.10f,\n",team.c_str(),offr,defr,diff);

	    	}
	    }
	}

	printf("\n");

	fclose(oFile);

}
void TeamWinSharesRating(runparams &parms, vector<Player> &P) {

	if (parms.read_team_update_team.empty()) { parms.read_team_update_team="teams.csv"; }

	FILE * oFile = fopen ("teams.update.csv","w");
	if (!parms.print_team_update.empty()) { oFile = fopen (parms.print_team_update.c_str(),"w"); }

	ReadPlayerRestartNew(parms, P, parms.read_team_update_player);

	map<string,vector<double> > teams;

	vector<double> vals(4,0.0);
	vector<string> tmp;
	string line;

	double minutes;
	double offrtg;
	double defrtg;
	double offws;
	double defws;

	double pmins;
	double poff;
	double pdef;

	char year[8];
	sprintf(year,"%d",parms.team_update_year);


	int num;

	ifstream file0(parms.read_team_update_team.c_str());

	// Find year for standings
	if (file0.is_open()) {
	    while (file0.good()) {

	    	getline(file0,line);
	    	StringExplode(line,",",&tmp);

	    	if (tmp.at(0)=="team") {

	    		string team = tmp.at(1);
	    		printf("     ANALYSIS| Updating team         %53s\n", team.c_str());

	    		getline(file0,line);
	    		StringExplode(line,",",&tmp);

	    		offrtg=0.0;
	    		defrtg=0.0;
	    		offws=0.0;
	    		defws=0.0;
	    		minutes=0;

	    		num=0;

	    		vals[0]=0.0;
	    		vals[1]=0.0;

	    		while (tmp.at(0)=="player") {

	    			string pid=tmp.at(3);

	    			pmins=0.0;
	    			poff=0.0;
	    			pdef=0.0;

	    			for (int i=0; i<(int)P.size(); i++) {

	    				if (P.at(i).bballref_id==pid) {

	    					pmins=P.at(i).minsreg(year);
	    					poff=P.at(i).ortgreg(year);
	    					pdef=P.at(i).drtgreg(year);

	    					minutes+=pmins;
	    					offrtg+=poff;
	    					defrtg+=pdef;

	    	    			pmins=0.0;
	    	    			poff=0.0;
	    	    			pdef=0.0;

	    					pmins=P.at(i).minsreg(year);
	    					poff=P.at(i).owsreg(year);
	    					pdef=P.at(i).dwsreg(year);

	    					if (pmins==0) break;

	    					offws+=poff;///pmins;
	    					defws+=pdef;///pmins;

	    					break;
	    				}
	    			}

	    			getline(file0,line);
	    			StringExplode(line,",",&tmp);

	    		}

	    		vals[0]=offws;
	    		vals[1]=defws;
	    		vals[2]=offrtg/minutes;
	    		vals[3]=defrtg/minutes;

	    		teams.insert(pair<string,vector<double> >(team,vals));

	    	}
	    }
	}

	printf("\n");

	double average_off=0.0;
	double average_def=0.0;

	int count=0;

	typedef map<string, vector<double> >::iterator it_type;
	for (it_type iterator = teams.begin(); iterator != teams.end(); iterator++) {

		average_off += iterator->second[0];
		average_def += iterator->second[1];

		count += 1;

	}

	average_off = average_off/double(count);
	average_def = average_def/double(count);

	typedef map<string, vector<double> >::iterator it_type;
	for (it_type iterator = teams.begin(); iterator != teams.end(); iterator++) {

		iterator->second[0] -= average_off;
		iterator->second[1] -= average_def;

		if (iterator->second[0]>=0.0) { iterator->second[0] = sqrt(iterator->second[0]); }
		else { iterator->second[0] = -1*sqrt(-1*iterator->second[0]); }

		if (iterator->second[1]>=0.0) { iterator->second[1] = sqrt(iterator->second[1]); }
		else { iterator->second[1] = -1*sqrt(-1*iterator->second[1]); }

		iterator->second[0] += 105.0;
		iterator->second[1] = 105.0 - iterator->second[1];

		double offr = (iterator->second[0] + iterator->second[2])/2.0;
		double defr = (iterator->second[1] + iterator->second[3])/2.0;
		double diff = offr-defr;

		fprintf(oFile,"%s,%15.10f,%15.10f,%15.10f,\n",iterator->first.c_str(),offr,defr,diff);
	}

	fclose(oFile);

}
void TeamNew(runparams &parms, vector<Player> &P) {

	if (parms.read_team_update_team.empty()) { parms.read_team_update_team="teams.csv"; }

	FILE * oFile = fopen ("teams.update.csv","w");
	if (!parms.print_team_update.empty()) { oFile = fopen (parms.print_team_update.c_str(),"w"); }

	ReadPlayerRestartNew(parms, P, parms.read_team_update_player);

	map<string,vector<double> > teams;

	vector<double> vals(4,0.0);
	vector<string> tmp;
	string line;

	map<string,double> minutes;
	map<string,double> points;
	map<string,double> fga;
	map<string,double> turnovers;
	map<string,double> oreb;
	map<string,double> fta;

	map<string,double> threepa;

	double pmins;
	double poff;
	double pdef;

	char year[8];
	sprintf(year,"%d",parms.team_update_year);

	double hm3,hm2,hm1,hf3,hf2,hf1,age;

	int num;

	double m3=LeagueAVG(parms,P,"mins",2013);
	double f3=LeagueAVG(parms,P,"fta",2013);

	double m2=LeagueAVG(parms,P,"mins",2012);
	double f2=LeagueAVG(parms,P,"fta",2012);

	double m1=LeagueAVG(parms,P,"mins",2011);
	double f1=LeagueAVG(parms,P,"fta",2011);

	ifstream file0(parms.read_team_update_team.c_str());

	// Find year for standings
	if (file0.is_open()) {
	    while (file0.good()) {

	    	getline(file0,line);
	    	StringExplode(line,",",&tmp);

	    	if (tmp.at(0)=="team") {

	    		string team = tmp.at(1);
	    		printf("     ANALYSIS| Updating team         %53s\n", team.c_str());

	    		getline(file0,line);
	    		StringExplode(line,",",&tmp);

	    		minutes.clear();
	    		points.clear();
	    		fga.clear();
	    		turnovers.clear();
	    		oreb.clear();
	    		fta.clear();

	    		threepa.clear();

	    		while (tmp.at(0)=="player") {

	    			string pid=tmp.at(3);

	    			pmins=0.0;
	    			poff=0.0;
	    			pdef=0.0;

	    			for (int i=0; i<(int)P.size(); i++) {

	    				if (P.at(i).bballref_id==pid) {

	    					minutes[pid]=P.at(i).Stat(parms.team_update_year,"mins");

	    					double pstat=SPS(P.at(i),"fta",2013,m3,m2,m1,f3,f2,f1);

	    					if (P.at(i).bballref_id=="anthoca01") {

	    						hm3=P.at(i).Stat(2013,"mins");
	    						hm2=P.at(i).Stat(2012,"mins");
	    						hm1=P.at(i).Stat(2011,"mins");

	    						hf3=P.at(i).Stat(2013,"fga");
	    						hf2=P.at(i).Stat(2012,"fga");
	    					    hf1=P.at(i).Stat(2011,"fga");

	    					    age=P.at(i).Stat(2013,"age");
	    					}

	    					break;
	    				}
	    			}

	    			getline(file0,line);
	    			StringExplode(line,",",&tmp);

	    		}

	    		double m3=LeagueAVG(parms,P,"mins",2013);
	    		double f3=LeagueAVG(parms,P,"fga",2013);

	    		double m2=LeagueAVG(parms,P,"mins",2012);
	    		double f2=LeagueAVG(parms,P,"fga",2012);

	    		double m1=LeagueAVG(parms,P,"mins",2011);
	    		double f1=LeagueAVG(parms,P,"fga",2011);


	    		double rrr= 6.0*hm3*f3/m3+3.0*hm2*f2/m2+1.0*hm1*f1/m1;

	    		double hm=6.0*hm3+3.0*hm2+1.0*hm1;
	    		double hf=6.0*hf3+3.0*hf2+1.0*hf1;

	    		double mm=1000*rrr/hm;

	    		double finish=36*(mm+hf)/(hm+1000);

	    		if (age>28) { cout << (1+ (28.0-age-1)*0.002)*finish << endl; }
	    		else { cout << (1 + (28.0-age-1)*0.004)*finish << endl; }

	    		while (SUM(minutes)+10<TEAMAVGMIN || SUM(minutes)-10>TEAMAVGMIN) {

					map<string,double>::iterator iter;
					for (iter=minutes.begin(); iter!=minutes.end(); iter++) {

						double team_min=SUM(minutes);
						double tmp_min=TEAMAVGMIN*(iter->second)/team_min;

						//BUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUG
						//needs to be average of actual data for total minutes played
						if (tmp_min>42.0*82) tmp_min=42.0*82;

						//save temporary player minutes to minutes map
						iter->second=tmp_min;
						//printf("%10s %s %15.10f\n",team.c_str(),iter->first.c_str(),tmp_min);

					}

	    		}
	    		//printf("total=%15.10f\n",SUM(minutes));

	    		teams.insert(pair<string,vector<double> >(team,vals));

	    	}
	    }
	}

	fclose(oFile);

}
/*
double LeagueAVG(runparams &parms, vector<Player> &P, string stat, int year) {

	double v;
	double statistic=0.0;
	int count=0;

	for (int i=0; i<(int)P.size(); i++) {
		v=P.at(i).Stat(year,stat); if (v==NONNUMBER) continue; //  skip player if absent last year
		count+=1;
		statistic+=v;
	}
	return statistic/count;
}

double SPS(Player &p, string stat, int year, double lmins3, double lmins2, double lmins1, double lstat3, double lstat2, double lstat1) {

	//Based on the Basketball-reference Simple Projection System
	//http://www.basketball-reference.com/about/projections.html

	double pmins3,pmins2,pmins1;
	double pstat3,pstat2,pstat1;
	double age;

	double pstat;

	pmins3=p.Stat(year-0,"mins"); if (pmins3==NONNUMBER) pmins3=0.0;
	pmins2=p.Stat(year-1,"mins"); if (pmins2==NONNUMBER) pmins2=0.0;
	pmins1=p.Stat(year-2,"mins"); if (pmins1==NONNUMBER) pmins1=0.0;

	pstat3=p.Stat(year-0,stat); if (pstat3==NONNUMBER) pstat3=0.0;
	pstat2=p.Stat(year-1,stat); if (pstat2==NONNUMBER) pstat2=0.0;
    pstat1=p.Stat(year-2,stat); if (pstat1==NONNUMBER) pstat1=0.0;

    age=p.Stat(2013,"age")+1;

    double ind_stat_proj=WeightedSum(pstat3,pstat2,pstat1);
    double ind_mins_proj=WeightedSum(pmins3,pmins2,pmins1);

    double rrr= WeightedSum(pmins3*lstat3/lmins3,pmins3*lstat3/lmins3,pmins3*lstat3/lmins3);
	double mm=1000*rrr/ind_mins_proj;

    //per 36 minutes projection
	double p36stat=36*(mm+ind_stat_proj)/(ind_mins_proj+1000);
	//double p36stat=(mm+ind_stat_proj)/(1000);

	if (stat=="tov" || stat=="fouls") {

		if (age>28) pstat=(1 + (28.0-age)*-0.002)*p36stat;
		else pstat=(1 + (28.0-age)*-0.004)*p36stat;

	} else {

		if (age>28) pstat=(1 + (28.0-age)*0.002)*p36stat;
		else pstat=(1 + (28.0-age)*0.004)*p36stat;

	}

	printf("%10s %6s %10.5f\n",p.bballref_id.c_str(),stat.c_str(),pstat);
	return pstat;

}
*/
void RunAnalysis(runparams &parms, vector<vector<Game> > &G, vector<map<string, Team> > &T,
		vector<map<string, vector<double> > > &AR, map<string, map<string, vector<double> > > &H, vector<Player> &P) {

	int NSIM=parms.nsims; parms.nsims=1;

	InitGlobals(parms,T,G,AR);

	if (parms.player_download) { DownloadPlayers(parms); }

	//if (parms.player_update) { UpdatePlayers(parms,P); UinitGlobals(parms,T,G,AR,H,P); InitGlobals(parms,T,G,AR); }
	if (parms.player_update) { UpdatePlayersNew(parms,P); UinitGlobals(parms,T,G,AR,H,P); InitGlobals(parms,T,G,AR); }

	if (parms.player_analysis) { AnalysisPlayers(parms,P); UinitGlobals(parms,T,G,AR,H,P); InitGlobals(parms,T,G,AR); }

	if (parms.team_download) { DownloadTeam(parms,P); UinitGlobals(parms,T,G,AR,H,P); InitGlobals(parms,T,G,AR); }

	if (parms.team_update) { UpdateTeam(parms,P); UinitGlobals(parms,T,G,AR,H,P); InitGlobals(parms,T,G,AR); }

	if (parms.season_download) { DownloadSchedule(G,T,parms); UinitGlobals(parms,T,G,AR,H,P); InitGlobals(parms,T,G,AR); }

	if (parms.season_update) { UpdateSchedule(G,T,AR,H,P,parms); UinitGlobals(parms,T,G,AR,H,P); InitGlobals(parms,T,G,AR); }

	UinitGlobals(parms,T,G,AR,H,P);

	parms.nsims=NSIM;
}
