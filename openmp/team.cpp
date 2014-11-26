/*
 * team.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: Junior
 */

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <time.h>
#include <fstream>

#include "game.h"
#include "random.h"
#include "team.h"
#include "read.h"

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::ofstream;
using std::ifstream;

class Game;

#define PI 3.14159265

Team::Team() {

};
void Team::Load(string name, string conf, string divs) {

	TeamName = name;
	Conference = conf;
	Division = divs;

	HomeGames = 0;
	AwayGames = 0;

	HomeGamesLast10 = 0;
	AwayGamesLast10 = 0;

	HomeGamesQuarter = 0;
	AwayGamesQuarter = 0;

	startOffRtg = OffRtg;
	startDefRtg = DefRtg;
	startRtgDiff = OffRtg-DefRtg;

	Win = 0;
	Loss = 0;
	WinPercent = 0.0;
	LossPercent = 0.0;

	eWin = 0;
	eLoss = 0;
	eWinPercent = 0.0;
	eLossPercent = 0.0;

	DivWin = 0;
	DivLoss = 0;
	DivWinPercent = 0.0;
	DivLossPercent = 0.0;

	ConfWin = 0;
	ConfLoss = 0;
	ConfWinPercent = 0.0;
	ConfLossPercent = 0.0;

	hBestConfWin = 0.0;
	hBestConfLoss = 0.0;
	aBestConfWin = 0.0;
	aBestConfLoss = 0.0;

	hBestConfWinPercent = 0.0;
	aBestConfWinPercent = 0.0;

	avgP4 = 0.0;
	avgPA = 0.0;

	avgP4Last10 = 0.0;
	avgPALast10 = 0.0;

	avgP4Quarter = 0.0;
	avgPAQuarter = 0.0;

	avgLeagueP4 = 105.0;
	avgLeaguePA = 105.0;

	// Playoff variables
	PlayoffSeed=-1;

	pWin = 0;
	pLoss = 0;
	pWinPercent = 0.0;
	pLossPercent = 0.0;

	epWin = 0;
	epLoss = 0;
	epWinPercent = 0.0;
	epLossPercent = 0.0;

	oneWin=0;
	oneLoss=0;
	oneWinPercent=0.0;
	oneLossPercent=0.0;

	twoWin=0;
	twoLoss=0;
	twoWinPercent=0.0;
	twoLossPercent=0.0;

	threeWin=0;
	threeLoss=0;
	threeWinPercent=0.0;
	threeLossPercent=0.0;

	fourWin=0;
	fourLoss=0;
	fourWinPercent=0.0;
	fourLossPercent=0.0;

	pavgP4 = 0.0;
	pavgPA = 0.0;

	GamesPlayed=0;


};

void Team::Load(string name) {

	TeamName = name;
}

void Team::Distance(double lat1, double lat2, double lon1, double lon2, int i) {

	double R = 6371.0; // km
	double dLat = (lat2 - lat1) * PI / 180.0;
	double dLon = (lon2 - lon1) * PI / 180.0;
	double latone = lat1 * PI / 180.0;
	double lattwo = lat2 * PI / 180.0;

	double a = sin (dLat/2.0) * sin (dLat/2.0) +
			   sin (dLon/2.0) * sin (dLon/2.0 ) * cos (latone) * cos (lattwo);

	double c = 2.0 * atan2(sqrt(a),sqrt(1-a));

	Schedule.at(i).Distance = R * c;
};

