/*
 * players.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: oosode
 */


#include "players.h"

# define NONNUMBER -13982934874

Player::Player() {

};

double Player::Info(int year, string stat) {

	if (statMap[stat].find(year)!=statMap[stat].end()) return statMap[stat].find(year)->second;
	else return NONNUMBER;
}
double Player::Stat(int year, string stat) {

	if (statMap[stat].find(year)!=statMap[stat].end()) return statMap[stat].find(year)->second;
	else return NONNUMBER;
}

double Player::SPS(double v1, double v2, double v3) {

	v1=v1*1.0;
	v2=v2*3.0;
	v3=v3*6.0;

	return v1+v2+v3;
}

double Player::ortgavg(string year) {

	char y3[8];
	char y2[8];
	char y1[8];

	int yr3=atoi(year.c_str()); sprintf(y3,"%d",yr3);
	int yr2=yr3-1;				sprintf(y2,"%d",yr2);
	int yr1=yr2-1;				sprintf(y1,"%d",yr1);

	double weight3=0.0;
	double weight2=0.0;
	double weight1=0.0;

	double ortg3=0.0;
	double ortg2=0.0;
	double ortg1=0.0;

	double mins3=0.0;
	double mins2=0.0;
	double mins1=0.0;

	if (ortg.find(y3)!=ortg.end()) {

		ortg3=ortg.find(y3)->second;
		mins3=mins.find(y3)->second;
		weight3=mins3/3936;

	}
	if (ortg.find(y2)!=ortg.end()) {

		ortg2=ortg.find(y2)->second;
		mins2=mins.find(y2)->second;
		weight2=mins2/3936;

	}
	if (ortg.find(y1)!=ortg.end()) {

		ortg1=ortg.find(y1)->second;
		mins1=mins.find(y1)->second;
		weight1=mins1/3936;

	}

	double totalmins=mins3+mins2+mins1;

	if (totalmins==0.0) return 0.0;

	weight3=mins3/totalmins;
	weight2=mins2/totalmins;
	weight1=mins1/totalmins;

	double orating=weight3*ortg3*mins3 + weight2*ortg2*mins2 + weight1*ortg1*mins1;

	return orating;

}
double Player::drtgavg(string year) {

	char y3[8];
	char y2[8];
	char y1[8];

	int yr3=atoi(year.c_str()); sprintf(y3,"%d",yr3);
	int yr2=yr3-1;				sprintf(y2,"%d",yr2);
	int yr1=yr2-1;				sprintf(y1,"%d",yr1);

	double weight3=0.0;
	double weight2=0.0;
	double weight1=0.0;

	double drtg3=0.0;
	double drtg2=0.0;
	double drtg1=0.0;

	double mins3=0.0;
	double mins2=0.0;
	double mins1=0.0;

	if (drtg.find(y3)!=drtg.end()) {

		drtg3=drtg.find(y3)->second;
		mins3=mins.find(y3)->second;
		weight3=mins3/3936;

	}
	if (drtg.find(y2)!=drtg.end()) {

		drtg2=drtg.find(y2)->second;
		mins2=mins.find(y2)->second;
		weight2=mins2/3936;

	}
	if (drtg.find(y1)!=drtg.end()) {

		drtg1=drtg.find(y1)->second;
		mins1=mins.find(y1)->second;
		weight1=mins1/3936;

	}

	double totalmins=mins3+mins2+mins1;

	if (totalmins==0.0) return 0.0;

	weight3=mins3/totalmins;
	weight2=mins2/totalmins;
	weight1=mins1/totalmins;

	double drating=weight3*drtg3*mins3 + weight2*drtg2*mins2 + weight1*drtg1*mins1;

	return drating;

}
double Player::owsavg(string year) {

	char y3[8];
	char y2[8];
	char y1[8];

	int yr3=atoi(year.c_str()); sprintf(y3,"%d",yr3);
	int yr2=yr3-1;				sprintf(y2,"%d",yr2);
	int yr1=yr2-1;				sprintf(y1,"%d",yr1);

	double weight3=0.0;
	double weight2=0.0;
	double weight1=0.0;

	double ows3=0.0;
	double ows2=0.0;
	double ows1=0.0;

	double mins3=0.0;
	double mins2=0.0;
	double mins1=0.0;

	if (ows.find(y3)!=ows.end()) {

		ows3=ows.find(y3)->second;
		mins3=mins.find(y3)->second;
		weight3=mins3/3936;

	}
	if (ows.find(y2)!=ows.end()) {

		ows2=ows.find(y2)->second;
		mins2=mins.find(y2)->second;
		weight2=mins2/3936;

	}
	if (ows.find(y1)!=ows.end()) {

		ows1=ows.find(y1)->second;
		mins1=mins.find(y1)->second;
		weight1=mins1/3936;

	}

	double totalmins=mins3+mins2+mins1;

	if (totalmins==0.0) return 0.0;

	weight3=mins3/totalmins;
	weight2=mins2/totalmins;
	weight1=mins1/totalmins;

	//printf("ws3 %f ws2 %f ws1 %f\n",ows3,ows2,ows1);
	double offensive_ws=weight3*ows3*mins3 + weight2*ows2*mins2 + weight1*ows1*mins1;

	return offensive_ws;

}
double Player::dwsavg(string year) {

	char y3[8];
	char y2[8];
	char y1[8];

	int yr3=atoi(year.c_str()); sprintf(y3,"%d",yr3);
	int yr2=yr3-1;				sprintf(y2,"%d",yr2);
	int yr1=yr2-1;				sprintf(y1,"%d",yr1);

	double weight3=0.0;
	double weight2=0.0;
	double weight1=0.0;

	double dws3=0.0;
	double dws2=0.0;
	double dws1=0.0;

	double mins3=0.0;
	double mins2=0.0;
	double mins1=0.0;

	if (dws.find(y3)!=dws.end()) {

		dws3=dws.find(y3)->second;
		mins3=mins.find(y3)->second;
		weight3=mins3/3936;

	}
	if (dws.find(y2)!=dws.end()) {

		dws2=dws.find(y2)->second;
		mins2=mins.find(y2)->second;
		weight2=mins2/3936;

	}
	if (dws.find(y1)!=dws.end()) {

		dws1=dws.find(y1)->second;
		mins1=mins.find(y1)->second;
		weight1=mins1/3936;

	}

	double totalmins=mins3+mins2+mins1;

	if (totalmins==0.0) return 0.0;

	weight3=mins3/totalmins;
	weight2=mins2/totalmins;
	weight1=mins1/totalmins;

	//printf("ws3 %f ws2 %f ws1 %f\n",dws3,dws2,dws1);
	double defensive_ws=weight3*dws3*mins3 + weight2*dws2*mins2 + weight1*dws1*mins1;

	return defensive_ws;

}
double Player::minsavg(string year) {

	char y3[8];
	char y2[8];
	char y1[8];

	int yr3=atoi(year.c_str()); sprintf(y3,"%d",yr3);
	int yr2=yr3-1;				sprintf(y2,"%d",yr2);
	int yr1=yr2-1;				sprintf(y1,"%d",yr1);

	double mins3=0.0;
	double mins2=0.0;
	double mins1=0.0;

	if (mins.find(y3)!=mins.end()) { mins3=mins.find(y3)->second; }
	if (mins.find(y2)!=mins.end()) { mins2=mins.find(y2)->second; }
	if (mins.find(y1)!=mins.end()) { mins1=mins.find(y1)->second; }

	double totalmins=mins3+mins2+mins1;
	double avgmins=mins3*(mins3/totalmins) + mins2*(mins2/totalmins) + mins1*(mins1/totalmins);

	if (totalmins==0.0) return 0.0;

	return avgmins;

}

