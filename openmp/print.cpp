/*
 * print.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: Junior
 */


#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <limits>

#include "random.h"
#include "game.h"
#include "read.h"
#include "team.h"
#include "standing.h"
#include "functions.h"
#include "ranking.h"
#include "postseason.h"
#include "histograms.h"

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;
using std::ofstream;
using std::ios;
using std::pair;

class Game;
class Team;

void PrintLevel(int p, bool &p_margins, bool &p_averages, bool &p_rankings,
		       bool &p_histograms, bool &p_standings, double &t, bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintLevel starting...\n"); }

	if (p>=16) {

		p_margins=true;

		if (p>=24) {

			p_averages=true;

			if (p>=28) {

				p_rankings=true;

				if (p>=30) {

					p_histograms=true;

					if (p==31) p_standings=true;

					else p_standings=false;

				} else {

					p_histograms=false;

					if (p==29) p_standings=true;

					else p_standings=false;

				}

			} else {

				p_rankings=false;

				if (p>=26) {

					p_histograms=true;

					if (p==27) p_standings=true;

					else p_standings=false;

				} else {

					p_histograms=false;

					if (p==25) p_standings=true;

					else p_standings=false;

				}

			}

		} else {

			p_averages=false;

			if (p>=20) {

				p_rankings=true;

				if (p>=22) {

					p_histograms=true;

					if (p==23) p_standings=true;

					else p_standings=false;

				} else {

					p_histograms=false;

					if (p==21) p_standings=true;

					else p_standings=false;

				}

			} else {

				p_rankings=false;

				if (p>=18) {

					p_histograms=true;

					if (p==19) p_standings=true;

					else p_standings=false;

				} else {

					p_histograms=false;

					if (p==17) p_standings=true;

					else p_standings=false;

				}

			}

		}

	} else {

		p_margins=false;

		if (p>=8) {

			p_averages=true;

			if (p>=12) {

				p_rankings=true;

				if (p>=14) {

					p_histograms=true;

					if (p==15) p_standings=true;

					else p_standings=false;

				} else {

					p_histograms=false;

					if (p==13) p_standings=true;

					else p_standings=false;

				}

			} else {

				p_rankings=false;

				if (p>=10) {

					p_histograms=true;

					if (p==11) p_standings=true;

					else p_standings=false;

				} else {

					p_histograms=false;

					if (p==9) p_standings=true;

					else p_standings=false;

				}

			}

		} else {

			p_averages=false;

			if (p>=4) {

				p_rankings=true;

				if (p>=6) {

					p_histograms=true;

					if (p==7) p_standings=true;

					else p_standings=false;

				} else {

					p_histograms=false;

					if (p==5) p_standings=true;

					else p_standings=false;

				}

			} else {

				p_rankings=false;

				if (p>=2) {

					p_histograms=true;

					if (p==3) p_standings=true;

					else p_standings=false;

				} else {

					p_histograms=false;

					if (p==1) p_standings=true;

					else p_standings=false;

				}

			}

		}

	}

	if (debug) { printf("PrintLevel exiting...\n\n"); }

	clock_t endtime=clock();
	t=double(endtime-starttime)/CLOCKS_PER_SEC;
}
void PrintLevel(runparams &parms) {

	clock_t starttime=clock();

	if (parms.debug) { printf("PrintLevel starting...\n"); }

	if (parms.pl>=16) {

		parms.p_margins=true;

		if (parms.pl>=24) {

			parms.p_averages=true;

			if (parms.pl>=28) {

				parms.p_rankings=true;

				if (parms.pl>=30) {

					parms.p_histograms=true;

					if (parms.pl==31) parms.p_standings=true;

					else parms.p_standings=false;

				} else {

					parms.p_histograms=false;

					if (parms.pl==29) parms.p_standings=true;

					else parms.p_standings=false;

				}

			} else {

				parms.p_rankings=false;

				if (parms.pl>=26) {

					parms.p_histograms=true;

					if (parms.pl==27) parms.p_standings=true;

					else parms.p_standings=false;

				} else {

					parms.p_histograms=false;

					if (parms.pl==25) parms.p_standings=true;

					else parms.p_standings=false;

				}

			}

		} else {

			parms.p_averages=false;

			if (parms.pl>=20) {

				parms.p_rankings=true;

				if (parms.pl>=22) {

					parms.p_histograms=true;

					if (parms.pl==23) parms.p_standings=true;

					else parms.p_standings=false;

				} else {

					parms.p_histograms=false;

					if (parms.pl==21) parms.p_standings=true;

					else parms.p_standings=false;

				}

			} else {

				parms.p_rankings=false;

				if (parms.pl>=18) {

					parms.p_histograms=true;

					if (parms.pl==19) parms.p_standings=true;

					else parms.p_standings=false;

				} else {

					parms.p_histograms=false;

					if (parms.pl==17) parms.p_standings=true;

					else parms.p_standings=false;

				}

			}

		}

	} else {

		parms.p_margins=false;

		if (parms.pl>=8) {

			parms.p_averages=true;

			if (parms.pl>=12) {

				parms.p_rankings=true;

				if (parms.pl>=14) {

					parms.p_histograms=true;

					if (parms.pl==15) parms.p_standings=true;

					else parms.p_standings=false;

				} else {

					parms.p_histograms=false;

					if (parms.pl==13) parms.p_standings=true;

					else parms.p_standings=false;

				}

			} else {

				parms.p_rankings=false;

				if (parms.pl>=10) {

					parms.p_histograms=true;

					if (parms.pl==11) parms.p_standings=true;

					else parms.p_standings=false;

				} else {

					parms.p_histograms=false;

					if (parms.pl==9) parms.p_standings=true;

					else parms.p_standings=false;

				}

			}

		} else {

			parms.p_averages=false;

			if (parms.pl>=4) {

				parms.p_rankings=true;

				if (parms.pl>=6) {

					parms.p_histograms=true;

					if (parms.pl==7) parms.p_standings=true;

					else parms.p_standings=false;

				} else {

					parms.p_histograms=false;

					if (parms.pl==5) parms.p_standings=true;

					else parms.p_standings=false;

				}

			} else {

				parms.p_rankings=false;

				if (parms.pl>=2) {

					parms.p_histograms=true;

					if (parms.pl==3) parms.p_standings=true;

					else parms.p_standings=false;

				} else {

					parms.p_histograms=false;

					if (parms.pl==1) parms.p_standings=true;

					else parms.p_standings=false;

				}

			}

		}

	}

	if (parms.debug) { printf("PrintLevel exiting...\n\n"); }

	clock_t endtime=clock();
	parms.tprint=double(endtime-starttime)/CLOCKS_PER_SEC;
}
void PrintStandings(vector<map<string,Team> > &TheTeams, double &q,bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintStandings starting...\n"); }

	//ofstream ofile;

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.front().begin(); iterator != TheTeams.front().end(); iterator++) {

		string team = iterator->second.TeamName;
		string filename = team;
		filename.append(".league.csv");
		ofstream ofile(filename.c_str(), ios::trunc);

		int t; char buffer [80]; string strlist;

		for (int i=0; i<(int)TheTeams.front().find(team)->second.Lstand.size(); i++) {

			for (int j=0; j<(int)TheTeams.size(); j++) {

				t=sprintf(buffer,"%d,",TheTeams.at(j).find(team)->second.Lstand.at(i));
				strlist.append(buffer);
			}
			strlist.append("\n");

		}

		if (ofile.is_open()) {
			ofile << strlist;
			ofile.close();
		} else cout << "Unable to open file";

		string filename2 = team;
		filename2.append(".conference.csv");
		ofstream ofile2(filename2.c_str(), ios::trunc);
		strlist.clear();

		for (int i=0; i<(int)TheTeams.front().find(team)->second.Cstand.size(); i++) {

			for (int j=0; j<(int)TheTeams.size(); j++) {

				t=sprintf(buffer,"%d,",TheTeams.at(j).find(team)->second.Cstand.at(i));
				strlist.append(buffer);
			}
			strlist.append("\n");
		}

		if (ofile2.is_open()) {
			ofile2 << strlist;
			ofile2.close();
		} else cout << "Unable to open file";

		string filename3 = team;
		filename3.append(".division.csv");
		ofstream ofile3(filename3.c_str(), ios::trunc);
		strlist.clear();

		for (int i=0; i<(int)TheTeams.front().find(team)->second.Dstand.size(); i++) {

			for (int j=0; j<(int)TheTeams.size(); j++) {

				t=sprintf(buffer,"%d,",TheTeams.at(j).find(team)->second.Dstand.at(i));
				strlist.append(buffer);
			}
			strlist.append("\n");
		}

		if (ofile3.is_open()) {
			ofile3 << strlist;
			ofile3.close();
		} else cout << "Unable to open file";

	}

	if (debug) { printf("PrintStandings exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}

void PrintRankings(vector<map<string,Team> > &TheTeams,double &q,bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintRankings starting...\n"); }

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.front().begin(); iterator != TheTeams.front().end(); iterator++) {

		string team = iterator->second.TeamName;
		string filename = team;
		filename.append(".offense.csv");
		ofstream ofile(filename.c_str(), ios::trunc);

		int t; char buffer [80]; string strlist;

		for (int i=0; i<(int)TheTeams.front().find(team)->second.OffRtgRank.size(); i++) {

			for (int j=0; j<(int)TheTeams.size(); j++) {

				t=sprintf(buffer,"%d,",TheTeams.at(j).find(team)->second.OffRtgRank.at(i));
				strlist.append(buffer);
			}
			strlist.append("\n");

		}

		if (ofile.is_open()) {
			ofile << strlist;
			ofile.close();
		} else cout << "Unable to open file";

		string filename2 = team;
		filename2.append(".defense.csv");
		ofstream ofile2(filename2.c_str(), ios::trunc);
		strlist.clear();

		for (int i=0; i<(int)TheTeams.front().find(team)->second.DefRtgRank.size(); i++) {

			for (int j=0; j<(int)TheTeams.size(); j++) {

				t=sprintf(buffer,"%d,",TheTeams.at(j).find(team)->second.DefRtgRank.at(i));
				strlist.append(buffer);
			}
			strlist.append("\n");

		}

		if (ofile2.is_open()) {
			ofile2 << strlist;
			ofile2.close();
		} else cout << "Unable to open file";

		string filename3 = team;
		filename3.append(".differential.csv");
		ofstream ofile3(filename3.c_str(), ios::trunc);
		strlist.clear();

		for (int i=0; i<(int)TheTeams.front().find(team)->second.RtgDiffRank.size(); i++) {

			for (int j=0; j<(int)TheTeams.size(); j++) {

				t=sprintf(buffer,"%d,",TheTeams.at(j).find(team)->second.RtgDiffRank.at(i));
				strlist.append(buffer);
			}
			strlist.append("\n");

		}

		if (ofile3.is_open()) {
			ofile3 << strlist;
			ofile3.close();
		} else cout << "Unable to open file";
	}

	if (debug) { printf("PrintRankings exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}

void PrintAvgStandings(vector<map<string,Team> > &TheTeams,double &q,bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintAvgStandings starting...\n"); }

	map<string, vector<double> > stands;
	ofstream ofile("average_stands.csv", ios::trunc);
	int t; char buffer [80]; string strlist;

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.front().begin(); iterator != TheTeams.front().end(); iterator++) {

		string team = iterator->second.TeamName;

		vector<double> winloss(4,0.0);

		int sz = TheTeams.size();
		for (int i=0; i<(int)TheTeams.size(); i++) {

			winloss.at(0) += double(TheTeams.at(i).find(team)->second.Win)/double(sz);
			winloss.at(1) += double(TheTeams.at(i).find(team)->second.Loss)/double(sz);

			winloss.at(2) += double(TheTeams.at(i).find(team)->second.eWin)/double(sz);
			winloss.at(3) += double(TheTeams.at(i).find(team)->second.eLoss)/double(sz);

		}
		stands.insert(pair<string, vector<double> >(team,winloss));

	}

	vector<string> LeagueS;
	vector<string> EastS;
    vector<string> WestS;
    vector<string> AtlS;
    vector<string> CenS;
    vector<string> SES;
    vector<string> NWS;
    vector<string> PacS;
    vector<string> SWS;
    vector<string> MWS;

	vector<string> eLeagueS;
	vector<string> eEastS;
    vector<string> eWestS;
    vector<string> eAtlS;
    vector<string> eCenS;
    vector<string> eSES;
    vector<string> eNWS;
    vector<string> ePacS;
    vector<string> eSWS;
    vector<string> eMWS;

	for (it_type iterator = TheTeams.front().begin(); iterator != TheTeams.front().end(); iterator++) {

		string team = iterator->second.TeamName;

		//cout << team << " " << iterator->second.Division << endl;

		//League
		bool lfound = false;
		for (int i=0; i<(int)LeagueS.size(); i++) {

			if (stands.find(team)->second.at(0) >= stands.find(LeagueS.at(i))->second.at(0)) {

				LeagueS.insert(LeagueS.begin()+i,team);
				lfound = true;
				break;

			}
		}
		if (!lfound) {

			LeagueS.push_back(team);
		}

		bool elfound = false;
		for (int i=0; i<(int)eLeagueS.size(); i++) {

			if (stands.find(team)->second.at(2) >= stands.find(eLeagueS.at(i))->second.at(2)) {

				eLeagueS.insert(eLeagueS.begin()+i,team);
				elfound = true;
				break;

			}
		}
		if (!elfound) {

			eLeagueS.push_back(team);
		}

		/*
		 *
		 */

		// Eastern
		if (iterator->second.Conference=="Eastern") {

			bool efound = false;
			for (int i=0; i<(int)EastS.size(); i++) {

				if (stands.find(team)->second.at(0) >= stands.find(EastS.at(i))->second.at(0)) {

					EastS.insert(EastS.begin()+i,team);
					efound = true;
					break;

				}
			}
			if (!efound) {

				EastS.push_back(team);

			}

			bool eefound = false;
			for (int i=0; i<(int)eEastS.size(); i++) {

				if (stands.find(team)->second.at(2) >= stands.find(eEastS.at(i))->second.at(2)) {

					eEastS.insert(eEastS.begin()+i,team);
					eefound = true;
					break;

				}
			}
			if (!eefound) {

				eEastS.push_back(team);

			}
		}

		/*
		 *
		 */

		// Western
		if (iterator->second.Conference=="Western") {

			bool wfound = false;
			for (int i=0; i<(int)WestS.size(); i++) {

				if (stands.find(team)->second.at(0) >= stands.find(WestS.at(i))->second.at(0)) {

					WestS.insert(WestS.begin()+i,team);
					wfound = true;
					break;

				}
			}
			if (!wfound) {

				WestS.push_back(team);

			}

			bool ewfound = false;
			for (int i=0; i<(int)eWestS.size(); i++) {

				if (stands.find(team)->second.at(2) >= stands.find(eWestS.at(i))->second.at(2)) {

					eWestS.insert(eWestS.begin()+i,team);
					ewfound = true;
					break;

				}
			}
			if (!ewfound) {

				eWestS.push_back(team);

			}
		}

		/*
		 *
		 */

		// Atlantic
		if (iterator->second.Division == "Atlantic") {

			bool afound = false;
			for (int i=0; i<(int)AtlS.size(); i++) {

				if (stands.find(team)->second.at(0) >= stands.find(AtlS.at(i))->second.at(0)) {

					AtlS.insert(AtlS.begin()+i,team);
					afound = true;
					break;

				}
			}
			if (!afound) {

				AtlS.push_back(team);

			}

			bool eafound = false;
			for (int i=0; i<(int)eAtlS.size(); i++) {

				if (stands.find(team)->second.at(2) >= stands.find(eAtlS.at(i))->second.at(2)) {

					eAtlS.insert(eAtlS.begin()+i,team);
					eafound = true;
					break;

				}
			}
			if (!eafound) {

				eAtlS.push_back(team);

			}
		}

		/*
		 *
		 */

		// Central
		if (iterator->second.Division == "Central") {

			bool cfound = false;
			for (int i=0; i<(int)CenS.size(); i++) {

				if (stands.find(team)->second.at(0) >= stands.find(CenS.at(i))->second.at(0)) {

					CenS.insert(CenS.begin()+i,team);
					cfound = true;
					break;

				}
			}
			if (!cfound) {

				CenS.push_back(team);

			}

			bool ecfound = false;
			for (int i=0; i<(int)eCenS.size(); i++) {

				if (stands.find(team)->second.at(2) >= stands.find(eCenS.at(i))->second.at(2)) {

					eCenS.insert(eCenS.begin()+i,team);
					ecfound = true;
					break;

				}
			}
			if (!ecfound) {

				eCenS.push_back(team);

			}
		}

		/*
		 *
		 */

		// Southeast
		if (iterator->second.Division == "Southeast") {

			bool sefound = false;
			for (int i=0; i<(int)SES.size(); i++) {

				if (stands.find(team)->second.at(0) >= stands.find(SES.at(i))->second.at(0)) {

					SES.insert(SES.begin()+i,team);
					sefound = true;
					break;

				}
			}
			if (!sefound) {

				SES.push_back(iterator->second.TeamName);

			}

			bool esefound = false;
			for (int i=0; i<(int)eSES.size(); i++) {

				if (stands.find(team)->second.at(2) >= stands.find(eSES.at(i))->second.at(2)) {

					eSES.insert(eSES.begin()+i,team);
					esefound = true;
					break;

				}
			}
			if (!esefound) {

				eSES.push_back(iterator->second.TeamName);

			}
		}

		/*
		 *
		 */

		// Northwest
		if (iterator->second.Division == "Northwest") {

			bool nfound = false;
			for (int i=0; i<(int)NWS.size(); i++) {

				if (stands.find(team)->second.at(0) >= stands.find(NWS.at(i))->second.at(0)) {

					NWS.insert(NWS.begin()+i,team);
					nfound = true;
					break;

				}
			}
			if (!nfound) {

				NWS.push_back(team);

			}

			bool enfound = false;
			for (int i=0; i<(int)eNWS.size(); i++) {

				if (stands.find(team)->second.at(2) >= stands.find(eNWS.at(i))->second.at(2)) {

					eNWS.insert(eNWS.begin()+i,team);
					enfound = true;
					break;

				}
			}
			if (!enfound) {

				eNWS.push_back(team);

			}
		}


		/*
		 *
		 */

		// Pacific
		if (iterator->second.Division == "Pacific") {

			bool pfound = false;
			for (int i=0; i<(int)PacS.size(); i++) {

				if (stands.find(team)->second.at(0) >= stands.find(PacS.at(i))->second.at(0)) {

					PacS.insert(PacS.begin()+i,team);
					pfound = true;
					break;

				}
			}
			if (!pfound) {

				PacS.push_back(team);

			}

			bool epfound = false;
			for (int i=0; i<(int)ePacS.size(); i++) {

				if (stands.find(team)->second.at(2) >= stands.find(ePacS.at(i))->second.at(2)) {

					ePacS.insert(ePacS.begin()+i,team);
					epfound = true;
					break;

				}
			}
			if (!epfound) {

				ePacS.push_back(team);

			}
		}



		// Southwest
		if (iterator->second.Division == "Southwest") {

			bool swfound = false;
			for (int i=0; i<(int)SWS.size(); i++) {

				if (stands.find(team)->second.at(0) >= stands.find(SWS.at(i))->second.at(0)) {

					SWS.insert(SWS.begin()+i,team);
					swfound = true;
					break;

				}
			}
			if (!swfound) {

				SWS.push_back(team);

			}

			bool eswfound = false;
			for (int i=0; i<(int)eSWS.size(); i++) {

				if (stands.find(team)->second.at(2) >= stands.find(eSWS.at(i))->second.at(2)) {

					eSWS.insert(eSWS.begin()+i,team);
					eswfound = true;
					break;

				}
			}
			if (!eswfound) {

				eSWS.push_back(team);

			}
		}

		/*
		 *
		 */

		// Midwest
		if (iterator->second.Division == "Midwest") {

			bool mfound = false;
			for (int i=0; i<(int)MWS.size(); i++) {

				if (stands.find(team)->second.at(0) >= stands.find(MWS.at(i))->second.at(0)) {

					MWS.insert(MWS.begin()+i,team);
					mfound = true;
					break;

				}
			}
			if (!mfound) {

				MWS.push_back(team);

			}

			bool emfound = false;
			for (int i=0; i<(int)eMWS.size(); i++) {

				if (stands.find(team)->second.at(2) >= stands.find(eMWS.at(i))->second.at(2)) {

					eMWS.insert(eMWS.begin()+i,team);
					emfound = true;
					break;

				}
			}
			if (!emfound) {

				eMWS.push_back(team);

			}
		}

	}

	strlist.append("Real,,,,,,,,,,,Effective,\n");

	strlist.append("League,Eastern,Western,Atlantic,Central,Southeast,Midwest,Northwest,Pacific,Southwest,,League,Eastern,Western,Atlantic,Central,Southeast,Midwest,Northwest,Pacific,Southwest,\n");
/*
	if (MWS.size()>0) {
		strlist.append("League,Eastern,Western,Atlantic,Central,Midwest,Pacific,,,,League,Eastern,Western,Atlantic,Central,Midwest,Pacific,\n");
	} else if (SES.size()>0) {
		strlist.append("League,Eastern,Western,Atlantic,Central,Southeast,Northwest,Pacific,Southwest,,League,Eastern,Western,Atlantic,Central,Southeast,Northwest,Pacific,Southwest,\n");
	}
*/
	for (int i=0; i<(int)LeagueS.size(); i++) {

		t=sprintf(buffer,"%s ",LeagueS.at(i).c_str());
		strlist.append(buffer);
		t=sprintf(buffer,"%4.2f - ",stands.find(LeagueS.at(i))->second.at(0));
		strlist.append(buffer);
		t=sprintf(buffer,"%4.2f,",stands.find(LeagueS.at(i))->second.at(1));
		strlist.append(buffer);

		if (i<(int)EastS.size()) {
			t=sprintf(buffer,"%s ",EastS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(EastS.at(i))->second.at(0));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(EastS.at(i))->second.at(1));
			strlist.append(buffer);
		}
		strlist.append(",");
		if (i<(int)WestS.size()) {
			t=sprintf(buffer,"%s ",WestS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(WestS.at(i))->second.at(0));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(WestS.at(i))->second.at(1));
			strlist.append(buffer);
		}
		strlist.append(",");
/*
		cout << "hello conf" << endl;
		if (i<14) {

			if (i<(int)EastS.size()) {
				t=sprintf(buffer,"%s ",EastS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(EastS.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f",stands.find(EastS.at(i))->second.at(1));
				strlist.append(buffer);
			}
			strlist.append(",");
			if (i<(int)WestS.size()) {
				t=sprintf(buffer,"%s ",WestS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(WestS.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f",stands.find(WestS.at(i))->second.at(1));
				strlist.append(buffer);
			}
			strlist.append(",");
		} else {

			strlist.append(",,");

		}
*/

		if (i<(int)AtlS.size()) {
			t=sprintf(buffer,"%s ",AtlS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(AtlS.at(i))->second.at(0));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(AtlS.at(i))->second.at(1));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)CenS.size()) {
			t=sprintf(buffer,"%s ",CenS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(CenS.at(i))->second.at(0));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(CenS.at(i))->second.at(1));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)SES.size()) {
			t=sprintf(buffer,"%s ",SES.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(SES.at(i))->second.at(0));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(SES.at(i))->second.at(1));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)MWS.size()) {
			t=sprintf(buffer,"%s ",MWS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(MWS.at(i))->second.at(0));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(MWS.at(i))->second.at(1));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)NWS.size()) {
			t=sprintf(buffer,"%s ",NWS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(NWS.at(i))->second.at(0));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(NWS.at(i))->second.at(1));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)PacS.size()) {
			t=sprintf(buffer,"%s ",PacS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(PacS.at(i))->second.at(0));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(PacS.at(i))->second.at(1));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)SWS.size()) {
			t=sprintf(buffer,"%s ",SWS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(SWS.at(i))->second.at(0));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(SWS.at(i))->second.at(1));
			strlist.append(buffer);
		}
		strlist.append(",");