int Team::Rest(const time_t dat) {

	struct tm* tm = localtime(&dat);

	for (int i=0; i<(int)Schedule.size(); i++) {

		if (dat == Schedule.at(i).Date) {

			tm->tm_mday -= 1;
			time_t today_1 = mktime(tm);

			tm->tm_mday -= 1;
			time_t today_2 = mktime(tm);

			tm->tm_mday -= 1;
			time_t today_3 = mktime(tm);

			tm->tm_mday -= 1;
			time_t today_4 = mktime(tm);

			if (i == 0) {

				return 0;

			} else if (i == 1) {

				if (Schedule.at(i-1).Date == today_4) return 1;

				else if (Schedule.at(i-1).Date == today_3) return 2;

				else if (Schedule.at(i-1).Date == today_2) return 4;

				else if (Schedule.at(i-1).Date == today_1) return 8;

				else return 0;

			} else if (i == 2) {

				if (Schedule.at(i-2).Date == today_4 && Schedule.at(i-1).Date == today_3) return 3;

				else if (Schedule.at(i-2).Date == today_3 && Schedule.at(i-1).Date == today_2) return 6;

				else if (Schedule.at(i-2).Date == today_2 && Schedule.at(i-1).Date == today_1) return 12;

				else if (Schedule.at(i-2).Date == today_4 && Schedule.at(i-1).Date == today_2) return 5;

				else if (Schedule.at(i-2).Date == today_4 && Schedule.at(i-1).Date == today_1) return 9;

				else if (Schedule.at(i-2).Date == today_3 && Schedule.at(i-1).Date == today_1) return 10;

				else if (Schedule.at(i-1).Date == today_4) return 1;

				else if (Schedule.at(i-1).Date == today_3) return 2;

				else if (Schedule.at(i-1).Date == today_2) return 4;

				else if (Schedule.at(i-1).Date == today_1) return 8;

				else return 0;

			} else {

				if (Schedule.at(i-3).Date == today_4 && Schedule.at(i-2).Date == today_3 && Schedule.at(i-1).Date == today_2) return 7;

				else if (Schedule.at(i-3).Date == today_3 && Schedule.at(i-2).Date == today_2 && Schedule.at(i-1).Date == today_1) return 14;

				else if (Schedule.at(i-3).Date == today_4 && Schedule.at(i-2).Date == today_3 && Schedule.at(i-1).Date == today_1) return 11;

				else if (Schedule.at(i-3).Date == today_4 && Schedule.at(i-2).Date == today_2 && Schedule.at(i-1).Date == today_1) return 13;

				else if (Schedule.at(i-2).Date == today_4 && Schedule.at(i-1).Date == today_3) return 3;

				else if (Schedule.at(i-2).Date == today_3 && Schedule.at(i-1).Date == today_2) return 6;

				else if (Schedule.at(i-2).Date == today_2 && Schedule.at(i-1).Date == today_1) return 12;

				else if (Schedule.at(i-2).Date == today_4 && Schedule.at(i-1).Date == today_2) return 5;

				else if (Schedule.at(i-2).Date == today_4 && Schedule.at(i-1).Date == today_1) return 9;

				else if (Schedule.at(i-2).Date == today_3 && Schedule.at(i-1).Date == today_1) return 10;

				else if (Schedule.at(i-1).Date == today_4) return 1;

				else if (Schedule.at(i-1).Date == today_3) return 2;

				else if (Schedule.at(i-1).Date == today_2) return 4;

				else if (Schedule.at(i-1).Date == today_1) return 8;

				else return 0;
			}
		}
	}
	return 0;

};
int Team::Game(string opp, double off, double def, time_t date) {

	int i;


	for (i=0; i<(int)Schedule.size(); i++) {

		if (Schedule.at(i).Date==date) {

			Schedule.at(i).Ratings.push_back(off);
			Schedule.at(i).Ratings.push_back(def);

			if (off>def) {

				Schedule.at(i).DidWin = true;

				if (Schedule.at(i).Opp->Division==Division) {

					DivWin++;
					ConfWin++;

				}

				else if (Schedule.at(i).Opp->Conference==Conference) {

					ConfWin++;

				}

				Win++;

			} else {

				Schedule.at(i).DidWin = false;

				if (Schedule.at(i).Opp->Division==Division) {

					DivLoss++;
					ConfLoss++;

				}

				else if (Schedule.at(i).Opp->Conference==Conference) {

					ConfLoss++;

				}

				Loss++;

			}

			if (Schedule.at(i).IsHome) {

				HomeGames++;

			} else {

				AwayGames++;

			}

			return i;
			break;
		}
	}
	return i;
};
int Team::GameAlready(string opp, double off, double def, time_t date) {

	int i;
	++GamesPlayed;

	for (i=0; i<(int)Schedule.size(); i++) {

		if (Schedule.at(i).Date==date) {

			Schedule.at(i).Ratings.push_back(off);
			Schedule.at(i).Ratings.push_back(def);

			if (off>def) {

				Schedule.at(i).DidWin = true;

				if (Schedule.at(i).Opp->Division==Division) {

					DivWin++;
					ConfWin++;

				}

				else if (Schedule.at(i).Opp->Conference==Conference) {

					ConfWin++;

				}

				Win++;

			} else {

				Schedule.at(i).DidWin = false;

				if (Schedule.at(i).Opp->Division==Division) {

					DivLoss++;
					ConfLoss++;

				}

				else if (Schedule.at(i).Opp->Conference==Conference) {

					ConfLoss++;

				}

				Loss++;

			}

			if (Schedule.at(i).IsHome) {

				HomeGames++;

			} else {

				AwayGames++;

			}

			return i;
			break;
		}
	}
	return i;
};
int Team::PlayoffGame(string opp, double off, double def, int r) {

	int dummy=0;

	PlayoffSchedule.back().Ratings.push_back(off);
	PlayoffSchedule.back().Ratings.push_back(def);

	if (off>def) {

		PlayoffSchedule.back().DidWin = true;

		if (r==1) {	oneWin++;}

		else if (r==2) { twoWin++; }

		else if (r==3) { threeWin++; }

		else if (r==4) { fourWin++; }

		pWin++;

	} else {

		PlayoffSchedule.back().DidWin = false;

		if (r==1) {	oneLoss++;}

		else if (r==2) { twoLoss++; }

		else if (r==3) { threeLoss++; }

		else if (r==4) { fourLoss++; }

		pLoss++;

	}

	if (PlayoffSchedule.back().IsHome) {

		HomeGames++;

	} else {

		AwayGames++;

	}

	return dummy;

};
void Team::CalcBestPercent() {

	for (int i=0; i<(int)Schedule.size(); i++) {

		if (Schedule.at(i).DidWin) {

			if (Schedule.at(i).Opp->Conference==Conference) {


				if (Schedule.at(i).Opp->Cstand.back()<=8) {

					hBestConfWin++;
				}

			} else {

				if (Schedule.at(i).Opp->Cstand.back()<=8) {

					aBestConfWin++;
				}
			}

		} else {

			if (Schedule.at(i).Opp->Conference==Conference) {

				if (Schedule.at(i).Opp->Cstand.back()<=8) {

					hBestConfLoss++;
				}

			} else {

				if (Schedule.at(i).Opp->Cstand.back()<=8) {

					aBestConfLoss++;
				}
			}
		}
	}

	hBestConfWinPercent = double(hBestConfWin) / double (hBestConfWin+hBestConfLoss);
	hBestConfLossPercent = double(hBestConfLoss) / double (hBestConfWin+hBestConfLoss);

	aBestConfWinPercent = double(aBestConfWin) / double (aBestConfWin+aBestConfLoss);
	aBestConfLossPercent = double(aBestConfLoss) / double(aBestConfWin+aBestConfLoss);
}