double Player::owsreg(string year) {

	char y3[8];
	char y2[8];
	char y1[8];

	int yr3=atoi(year.c_str()); sprintf(y3,"%d",yr3);
	int yr2=yr3-1;				sprintf(y2,"%d",yr2);
	int yr1=yr2-1;				sprintf(y1,"%d",yr1);

	double weight3=0.0;
	double weight2=0.0;
	double weight1=0.0;

	double ows3=0.0;
	double ows2=0.0;
	double ows1=0.0;

	double mins3=0.0;
	double mins2=0.0;
	double mins1=0.0;

	double ows_init=0.4376;

	if (ows.find(y3)!=ows.end()) {

		ows3=ows.find(y3)->second;
		mins3=mins.find(y3)->second;
		weight3=mins3/3936;

	}
	if (ows.find(y2)!=ows.end()) {

		ows2=ows.find(y2)->second;
		mins2=mins.find(y2)->second;
		weight2=mins2/3936;

	}
	if (ows.find(y1)!=ows.end()) {

		ows1=ows.find(y1)->second;
		mins1=mins.find(y1)->second;
		weight1=mins1/3936;

	}

	double totalmins=mins3+mins2+mins1;

	if (totalmins==0.0) return 0.0;

	if (totalmins==0.0) { return 1.0069*log(1) + ows_init; }

	else if (mins1==0.0 && mins2==0.0) { return 1.0069*log(2) + ows3; }

	else if (mins1==0.0) { return 1.0069*log(3) + ows2; }

	weight3=mins3/totalmins;
	weight2=mins2/totalmins;
	weight1=mins1/totalmins;

	//printf("ws3 %f ws2 %f ws1 %f\n",ows3,ows2,ows1);
	double offensive_ws=weight3*ows3*mins3 + weight2*ows2*mins2 + weight1*ows1*mins1;

	//regression stuff
	double y  = ows1 + ows2 + ows3;
	double x  = double(yr1)  + double(yr2)  + double(yr3);
	double xy = ows1*double(yr1) + ows2*double(yr2) + ows3*double(yr3);
	double x2 = double(yr1)*double(yr1) + double(yr2)*double(yr2) + double(yr3)*double(yr3);

	double a = (y*x2 - x*xy)/(3*x2 - x*x);
	double b = (3*xy - x*y)/(3*x2 - x*x);

	offensive_ws = b*yr3+1.0 + a;

	//printf("%15.10f %15.10f %15.10f %15.10f\n",ows1,ows2,ows3,offensive_ws);
	//printf("%5.3f %5.3f %5.3f %5.3f %5.3f %5.3f\n",ows1,ows2,ows3,double(yr1),double(yr2),double(yr3));

	//exit(0);
	return offensive_ws;

}
double Player::dwsreg(string year) {

	char y3[8];
	char y2[8];
	char y1[8];

	int yr3=atoi(year.c_str()); sprintf(y3,"%d",yr3);
	int yr2=yr3-1;				sprintf(y2,"%d",yr2);
	int yr1=yr2-1;				sprintf(y1,"%d",yr1);

	double weight3=0.0;
	double weight2=0.0;
	double weight1=0.0;

	double dws3=0.0;
	double dws2=0.0;
	double dws1=0.0;

	double mins3=0.0;
	double mins2=0.0;
	double mins1=0.0;

	double dws_init=0.8385;
	double value=0.0;

	if (dws.find(y3)!=dws.end()) {

		dws3=dws.find(y3)->second;
		mins3=mins.find(y3)->second;
		weight3=mins3/3936;

	}
	if (dws.find(y2)!=dws.end()) {

		dws2=dws.find(y2)->second;
		mins2=mins.find(y2)->second;
		weight2=mins2/3936;

	}
	if (dws.find(y1)!=dws.end()) {

		dws1=dws.find(y1)->second;
		mins1=mins.find(y1)->second;
		weight1=mins1/3936;

	}

	double totalmins=mins3+mins2+mins1;

	if (totalmins==0.0) { return 0.5379*log(1) + dws_init; }

	else if (mins1==0.0 && mins2==0.0) { return 0.5379*log(2) + dws3; }

	else if (mins1==0.0) { return 0.5379*log(3) + dws2; }

	weight3=mins3/totalmins;
	weight2=mins2/totalmins;
	weight1=mins1/totalmins;

	double defensive_ws=weight3*dws3*mins3 + weight2*dws2*mins2 + weight1*dws1*mins1;

	//regression stuff
	double y  = dws1 + dws2 + dws3;
	double x  = yr1  + yr2  + yr3;
	double xy = dws1*yr1 + dws2*yr2 + dws3*yr3;
	double x2 = yr1*yr1  + yr2*yr2  + yr3*yr3;

	double a = (y*x2 - x*xy)/(3*x2 - x*x);
	double b = (3*xy - x*y)/(3*x2 - x*x);

	defensive_ws = b*(yr3+1) + a;

	return defensive_ws;

}
double Player::ortgreg(string year) {

	char y3[8];
	char y2[8];
	char y1[8];

	int yr3=atoi(year.c_str()); sprintf(y3,"%d",yr3);
	int yr2=yr3-1;				sprintf(y2,"%d",yr2);
	int yr1=yr2-1;				sprintf(y1,"%d",yr1);

	double weight3=0.0;
	double weight2=0.0;
	double weight1=0.0;

	double ortg3=0.0;
	double ortg2=0.0;
	double ortg1=0.0;

	double mins3=0.0;
	double mins2=0.0;
	double mins1=0.0;

	if (ortg.find(y3)!=ortg.end()) {

		ortg3=ortg.find(y3)->second;
		mins3=mins.find(y3)->second;
		weight3=mins3/3936;

	}
	if (ortg.find(y2)!=ortg.end()) {

		ortg2=ortg.find(y2)->second;
		mins2=mins.find(y2)->second;
		weight2=mins2/3936;

	}
	if (ortg.find(y1)!=ortg.end()) {

		ortg1=ortg.find(y1)->second;
		mins1=mins.find(y1)->second;
		weight1=mins1/3936;

	}

	double totalmins=mins3+mins2+mins1;

	if (totalmins==0.0) return 0.0;

	double o1 = ortg1*mins1;
	double o2 = ortg2*mins2;
	double o3 = ortg3*mins3;

	printf("%20.10f %20.10f %20.10f\n",ortg1,ortg2,ortg3);
	//regression stuff
	double y  = ortg1 + ortg2 + ortg3;
	double x  = yr1  + yr2  + yr3;
	double xy = ortg1*yr1 + ortg2*yr2 + ortg3*yr3;
	double x2 = yr1*yr1  + yr2*yr2  + yr3*yr3;

	double a = (y*x2 - x*xy)/(3*x2 - x*x);
	double b = (3*xy - x*y)/(3*x2 - x*x);

	double orating = b*(yr3+1) + a;

	if (orating<0.0) return 0.0;

	return orating;

}
double Player::drtgreg(string year) {

	char y3[8];
	char y2[8];
	char y1[8];

	int yr3=atoi(year.c_str()); sprintf(y3,"%d",yr3);
	int yr2=yr3-1;				sprintf(y2,"%d",yr2);
	int yr1=yr2-1;				sprintf(y1,"%d",yr1);

	double weight3=0.0;
	double weight2=0.0;
	double weight1=0.0;

	double drtg3=0.0;
	double drtg2=0.0;
	double drtg1=0.0;

	double mins3=0.0;
	double mins2=0.0;
	double mins1=0.0;

	if (drtg.find(y3)!=drtg.end()) {

		drtg3=drtg.find(y3)->second;
		mins3=mins.find(y3)->second;
		weight3=mins3/3936;

	}
	if (drtg.find(y2)!=drtg.end()) {

		drtg2=drtg.find(y2)->second;
		mins2=mins.find(y2)->second;
		weight2=mins2/3936;

	}
	if (drtg.find(y1)!=drtg.end()) {

		drtg1=drtg.find(y1)->second;
		mins1=mins.find(y1)->second;
		weight1=mins1/3936;

	}

	double totalmins=mins3+mins2+mins1;

	if (totalmins==0.0) return 0.0;

	double d1 = drtg1*mins1;
	double d2 = drtg2*mins2;
	double d3 = drtg3*mins3;

	//regression stuff
	double y  = drtg1 + drtg2 + drtg3;
	double x  = yr1  + yr2  + yr3;
	double xy = drtg1*yr1 + drtg2*yr2 + drtg3*yr3;
	double x2 = yr1*yr1  + yr2*yr2  + yr3*yr3;

	double a = (y*x2 - x*xy)/(3*x2 - x*x);
	double b = (3*xy - x*y)/(3*x2 - x*x);

	double drating = b*(yr3+1) + a;

	if (drating<0.0) return 0.0;

	return drating;

}
double Player::minsreg(string year) {

	char y3[8];
	char y2[8];
	char y1[8];

	int yr3=atoi(year.c_str()); sprintf(y3,"%d",yr3);
	int yr2=yr3-1;				sprintf(y2,"%d",yr2);
	int yr1=yr2-1;				sprintf(y1,"%d",yr1);

	double mins3=0.0;
	double mins2=0.0;
	double mins1=0.0;

	if (mins.find(y3)!=mins.end()) { mins3=mins.find(y3)->second; }
	if (mins.find(y2)!=mins.end()) { mins2=mins.find(y2)->second; }
	if (mins.find(y1)!=mins.end()) { mins1=mins.find(y1)->second; }

	//double totalmins=mins3+mins2+mins1;
	//double avgmins=mins3*(mins3/totalmins) + mins2*(mins2/totalmins) + mins1*(mins1/totalmins);

	//if (totalmins==0.0) return 0.0;

	//regression stuff
	double y  = mins1 + mins2 + mins3;
	double x  = yr1  + yr2  + yr3;
	double xy = mins1*yr1 + mins2*yr2 + mins3*yr3;
	double x2 = yr1*yr1  + yr2*yr2  + yr3*yr3;

	double a = (y*x2 - x*xy)/(3*x2 - x*x);
	double b = (3*xy - x*y)/(3*x2 - x*x);

	double regmins = b*(yr3+1) + a;

	if (regmins<0.0) regmins =0.0;

	return regmins;

}