/*
		if (i<5) {

			if (SES.size()>0) {

				t=sprintf(buffer,"%s ",AtlS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(AtlS.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(AtlS.at(i))->second.at(1));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",CenS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(CenS.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(CenS.at(i))->second.at(1));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",SES.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(SES.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(SES.at(i))->second.at(1));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",NWS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(NWS.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(NWS.at(i))->second.at(1));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",PacS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(PacS.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(PacS.at(i))->second.at(1));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",SWS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(SWS.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(SWS.at(i))->second.at(1));
				strlist.append(buffer);

			} else if (MWS.size()>0) {

				t=sprintf(buffer,"%s ",AtlS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(AtlS.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(AtlS.at(i))->second.at(1));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",CenS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(CenS.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(CenS.at(i))->second.at(1));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",MWS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(MWS.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(MWS.at(i))->second.at(1));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",PacS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(PacS.at(i))->second.at(0));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(PacS.at(i))->second.at(1));
				strlist.append(buffer);

			}


		} else {

			strlist.append(",,,,,,,,");
		}
*/

		strlist.append(",");

		t=sprintf(buffer,"%s ",eLeagueS.at(i).c_str());
		strlist.append(buffer);
		t=sprintf(buffer,"%4.2f - ",stands.find(eLeagueS.at(i))->second.at(2));
		strlist.append(buffer);
		t=sprintf(buffer,"%4.2f,",stands.find(eLeagueS.at(i))->second.at(3));
		strlist.append(buffer);

		if (i<(int)eEastS.size()) {
			t=sprintf(buffer,"%s ",eEastS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(eEastS.at(i))->second.at(2));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(eEastS.at(i))->second.at(3));
			strlist.append(buffer);
		}
		strlist.append(",");
		if (i<(int)eWestS.size()) {
			t=sprintf(buffer,"%s ",eWestS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(eWestS.at(i))->second.at(2));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(eWestS.at(i))->second.at(3));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)eAtlS.size()) {
			t=sprintf(buffer,"%s ",eAtlS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(eAtlS.at(i))->second.at(2));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(eAtlS.at(i))->second.at(3));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)eCenS.size()) {
			t=sprintf(buffer,"%s ",eCenS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(eCenS.at(i))->second.at(2));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(eCenS.at(i))->second.at(3));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)eSES.size()) {
			t=sprintf(buffer,"%s ",eSES.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(eSES.at(i))->second.at(2));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(eSES.at(i))->second.at(3));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)eMWS.size()) {
			t=sprintf(buffer,"%s ",eMWS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(eMWS.at(i))->second.at(2));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(eMWS.at(i))->second.at(3));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)eNWS.size()) {
			t=sprintf(buffer,"%s ",eNWS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(eNWS.at(i))->second.at(2));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(eNWS.at(i))->second.at(3));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)ePacS.size()) {
			t=sprintf(buffer,"%s ",ePacS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(ePacS.at(i))->second.at(2));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(ePacS.at(i))->second.at(3));
			strlist.append(buffer);
		}
		strlist.append(",");

		if (i<(int)eSWS.size()) {
			t=sprintf(buffer,"%s ",eSWS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(eSWS.at(i))->second.at(2));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f",stands.find(eSWS.at(i))->second.at(3));
			strlist.append(buffer);
		}
		strlist.append(",");

		/*
		 *
		 *
		 *
		 *
		 */
