/*
 * projection.cpp
 *
 *  Created on: Oct 23, 2013
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
#include <math.h>


#include "random.h"
#include "game.h"
#include "read.h"
#include "team.h"
#include "standing.h"
#include "functions.h"
#include "online.h"
#include "players.h"

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

class Game;
class Team;
class Player;

# define NONNUMBER -13982934874

# define TEAMAVGMPG 241.85
# define TEAMAVGMPG 250.00
# define TEAMAVGMIN TEAMAVGMPG*82

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
double SPS(Player &p, string stat, int year, double lmins3, double lmins2, double lmins1,
										     double lstat3, double lstat2, double lstat1) {

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

    age=p.Stat(year,"age")+1;
    if (age==NONNUMBER+1) age=p.Stat(year-1,"age")+2;
    if (age==NONNUMBER+2) age=p.Stat(year-2,"age")+3;

    if (pmins3+pmins2+pmins1==0.0) return lstat3*0.6/lmins3;

    double ind_stat_proj=WeightedSum(pstat3,pstat2,pstat1);
    double ind_mins_proj=WeightedSum(pmins3,pmins2,pmins1);

    double rrr= WeightedSum(pmins3*lstat3/lmins3,pmins3*lstat3/lmins3,pmins3*lstat3/lmins3);
	double mm=1000*rrr/ind_mins_proj;

    //per minute projection
	double p36stat=(mm+ind_stat_proj)/(ind_mins_proj+1000);

	if (stat=="tov" || stat=="fouls" || stat=="drtg") {

		if (age>28) pstat=(1 + (28.0-age)*-0.002)*p36stat;
		else pstat=(1 + (28.0-age)*-0.004)*p36stat;

	} else {

		if (age>28) pstat=(1 + (28.0-age)*0.002)*p36stat;
		else pstat=(1 + (28.0-age)*0.004)*p36stat;

	}

	return pstat;

}
void PlayerProjection(runparams &parms,vector<Player> &P, Player &p, int year) {

	double m3=LeagueAVG(parms,P,"mins",year);
	double m2=LeagueAVG(parms,P,"mins",year-1);
	double m1=LeagueAVG(parms,P,"mins",year-2);

	string arr[] = {"fg","fga","threeg","threega","ft","fta",
					"ast_tot","stl_tot","blk_tot","tov_tot",
					"foul_tot"};

	printf("%10s ",p.bballref_id.c_str());
	for (int i=0; i<11; i++) {

		double s3=LeagueAVG(parms,P,arr[i],year);
		double s2=LeagueAVG(parms,P,arr[i],year-1);
		double s1=LeagueAVG(parms,P,arr[i],year-2);

		double stat=SPS(p,arr[i],year,m3,m2,m1,s3,s2,s1);

		printf("%6.2f ",stat);
	}

	printf("\n");

}

double DRBrefactor(double drb) {

	//historical drb per possesion average
	double drbavg=0.33402;
	//error function x value
	//multiply by 10 to situate values in range [-1,1]
	//normal drb% is between [0.300,0.3800]
	double v=(drb-drbavg)*10.0;
	//calculate error function
	//divide by 25 to minimize values to range [-0.04,0.04]
	double t=erf(v)/25.0+drbavg;
	//calculate affect on offensive rating
	//historical linear fit of drb% with defensive rating
	double r_drb=(t-drbavg)*(-147.83);
	cout << "DRB% " << t << endl;

	return r_drb;

}
double STLrefactor(double stl) {

	//historical stl per possesion average
	double stlavg=0.08830;
	//error function x value
	//multiply by 50 to situate values in range [-1,1]
	//normal drb% is between about [0.060,0.110]
	double v=(stl-stlavg)*15.0;
	//calculate error function
	//divide by 25 to minimize values to range [-0.03,0.03]
	double t=erf(v)/33.0+stlavg;
	//calculate affect on offensive rating
	//historical linear fit of drb% with defensive rating
	double r_stl=(t-stlavg)*(-152.06);
	//cout << t<< endl;

	return r_stl;

}
double BLKrefactor(double blk) {

	//historical blk per possesion average
	double blkavg=0.05373;
	//error function x value
	//multiply by 40 to situate values in range [-1,1]
	//normal drb% is between about [0.030,0.070]
	double v=(blk-blkavg)*30.0;
	//calculate error function
	//divide by 33 to minimize values to range [-0.02,0.02]
	double t=erf(v)/50.0+blkavg;
	//calculate affect on offensive rating
	//historical linear fit of drb% with defensive rating
	double r_blk=(t-blkavg)*(-137.93);
	//cout << t << " DRB%" << endl;

	return r_blk;

}
double FOULrefactor(double foul) {

	//historical foul per possesion average
	double foulavg=0.23386;
	//error function x value
	//multiply by 15 to situate values in range [-1,1]
	//normal foul% is between about [0.175,0.275]
	double v=(foul-foulavg)*15.0;
	//calculate error function
	//divide by 20 to minimize values to range [-0.05,0.05]
	double t=erf(v)/20.0+foulavg;
	//calculate affect on offensive rating
	//historical linear fit of foul% with defensive rating
	double r_fouls=(t-foulavg)*(7.0694);
	//cout << t<< endl;

	return r_fouls;

}

void TeamProjection(runparams &parms, vector<Player> &P) {

	if (parms.read_team_update_team.empty()) { parms.read_team_update_team="teams.csv"; }

	FILE * oFile = fopen ("teams.update.csv","w");
	if (!parms.print_team_update.empty()) { oFile = fopen (parms.print_team_update.c_str(),"w"); }
	FILE * mFile = fopen ("teams.updated.stats.csv","w");

	ReadPlayerRestartNew(parms,P,parms.read_team_update_player);

	vector<double> vals(4,0.0);
	vector<string> tmp;
	string line,team;

	map<int,double> temp0;
	map<string,double> temp1;
	map<string, map<string,double> >tst; //team stats
	map<string, map<int,double> >   lst; //league stats
	map<string, map<string,double> > teams;

	int year=parms.team_update_year-1;
	string arr[16] = {"mins","fg","fga","threeg","threega","ft","fta",
					  "ast_tot","stl_tot","blk_tot","tov_tot",
					  "foul_tot","orb_tot","drb_tot","ortg",
					  "drtg"};
	for (int j=0; j<16; j++) {

		map<int,double> temp0;
		for (int k=0; k<3; k++) {
			temp0[year-k]=LeagueAVG(parms,P,arr[j],year-k);
		}
		lst[arr[j]]=temp0;

	}

	//char year[8];
	//sprintf(year,"%d",parms.team_update_year);

	ifstream file0(parms.read_team_update_team.c_str());

	// Find year for standings
	if (file0.is_open()) {

	    while (file0.good()) {

	    	getline(file0,line);
	    	StringExplode(line,",",&tmp);

	    	tst.clear();

	    	if (tmp.at(0)=="team") {

	    		team = tmp.at(1);
	    		printf("     ANALYSIS| Updating team         %53s\n", team.c_str());
	    		fprintf(mFile,"%s,\n",team.c_str());

	    		fprintf(mFile,"last,first,id,");
	    		for (int j=0; j<16; j++) {

	    			fprintf(mFile,"%s,",arr[j].c_str());
	    		}
	    		fprintf(mFile,"\n");

	    		getline(file0,line);
	    		StringExplode(line,",",&tmp);

	    		while (tmp.at(0)=="player") {

	    			string pid=tmp.at(3);

					for (int i=0; i<(int)P.size(); i++) {

						if (P.at(i).bballref_id==pid) {

							fprintf(mFile,"%s,%s,%s,",P.at(i).LastName.c_str(),P.at(i).FirstName.c_str(),pid.c_str());

							for (int j=0; j<16; j++) {

								double m3=lst["mins"][year];
								double m2=lst["mins"][year-1];
								double m1=lst["mins"][year-2];

								double s3=lst[arr[j]][year];
								double s2=lst[arr[j]][year-1];
								double s1=lst[arr[j]][year-2];

								if (arr[j]=="mins") {

									tst[arr[j]][pid]=P.at(i).MinutesReg(year);
									fprintf(mFile,"%.4f,",tst[arr[j]][pid]);
									//tst[arr[j]][pid]=P.at(i).Stat(2013,"mins");
									//if (tst[arr[j]][pid]==NONNUMBER) tst[arr[j]][pid]=0.0;
									//cout << tst[arr[j]][pid] << " " << pid <<  endl;

								} else {

									tst[arr[j]][pid]=SPS(P.at(i),arr[j],year,m3,m2,m1,s3,s2,s1);
									fprintf(mFile,"%.4f,",tst[arr[j]][pid]*tst["mins"][pid]);
									//tst[arr[j]][pid]=P.at(i).Stat(2013,arr[j]);
									//if (tst[arr[j]][pid]==NONNUMBER) tst[arr[j]][pid]=0.0;
									//cout << tst[arr[j]][pid] << endl;
								}

							}

						}
						//fprintf(mFile,"%s",pline);

	    			}
					fprintf(mFile,"\n");
		    		getline(file0,line);
		    		StringExplode(line,",",&tmp);
	    		}
	    		fprintf(mFile,"\n");

				int iteration=0;
				while (SUM(tst["mins"])+1<TEAMAVGMIN || SUM(tst["mins"])-1>TEAMAVGMIN) {
					iteration++;


					double team_min=SUM(tst["mins"]);

					map<string,double>::iterator iter;
					for (iter=tst["mins"].begin(); iter!=tst["mins"].end(); iter++) {


						double factor=(3400-iter->second)/3400;

						double tmp_min=(factor)*TEAMAVGMIN*(iter->second)/team_min +
									   (1-factor)*iter->second;

						//BUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUG
						//needs to be average of actual data for total minutes played
						if (tmp_min>42.0*82) tmp_min=42.0*82;

						//save temporary player minutes to minutes map

						iter->second=tmp_min;
						//printf("%3s %s %15.10f\n",team.c_str(),iter->first.c_str(),iter->second);

					}

					if (iteration>50) break;

				}

				double FG=0.0,FGA=0.0,FT=0.0,FTA=0.0,TG=0.0,TGA=0.0;
				double AST=0.0,BLK=0.0,STL=0.0,TOV=0.0,FOULS=0.0,ORB=0.0,DRB=0.0;

				double DRTG=0.0,ORTG=0.0;

				map<string,double>::iterator iter;
				for (iter=tst["mins"].begin(); iter!=tst["mins"].end(); iter++) {

					string pid=iter->first;

					double min=iter->second;
					double old_min=0.0;

					for (int i=0; i<(int)P.size(); i++) {
						if (P.at(i).bballref_id==pid) {
							old_min=tst["mins"][pid]=P.at(i).MinutesReg(year);
							break;
						}
					}

					//cout << min-old_min << " " << min/old_min << " :minutes " << pid << endl;

					//usage adjustment
					//double usg=(old_min-100)/min;
					//double usg=old_min/min;
					double usg=1.0;

					double fga=tst["fga"][pid];
					double fgm=tst["fg"][pid];
					double fta=tst["fta"][pid];
					double ftm=tst["ft"][pid];
					double tgm=tst["threeg"][pid]; //three point field goals
					double tga=tst["threega"][pid]; //three point field goals attempted

					double ast=tst["ast_tot"][pid];
					double blk=tst["blk_tot"][pid];
					double stl=tst["stl_tot"][pid];
					double tov=tst["tov_tot"][pid];
					double fls=tst["foul_tot"][pid];

					double orb=tst["orb_tot"][pid];
					double drb=tst["drb_tot"][pid];

					double ortg=tst["ortg"][pid];
					double drtg=tst["drtg"][pid];

					teams["fg"][team]    	+=min*fgm*usg;
					teams["fga"][team]   	+=min*fga*usg;
					teams["ft"][team]	 	+=min*ftm*usg;
					teams["fta"][team]   	+=min*fta*usg;
					teams["threeg"][team] 	+=min*tgm*usg;
					teams["threega"][team] 	+=min*tga*usg;

					teams["ast_tot"][team]  +=min*ast*usg;
					teams["blk_tot"][team]  +=min*blk*usg;
					teams["stl_tot"][team]  +=min*stl*usg;
					teams["tov_tot"][team]  +=min*tov/usg;
					teams["foul_tot"][team] +=min*fls/usg;

					teams["orb_tot"][team]  +=min*orb*usg;
					teams["drb_tot"][team] 	+=min*drb*usg;

					teams["drtg"][team]  	+=min*drtg*usg/TEAMAVGMIN;
					teams["ortg"][team]  	+=min*ortg/usg/TEAMAVGMIN;

				}

				FG		=teams["fg"][team];
				FGA		=teams["fga"][team];
				FT		=teams["ft"][team];
				FTA		=teams["fta"][team];
				TG		=teams["threeg"][team];
				TGA		=teams["threega"][team];

				AST		=teams["ast_tot"][team];
				STL 	=teams["stl_tot"][team];
				BLK		=teams["blk_tot"][team];
				TOV		=teams["tov_tot"][team];
				FOULS	=teams["fouls_tot"][team];

				ORB		=teams["orb_tot"][team];
				DRB		=teams["drb_tot"][team];

				double points=(FG-TG)*2.0 + TG*3.0 + FT;
				double posses=0.96*(FGA + TOV - ORB + 0.44*FTA);

				double rate3avg=0.21266;
				teams["r_three"][team]=(TGA/FGA);
				double r_three=(teams["r_three"][team]-rate3avg)*32.435;

				double rateftavg=0.30491;
				teams["r_ft"][team]=(FTA/FGA);
				double r_ft=(teams["r_ft"][team]-rateftavg)*17.728;

				double rateastavg=0.23449;
				teams["r_ast"][team]=(AST/posses);
				double r_ast=(teams["r_ast"][team]-rateastavg)*59.57;

				//defensive
				double foulsavg=7.0694;
				teams["r_fouls"][team]=FOULS/posses;
				//double r_fouls=(FOULS/posses-foulsavg)*0.0043;
				double r_fouls=FOULrefactor(FOULS/posses);

				//double blkavg=0.05373;
				teams["r_blk"][team]=BLK/posses;
				//double r_blk=(BLK/posses-blkavg)*(-137.93);
				double r_blk=BLKrefactor(BLK/posses);

				//double stlavg=0.08830;
				teams["r_stl"][team]=STL/posses;
				//calculate affect on defensize rating
				double r_stl=STLrefactor(STL/posses);

				//calculate affect on defensive rating
				teams["r_drb"][team]=DRB/posses;
				//double r_drb=(teams["r_drb"][team]-drbavg)*(-147.83);
				double r_drb=DRBrefactor(DRB/posses);

				teams["offensive"][team]=100*points/posses + r_ft + r_three + r_ast;
				teams["defensive"][team]=106.0412 + r_drb + r_stl + r_blk + r_fouls;

	    	}
		}
	}

	//average values
	double average=106.0412;
	double foulsavg=SUM(teams["r_fouls"])/30.0;
	double blkavg=SUM(teams["r_blk"])/30.0;
	double stlavg=SUM(teams["r_stl"])/30.0;
	double drbavg=SUM(teams["r_drb"])/30.0;

	//BUGBUGBUGBUGBUGBUGBGUBGUG
	//not always divided by 30 teams
	double offavg=SUM(teams["offensive"])/30.0;
	double defavg=SUM(teams["defensive"])/30.0;
	map<string,double >::iterator iter;
	for (iter=teams["offensive"].begin(); iter!=teams["offensive"].end(); iter++) {

		iter->second=iter->second+ average-offavg;
		teams["defensive"][iter->first]=teams["defensive"][iter->first]+average-defavg;
		cout << iter->second << " " << iter->first << " " << teams["defensive"][iter->first] << " " << teams["r_drb"][iter->first] << endl;

		fprintf(oFile,"%s,%8.4f,%8.4f\n",iter->first.c_str(),iter->second,teams["defensive"][iter->first]);



	}



	fclose(oFile);
	fclose(mFile);

}