double Player::MinutesReg(int year) {

	double m3=Stat(year-0,"mins");
	double m2=Stat(year-1,"mins");
	double m1=Stat(year-2,"mins");

	double g3=Stat(year-0,"games");
	double g2=Stat(year-1,"games");
	double g1=Stat(year-2,"games");

	double regmins=0;

	if (m1==NONNUMBER && m2==NONNUMBER && m3==NONNUMBER) {
		//rookie
		return 600;

	} else if (m1==NONNUMBER && m2==NONNUMBER) {
		//second year
		return m3+300;

	} else if (m1==NONNUMBER) {

		regmins=(m3-m2)/2.0+m3;
		if (regmins<300) regmins=300;

		return regmins;

	} else {

		if (m1==NONNUMBER) { m1=0; g1=1; }
		if (m2==NONNUMBER) { m2=0; g2=1; }
		if (m3==NONNUMBER) { m3=0; g3=1; }

		m1=m1/g1; m2=m2/g2; m3=m3/g3;

		//regression stuff
		double y  = m1 + m2 + m3;
		double x  = 6;
		double xy = m1*(1) + m2*(2) + m3*(3);
		double x2 = (1)*(1)  + (2)*(2)  + 3*3;

		//double a = (y - x*xy)/(3*x2 - x*x);
		double b = (3*xy - x*y)/(3*x2 - x*x);
		double a = (y - b*x)/3;

		//cout << b << " " << a << endl;

		if (b>6.0) b=6.0;
		if (b<-6.0) b=-6.0;

		if (m3!=0) { regmins = (m3+b); }
		else { regmins = (7.32+b); }

		//cout << regmins << endl;

		regmins = (regmins + b*double(4) + a)/2.0;

		//cout << bballref_id << " " << regmins << endl;


		regmins = regmins*82;

		if (regmins<150.0) regmins = 150.0;

		//if (bballref_id=="rosede01") {

		//	printf("%s %10.3f %10.3f %10.3f %10.3f\n",bballref_id.c_str(),m1,m2,m3,regmins);
		//	exit(1);
		//}

		//if (bballref_id=="duranke01") { cout << m1 << " " << m2 << " " << m3 <<  " "  << endl; cout << regmins << endl; exit(0);}

		//if (bballref_id=="samuesa01") { cout << m1 << " " << m2 << " " << m3 <<  " "  << endl; cout << regmins << endl; exit(0);}

		//cout << bballref_id << " " << regmins << endl;
		return regmins;

	}

	return regmins;

}

double Player::OTest() {

	return Minutes*ORtg;
}
double Player::DTest() {

	return Minutes*DRtg;
}