void Team::CalcPercent() {

	WinPercent = double(Win) / double(Win+Loss);
	LossPercent = double(Loss) / double(Win+Loss);

	DivWinPercent = double(DivWin) / double(DivWin+DivLoss);
	DivLossPercent = double(DivLoss) / double(DivWin+DivLoss);

	ConfWinPercent = double(ConfWin) / double(ConfWin+ConfLoss);
	ConfLossPercent = double(ConfLoss) / double(ConfWin+ConfLoss);

	eWinPercent = pow(avgP4,13.9)/(pow(avgP4,13.91)+pow(avgPA,13.91));
	eLossPercent = pow(avgPA,13.9)/(pow(avgP4,13.91)+pow(avgPA,13.91));

	eWin = ceil(eWinPercent*double(Win+Loss));
	eLoss = 82.0 - eWin;
	//eWin = ceil(eLossPercent*double(Win+Loss));

	Over500 = double(Win - Loss)/2.0;
	eOver500 = double(eWin - eLoss)/2.0;

};
void Team::PlayoffCalcPercent() {

	pWinPercent = double(pWin) / double(pWin+Loss);
	pLossPercent = double(pLoss) / double(pWin+Loss);

	oneWinPercent = double(oneWin) / double(oneWin+oneLoss);
	oneLossPercent = double(oneLoss) / double(oneWin+oneLoss);

	twoWinPercent = double(twoWin) / double(twoWin+twoLoss);
	twoLossPercent = double(twoLoss) / double(twoWin+twoLoss);

	threeWinPercent = double(threeWin) / double(threeWin+threeLoss);
	threeLossPercent = double(threeLoss) / double(threeWin+threeLoss);

	fourWinPercent = double(fourWin) / double(fourWin+fourLoss);
	fourLossPercent = double(fourLoss) / double(fourWin+fourLoss);

	epWinPercent = pow(pavgP4,13.9)/(pow(pavgP4,13.91)+pow(pavgPA,13.91));
	epLossPercent = pow(pavgPA,13.9)/(pow(pavgP4,13.91)+pow(pavgPA,13.91));

	epWin = ceil(epWinPercent*double(pWin+pLoss));
	epLoss = ceil(epLossPercent*double(pWin+pLoss));

	pOver500 = double(pWin - pLoss)/2.0;
	epOver500 = double(epWin - epLoss)/2.0;

};
void Team::CalcRatg1(int g) {

	double off,def;

	off = 5.0*startOffRtg;
	def = 5.0*startOffRtg;

	int div=5;

	for (int i=0; i<=g; i++) {

		if (abs(Schedule.at(i).Ratings.at(0)) != abs(0.00001) && abs(Schedule.at(i).Ratings.at(1)) != abs(0.00001)) {

		    off += Schedule.at(i).Ratings.at(0);
		    def += Schedule.at(i).Ratings.at(1);

		    div++;

		}
	}

	if (div > 0) {

		OffRtg = off/double(div);
		DefRtg = def/double(div);

	}
};
void Team::CalcRatg2(int g) {

	double off,def;

	// coefficients
	vector<double> coff;
	vector<double> cdef;

	off = 0.0;
	def = 0.0;

	int div=0;

	for (int i=0; i<=g; i++) {

		if (abs(Schedule.at(i).Ratings.at(0)) != abs(0.00001) && abs(Schedule.at(i).Ratings.at(1)) != abs(0.00001)) {

			if (Schedule.at(i).Opp->avgP4 > 0.0 && Schedule.at(i).Opp->avgPA > 0.0) {
				if (TeamName == "MIA") {
				//cout << (Schedule.at(i).Opp->avgP4-avgLeagueP4+50.0)/100.0;
				//cout << " " << -1.0*(Schedule.at(i).Opp->avgPA-avgLeaguePA-50.0)/100.0 << " " << i << " ";
				//cout << Schedule.at(i).Opp->avgP4 << " " << Schedule.at(i).Opp->avgPA << " " << avgLeagueP4 << endl;
				}
				cdef.push_back((Schedule.at(i).Opp->avgP4-avgLeagueP4+52.5)/105.0); // opponents defense
				coff.push_back(-1.0*(Schedule.at(i).Opp->avgPA-avgLeaguePA-52.5)/105.0); // opponents offense

			}
		}
	}

	for (int i=0; i<=g; i++) {

		if (abs(Schedule.at(i).Ratings.at(0)) != abs(0.00001) && abs(Schedule.at(i).Ratings.at(1)) != abs(0.00001)) {

			if (Schedule.at(i).Opp->avgP4 > 0.0 && Schedule.at(i).Opp->avgPA) {
				//if (TeamName == "MIA") {
				//cout << coff.at(i) << " " << Schedule.at(i).Ratings.at(0) << " Ratings ";
				//cout << coff.at(i)*Schedule.at(i).Ratings.at(0)*2.0 << " final " << endl;
				//}
				off += coff.at(i)*Schedule.at(i).Ratings.at(0)*2.0;
				def += cdef.at(i)*Schedule.at(i).Ratings.at(1)*2.0;

				div++;
			}
		}
	}


	if (div > 0) {

		OffRtg = off/div;
		DefRtg = def/div;

	}

};
void Team::CalcRatg3(int g) {
	double off,def;

	off=OffRtg;
	def=DefRtg;

	int div=1;

	for (int i=0; i<=g; i++) {

		if (abs(Schedule.at(i).Ratings.at(0)) != abs(0.00001) && abs(Schedule.at(i).Ratings.at(1)) != abs(0.00001)) {

		    off += Schedule.at(i).Ratings.at(0);
		    def += Schedule.at(i).Ratings.at(1);

		    div++;

		}
	}


	//int ngames = Schedule.size();

	//double per1 = double(g+1)/double(ngames);
	//double per2 = 1.0 - per1;

	OffRtg = off/div;
	DefRtg = def/div;

};