/*
		t=sprintf(buffer,"%s ",eLeagueS.at(i).c_str());
		strlist.append(buffer);
		t=sprintf(buffer,"%4.2f - ",stands.find(eLeagueS.at(i))->second.at(2));
		strlist.append(buffer);
		t=sprintf(buffer,"%4.2f,",stands.find(eLeagueS.at(i))->second.at(3));
		strlist.append(buffer);

		cout << "hello conf" << endl;
		if (i<14) {

			t=sprintf(buffer,"%s ",eEastS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(eEastS.at(i))->second.at(2));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f,",stands.find(eEastS.at(i))->second.at(3));
			strlist.append(buffer);

			t=sprintf(buffer,"%s ",eWestS.at(i).c_str());
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f - ",stands.find(eWestS.at(i))->second.at(2));
			strlist.append(buffer);
			t=sprintf(buffer,"%4.2f,",stands.find(eWestS.at(i))->second.at(3));
			strlist.append(buffer);

		} else {

			strlist.append(",,");

		}

		cout << "hello division" << endl;
		if (i<5) {

			if (SES.size()>0) {

				t=sprintf(buffer,"%s ",eAtlS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(eAtlS.at(i))->second.at(2));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(eAtlS.at(i))->second.at(3));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",eCenS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(eCenS.at(i))->second.at(2));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(eCenS.at(i))->second.at(3));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",eSES.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(eSES.at(i))->second.at(2));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(eSES.at(i))->second.at(3));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",eNWS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(eNWS.at(i))->second.at(2));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(eNWS.at(i))->second.at(3));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",ePacS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(ePacS.at(i))->second.at(2));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(ePacS.at(i))->second.at(3));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",eSWS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(eSWS.at(i))->second.at(2));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(eSWS.at(i))->second.at(3));
				strlist.append(buffer);

			} else if (MWS.size()>0) {

				t=sprintf(buffer,"%s ",eAtlS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(eAtlS.at(i))->second.at(2));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(eAtlS.at(i))->second.at(3));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",eCenS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(eCenS.at(i))->second.at(2));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(eCenS.at(i))->second.at(3));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",eMWS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(eMWS.at(i))->second.at(2));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(eMWS.at(i))->second.at(3));
				strlist.append(buffer);

				t=sprintf(buffer,"%s ",ePacS.at(i).c_str());
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f - ",stands.find(ePacS.at(i))->second.at(2));
				strlist.append(buffer);
				t=sprintf(buffer,"%4.2f,",stands.find(ePacS.at(i))->second.at(3));
				strlist.append(buffer);

			}

		} else {

			strlist.append(",,,,,,,,");
		}
*/
		strlist.append("\n");

	}

	if (ofile.is_open()) {
		ofile << strlist;
		ofile.close();
	} else cout << "Unable to open file";

	if (debug) { printf("PrintAvgStandings exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;
}
void PrintAgainst(vector<map<string, Team> > &T, const vector<vector<vector<double> > > &oppwin,double  &q,bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintAgainst starting...\n"); }

	string filename = "against.csv";
	ofstream ofile(filename.c_str(), ios::trunc);
	int t; char buffer [80]; string strlist;

	map<string, Team> NT = T.front();

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = T.front().begin(); iterator != T.front().end(); iterator++) {

		t=sprintf(buffer,",%s",iterator->second.TeamName.c_str());
		strlist.append(buffer);

	}
	strlist.append(",\n");

	int row=0;
	for (it_type iterator = T.front().begin(); iterator != T.front().end(); iterator++) {

		t=sprintf(buffer,"%s,",iterator->second.TeamName.c_str());
		strlist.append(buffer);

		for (int i=0; i<(int)oppwin.at(row).size(); i++) {

			if (row==i) { strlist.append(","); continue; }

			t=sprintf(buffer,"%6.4f-",oppwin.at(row).at(i).at(0));
			strlist.append(buffer);
			t=sprintf(buffer,"%6.4f,",oppwin.at(row).at(i).at(1));
			strlist.append(buffer);

		}
		strlist.append("\n");
		row++;
	}

	if (ofile.is_open()) {
		ofile << strlist;
		ofile.close();
	} else cout << "Unable to open file";

	if (debug) { printf("PrintAgainst exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}
void PrintSchedule(vector<map<string, Team> > &T, vector<vector<Game> > &Games,double &q, bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintSchedule starting...\n"); }

	string filename = "schedule.csv";
	ofstream ofile(filename.c_str(), ios::trunc);
	int t; char buffer [80]; string strlist;

	time_t closing_day;
	time_t opening_day = Games.front().front().GameDate;

	for (int k=(int)Games.front().size()-1; k>=0; k--) {

		if (!Games.front().at(k).Playoff) { closing_day=Games.front().at(k).GameDate; break; }

	}

	struct tm* tm = localtime(&opening_day);
	struct tm* tt = localtime(&opening_day);

	time_t today;

	strlist.append("Date,");
	do {

		int year = 1900 + tm->tm_year;
		int month = 1 + tm->tm_mon;
		int day = tm->tm_mday;

		t=sprintf(buffer,"%d-",year);
		strlist.append(buffer);
		t=sprintf(buffer,"%d-",month);
		strlist.append(buffer);
		t=sprintf(buffer,"%d,",day);
		strlist.append(buffer);

		tm->tm_mday++;
		today = mktime(tm);

	} while (today <= closing_day);

	strlist.append("Date,\n");

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = T.front().begin(); iterator != T.front().end(); iterator++) {

		string team = iterator->second.TeamName;
		strlist.append(team);
		strlist.append(",");

		tt = localtime(&opening_day);
		today = mktime(tt);

		while (today <= closing_day) {

			bool found = false;
			for (int i=0; i<(int)iterator->second.Schedule.size(); i++) {

				if (iterator->second.Schedule.at(i).Date==today) {

					found=true;
					string opp = iterator->second.Schedule.at(i).Opponent;
					double win = 0;
					double off = 0, def = 0;
					string home;

					if (iterator->second.Schedule.at(i).IsHome) {
						home = "";
					} else {
						home = "@";
					}

					for (int j=0; j<(int)T.size(); j++) {

						off += T.at(j).find(team)->second.Schedule.at(i).Ratings.at(0)/T.size();
						def += T.at(j).find(team)->second.Schedule.at(i).Ratings.at(1)/T.size();

						if (T.at(j).find(team)->second.Schedule.at(i).DidWin) {

							win = win + 1.0/T.size();

						}
					}

					t=sprintf(buffer,"%6.4f ",win);
					strlist.append(buffer);
					strlist.append(home);
					strlist.append(" ");
					strlist.append(opp);

					if (abs(off) > 0.001 && abs(def) > 0.001) {

						t=sprintf(buffer," %6.3f-",off);
						strlist.append(buffer);
						t=sprintf(buffer,"%6.3f",def);
						strlist.append(buffer);

					}
					strlist.append(",");

				}
			}
			if (!found){

				strlist.append(",");

			}
			tt->tm_mday++;
			today = mktime(tt);

		}
		strlist.append(iterator->second.TeamName);
		strlist.append(",\n");

	}

	struct tm* oz = localtime(&opening_day);

	strlist.append("Date,");
	do {

		int y = 1900 + oz->tm_year;
		int m = 1 + oz->tm_mon;
		int d = oz->tm_mday;

		t=sprintf(buffer,"%d-",y);
		strlist.append(buffer);
		t=sprintf(buffer,"%d-",m);
		strlist.append(buffer);
		t=sprintf(buffer,"%d,",d);
		strlist.append(buffer);

		oz->tm_mday++;
		today = mktime(oz);

	} while (today <= closing_day);
	strlist.append("Date,\n");

	if (ofile.is_open()) {
		ofile << strlist;
		ofile.close();
	} else cout << "Unable to open file";

	if (debug) { printf("PrintSchedule exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}
void PrintRefSchedule(vector<map<string, Team> > &T, vector<vector<Game> > &Games,string name,double &q, bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintSchedule starting...\n"); }

	string filename = name;
	ofstream ofile(filename.c_str(), ios::trunc);
	int t; char buffer [80]; string strlist;

	time_t closing_day;
	time_t opening_day = Games.front().front().GameDate;

	for (int k=(int)Games.front().size()-1; k>=0; k--) {

		if (!Games.front().at(k).Playoff) { closing_day=Games.front().at(k).GameDate; break; }

	}

	struct tm* tm = localtime(&opening_day);
	struct tm* tt = localtime(&opening_day);

	time_t today;

	strlist.append("Date,");
	do {

		int year = 1900 + tm->tm_year;
		int month = 1 + tm->tm_mon;
		int day = tm->tm_mday;

		t=sprintf(buffer,"%d-",year);
		strlist.append(buffer);
		t=sprintf(buffer,"%d-",month);
		strlist.append(buffer);
		t=sprintf(buffer,"%d,",day);
		strlist.append(buffer);

		tm->tm_mday++;
		today = mktime(tm);

	} while (today <= closing_day);
	strlist.append("Date,\n");

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = T.front().begin(); iterator != T.front().end(); iterator++) {

		string team = iterator->second.TeamName;
		strlist.append(team);
		strlist.append(",");

		tt = localtime(&opening_day);
		today = mktime(tt);

		while (today <= closing_day) {

			bool found = false;
			for (int i=0; i<(int)iterator->second.Schedule.size(); i++) {

				if (iterator->second.Schedule.at(i).Date==today) {

					found=true;
					string opp = iterator->second.Schedule.at(i).Opponent;
					string win = "";
					double off = 0.0, def = 0.0;
					string home;

					if (iterator->second.Schedule.at(i).IsHome) home = "";
					else home = "@";

					if (T.at(0).find(team)->second.Schedule.at(i).Ratings.size() == 2) {

						off = T.at(0).find(team)->second.Schedule.at(i).Ratings.at(0);
						def = T.at(0).find(team)->second.Schedule.at(i).Ratings.at(1);

					}

					if (T.at(0).find(team)->second.Schedule.at(i).Ratings.size()==0) {

						win ="";

					} else if (T.at(0).find(team)->second.Schedule.at(i).DidWin==true) {

						win = "W";

					} else if (T.at(0).find(team)->second.Schedule.at(i).DidWin==false) {

						win = "L";
					}

					t=sprintf(buffer,"%s ",win.c_str());
					strlist.append(buffer);
					strlist.append(home);
					strlist.append(" ");
					strlist.append(opp);

					if (abs(off) > 0.001 && abs(def) > 0.001) {

						t=sprintf(buffer," %5.2f-",off);
						strlist.append(buffer);
						t=sprintf(buffer,"%5.2f",def);
						strlist.append(buffer);

					}
					strlist.append(",");

				}
			}
			if (!found){

				strlist.append(",");

			}
			tt->tm_mday++;
			today = mktime(tt);

		}
		strlist.append(iterator->second.TeamName);
		strlist.append(",\n");

	}

	struct tm* oz = localtime(&opening_day);

	strlist.append("Date,");
	do {

		int y = 1900 + oz->tm_year;
		int m = 1 + oz->tm_mon;
		int d = oz->tm_mday;

		t=sprintf(buffer,"%d-",y);
		strlist.append(buffer);
		t=sprintf(buffer,"%d-",m);
		strlist.append(buffer);
		t=sprintf(buffer,"%d,",d);
		strlist.append(buffer);

		oz->tm_mday++;
		today = mktime(oz);

	} while (today <= closing_day);
	strlist.append("Date,\n");

	if (ofile.is_open()) {
		ofile << strlist;
		ofile.close();
	} else cout << "Unable to open file";

	if (debug) { printf("PrintSchedule exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}
void PrintAvgRankings(vector<map<string, Team> > &T, map<string, vector<double> > &AvgTeamRanks,double &q,bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintAvgRankings starting...\n"); }

	vector<vector<string> > ROstring((int)T.size());
	vector<vector<string> > RDstring((int)T.size());
	vector<vector<string> > Diffstring((int)T.size());

	vector<string> avgROstring;
	vector<string> avgRDstring;
	vector<string> avgDiffstring;

	vector<string> avgPOstring;
	vector<string> avgPDstring;
	vector<string> avgPDiffstring;

	for (int i=0; i<(int)T.size(); i++) {

		typedef map<string, vector<double> >::iterator its_type;
		if (i==0) {

			for (its_type iterator = AvgTeamRanks.begin(); iterator != AvgTeamRanks.end(); iterator++) {

				// Offensive Ratings
				bool fd = false;
				for (int j=0; j<(int)avgROstring.size(); j++) {

					if (iterator->second.at(0) > AvgTeamRanks.find(avgROstring.at(j))->second.at(0)) {

						avgROstring.insert(avgROstring.begin()+j,iterator->first);
						fd = true;
						break;
					}
				}
				if (!fd) {

					avgROstring.push_back(iterator->first);

				}

				// Defensive Ratings
				fd = false;
				for (int j=0; j<(int)avgRDstring.size(); j++) {

					if (iterator->second.at(1) < AvgTeamRanks.find(avgRDstring.at(j))->second.at(1)) {

						avgRDstring.insert(avgRDstring.begin()+j,iterator->first);
						fd = true;
						break;

					}
				}
				if (!fd) {

					avgRDstring.push_back(iterator->first);

				}

				// Differential Ratings
				fd = false;
				for (int j=0; j<(int)avgDiffstring.size(); j++) {

					if (iterator->second.at(2) > AvgTeamRanks.find(avgDiffstring.at(j))->second.at(2)) {

						avgDiffstring.insert(avgDiffstring.begin()+j,iterator->first);
						fd = true;
						break;

					}
				}
				if (!fd) {

					avgDiffstring.push_back(iterator->first);

				}

				/*
				 *
				 */

				// Offensive Points
				fd = false;
				for (int j=0; j<(int)avgPOstring.size(); j++) {

					if (iterator->second.at(3) > AvgTeamRanks.find(avgPOstring.at(j))->second.at(3)) {

						avgPOstring.insert(avgPOstring.begin()+j,iterator->first);
						fd = true;
						break;
					}
				}
				if (!fd) {

					avgPOstring.push_back(iterator->first);

				}

				// Defensive Points
				fd = false;
				for (int j=0; j<(int)avgPDstring.size(); j++) {

					if (iterator->second.at(4) < AvgTeamRanks.find(avgPDstring.at(j))->second.at(4)) {

						avgPDstring.insert(avgPDstring.begin()+j,iterator->first);
						fd = true;
						break;

					}
				}
				if (!fd) {

					avgPDstring.push_back(iterator->first);

				}

				// Differential Points
				fd = false;
				for (int j=0; j<(int)avgPDiffstring.size(); j++) {

					if (iterator->second.at(5) > AvgTeamRanks.find(avgPDiffstring.at(j))->second.at(5)) {

						avgPDiffstring.insert(avgPDiffstring.begin()+j,iterator->first);
						fd = true;
						break;

					}
				}
				if (!fd) {

					avgPDiffstring.push_back(iterator->first);

				}
			}
		}

		typedef map<string, Team>::iterator it_type;
		for (it_type iterator = T.at(i).begin(); iterator != T.at(i).end(); iterator++) {

			// Offensive Ratings
			bool found = false;
			for (int j=0; j<(int)ROstring.at(i).size(); j++) {

				if (iterator->second.OffRtg > T.at(i).find(ROstring.at(i).at(j))->second.OffRtg) {

					ROstring.at(i).insert(ROstring.at(i).begin()+j,iterator->second.TeamName);
					found = true;
					break;

				}
			}
			if (!found) {

				ROstring.at(i).push_back(iterator->second.TeamName);

			}

			/*
			 *
			 */

			// Defensive Ratings
			found = false;
			for (int j=0; j<(int)RDstring.at(i).size(); j++) {

				if (iterator->second.DefRtg < T.at(i).find(RDstring.at(i).at(j))->second.DefRtg) {

					RDstring.at(i).insert(RDstring.at(i).begin()+j,iterator->second.TeamName);
					found = true;
					break;

				}
			}
			if (!found) {

				RDstring.at(i).push_back(iterator->second.TeamName);

			}

			/*
			 *
			 */

			// Rating Differential
			found = false;
			double tdiff = iterator->second.OffRtg - iterator->second.DefRtg;

			for (int j=0; j<(int)Diffstring.at(i).size(); j++) {
				double diff = T.at(i).find(Diffstring.at(i).at(j))->second.OffRtg - T.at(i).find(Diffstring.at(i).at(j))->second.DefRtg;

				if (tdiff >= diff) {

					Diffstring.at(i).insert(Diffstring.at(i).begin()+j,iterator->second.TeamName);
					found = true;
					break;
				}
			}
			if (!found) {

				Diffstring.at(i).push_back(iterator->second.TeamName);

			}
		}
	}


	string filename = "rating.csv";
	ofstream ofile(filename.c_str(), ios::trunc);
	int t; char buffer [80]; string strlist;

	for (int i=0; i<(int)ROstring.front().size(); i++) {

		strlist.append(avgROstring.at(i));
		t=sprintf(buffer," %5.2f,,",AvgTeamRanks.find(avgROstring.at(i))->second.at(0));
		strlist.append(buffer);

		for (int j=0; j<(int)ROstring.size(); j++) {

			strlist.append(ROstring.at(j).at(i));
			t=sprintf(buffer," %5.2f,",T.at(j).find(ROstring.at(j).at(i))->second.OffRtg);
			strlist.append(buffer);

		}
		strlist.append("\n");
	}
	strlist.append("\n");

	for (int i=0; i<(int)RDstring.front().size(); i++) {

		strlist.append(avgRDstring.at(i));
		t=sprintf(buffer," %5.2f,,",AvgTeamRanks.find(avgRDstring.at(i))->second.at(1));
		strlist.append(buffer);

		for (int j=0; j<(int)RDstring.size(); j++) {

			strlist.append(RDstring.at(j).at(i));
			t=sprintf(buffer," %5.2f,",T.at(j).find(RDstring.at(j).at(i))->second.DefRtg);
			strlist.append(buffer);

		}
		strlist.append("\n");
	}
	strlist.append("\n");

	for (int i=0; i<(int)Diffstring.front().size(); i++) {

		strlist.append(avgDiffstring.at(i));
		t=sprintf(buffer," %5.2f,,",AvgTeamRanks.find(avgDiffstring.at(i))->second.at(2));
		strlist.append(buffer);

		for (int j=0; j<(int)Diffstring.size(); j++) {

			double diff = T.at(j).find(Diffstring.at(j).at(i))->second.OffRtg-T.at(j).find(Diffstring.at(j).at(i))->second.DefRtg;

			strlist.append(Diffstring.at(j).at(i));
			t=sprintf(buffer," %5.2f,",diff);
			strlist.append(buffer);

		}
		strlist.append("\n");
	}
	strlist.append("\n");

	if (ofile.is_open()) {
		ofile << strlist;
		ofile.close();
	} else cout << "Unable to open file";

	string file = "avgp4rating.csv";
	ofstream mfile(file.c_str(), ios::trunc);
    string str = "Points,Rating,\n";

	for (int i=0; i<(int)avgROstring.size(); i++) {

		str.append(avgPOstring.at(i));
		t=sprintf(buffer," %5.2f,",AvgTeamRanks.find(avgPOstring.at(i))->second.at(3));
		str.append(buffer);

		str.append(avgROstring.at(i));
		t=sprintf(buffer," %5.2f,",AvgTeamRanks.find(avgROstring.at(i))->second.at(0));
		str.append(buffer);

		str.append("\n");

	}
	str.append("\n");

	for (int i=0; i<(int)avgRDstring.size(); i++) {

		str.append(avgPDstring.at(i));
		t=sprintf(buffer," %5.2f,",AvgTeamRanks.find(avgPDstring.at(i))->second.at(4));
		str.append(buffer);

		str.append(avgRDstring.at(i));
		t=sprintf(buffer," %5.2f,",AvgTeamRanks.find(avgRDstring.at(i))->second.at(1));
		str.append(buffer);

		str.append("\n");

	}
	str.append("\n");

	for (int i=0; i<(int)avgDiffstring.size(); i++) {

		str.append(avgPDiffstring.at(i));
		t=sprintf(buffer," %5.2f,",AvgTeamRanks.find(avgPDiffstring.at(i))->second.at(5));
		str.append(buffer);

		str.append(avgDiffstring.at(i));
		t=sprintf(buffer," %5.2f,",AvgTeamRanks.find(avgDiffstring.at(i))->second.at(2));
		str.append(buffer);


		str.append("\n");

	}
	str.append("\n");

	if (mfile.is_open()) {
		mfile << str;
		mfile.close();
	} else cout << "Unable to open file";

	filename = "rating.restart.csv";
	ofstream bfile(filename.c_str(), ios::trunc);
	strlist="";

	for (int i=0; i<(int)ROstring.front().size(); i++) {

		strlist.append(avgROstring.at(i));
		t=sprintf(buffer,",%5.2f,%5.2f,%5.2f,\n",AvgTeamRanks.find(avgROstring.at(i))->second.at(0),
										         AvgTeamRanks.find(avgROstring.at(i))->second.at(1),
										         AvgTeamRanks.find(avgROstring.at(i))->second.at(2));
		strlist.append(buffer);
	}

	if (bfile.is_open()) {
		bfile << strlist;
		bfile.close();
	} else cout << "Unable to open file";


	if (debug) { printf("PrintAvgRankings exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}
void PrintDraft(vector<map<string, Team> > &T, map<string, vector<double> > &AvgDraftPos,double &q,bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintDraft starting...\n"); }

	vector<vector<string> > Lstring((int)T.size());
	vector<vector<string> > Dstring((int)T.size());

	vector<string> avgLstring;
	vector<string> avgDstring;

	typedef map<string, vector<double> >::iterator its_type;

	for (int i=0; i<(int)T.size(); i++) {

		if (i==0) {

			for (its_type iterator = AvgDraftPos.begin(); iterator != AvgDraftPos.end(); iterator++) {

				// Lottery
				bool fd = false;
				for (int j=0; j<(int)avgLstring.size(); j++) {

					if (iterator->second.at(0) > AvgDraftPos.find(avgLstring.at(j))->second.at(0)) {

						avgLstring.insert(avgLstring.begin()+j,iterator->first);
						fd = true;
						break;
					}
				}
				if (!fd) {

					avgLstring.push_back(iterator->first);

				}
			}

			for (its_type iterator = AvgDraftPos.begin(); iterator != AvgDraftPos.end(); iterator++) {

				// Draft Position
				bool fd = false;
				for (int j=0; j<(int)avgDstring.size(); j++) {

					if (iterator->second.at(1) > AvgDraftPos.find(avgDstring.at(j))->second.at(1)) {

						avgDstring.insert(avgDstring.begin()+j,iterator->first);
						fd = true;
						break;
					}
				}
				if (!fd) {

					avgDstring.push_back(iterator->first);

				}
			}

		}

		typedef map<string, Team>::iterator it_type;
		for (it_type iterator = T.at(i).begin(); iterator != T.at(i).end(); iterator++) {

			// Offensive Ratings
			bool found = false;
			for (int j=0; j<(int)Lstring.at(i).size(); j++) {

				if (iterator->second.Lottery > T.at(i).find(Lstring.at(i).at(j))->second.Lottery) {

					Lstring.at(i).insert(Lstring.at(i).begin()+j,iterator->second.TeamName);
					found = true;
					break;

				}
			}
			if (!found) {

				Lstring.at(i).push_back(iterator->second.TeamName);

			}
		}

		for (it_type iterator = T.at(i).begin(); iterator != T.at(i).end(); iterator++) {

			// Offensive Ratings
			bool found = false;
			for (int j=0; j<(int)Dstring.at(i).size(); j++) {

				if (iterator->second.DraftPos > T.at(i).find(Dstring.at(i).at(j))->second.DraftPos) {

					Dstring.at(i).insert(Dstring.at(i).begin()+j,iterator->second.TeamName);
					found = true;
					break;

				}
			}
			if (!found) {

				Dstring.at(i).push_back(iterator->second.TeamName);

			}
		}
	}

	string filename = "draft.csv";
	ofstream ofile(filename.c_str(), ios::trunc);
	int t; char buffer [80]; string strlist;

	for (int i=0; i<(int)avgLstring.size(); i++) {

		strlist.append(avgLstring.at(i));
		t=sprintf(buffer," %5.2f,,",AvgDraftPos.find(avgLstring.at(i))->second.at(0));
		strlist.append(buffer);

		for (int j=0; j<(int)Lstring.size(); j++) {

			strlist.append(Lstring.at(j).at(i));
			t=sprintf(buffer," %2d,",T.at(j).find(Lstring.at(j).at(i))->second.Lottery+1);
			strlist.append(buffer);

		}
		strlist.append("\n");
	}
	strlist.append("\n\n");

	for (int i=0; i<(int)avgDstring.size(); i++) {

		strlist.append(avgDstring.at(i));
		t=sprintf(buffer," %5.2f,,",AvgDraftPos.find(avgDstring.at(i))->second.at(1));
		strlist.append(buffer);

		for (int j=0; j<(int)Dstring.size(); j++) {

			strlist.append(Dstring.at(j).at(i));
			t=sprintf(buffer," %2d,",T.at(j).find(Dstring.at(j).at(i))->second.DraftPos+1);
			strlist.append(buffer);

		}
		strlist.append("\n");
	}
	strlist.append("\n");

	if (ofile.is_open()) {
		ofile << strlist;
		ofile.close();
	} else cout << "Unable to open file";

	string file = "avgp4draft.csv";
	ofstream mfile(file.c_str(), ios::trunc);
    string str = "Points,Rating,\n";

	for (int i=0; i<(int)avgLstring.size(); i++) {

		str.append(avgLstring.at(i));
		t=sprintf(buffer," %5.2f,",AvgDraftPos.find(avgLstring.at(i))->second.at(0));
		str.append(buffer);

		str.append(avgLstring.at(i));
		t=sprintf(buffer," %5.2f,",AvgDraftPos.find(avgDstring.at(i))->second.at(1));
		str.append(buffer);

		str.append("\n");

	}
	str.append("\n");

	str.append("\n");

	if (mfile.is_open()) {
		mfile << str;
		mfile.close();
	} else cout << "Unable to open file";


	if (debug) { printf("PrintDraft exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}
void PrintPlayoffs(vector<map<string, Team> > &T, double &q, bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintPlayoffs starting...\n"); }

	string filename = "playoffs.csv";
	ofstream ofile(filename.c_str(), ios::trunc);
	int t; char buffer [100]; string strlist;

	string name;

	vector<string> data(30);
	vector<int> ngames(30);

	for (int i=0; i<(int)T.size(); i++) {

		data.clear(); ngames.clear();name="";
		data.resize(30); ngames.resize(30);

		typedef map<string, Team>::iterator it_type;
		for (it_type iterator = T.at(i).begin(); iterator != T.at(i).end(); iterator++) {

			if (iterator->second.Conference=="Eastern") {

				if (iterator->second.PlayoffSeed==0) { data.at(0)=iterator->first; ngames.at(0)=iterator->second.oneWin; }
				else if (iterator->second.PlayoffSeed==7) { data.at(1)=iterator->first; ngames.at(1)=iterator->second.oneWin; }

				else if (iterator->second.PlayoffSeed==1) { data.at(6)=iterator->first; ngames.at(6)=iterator->second.oneWin; }
				else if (iterator->second.PlayoffSeed==6) { data.at(7)=iterator->first; ngames.at(7)=iterator->second.oneWin; }

				else if (iterator->second.PlayoffSeed==2) { data.at(4)=iterator->first; ngames.at(4)=iterator->second.oneWin; }
				else if (iterator->second.PlayoffSeed==5) { data.at(5)=iterator->first; ngames.at(5)=iterator->second.oneWin; }

				else if (iterator->second.PlayoffSeed==3) { data.at(2)=iterator->first; ngames.at(2)=iterator->second.oneWin; }
				else if (iterator->second.PlayoffSeed==4) { data.at(3)=iterator->first; ngames.at(3)=iterator->second.oneWin; }

				if (iterator->second.secondround=="east_A") { data.at(8)=iterator->first; ngames.at(8)=iterator->second.twoWin; }
				else if (iterator->second.secondround=="east_B") { data.at(9)=iterator->first; ngames.at(9)=iterator->second.twoWin; }

				else if (iterator->second.secondround=="east_C") { data.at(10)=iterator->first; ngames.at(10)=iterator->second.twoWin; }
				else if (iterator->second.secondround=="east_D") { data.at(11)=iterator->first; ngames.at(11)=iterator->second.twoWin; }

				if (iterator->second.conffinals=="east_top") { data.at(12)=iterator->first; ngames.at(12)=iterator->second.threeWin; }
				else if (iterator->second.conffinals=="east_bot") { data.at(13)=iterator->first; ngames.at(13)=iterator->second.threeWin; }

				if (iterator->second.finals=="east") { data.at(14)=iterator->first; ngames.at(14)=iterator->second.fourWin; }

			} else if (iterator->second.Conference=="Western") {

				if (iterator->second.PlayoffSeed==0) { data.at(15)=iterator->first; ngames.at(15)=iterator->second.oneWin; }
				else if (iterator->second.PlayoffSeed==7) { data.at(16)=iterator->first; ngames.at(16)=iterator->second.oneWin; }

				else if (iterator->second.PlayoffSeed==1) { data.at(21)=iterator->first; ngames.at(21)=iterator->second.oneWin; }
				else if (iterator->second.PlayoffSeed==6) { data.at(22)=iterator->first; ngames.at(22)=iterator->second.oneWin; }

				else if (iterator->second.PlayoffSeed==2) { data.at(19)=iterator->first; ngames.at(19)=iterator->second.oneWin; }
				else if (iterator->second.PlayoffSeed==5) { data.at(20)=iterator->first; ngames.at(20)=iterator->second.oneWin; }

				else if (iterator->second.PlayoffSeed==3) { data.at(17)=iterator->first; ngames.at(17)=iterator->second.oneWin; }
				else if (iterator->second.PlayoffSeed==4) { data.at(18)=iterator->first; ngames.at(18)=iterator->second.oneWin; }

				if (iterator->second.secondround=="west_A") { data.at(23)=iterator->first; ngames.at(23)=iterator->second.twoWin; }
				else if (iterator->second.secondround=="west_B") { data.at(24)=iterator->first; ngames.at(24)=iterator->second.twoWin; }

				else if (iterator->second.secondround=="west_C") { data.at(25)=iterator->first; ngames.at(25)=iterator->second.twoWin; }
				else if (iterator->second.secondround=="west_D") { data.at(26)=iterator->first; ngames.at(26)=iterator->second.twoWin; }

				if (iterator->second.conffinals=="west_top") { data.at(27)=iterator->first; ngames.at(27)=iterator->second.threeWin; }
				else if (iterator->second.conffinals=="west_bot") { data.at(28)=iterator->first; ngames.at(28)=iterator->second.threeWin; }

				if (iterator->second.finals=="west") { data.at(29)=iterator->first; ngames.at(29)=iterator->second.fourWin; }

			}
		}

		//eastern first round
		t=sprintf(buffer,"%s%d%s%d-%s%d%s%d-%s%d%s%d-%s%d%s%d--",
				  data.at(0).c_str(),ngames.at(0),data.at(1).c_str(),ngames.at(1),
				  data.at(2).c_str(),ngames.at(2),data.at(3).c_str(),ngames.at(3),
				  data.at(4).c_str(),ngames.at(4),data.at(5).c_str(),ngames.at(5),
				  data.at(6).c_str(),ngames.at(6),data.at(7).c_str(),ngames.at(7));

		name.append(buffer);

		//eastern last rounds
		t=sprintf(buffer,"%s%d%s%d-%s%d%s%d--%s%d%s%d--%s%d---",
				  data.at(8).c_str(),ngames.at(8),data.at(9).c_str(),ngames.at(9),
				  data.at(10).c_str(),ngames.at(10),data.at(11).c_str(),ngames.at(11),
				  data.at(12).c_str(),ngames.at(12),data.at(13).c_str(),ngames.at(13),
				  data.at(14).c_str(),ngames.at(14));

		name.append(buffer);

		//western first round
		t=sprintf(buffer,"%s%d%s%d-%s%d%s%d-%s%d%s%d-%s%d%s%d--",
				  data.at(15).c_str(),ngames.at(15),data.at(16).c_str(),ngames.at(16),
				  data.at(17).c_str(),ngames.at(17),data.at(18).c_str(),ngames.at(18),
				  data.at(19).c_str(),ngames.at(19),data.at(20).c_str(),ngames.at(20),
				  data.at(21).c_str(),ngames.at(21),data.at(22).c_str(),ngames.at(22));

		name.append(buffer);

		//western last rounds
		t=sprintf(buffer,"%s%d%s%d-%s%d%s%d--%s%d%s%d--%s%d",
				  data.at(23).c_str(),ngames.at(23),data.at(24).c_str(),ngames.at(24),
				  data.at(25).c_str(),ngames.at(25),data.at(26).c_str(),ngames.at(26),
				  data.at(27).c_str(),ngames.at(27),data.at(28).c_str(),ngames.at(28),
				  data.at(29).c_str(),ngames.at(29));

		name.append(buffer);

		strlist.append("RND 1, RND 2, RND 3,,Finals,, RND 3, RND 2, RND 1,,ID,");
		strlist.append(name); strlist.append(",\n");
		t=sprintf(buffer,"%s %2d,,,,,,,,%s %2d,\n",data.at(0).c_str(),ngames.at(0),data.at(15).c_str(),ngames.at(15));
		strlist.append(buffer);

		t=sprintf(buffer,",%s %2d,,,,,,%s %2d,,\n",data.at(8).c_str(),ngames.at(8),data.at(23).c_str(),ngames.at(23));
		strlist.append(buffer);

		t=sprintf(buffer,"%s %2d,,,,,,,,%s %2d,\n",data.at(1).c_str(),ngames.at(1),data.at(16).c_str(),ngames.at(16));
		strlist.append(buffer);

		t=sprintf(buffer,",,%s %2d,,,,%s %2d,,,\n",data.at(12).c_str(),ngames.at(12),data.at(27).c_str(),ngames.at(27));
		strlist.append(buffer);

		t=sprintf(buffer,"%s %2d,,,,,,,,%s %2d,\n",data.at(2).c_str(),ngames.at(2),data.at(17).c_str(),ngames.at(17));
		strlist.append(buffer);

		t=sprintf(buffer,",%s %2d,,,,,,%s %2d,,\n",data.at(9).c_str(),ngames.at(9),data.at(24).c_str(),ngames.at(24));
		strlist.append(buffer);

		t=sprintf(buffer,"%s %2d,,,,,,,,%s %2d,\n",data.at(3).c_str(),ngames.at(3),data.at(18).c_str(),ngames.at(18));
		strlist.append(buffer);

		t=sprintf(buffer,",,,%s %2d,,%s %2d,,,,\n",data.at(14).c_str(),ngames.at(14),data.at(29).c_str(),ngames.at(29));
		strlist.append(buffer);



		t=sprintf(buffer,"%s %2d,,,,,,,,%s %2d,\n",data.at(4).c_str(),ngames.at(4),data.at(19).c_str(),ngames.at(19));
		strlist.append(buffer);

		t=sprintf(buffer,",%s %2d,,,,,,%s %2d,,\n",data.at(10).c_str(),ngames.at(10),data.at(25).c_str(),ngames.at(25));
		strlist.append(buffer);

		t=sprintf(buffer,"%s %2d,,,,,,,,%s %2d,\n",data.at(5).c_str(),ngames.at(5),data.at(20).c_str(),ngames.at(20));
		strlist.append(buffer);

		t=sprintf(buffer,",,%s %2d,,,,%s %2d,,,\n",data.at(13).c_str(),ngames.at(13),data.at(28).c_str(),ngames.at(28));
		strlist.append(buffer);

		t=sprintf(buffer,"%s %2d,,,,,,,,%s %2d,\n",data.at(6).c_str(),ngames.at(6),data.at(21).c_str(),ngames.at(21));
		strlist.append(buffer);

		t=sprintf(buffer,",%s %2d,,,,,,%s %2d,,\n",data.at(11).c_str(),ngames.at(11),data.at(26).c_str(),ngames.at(26));
		strlist.append(buffer);

		t=sprintf(buffer,"%s %2d,,,,,,,,%s %2d,\n",data.at(7).c_str(),ngames.at(7),data.at(22).c_str(),ngames.at(22));
		strlist.append(buffer);
		strlist.append("RND 1, RND 2, RND 3,,Finals,, RND 3, RND 2, RND 1,\n\n\n");

	}

	if (ofile.is_open()) {
		ofile << strlist;
		ofile.close();
	} else cout << "Unable to open file";

	if (debug) { printf("PrintPlayoffs exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}
void PrintHist(map<string, map<string, vector<double> > >&Hist, double &q, bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintHist starting...\n"); }

	string name;
	typedef map<string, map<string, vector<double> > >::iterator its_type;

	for (its_type iterator = Hist.begin(); iterator != Hist.end(); iterator++) {

		name=iterator->first;

		string filename = name; filename.append(".hist.csv");
		ofstream mfile(filename.c_str(), ios::trunc);
		int t; char buffer [80];

		string strlist="";

		strlist.append("Wins");

		for (int l=0; l<83; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("Wins")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("Wins")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		strlist.append("Loss");

		for (int l=0; l<83; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("Loss")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("Loss")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		strlist.append("pWins");

		for (int l=0; l<=16; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("pWins")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("pWins")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		strlist.append("pLoss");

		for (int l=0; l<=13; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("pLoss")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("pLoss")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		strlist.append("ORanks");

		for (int l=1; l<=30; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("ORanks")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("ORanks")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		strlist.append("DRanks");

		for (int l=1; l<=30; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("DRanks")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("DRanks")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		strlist.append("League");

		for (int l=1; l<=30; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("League")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("League")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		strlist.append("Conference");

		for (int l=1; l<=15; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("Conference")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("Conference")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		strlist.append("Division");

		for (int l=1; l<=5; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("Division")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("Division")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		strlist.append("Seeds");

		for (int l=1; l<=8; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("Seeds")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("Seeds")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		strlist.append("Lottery");

		for (int l=1; l<=30; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("Lottery")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("Lottery")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		strlist.append("DraftPos");

		for (int l=1; l<=30; l++) { t=sprintf(buffer,",%d",l); strlist.append(buffer); }

		strlist.append("\n");

		for (int i=0; i<(int)iterator->second.find("DraftPos")->second.size(); i++ ) {

			t=sprintf(buffer,",%.6f",iterator->second.find("DraftPos")->second.at(i));
			strlist.append(buffer);

		}
		strlist.append("\n\n");

		if (mfile.is_open()) {
			mfile << strlist;
			mfile.close();
		} else cout << "Unable to open file";
	}

	if (debug) { printf("PrintHist exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}
void PrintMargins(vector<MarginRankings> &MarginRanks, vector<MarginStandings> &MarginStands, double &q, bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("PrintMargins starting...\n"); }

	for (int i=0; i<(int)MarginRanks.size(); i++) {

		string team = MarginRanks.at(i).TeamName;
		string filename = team;
		filename.append(".margins.csv");
		ofstream ofile(filename.c_str(), ios::trunc);

		int t; char buffer [80]; string strlist;

		t=sprintf(buffer,"%f,",MarginRanks.at(i).BestOff);
		strlist.append(buffer);

		t=sprintf(buffer,"%f,",MarginRanks.at(i).WorstOff);
		strlist.append(buffer);

		t=sprintf(buffer,"%f,",MarginRanks.at(i).BestDef);
		strlist.append(buffer);

		t=sprintf(buffer,"%f,",MarginRanks.at(i).WorstDef);
		strlist.append(buffer);

		t=sprintf(buffer,"%f,",MarginRanks.at(i).BestDiff);
		strlist.append(buffer);

		t=sprintf(buffer,"%f,",MarginRanks.at(i).WorstDiff);
		strlist.append(buffer);

		t=sprintf(buffer,"'%d-%d,",MarginStands.at(i).BestWin,MarginStands.at(i).BestLoss);
		strlist.append(buffer);

		t=sprintf(buffer,"'%d-%d,",MarginStands.at(i).WorstWin,MarginStands.at(i).WorstLoss);
		strlist.append(buffer);

		t=sprintf(buffer,"'%d-%d,",MarginStands.at(i).BestWinC,MarginStands.at(i).BestLossC);
		strlist.append(buffer);

		t=sprintf(buffer,"'%d-%d,",MarginStands.at(i).WorstWinC,MarginStands.at(i).WorstLossC);
		strlist.append(buffer);

		t=sprintf(buffer,"'%d-%d,",MarginStands.at(i).BestWinD,MarginStands.at(i).BestLossD);
		strlist.append(buffer);

		t=sprintf(buffer,"'%d-%d,",MarginStands.at(i).WorstWinD,MarginStands.at(i).WorstLossD);
		strlist.append(buffer);

		strlist.append("\n");

		strlist.append("Best Offense,Worst Offense,Best Defense,Worst Defensive,Best Differential,Worst Differential,"
					   "Best League Record, Worst League Record,Best Conference Record,Worst Conference Record,"
					   "Best Division Record, Worst Division Record\n");


		for (int j=0; j<(int)MarginRanks.at(i).BestOffense.size(); j++) {

			t=sprintf(buffer,"%d,",MarginRanks.at(i).BestOffense.at(j));
			strlist.append(buffer);

			t=sprintf(buffer,"%d,",MarginRanks.at(i).WorstOffense.at(j));
			strlist.append(buffer);

			t=sprintf(buffer,"%d,",MarginRanks.at(i).BestDefense.at(j));
			strlist.append(buffer);

			t=sprintf(buffer,"%d,",MarginRanks.at(i).WorstDefense.at(j));
			strlist.append(buffer);

			t=sprintf(buffer,"%d,",MarginRanks.at(i).BestDifferential.at(j));
			strlist.append(buffer);

			t=sprintf(buffer,"%d,",MarginRanks.at(i).WorstDifferential.at(j));
			strlist.append(buffer);

			t=sprintf(buffer,"%d,",MarginStands.at(i).BestLStanding.at(j));
			strlist.append(buffer);

			t=sprintf(buffer,"%d,",MarginStands.at(i).WorstLStanding.at(j));
			strlist.append(buffer);

			t=sprintf(buffer,"%d,",MarginStands.at(i).BestCStanding.at(j));
			strlist.append(buffer);

			t=sprintf(buffer,"%d,",MarginStands.at(i).WorstCStanding.at(j));
			strlist.append(buffer);

			t=sprintf(buffer,"%d,",MarginStands.at(i).BestDStanding.at(j));
			strlist.append(buffer);

			t=sprintf(buffer,"%d,",MarginStands.at(i).WorstDStanding.at(j));
			strlist.append(buffer);

			strlist.append("\n");

		}

		if (ofile.is_open()) {
			ofile << strlist;
			ofile.close();
		} else cout << "Unable to open file";
	}

	if (debug) { printf("PrintMargins exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;
}
void PrintSimulation(runparams &parms, vector<map<string, Team> > &T, vector<vector<Game> > &G,
		map<string,map<string, vector<double> > > &Hist) {

	vector<Bracket> Brackets;
	Brackets.resize(parms.Sim);

	//map<string, map<string, vector<double> > > Hist;
	map<string, vector<double> > AvgTeamRanks;
	map<string, vector<double> > AvgDraftPos;
	vector<MarginRankings> MarginRanks;
	vector<MarginStandings> MarginStands;

	vector<vector<vector<double> > > oppwin(T.front().size(), vector<vector<double> >(T.front().size(), vector<double>(2,0.0)));

#ifdef _OPENMP

	#pragma omp parallel sections
	{
		#pragma omp section
		if (parms.p_histograms) {

			PopulateHists(T,Hist,parms.thist,parms.debug);

		}

		#pragma omp section
		WinsAgainst(T,oppwin,parms.tagainst,parms.debug);

		#pragma omp section
		if (parms.p_rankings) {

			AverageRanking(T,AvgTeamRanks,parms.traverage,parms.debug);

		}

		#pragma omp section
		AverageDraft(T,AvgDraftPos,parms.tdaverage,parms.debug);

		#pragma omp section
		if (parms.p_margins) {

			BestWorstRanking(T,MarginRanks,parms.trmargin,parms.debug);
			BestWorstStanding(T,MarginStands,parms.tsmargin,parms.debug);

		}
	}

	#pragma omp parallel sections
	{
		#pragma omp section
		if (parms.p_standings) {

			printf("     MAIN| printing league standings    %50s\n","???.league.csv");
			printf("     MAIN| printing conference standings     %45s\n","???.conference.csv");
			printf("     MAIN| printing division standings       %45s\n","???.division.csv");
			PrintStandings(T,parms.tpstands,parms.debug);

			printf("     MAIN| printing average standings %52s\n","average_stands.csv");
			PrintAvgStandings(T,parms.tpraverage,parms.debug);

		}

		#pragma omp section
		{
			printf("     MAIN| printing win total against other teams %40s\n","against.csv");
			PrintAgainst(T,oppwin,parms.tpagainst,parms.debug);
		}


		#pragma omp section
		{
			printf("     MAIN| printing full schedule %56s\n","schedule.csv");
			PrintSchedule(T,G,parms.tpschedule,parms.debug);
		}


		#pragma omp section
		if (parms.p_rankings) {

			printf("     MAIN| printing average rankings    %50s\n","rating.csv");
			PrintAvgRankings(T,AvgTeamRanks,parms.tpraverage,parms.debug);
			printf("     MAIN| printing offensive rankings  %50s\n","???.offensive.csv");
			printf("     MAIN| printing defensive rankings  %50s\n","???.defensive.csv");
			printf("     MAIN| printing differential rankings    %45s\n","???.differential.csv");
			PrintRankings(T,parms.tpranks,parms.debug);

		}

		#pragma omp section
		{
			printf("     MAIN| printing draft information (lottery,position) %33s\n","draft.csv");
			PrintDraft(T,AvgDraftPos,parms.tpdraft,parms.debug);
		}

		#pragma omp section
		{
			printf("     MAIN| printing playoff brackets                     %33s\n","playoff.csv");
			PrintPlayoffs(T,parms.tpplayoffs,parms.debug);

		}

		#pragma omp section
		if (parms.p_margins) {

			printf("     MAIN| printing best and worst seasons   %45s\n","margins.csv");
			PrintMargins(MarginRanks,MarginStands,parms.tpmargin,parms.debug);

		}

		#pragma omp section
		if (parms.p_histograms) {

			printf("     MAIN| printing histogram data %55s\n","???.hist.csv");
			PrintHist(Hist,parms.tphist,parms.debug);

		}
	}
#else

	AverageDraft(T,AvgDraftPos,parms.tdaverage,parms.debug);
	WinsAgainst(T,oppwin,parms.tagainst,parms.debug);

	if (parms.p_histograms) {

		printf("     MAIN| calculating histogram data\n");
		PopulateHists(T,Hist,parms.thist,parms.debug);

	}

	if (parms.p_rankings) {

		printf("     MAIN| calculating average rank data\n");
		AverageRanking(T,AvgTeamRanks,parms.traverage,parms.debug);

	}

	if (parms.p_margins) {

		printf("     MAIN| calculating marginal data\n");
		BestWorstRanking(T,MarginRanks,parms.trmargin,parms.debug);
		BestWorstStanding(T,MarginStands,parms.tsmargin,parms.debug);

	}

	printf("     MAIN| printing win total against other teams %40s\n","against.csv");
	PrintAgainst(T,oppwin,parms.tpagainst,parms.debug);

	printf("     MAIN| printing full schedule %56s\n","schedule.csv");
	PrintSchedule(T,G,parms.tpschedule,parms.debug);

	printf("     MAIN| printing draft information (lottery,position) %33s\n","draft.csv");
	PrintDraft(T,AvgDraftPos,parms.tpdraft,parms.debug);

	if (parms.p_standings) {

		printf("     MAIN| printing league standings    %50s\n","???.league.csv");
		printf("     MAIN| printing conference standings     %45s\n","???.conference.csv");
		printf("     MAIN| printing division standings       %45s\n","???.division.csv");
		PrintStandings(T,parms.tpstands,parms.debug);

		printf("     MAIN| printing average standings %52s\n","average_stands.csv");
		PrintAvgStandings(T,parms.tpsaverage,parms.debug);

	}

	if (parms.p_rankings) {

		printf("     MAIN| printing offensive rankings  %50s\n","???.offensive.csv");
		printf("     MAIN| printing defensive rankings  %50s\n","???.defensive.csv");
		printf("     MAIN| printing differential rankings    %45s\n","???.differential.csv");
		PrintRankings(T,parms.tpranks,parms.debug);

		printf("     MAIN| printing average rankings    %50s\n","rating.csv");
		PrintAvgRankings(T,AvgTeamRanks,parms.tpraverage,parms.debug);

	}

	if (parms.p_margins) {

		printf("     MAIN| printing best and worst seasons   %45s\n","margins.csv");
		PrintMargins(MarginRanks,MarginStands,parms.tpmargin,parms.debug);

	}

	if (parms.p_histograms) {

		printf("     MAIN| printing histogram data %55s\n","???.hist.csv");
		PrintHist(Hist,parms.tphist,parms.debug);

	}
#endif
	printf("\n");
}
void PrintHeader(runparams &parms) {

	printf("\n\n\n");


    printf("                                        888                      \n");
    printf("                 ,e e,  888 8e   ,e e,  888 88e   ,e e,   ,'Y88b \n");
    printf("                d88 88b 888 88b d88 88b 888 888b d88 88b '8' 888 \n");
    printf("                888   , 888 888 888   , 888 888P 888   , ,ee 888 \n");
    printf("                 'YeeP' 888 888  'YeeP' 888 88'   'YeeP' '88 888 \n");
    printf("\n");
    printf("                                                            d8           \n");
    printf("                            888 888 8e   e88 88e  888 8e   d88    ,e e,  \n");
    printf("                            888 888 88b d888 888b 888 88b d88888 d88 88b \n");
    printf("                            888 888 888 Y888 888P 888 888  888   888   , \n");
    printf("                            888 888 888  '88 88'  888 888  888    'YeeP' \n");
    printf("\n");
    printf("                                                                 888           \n");
    printf("                                          e88'888  ,'Y88b 888,8, 888  e88 88e  \n");
    printf("                                         d888  '8 '8' 888 888 '  888 d888 888b \n");
    printf("                                         Y888   , ,ee 888 888    888 Y888 888P \n");
    printf("                                          '88,e8' '88 888 888    888  '88 88'  \n");
    printf("\n\n");

	int t; char buffer [80];
	time_t now = time(0);
	struct tm* tm = localtime(&now);

	int year = 1900 + tm->tm_year;
	int month = 1 + tm->tm_mon;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int min = tm->tm_min;
	int sec = tm->tm_sec;

	t=sprintf(buffer,"%4d-",year);
	parms.stime.append(buffer);
	t=sprintf(buffer,"%02d-",month);
	parms.stime.append(buffer);
	t=sprintf(buffer,"%02d ",day);
	parms.stime.append(buffer);
	t=sprintf(buffer,"%02d:",hour);
	parms.stime.append(buffer);
	t=sprintf(buffer,"%02d:",min);
	parms.stime.append(buffer);
	t=sprintf(buffer,"%02d",sec);
	parms.stime.append(buffer);

	parms.cwd=getenv("PWD");
	parms.uname=getenv("USER");
	parms.hostname=getenv("TERM_PROGRAM");

	printf("     MAIN| program started at %60s\n",parms.stime.c_str());
	printf("     MAIN| program started on %60s\n",parms.hostname);
	printf("     MAIN| program started by %60s\n",parms.uname);
	printf("     MAIN| program started for %59s\n","");
	printf("     MAIN| program started in %60s\n",parms.cwd);
	printf("\n");

}
void PrintFooter(runparams &parms) {

	parms.stopwallclock=clock();
    parms.wallclock=double(parms.stopwallclock-parms.startwallclock)/CLOCKS_PER_SEC;

    printf("     TIMINGS| ReadInput finished in     %50.6f\n", parms.tread);
    printf("     TIMINGS| PrintLevel finished in    %50.6f\n", parms.tprint);
    printf("     TIMINGS| ReadSchedule finished in  %50.6f\n", parms.tschedule);
    printf("     TIMINGS| Rankings finished in      %50.6f\n", parms.trank);
    printf("     TIMINGS| FinalStanding finished in %50.6f\n", parms.tfinal);
    printf("     TIMINGS| Draft finished in         %50.6f\n", parms.tdraft);
    printf("     TIMINGS| Playoffs finished in      %50.6f\n", parms.tplayoffs);
    printf("     TIMINGS| WinsAgainst finished in   %50.6f\n", parms.tagainst);
    printf("     TIMINGS| AverageDraft finished in  %50.6f\n", parms.tdaverage);
    if (parms.p_histograms) {

    	printf("     TIMINGS| PopulateHists finished in           %40.6f\n", parms.thist);
    	printf("     TIMINGS| PrintHist finished in               %40.6f\n", parms.tphist);

    }
    if (parms.p_rankings) {

    	printf("     TIMINGS| AverageRanking finished in          %40.6f\n", parms.traverage);
    	printf("     TIMINGS| PrintAvgRankings finished in        %40.6f\n", parms.tpraverage);
    	printf("     TIMINGS| PrintRankings finished in           %40.6f\n", parms.tpranks);

    }
    if (parms.p_margins) {

    	printf("     TIMINGS| MarginRanking finished in           %40.6f\n", parms.trmargin);
    	printf("     TIMINGS| MarginStanding finished in          %40.6f\n", parms.tsmargin);
    	printf("     TIMINGS| PrintMargins finished in            %40.6f\n", parms.tpmargin);

    }
    if (parms.p_standings) {

    	printf("     TIMINGS| PrintStandings finished in          %40.6f\n", parms.tpstands);
    	printf("     TIMINGS| PrintAvgStandings finished in       %40.6f\n", parms.tpsaverage);

    }
    printf("     TIMINGS| PrintAgainst finished in  %50.6f\n", parms.tpagainst);
    printf("     TIMINGS| PrintSchedule finished in %50.6f\n", parms.tpschedule);
    printf("     TIMINGS| PrintDraft finished in    %50.6f\n", parms.tpdraft);
    printf("     TIMINGS| PrintPlayoffs finished in %50.6f\n", parms.tpplayoffs);
    if (parms.save) printf("     TIMINGS| SaveData finished in      %50.6f\n", parms.tsave);
    printf("     TIMINGS| EnebeaMC finished in      %50.6f\n", parms.wallclock);

    printf("\n");

    int t; char buffer [80];
    parms.etime="";
	time_t now = time(0);
	struct tm* tm = localtime(&now);

	int year = 1900 + tm->tm_year;
	int month = 1 + tm->tm_mon;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int min = tm->tm_min;
	int sec = tm->tm_sec;

	t=sprintf(buffer,"%4d-",year);
	parms.etime.append(buffer);
	t=sprintf(buffer,"%02d-",month);
	parms.etime.append(buffer);
	t=sprintf(buffer,"%02d ",day);
	parms.etime.append(buffer);
	t=sprintf(buffer,"%02d:",hour);
	parms.etime.append(buffer);
	t=sprintf(buffer,"%02d:",min);
	parms.etime.append(buffer);
	t=sprintf(buffer,"%02d",sec);
	parms.etime.append(buffer);

	printf("     MAIN| program finished at %59s\n",parms.etime.c_str());
	printf("     MAIN| program finished on %59s\n",parms.hostname);
	printf("     MAIN| program finished by %59s\n",parms.uname);
	printf("     MAIN| program finished for %58s\n","");
	printf("     MAIN| program finished in %59s\n",parms.cwd);
	printf("\n");

    printf("                                        888                      \n");
    printf("                 ,e e,  888 8e   ,e e,  888 88e   ,e e,   ,'Y88b \n");
    printf("                d88 88b 888 88b d88 88b 888 888b d88 88b '8' 888 \n");
    printf("                888   , 888 888 888   , 888 888P 888   , ,ee 888 \n");
    printf("                 'YeeP' 888 888  'YeeP' 888 88'   'YeeP' '88 888 \n");
    printf("\n");
    printf("                                                            d8           \n");
    printf("                            888 888 8e   e88 88e  888 8e   d88    ,e e,  \n");
    printf("                            888 888 88b d888 888b 888 88b d88888 d88 88b \n");
    printf("                            888 888 888 Y888 888P 888 888  888   888   , \n");
    printf("                            888 888 888  '88 88'  888 888  888    'YeeP' \n");
    printf("\n");
    printf("                                                                 888           \n");
    printf("                                          e88'888  ,'Y88b 888,8, 888  e88 88e  \n");
    printf("                                         d888  '8 '8' 888 888 '  888 d888 888b \n");
    printf("                                         Y888   , ,ee 888 888    888 Y888 888P \n");
    printf("                                          '88,e8' '88 888 888    888  '88 88'  \n");
    printf("\n\n");

}