void Team::Shock() {

	double r = unifRand();

	//BUGBUGBUGBUGBUGBUG
	double threshold = 0.005; //  1/82

	if (r < threshold) {

		double strngth = r/threshold - 0.5; // strength of shock on -0.5 - 0.5 scale

		//BUGBUGBUGBUGBUGBUG

		int digit = int((r - int(r)) * 100) % 2; // check even/odd second digit

		if (digit==0) {

			startOffRtg = startOffRtg + (20.0*strngth); // largest change is 10.0
			//cout << 20.0*strngth << endl;

		} else {

			startDefRtg = startDefRtg + (20.0*strngth); // largest change is 10.0
			//cout << 20.0*strngth << endl;

		}
	}
};

void Team::Average() {

	HomeGamesLast10 = 0;
	AwayGamesLast10 = 0;

	HomeGamesQuarter = 0;
	AwayGamesQuarter = 0;

	avgP4 = 0.0;
	avgPA = 0.0;

	avgP4Last10 = 0.0;
	avgPALast10 = 0.0;

	avgP4Quarter = 0.0;
	avgPAQuarter = 0.0;

	int ngames = Schedule.size();
	int lastgame;

	int count = 0; int count10 = 0; int countQ = 0;

	for (int i=(int)Schedule.size()-1; i>=0; i--) {

		if (Schedule.at(i).Ratings.size()==2) {

			if (abs(Schedule.at(i).Ratings.at(0)) > 0.00001 && abs(Schedule.at(i).Ratings.at(1)) > 0.00001) {

				lastgame = ngames - (i + 1);
				break;

			}
	    }
	}

	double quarter = double(ngames-lastgame)/4.0;

	for (int i=(int)Schedule.size()-1; i>=0; i--) {

        if (Schedule.at(i).Ratings.size()==2) {

			if (abs(Schedule.at(i).Ratings.at(0)) > 0.00001 && abs(Schedule.at(i).Ratings.at(1)) > 0.00001) {

				avgP4 += Schedule.at(i).Ratings.at(0);
				avgPA += Schedule.at(i).Ratings.at(1);

				count++;

				if (countQ < quarter) {

					avgP4Quarter += Schedule.at(i).Ratings.at(0);
					avgPAQuarter += Schedule.at(i).Ratings.at(1);

					countQ++;

					if (Schedule.at(i).IsHome) {

						HomeGamesQuarter++;

					} else {

						AwayGamesQuarter++;
					}
				}

				if (count10 < 10) {

					avgP4Last10 += Schedule.at(i).Ratings.at(0);
					avgPALast10 += Schedule.at(i).Ratings.at(1);

					count10++;

					if (Schedule.at(i).IsHome) {

						HomeGamesLast10++;

					} else {

						AwayGamesLast10++;
					}
				}
			}
        }
	}

	if (count >= 1) {

		avgP4 = avgP4/double(count);
		avgPA = avgPA/double(count);

		avgP4Quarter = avgP4Quarter/double(countQ);
		avgPAQuarter = avgPAQuarter/double(countQ);

		avgP4Last10 = avgP4Last10/double(count10);
		avgPALast10 = avgPALast10/double(count10);

	}
};
void Team::PlayoffAverage() {

	HomeGamesLast10 = 0;
	AwayGamesLast10 = 0;

	HomeGamesQuarter = 0;
	AwayGamesQuarter = 0;

	avgP4 = 0.0;
	avgPA = 0.0;

	avgP4Last10 = 0.0;
	avgPALast10 = 0.0;

	avgP4Quarter = 0.0;
	avgPAQuarter = 0.0;

	int ngames_playoffs = PlayoffSchedule.size();
	int ngames = Schedule.size();
	int lastgame;

	int count = 0; int count10 = 0; int countQ = 0;


	for (int i=(int)Schedule.size()-1; i>=0; i--) {

		if (Schedule.at(i).Ratings.size()==2) {

			if (abs(Schedule.at(i).Ratings.at(0)) > 0.00001 && abs(Schedule.at(i).Ratings.at(1)) > 0.00001) {

				lastgame = ngames - (i + 1);
				break;

			}
	    }
	}

	double quarter = double(ngames_playoffs+ngames-lastgame)/4.0;

	for (int i=(int)PlayoffSchedule.size()-1; i>=0; i--) {

        if (PlayoffSchedule.at(i).Ratings.size()==2) {

			if (abs(PlayoffSchedule.at(i).Ratings.at(0)) > 0.00001 && abs(PlayoffSchedule.at(i).Ratings.at(1)) > 0.00001) {

				avgP4 += PlayoffSchedule.at(i).Ratings.at(0);
				avgPA += PlayoffSchedule.at(i).Ratings.at(1);

				count++;

				if (countQ < quarter) {

					avgP4Quarter += PlayoffSchedule.at(i).Ratings.at(0);
					avgPAQuarter += PlayoffSchedule.at(i).Ratings.at(1);

					countQ++;

					if (PlayoffSchedule.at(i).IsHome) {

						HomeGamesQuarter++;

					} else {

						AwayGamesQuarter++;
					}
				}

				if (count10 < 10) {

					avgP4Last10 += PlayoffSchedule.at(i).Ratings.at(0);
					avgPALast10 += PlayoffSchedule.at(i).Ratings.at(1);

					count10++;

					if (PlayoffSchedule.at(i).IsHome) {

						HomeGamesLast10++;

					} else {

						AwayGamesLast10++;
					}
				}
			}
        }
	}

	for (int i=(int)Schedule.size()-1; i>=0; i--) {

		if (Schedule.at(i).Ratings.size()==2) {

			if (abs(Schedule.at(i).Ratings.at(0)) > 0.00001 && abs(Schedule.at(i).Ratings.at(1)) > 0.00001) {

				avgP4 += Schedule.at(i).Ratings.at(0);
				avgPA += Schedule.at(i).Ratings.at(1);

				count++;

				if (countQ < quarter) {

					avgP4Quarter += Schedule.at(i).Ratings.at(0);
					avgPAQuarter += Schedule.at(i).Ratings.at(1);

					countQ++;

					if (Schedule.at(i).IsHome) {

						HomeGamesQuarter++;

					} else {

						AwayGamesQuarter++;
					}
				}

				if (count10 < 10) {

					avgP4Last10 += Schedule.at(i).Ratings.at(0);
					avgPALast10 += Schedule.at(i).Ratings.at(1);

					count10++;

					if (Schedule.at(i).IsHome) {

						HomeGamesLast10++;

					} else {

						AwayGamesLast10++;
					}
				}
			}
		}
	}

	if (count >= 1) {

		avgP4 = avgP4/double(count);
		avgPA = avgPA/double(count);

		avgP4Quarter = avgP4Quarter/double(countQ);
		avgPAQuarter = avgPAQuarter/double(countQ);

		avgP4Last10 = avgP4Last10/double(count10);
		avgPALast10 = avgPALast10/double(count10);

	}
};

void Team::Calculate(int tx) {

	Average();
	CalcPercent();
	Shock();

};
void Team::CalculatePlayoffs() {

	PlayoffAverage();
	PlayoffCalcPercent();
	Shock();

};
void Team::Calculate() {

	Average();
	CalcPercent();
	Shock();

};
void Team::read(ifstream *in) {
    
    in->read((char *) this, sizeof(Team));
};
void Team::write(ofstream *out) {
    
    out->write((char *) this, sizeof(Team));
    
};
