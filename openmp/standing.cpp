/*
 * standings.cpp
 *
 *  Created on: Dec 1, 2012
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
#include "run.h"

using std::pair;
using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

void AssignStanding(map<string, vector<string> > &Standings, int year, runparams &parms) {

	if (parms.debug) { printf("AssignStanding starting...\n"); }

	string arr[] = {"TOR","PHI","NYK","BRK","BKN","BOS","CHI","CLE","DET","IND","MIL",
			        "ATL","ORL","MIA","WAS","WSB","OKC","SEA","DEN","POR","UTA","MIN",
			        "LAL","PHO","GSW","LAC","SDC","SAC","KCK","MEM","VAN","HOU","SAS",
					"CHH","CHA","CHO","NOK","NOH","NOP","NOR","DAL"};
	vector<string> Teams (arr, arr + sizeof(arr) / sizeof(arr[0]));

	//2005 --

	static const string arr2[] = {"TOR","PHI","NYK","BKN","BOS","CHI","CLE","DET","IND","MIL",
	        					  "ATL","ORL","CHA","CHO","MIA","WAS","NJN","CHH","BRK"};
	vector<string> Eastern (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));

	static const string arr3[] = {"OKC","DEN","POR","UTA","MIN","SEA","NOR","NOP",
	        		 	 	 	  "LAL","PHO","GSW","LAC","SAC","NOH","MEM","HOU","SAS","DAL","NOK"};
	vector<string> Western (arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));

	static const string arr4[] = {"TOR","PHI","NYK","BKN","BRK","BOS","NJN"};
	vector<string> Atlantic (arr4, arr4 + sizeof(arr4) / sizeof(arr4[0]));

	static const string arr5[] = {"CHI","CLE","DET","IND","MIL"};
	vector<string> Central (arr5, arr5 + sizeof(arr5) / sizeof(arr5[0]));

	static const string arr6[] = {"ATL","ORL","CHA","CHO","MIA","WAS"};
	vector<string> Southeast (arr6, arr6 + sizeof(arr6) / sizeof(arr6[0]));

	static const string arr7[] = {"OKC","DEN","POR","UTA","MIN","SEA"};
	vector<string> Northwest (arr7, arr7 + sizeof(arr7) / sizeof(arr7[0]));

	static const string arr8[] = {"LAL","PHO","GSW","LAC","SAC"};
	vector<string> Pacific (arr8, arr8 + sizeof(arr8) / sizeof(arr8[0]));

	static const string arr9[] = {"NOH","NOR","NOK","NOP","MEM","HOU","SAS","DAL"};
	vector<string> Southwest (arr9, arr9 + sizeof(arr9) / sizeof(arr9[0]));


	static const string arr10[] = {"DraftPos","Lottery","Seeds","pWins","pLoss","Wins","Loss",
								   "Division","Conference","League","ORanks","DRanks"};
	vector<string> histvals (arr10,arr10 + sizeof(arr10) / sizeof(arr10[0]));


	//1992 -- 2004

	//Atlantic Division
	static const string arr11[] = {"ORL","WAS","PHI","BOS","NYK","MIA","NJN"};
	vector<string> Atlantic_ (arr11, arr11 + sizeof(arr11) / sizeof(arr11[0]));

	//Central Division
	static const string arr12[] = {"IND","DET","NOH","MIL","CLE","TOR","ATL","CHI","CHH"};
	vector<string> Central_ (arr12, arr12 + sizeof(arr12) / sizeof(arr12[0]));

	//Midwest Division
	static const string arr13[] = {"MIN","UTA","DEN","MEM","VAN","HOU","SAS","DAL"};
	vector<string> Midwest_ (arr13, arr13 + sizeof(arr13) / sizeof(arr13[0]));

	//Pacific Division
	static const string arr14[] = {"LAL","PHO","GSW","LAC","SAC","POR","SEA"};
	vector<string> Pacific_ (arr14, arr14 + sizeof(arr14) / sizeof(arr14[0]));

	static const string arr15[] = {"TOR","PHI","NYK","BKN","BOS","CHI","CLE","DET","IND","MIL",
	        					  "ATL","ORL","CHA","MIA","WAS","NJN","CHH","NOH"};
	vector<string> Eastern_ (arr15, arr15 + sizeof(arr15) / sizeof(arr15[0]));

	static const string arr16[] = {"DEN","POR","UTA","MIN","VAN","SEA","POR","SEA",
	        		 	 	 	  "LAL","PHO","GSW","LAC","SAC","MEM","HOU","SAS","DAL"};
	vector<string> Western_ (arr16, arr16 + sizeof(arr16) / sizeof(arr16[0]));


	//1991

	//Atlantic Division
    const char* arr17[] = {"WSB","PHI","BOS","NYK","MIA","NJN"};
	vector<string> Atlantic__ (arr17, arr17 + sizeof(arr17) / sizeof(arr17[0]));

	//Central Division
	const char* arr18[] = {"IND","DET","MIL","CLE","ATL","CHI","CHH"};
	vector<string> Central__ (arr18, arr18 + sizeof(arr18) / sizeof(arr18[0]));

	//Midwest Division
	static const string arr19[] = {"MIN","UTA","DEN","HOU","SAS","DAL","ORL"};
	vector<string> Midwest__ (arr19, arr19 + sizeof(arr19) / sizeof(arr19[0]));

	//Pacific Division
	static const string arr20[] = {"LAL","PHO","GSW","LAC","SAC","POR","SEA"};
	vector<string> Pacific__ (arr20, arr20 + sizeof(arr20) / sizeof(arr20[0]));

	static const string arr21[] = {"PHI","NYK","BOS","CHI","CLE","DET","IND","MIL",
	        					   "ATL","MIA","WSB","NJN","CHH"};
	vector<string> Eastern__ (arr21, arr21 + sizeof(arr21) / sizeof(arr21[0]));

	static const string arr22[] = {"DEN","POR","UTA","MIN","SEA","ORL",
	        		 	 	 	   "LAL","PHO","GSW","LAC","SAC","HOU","SAS","DAL"};
	vector<string> Western__ (arr22, arr22 + sizeof(arr22) / sizeof(arr22[0]));


	//1990

	//Atlantic Division
    const char* arr23[] = {"WSB","PHI","BOS","NYK","MIA","NJN"};
	vector<string> Atlantic___ (arr23, arr23 + sizeof(arr23) / sizeof(arr23[0]));

	//Central Division
	const char* arr24[] = {"IND","DET","MIL","CLE","ATL","CHI","ORL"};
	vector<string> Central___ (arr24, arr24 + sizeof(arr24) / sizeof(arr24[0]));

	//Midwest Division
	static const string arr25[] = {"MIN","UTA","DEN","HOU","SAS","DAL","CHH"};
	vector<string> Midwest___ (arr25, arr25 + sizeof(arr25) / sizeof(arr25[0]));

	//Pacific Division
	static const string arr26[] = {"LAL","PHO","GSW","LAC","SAC","POR","SEA"};
	vector<string> Pacific___ (arr26, arr26 + sizeof(arr26) / sizeof(arr26[0]));

	static const string arr27[] = {"PHI","NYK","NJN","BOS","CHI","CLE","DET","IND","MIL",
	        					   "ATL","MIA","WSB","ORL"};
	vector<string> Eastern___ (arr27, arr27 + sizeof(arr27) / sizeof(arr27[0]));

	static const string arr28[] = {"DEN","POR","UTA","MIN","SEA","CHH"
	        		 	 	 	   "LAL","PHO","GSW","LAC","SAC","HOU","SAS","DAL"};
	vector<string> Western___ (arr28, arr28 + sizeof(arr28) / sizeof(arr28[0]));


	//1989

	//Atlantic Division
    const char* arr29[] = {"WSB","PHI","BOS","NYK","CHH","NJN"};
	vector<string> Atlantic____ (arr29, arr29 + sizeof(arr29) / sizeof(arr29[0]));

	//Central Division
	const char* arr30[] = {"IND","DET","MIL","CLE","ATL","CHI"};
	vector<string> Central____ (arr30, arr30 + sizeof(arr30) / sizeof(arr30[0]));

	//Midwest Division
	static const string arr31[] = {"UTA","DEN","HOU","SAS","DAL","MIA"};
	vector<string> Midwest____ (arr31, arr31 + sizeof(arr31) / sizeof(arr31[0]));

	//Pacific Division
	static const string arr32[] = {"LAL","PHO","GSW","LAC","SAC","POR","SEA"};
	vector<string> Pacific____ (arr32, arr32 + sizeof(arr32) / sizeof(arr32[0]));

	static const string arr33[] = {"PHI","NYK","NJN","BOS","CHI","CLE","DET","IND","MIL",
	        					   "ATL","CHH","WSB"};
	vector<string> Eastern____ (arr33, arr33 + sizeof(arr33) / sizeof(arr33[0]));

	static const string arr34[] = {"DEN","POR","UTA","SEA","MIA"
	        		 	 	 	   "LAL","PHO","GSW","LAC","SAC","HOU","SAS","DAL"};
	vector<string> Western____ (arr34, arr34 + sizeof(arr34) / sizeof(arr34[0]));


	// 1981 -- 1988

	//Atlantic Division
    const char* arr35[] = {"WSB","PHI","BOS","NYK","NJN"};
	vector<string> Atlantic_1981 (arr35, arr35 + sizeof(arr35) / sizeof(arr35[0]));

	//Central Division
	const char* arr36[] = {"IND","DET","MIL","CLE","ATL","CHI"};
	vector<string> Central_1981 (arr36, arr36 + sizeof(arr36) / sizeof(arr36[0]));

	//Midwest Division
	static const string arr37[] = {"UTA","DEN","HOU","SAS","DAL","SAC","KCK"};
	vector<string> Midwest_1981 (arr37, arr37 + sizeof(arr37) / sizeof(arr37[0]));

	//Pacific Division
	static const string arr38[] = {"LAL","PHO","GSW","LAC","SDC","POR","SEA"};
	vector<string> Pacific_1981 (arr38, arr38 + sizeof(arr38) / sizeof(arr38[0]));

	static const string arr39[] = {"PHI","NYK","NJN","BOS","CHI","CLE","DET","IND",
	        					   "ATL","WSB","MIL"};
	vector<string> Eastern_1981 (arr39, arr39 + sizeof(arr39) / sizeof(arr39[0]));

	static const string arr40[] = {"DEN","POR","UTA","SEA","KCK","SDC",
	        		 	 	 	   "LAL","PHO","GSW","LAC","SAC","HOU","SAS","DAL"};
	vector<string> Western_1981 (arr40, arr40 + sizeof(arr40) / sizeof(arr40[0]));


	//

	if (year>=2005) {

		//Standings.insert(pair<string, vector<string> >("League", Teams));
		Standings.insert(pair<string, vector<string> >("Eastern", Eastern));
		Standings.insert(pair<string, vector<string> >("Western", Western));
		Standings.insert(pair<string, vector<string> >("Atlantic", Atlantic));
		Standings.insert(pair<string, vector<string> >("Central", Central));
		Standings.insert(pair<string, vector<string> >("Southeast", Southeast));
		Standings.insert(pair<string, vector<string> >("Northwest", Northwest));
		Standings.insert(pair<string, vector<string> >("Pacific", Pacific));
		Standings.insert(pair<string, vector<string> >("Southwest", Southwest));

	} else if (year<2005 && year>=1992) {

		//Standings.insert(pair<string, vector<string> >("League", Teams));
		Standings.insert(pair<string, vector<string> >("Eastern", Eastern_));
		Standings.insert(pair<string, vector<string> >("Western", Western_));
		Standings.insert(pair<string, vector<string> >("Atlantic", Atlantic_));
		Standings.insert(pair<string, vector<string> >("Central", Central_));
		Standings.insert(pair<string, vector<string> >("Midwest", Midwest_));
		Standings.insert(pair<string, vector<string> >("Pacific", Pacific_));


	} else if (year<1992 && year >=1990) {

		//Standings.insert(pair<string, vector<string> >("League", Teams));
		Standings.insert(pair<string, vector<string> >("Eastern", Eastern__));
		Standings.insert(pair<string, vector<string> >("Western", Western__));
		Standings.insert(pair<string, vector<string> >("Atlantic", Atlantic__));
		Standings.insert(pair<string, vector<string> >("Central", Central__));
		Standings.insert(pair<string, vector<string> >("Midwest", Midwest__));
		Standings.insert(pair<string, vector<string> >("Pacific", Pacific__));

	} else if (year==1990) {

		//Standings.insert(pair<string, vector<string> >("League", Teams));
		Standings.insert(pair<string, vector<string> >("Eastern", Eastern___));
		Standings.insert(pair<string, vector<string> >("Western", Western___));
		Standings.insert(pair<string, vector<string> >("Atlantic", Atlantic___));
		Standings.insert(pair<string, vector<string> >("Central", Central___));
		Standings.insert(pair<string, vector<string> >("Midwest", Midwest___));
		Standings.insert(pair<string, vector<string> >("Pacific", Pacific___));

	} else if (year==1989) {

		//Standings.insert(pair<string, vector<string> >("League", Teams));
		Standings.insert(pair<string, vector<string> >("Eastern", Eastern____));
		Standings.insert(pair<string, vector<string> >("Western", Western____));
		Standings.insert(pair<string, vector<string> >("Atlantic", Atlantic____));
		Standings.insert(pair<string, vector<string> >("Central", Central____));
		Standings.insert(pair<string, vector<string> >("Midwest", Midwest____));
		Standings.insert(pair<string, vector<string> >("Pacific", Pacific____));

	} else if (year<1989 && year >= 1981) {

		//Standings.insert(pair<string, vector<string> >("League", Teams));
		Standings.insert(pair<string, vector<string> >("Eastern", Eastern_1981));
		Standings.insert(pair<string, vector<string> >("Western", Western_1981));
		Standings.insert(pair<string, vector<string> >("Atlantic", Atlantic_1981));
		Standings.insert(pair<string, vector<string> >("Central", Central_1981));
		Standings.insert(pair<string, vector<string> >("Midwest", Midwest_1981));
		Standings.insert(pair<string, vector<string> >("Pacific", Pacific_1981));

	}

	if (parms.debug) { printf("AssignStanding exiting...\n\n"); }
}

bool TieBreak(Team &TA, Team &TB) {

	double win = 0;
	double loss = 0;

	// division winner
	if (TA.Dstand.size() == 0) {

		return true;

	} else if (TB.Dstand.size() == 0) {

		return false;

	} else {

		if (TA.Dstand.back() == 1 && TB.Dstand.back() != 1) {

			return true;

		} else if (TA.Dstand.back() != 1 && TB.Dstand.back() == 1) {

			return false;

		}
	}

	// head to head win percent
	for (int i=0; i<(int)TA.Schedule.size(); i++) {
 
		if (TA.Schedule.at(i).Opponent==TB.TeamName) {
		
			if (TA.Schedule.at(i).DidWin) {
				
			    win++;

			} else { 
			   
			    loss++;

			}
		}
	}

	if (win > loss) {

		return true;
		
	} else if (win < loss) {

		return false;

	}

	// conference win loss percent
	if (TA.ConfWinPercent > TB.ConfWinPercent) {

		return true;

	} else if (TA.ConfWinPercent > TB.ConfWinPercent) {

		return false;

	}


	/*

	// own playoff conference win percent
	if (TA.hBestConfWinPercent > TB.hBestConfWinPercent) {

		return true;

	} else if (TA.hBestConfWinPercent < TB.hBestConfWinPercent) {

		return false;

	}

	// other playoff conference win percent
	if (TA.aBestConfWinPercent > TB.aBestConfWinPercent) {

		return true;

	} else if (TA.aBestConfWinPercent < TB.aBestConfWinPercent) {

		return false;

	}

	*/

	// net points
	if (TA.avgP4 > TB.avgP4) {

		return true;

	}


    return false;
}

bool PlayoffTieBreak(Team &TA, Team &TB) {

	//cout << "inside playoff tiebreak" << endl;

	double win = 0;
	double loss = 0;

	// division winner
	if (TA.Dstand.back() == 1 && TB.Dstand.back() != 1) { return true; }

    else if (TA.Dstand.back() != 1 && TB.Dstand.back() == 1) { return false; }

	// head to head win percent
	for (int i=0; i<(int)TA.Schedule.size(); i++) {

		if (TA.Schedule.at(i).Opponent==TB.TeamName) {

			if (TA.Schedule.at(i).DidWin) {

			    win++;

			} else {

			    loss++;

			}
		}
	}

	if (win > loss) { return true; }

	else if (win < loss) { return false; }

	// division win percent if in same division
	if (TA.Division==TB.Division) {

		if (TA.DivWinPercent > TB.DivWinPercent) {

			return true;

		} else if (TA.DivWinPercent > TB.DivWinPercent) {

			return false;

		}

	}

	// conference win loss percent
	if (TA.ConfWinPercent > TB.ConfWinPercent) {

		return true;

	} else if (TA.ConfWinPercent > TB.ConfWinPercent) {

		return false;

	}


	// own playoff conference win percent
	if (TA.hBestConfWinPercent > TB.hBestConfWinPercent) {

		return true;

	} else if (TA.hBestConfWinPercent < TB.hBestConfWinPercent) {

		return false;

	}

	// other playoff conference win percent
	if (TA.aBestConfWinPercent > TB.aBestConfWinPercent) {

		return true;

	} else if (TA.aBestConfWinPercent < TB.aBestConfWinPercent) {

		return false;

	}


	// net points
	if (TA.avgP4 > TB.avgP4) {

		return true;

	}

    return false;


}

double GamesBack(int W, int L, int FirstW, int FirstL) {

	double gb = 0.0;

	gb = (FirstW - W) + (L - FirstL);
	gb = gb/2.0;

	return gb;

}

void Standing(map<string, Team> &TheTeams) {

	vector<string> League;
	vector<string> Western;
	vector<string> Eastern;
	vector<string> Atlantic;
	vector<string> Central;
	vector<string> Southeast;
	vector<string> Northwest;
	vector<string> Pacific;
	vector<string> Southwest;
	vector<string> Midwest;

	bool edge;

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		//League
		bool lfound = false;
		for (int i=0; i<(int)League.size(); i++) {

			if (iterator->second.WinPercent > TheTeams.find(League.at(i))->second.WinPercent) {

				League.insert(League.begin()+i,iterator->second.TeamName);
				lfound = true;
				break;

			} else if (iterator->second.WinPercent==TheTeams.find(League.at(i))->second.WinPercent) {

				edge = TieBreak(iterator->second,TheTeams.find(League.at(i))->second);
				if (edge) {

				    League.insert(League.begin()+i,iterator->second.TeamName);
				    lfound = true;
				    break;

				} 
			}

		}
		if (!lfound) {

			League.push_back(iterator->second.TeamName);
		}

		/*
		 *
		 */

		// Eastern
		if (iterator->second.Conference=="Eastern") {

			bool efound = false;
			for (int i=0; i<(int)Eastern.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Eastern.at(i))->second.WinPercent) {

					Eastern.insert(Eastern.begin()+i,iterator->second.TeamName);
					efound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Eastern.at(i))->second.WinPercent) {

					edge = TieBreak(iterator->second,TheTeams.find(Eastern.at(i))->second);
					if (edge) {

						Eastern.insert(Eastern.begin()+i,iterator->second.TeamName);
						efound = true;
					    break;

					}
				}
			}
			if (!efound) {

				Eastern.push_back(iterator->second.TeamName);

			}
		}

		/*
		 *
		 */

		// Western
		if (iterator->second.Conference=="Western") {

			bool wfound = false;
			for (int i=0; i<(int)Western.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Western.at(i))->second.WinPercent) {

					Western.insert(Western.begin()+i,iterator->second.TeamName);
					wfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Western.at(i))->second.WinPercent) {

					edge = TieBreak(iterator->second,TheTeams.find(Western.at(i))->second);
					if (edge) {

						Western.insert(Western.begin()+i,iterator->second.TeamName);
						wfound = true;
						break;

					}
				}
			}
			if (!wfound) {

				Western.push_back(iterator->second.TeamName);

			}
		}

		/*
		 *
		 */

		// Atlantic
		if (iterator->second.Division == "Atlantic") {

			bool afound = false;
			for (int i=0; i<(int)Atlantic.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Atlantic.at(i))->second.WinPercent) {

					Atlantic.insert(Atlantic.begin()+i,iterator->second.TeamName);
					afound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Atlantic.at(i))->second.WinPercent) {

					edge = TieBreak(iterator->second,TheTeams.find(Atlantic.at(i))->second);
					if (edge) {

						Atlantic.insert(Atlantic.begin()+i,iterator->second.TeamName);
						afound = true;
						break;

					}
				}
			}
			if (!afound) {

				Atlantic.push_back(iterator->second.TeamName);

			}
		}

		/*
		 *
		 */

		// Central
		if (iterator->second.Division == "Central") {

			bool cfound = false;
			for (int i=0; i<(int)Central.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Central.at(i))->second.WinPercent) {

					Central.insert(Central.begin()+i,iterator->second.TeamName);
					cfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Central.at(i))->second.WinPercent) {

					edge = TieBreak(iterator->second,TheTeams.find(Central.at(i))->second);
					if (edge) {

						Central.insert(Central.begin()+i,iterator->second.TeamName);
						cfound = true;
						break;

					}
				}
			}
			if (!cfound) {

				Central.push_back(iterator->second.TeamName);

			}
		}

		/*
		 *
		 */

		// Southeast
		if (iterator->second.Division == "Southeast") {

			bool sefound = false;
			for (int i=0; i<(int)Southeast.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Southeast.at(i))->second.WinPercent) {

					Southeast.insert(Southeast.begin()+i,iterator->second.TeamName);
					sefound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Southeast.at(i))->second.WinPercent) {

					edge = TieBreak(iterator->second,TheTeams.find(Southeast.at(i))->second);
					if (edge) {

						Southeast.insert(Southeast.begin()+i,iterator->second.TeamName);
						sefound = true;
						break;

					}
				}
			}
			if (!sefound) {

				Southeast.push_back(iterator->second.TeamName);

			}
		}

		/*
		 *
		 */

		// Northwest
		if (iterator->second.Division == "Northwest") {

			bool nfound = false;
			for (int i=0; i<(int)Northwest.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Northwest.at(i))->second.WinPercent) {

					Northwest.insert(Northwest.begin()+i,iterator->second.TeamName);
					nfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Northwest.at(i))->second.WinPercent) {

					edge = TieBreak(iterator->second,TheTeams.find(Northwest.at(i))->second);
					if (edge) {

						Northwest.insert(Northwest.begin()+i,iterator->second.TeamName);
						nfound = true;
						break;

					}
				}
			}
			if (!nfound) {

				Northwest.push_back(iterator->second.TeamName);

			}
		}


		/*
		 *
		 */

		// Pacific
		if (iterator->second.Division == "Pacific") {

			bool pfound = false;
			for (int i=0; i<(int)Pacific.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Pacific.at(i))->second.WinPercent) {

					Pacific.insert(Pacific.begin()+i,iterator->second.TeamName);
					pfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Pacific.at(i))->second.WinPercent) {

					edge = TieBreak(iterator->second,TheTeams.find(Pacific.at(i))->second);
					if (edge) {

						Pacific.insert(Pacific.begin()+i,iterator->second.TeamName);
						pfound = true;
						break;

					}
				}
			}
			if (!pfound) {

				Pacific.push_back(iterator->second.TeamName);

			}
		}

		/*
		 *
		 */

		// Southwest
		if (iterator->second.Division == "Southwest") {

			bool swfound = false;
			for (int i=0; i<(int)Southwest.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Southwest.at(i))->second.WinPercent) {

					Southwest.insert(Southwest.begin()+i,iterator->second.TeamName);
					swfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Southwest.at(i))->second.WinPercent) {

					edge = TieBreak(iterator->second,TheTeams.find(Southwest.at(i))->second);
					if (edge) {

						Southwest.insert(Southwest.begin()+i,iterator->second.TeamName);
						swfound = true;
						break;

					}
				}
			}
			if (!swfound) {

				Southwest.push_back(iterator->second.TeamName);

			}
		}


		/*
		 *
		 */

		// Midwest
		if (iterator->second.Division == "Midwest") {

			bool mwfound = false;
			for (int i=0; i<(int)Midwest.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Midwest.at(i))->second.WinPercent) {

					Midwest.insert(Midwest.begin()+i,iterator->second.TeamName);
					mwfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Midwest.at(i))->second.WinPercent) {

					edge = TieBreak(iterator->second,TheTeams.find(Midwest.at(i))->second);
					if (edge) {

						Midwest.insert(Midwest.begin()+i,iterator->second.TeamName);
						mwfound = true;
						break;

					}
				}
			}
			if (!mwfound) {

				Midwest.push_back(iterator->second.TeamName);

			}
		}
	}

	for (int i=0; i<(int)League.size(); i++) {
		TheTeams.find(League.at(i))->second.Lstand.push_back(i+1);
		double gb = GamesBack(TheTeams.find(League.at(i))->second.Win,
							  TheTeams.find(League.at(i))->second.Loss,
							  TheTeams.find(League.at(0))->second.Win,
							  TheTeams.find(League.at(0))->second.Loss);
		TheTeams.find(League.at(i))->second.GamesBehindL = gb;
	}
	for (int i=0; i<(int)Eastern.size(); i++) {
		TheTeams.find(Eastern.at(i))->second.Cstand.push_back(i+1);
		double gb = GamesBack(TheTeams.find(Eastern.at(i))->second.Win,
							  TheTeams.find(Eastern.at(i))->second.Loss,
							  TheTeams.find(Eastern.at(0))->second.Win,
							  TheTeams.find(Eastern.at(0))->second.Loss);
		TheTeams.find(League.at(i))->second.GamesBehindC = gb;
	}
	for (int i=0; i<(int)Western.size(); i++) {
		TheTeams.find(Western.at(i))->second.Cstand.push_back(i+1);
		double gb = GamesBack(TheTeams.find(Western.at(i))->second.Win,
							  TheTeams.find(Western.at(i))->second.Loss,
							  TheTeams.find(Western.at(0))->second.Win,
							  TheTeams.find(Western.at(0))->second.Loss);
		TheTeams.find(League.at(i))->second.GamesBehindC = gb;
	}
	for (int i=0; i<(int)Atlantic.size(); i++) {
		TheTeams.find(Atlantic.at(i))->second.Dstand.push_back(i+1);
		double gb = GamesBack(TheTeams.find(Atlantic.at(i))->second.Win,
							  TheTeams.find(Atlantic.at(i))->second.Loss,
							  TheTeams.find(Atlantic.at(0))->second.Win,
							  TheTeams.find(Atlantic.at(0))->second.Loss);
		TheTeams.find(League.at(i))->second.GamesBehindD = gb;
	}
	for (int i=0; i<(int)Central.size(); i++) {
		TheTeams.find(Central.at(i))->second.Dstand.push_back(i+1);
		double gb = GamesBack(TheTeams.find(Central.at(i))->second.Win,
							  TheTeams.find(Central.at(i))->second.Loss,
							  TheTeams.find(Central.at(0))->second.Win,
							  TheTeams.find(Central.at(0))->second.Loss);
		TheTeams.find(League.at(i))->second.GamesBehindD = gb;
	}
	for (int i=0; i<(int)Southeast.size(); i++) {
		TheTeams.find(Southeast.at(i))->second.Dstand.push_back(i+1);
		double gb = GamesBack(TheTeams.find(Southeast.at(i))->second.Win,
							  TheTeams.find(Southeast.at(i))->second.Loss,
							  TheTeams.find(Southeast.at(0))->second.Win,
							  TheTeams.find(Southeast.at(0))->second.Loss);
		TheTeams.find(League.at(i))->second.GamesBehindD = gb;
	}
	for (int i=0; i<(int)Pacific.size(); i++) {
		TheTeams.find(Pacific.at(i))->second.Dstand.push_back(i+1);
		double gb = GamesBack(TheTeams.find(Pacific.at(i))->second.Win,
							  TheTeams.find(Pacific.at(i))->second.Loss,
							  TheTeams.find(Pacific.at(0))->second.Win,
							  TheTeams.find(Pacific.at(0))->second.Loss);
		TheTeams.find(League.at(i))->second.GamesBehindD = gb;
	}
	for (int i=0; i<(int)Northwest.size(); i++) {
		TheTeams.find(Northwest.at(i))->second.Dstand.push_back(i+1);
		double gb = GamesBack(TheTeams.find(Northwest.at(i))->second.Win,
							  TheTeams.find(Northwest.at(i))->second.Loss,
							  TheTeams.find(Northwest.at(0))->second.Win,
							  TheTeams.find(Northwest.at(0))->second.Loss);
		TheTeams.find(League.at(i))->second.GamesBehindD = gb;
	}
	for (int i=0; i<(int)Southwest.size(); i++) {
		TheTeams.find(Southwest.at(i))->second.Dstand.push_back(i+1);
		double gb = GamesBack(TheTeams.find(Southwest.at(i))->second.Win,
							  TheTeams.find(Southwest.at(i))->second.Loss,
							  TheTeams.find(Southwest.at(0))->second.Win,
							  TheTeams.find(Southwest.at(0))->second.Loss);
		TheTeams.find(League.at(i))->second.GamesBehindD = gb;
	}
	for (int i=0; i<(int)Midwest.size(); i++) {
		TheTeams.find(Midwest.at(i))->second.Dstand.push_back(i+1);
		double gb = GamesBack(TheTeams.find(Midwest.at(i))->second.Win,
							  TheTeams.find(Midwest.at(i))->second.Loss,
							  TheTeams.find(Midwest.at(0))->second.Win,
							  TheTeams.find(Midwest.at(0))->second.Loss);
		TheTeams.find(League.at(i))->second.GamesBehindD = gb;
	}
}
void FinalStanding(map<string, Team> &TheTeams, double &q, bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("FinalStanding starting...\n"); }

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		iterator->second.CalcBestPercent();

	}

	vector<string> League;
	vector<string> Western;
	vector<string> Eastern;
	vector<string> Atlantic;
	vector<string> Central;
	vector<string> Southeast;
	vector<string> Northwest;
	vector<string> Pacific;
	vector<string> Southwest;
	vector<string> Midwest;

	bool edge;

	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		// Atlantic
		if (iterator->second.Division == "Atlantic") {

			bool afound = false;
			for (int i=0; i<(int)Atlantic.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Atlantic.at(i))->second.WinPercent) {

					Atlantic.insert(Atlantic.begin()+i,iterator->second.TeamName);
					afound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Atlantic.at(i))->second.WinPercent) {

					edge = PlayoffTieBreak(iterator->second,TheTeams.find(Atlantic.at(i))->second);
					if (edge) {

						Atlantic.insert(Atlantic.begin()+i,iterator->second.TeamName);
						afound = true;
						break;

					}
				}
			}
			if (!afound) {

				Atlantic.push_back(iterator->second.TeamName);

			}
		}
	}

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		// Central
		if (iterator->second.Division == "Central") {

			bool cfound = false;
			for (int i=0; i<(int)Central.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Central.at(i))->second.WinPercent) {

					Central.insert(Central.begin()+i,iterator->second.TeamName);
					cfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Central.at(i))->second.WinPercent) {

					edge = PlayoffTieBreak(iterator->second,TheTeams.find(Central.at(i))->second);
					if (edge) {

						Central.insert(Central.begin()+i,iterator->second.TeamName);
						cfound = true;
						break;

					}
				}
			}
			if (!cfound) {

				Central.push_back(iterator->second.TeamName);

			}
		}
	}

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		// Southeast
		if (iterator->second.Division == "Southeast") {

			bool sefound = false;
			for (int i=0; i<(int)Southeast.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Southeast.at(i))->second.WinPercent) {

					Southeast.insert(Southeast.begin()+i,iterator->second.TeamName);
					sefound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Southeast.at(i))->second.WinPercent) {

					edge = PlayoffTieBreak(iterator->second,TheTeams.find(Southeast.at(i))->second);
					if (edge) {

						Southeast.insert(Southeast.begin()+i,iterator->second.TeamName);
						sefound = true;
						break;

					}
				}
			}
			if (!sefound) {

				Southeast.push_back(iterator->second.TeamName);

			}
		}
	}

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		// Northwest
		if (iterator->second.Division == "Northwest") {

			bool nfound = false;
			for (int i=0; i<(int)Northwest.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Northwest.at(i))->second.WinPercent) {

					Northwest.insert(Northwest.begin()+i,iterator->second.TeamName);
					nfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Northwest.at(i))->second.WinPercent) {

					edge = PlayoffTieBreak(iterator->second,TheTeams.find(Northwest.at(i))->second);
					if (edge) {

						Northwest.insert(Northwest.begin()+i,iterator->second.TeamName);
						nfound = true;
						break;

					}
				}
			}
			if (!nfound) {

				Northwest.push_back(iterator->second.TeamName);

			}
		}
	}

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		// Pacific
		if (iterator->second.Division == "Pacific") {

			bool pfound = false;
			for (int i=0; i<(int)Pacific.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Pacific.at(i))->second.WinPercent) {

					Pacific.insert(Pacific.begin()+i,iterator->second.TeamName);
					pfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Pacific.at(i))->second.WinPercent) {

					edge = PlayoffTieBreak(iterator->second,TheTeams.find(Pacific.at(i))->second);
					if (edge) {

						Pacific.insert(Pacific.begin()+i,iterator->second.TeamName);
						pfound = true;
						break;

					}
				}
			}
			if (!pfound) {

				Pacific.push_back(iterator->second.TeamName);

			}
		}
	}

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		// Southwest
		if (iterator->second.Division == "Southwest") {

			bool swfound = false;
			for (int i=0; i<(int)Southwest.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Southwest.at(i))->second.WinPercent) {

					Southwest.insert(Southwest.begin()+i,iterator->second.TeamName);
					swfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Southwest.at(i))->second.WinPercent) {

					edge = PlayoffTieBreak(iterator->second,TheTeams.find(Southwest.at(i))->second);
					if (edge) {

						Southwest.insert(Southwest.begin()+i,iterator->second.TeamName);
						swfound = true;
						break;

					}
				}
			}
			if (!swfound) {

				Southwest.push_back(iterator->second.TeamName);

			}
		}
	}

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		// Midwest
		if (iterator->second.Division == "Midwest") {

			bool mwfound = false;
			for (int i=0; i<(int)Midwest.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Midwest.at(i))->second.WinPercent) {

					Midwest.insert(Midwest.begin()+i,iterator->second.TeamName);
					mwfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Midwest.at(i))->second.WinPercent) {

					edge = TieBreak(iterator->second,TheTeams.find(Midwest.at(i))->second);
					if (edge) {

						Midwest.insert(Midwest.begin()+i,iterator->second.TeamName);
						mwfound = true;
						break;

					}
				}
			}
			if (!mwfound) {

				Midwest.push_back(iterator->second.TeamName);

			}
		}
	}

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		// Western
		if (iterator->second.Conference=="Western") {

			bool wfound = false;
			for (int i=0; i<(int)Western.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Western.at(i))->second.WinPercent) {

					Western.insert(Western.begin()+i,iterator->second.TeamName);
					wfound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Western.at(i))->second.WinPercent) {

					edge = PlayoffTieBreak(iterator->second,TheTeams.find(Western.at(i))->second);
					if (edge) {

						Western.insert(Western.begin()+i,iterator->second.TeamName);
						wfound = true;
						break;

					}
				}
			}
			if (!wfound) {

				Western.push_back(iterator->second.TeamName);

			}
		}
	}

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		// Eastern
		if (iterator->second.Conference=="Eastern") {

			bool efound = false;
			for (int i=0; i<(int)Eastern.size(); i++) {

				if (iterator->second.WinPercent > TheTeams.find(Eastern.at(i))->second.WinPercent) {

					Eastern.insert(Eastern.begin()+i,iterator->second.TeamName);
					efound = true;
					break;

				} else if (iterator->second.WinPercent==TheTeams.find(Eastern.at(i))->second.WinPercent) {

					edge = PlayoffTieBreak(iterator->second,TheTeams.find(Eastern.at(i))->second);
					if (edge) {

						Eastern.insert(Eastern.begin()+i,iterator->second.TeamName);
						efound = true;
					    break;

					}
				}
			}
			if (!efound) {

				Eastern.push_back(iterator->second.TeamName);

			}
		}
	}

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

		//League
		bool lfound = false;
		for (int i=0; i<(int)League.size(); i++) {

			if (iterator->second.WinPercent > TheTeams.find(League.at(i))->second.WinPercent) {

				League.insert(League.begin()+i,iterator->second.TeamName);
				lfound = true;
				break;

			} else if (iterator->second.WinPercent==TheTeams.find(League.at(i))->second.WinPercent) {

				edge = PlayoffTieBreak(iterator->second,TheTeams.find(League.at(i))->second);
				if (edge) {

				    League.insert(League.begin()+i,iterator->second.TeamName);
				    lfound = true;
				    break;

				}
			}

		}
		if (!lfound) {

			League.push_back(iterator->second.TeamName);
		}
	}

	/*
	 *
	 */

	// playoff seeding

	vector<string> EastSeeds;
	vector<string> WestSeeds;
	vector<string> Lottery;

	// eastern conference
	vector<string> etmp;

	if (Atlantic.size()>0) etmp.push_back(Atlantic.front());
	if (Central.size()>0) etmp.push_back(Central.front());
	if (Southeast.size()>0) etmp.push_back(Southeast.front());

	// last top 4 seed
	for (int i=0; i<(int)Eastern.size(); i++) {

		if (etmp.size()==4) break;

		bool save=true;

		for (int j=0; j<(int)etmp.size(); j++) {

			if (etmp.at(j)==Eastern.at(i)) save=false;

		}

		if (save) { etmp.push_back(Eastern.at(i));	}

	}

	// western conference
	vector<string> wtmp;

	if (Northwest.size()>0) wtmp.push_back(Northwest.front());
	if (Pacific.size()>0) wtmp.push_back(Pacific.front());
	if (Southwest.size()>0) wtmp.push_back(Southwest.front());
	if (Midwest.size()>0) wtmp.push_back(Midwest.front());

	// last top 4 seed

	for (int i=0; i<(int)Western.size(); i++) {

		if (wtmp.size()==4) break;

		bool save=true;

		for (int j=0; j<(int)wtmp.size(); j++) {

			if (wtmp.at(j)==Western.at(i)) save=false;

		}

		if (save) { wtmp.push_back(Western.at(i));	}

	}

	// sort top 4 seeds
	for (int j=0; j<(int)etmp.size(); j++) {

		bool efound = false;

		for (int i=0; i<(int)EastSeeds.size(); i++) {

			if (TheTeams.find(etmp.at(j))->second.WinPercent > TheTeams.find(EastSeeds.at(i))->second.WinPercent) {

				EastSeeds.insert(EastSeeds.begin()+i,TheTeams.find(etmp.at(j))->second.TeamName);
				efound = true;
				break;

			} else if (TheTeams.find(etmp.at(j))->second.WinPercent == TheTeams.find(EastSeeds.at(i))->second.WinPercent) {

				edge = PlayoffTieBreak(TheTeams.find(etmp.at(j))->second,TheTeams.find(EastSeeds.at(i))->second);

				if (edge) {

					EastSeeds.insert(EastSeeds.begin()+i,TheTeams.find(etmp.at(j))->second.TeamName);
					efound = true;
					break;

				}
			}
		}

		if (!efound) {

			EastSeeds.push_back(TheTeams.find(etmp.at(j))->second.TeamName);

		}
	}

	for (int j=0; j<(int)wtmp.size(); j++) {

		bool wfound = false;

		for (int i=0; i<(int)WestSeeds.size(); i++) {

			if (TheTeams.find(wtmp.at(j))->second.WinPercent > TheTeams.find(WestSeeds.at(i))->second.WinPercent) {

				WestSeeds.insert(WestSeeds.begin()+i,TheTeams.find(wtmp.at(j))->second.TeamName);
				wfound = true;
				break;

			} else if (TheTeams.find(wtmp.at(j))->second.WinPercent == TheTeams.find(WestSeeds.at(i))->second.WinPercent) {

				edge = PlayoffTieBreak(TheTeams.find(wtmp.at(j))->second,TheTeams.find(WestSeeds.at(i))->second);

				if (edge) {

					WestSeeds.insert(WestSeeds.begin()+i,TheTeams.find(wtmp.at(j))->second.TeamName);
					wfound = true;
					break;

				}
			}
		}

		if (!wfound) {

			WestSeeds.push_back(TheTeams.find(wtmp.at(j))->second.TeamName);

		}
	}

	// sort bottom 4 teams
	typedef string::iterator it_type1;


	// eastern
	for (int i=0; i<8; i++) {

		bool found=false;

		for (int j=0; j<(int)EastSeeds.size(); j++) {

			if (Eastern.at(i) == EastSeeds.at(j)) {

				found=true;
				break;
			}
		}

		if (found)	continue;

		EastSeeds.push_back(TheTeams.find(Eastern.at(i))->second.TeamName);

	}

	// western
	for (int i=0; i<8; i++) {

		bool found=false;

		for (int j=0; j<(int)WestSeeds.size(); j++) {

			if (Western.at(i) == WestSeeds.at(j)) {

				found=true;
				break;
			}
		}

		if (found)	continue;

		WestSeeds.push_back(TheTeams.find(Western.at(i))->second.TeamName);

	}

	for (int i=League.size()-1; i>=0; i--) {

		if (Lottery.size()>=14) {

			break;

		}

		bool found=false;

		for (int j=0; j<(int)WestSeeds.size(); j++) {

			if (League.at(i) == WestSeeds.at(j)) {

				found=true;
				break;
			}
		}

		for (int j=0; j<(int)EastSeeds.size(); j++) {

			if (League.at(i) == EastSeeds.at(j)) {

				found=true;
				break;
			}
		}

		if (found) continue;

		Lottery.push_back(TheTeams.find(League.at(i))->second.TeamName);

	}


	for (int i=League.size()-1; i>=0; i--) {

		bool found=false;

		for (int j=0; j<(int)Lottery.size(); j++) {

			if (League.at(i) == Lottery.at(j)) {

				found=true;
				break;

			}
		}

		if (found) continue;

		Lottery.push_back(TheTeams.find(League.at(i))->second.TeamName);

	}


	typedef map<string, Team>::iterator it_type;

	for (int i=0; i<(int)Lottery.size(); i++) {

		for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

			if (Lottery.at(i)==iterator->first) {

				iterator->second.DraftPos=i;
				break;

			}
		}
	}

	for (int i=0; i<(int)EastSeeds.size(); i++) {

		for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

			if (EastSeeds.at(i)==iterator->first) {

				iterator->second.PlayoffSeed=i;
				break;

			}
		}
	}

	for (int i=0; i<(int)WestSeeds.size(); i++) {

		for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

			if (WestSeeds.at(i)==iterator->first) {

				iterator->second.PlayoffSeed=i;
				break;

			}
		}
	}

	if (debug) { printf("FinalStanding exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}
void WinsAgainst(vector<map<string, Team> > &T, vector<vector<vector<double> > > &oppwin, double &t, bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("WinsAgainst starting...\n"); }

	int sim = T.size();

	for (int q=0; q<sim; q++) {

		map<string, Team> NT = T.at(q);

		int col = 0;
		typedef map<string, Team>::iterator it_type;

		for (it_type iterator = T.at(q).begin(); iterator != T.at(q).end(); iterator++) {

			int row = 0;
			for (it_type iterator2 = NT.begin(); iterator2 != NT.end(); iterator2++) {

				string t2name=iterator2->second.TeamName;

				for (int i=0; i<(int)iterator->second.Schedule.size(); i++) {

					if (iterator->second.Schedule.at(i).Opponent==t2name) {

						if (iterator->second.Schedule.at(i).DidWin) {

							oppwin.at(col).at(row).at(0) = oppwin.at(col).at(row).at(0) + 1.0/sim;

						} else {

							oppwin.at(col).at(row).at(1) = oppwin.at(col).at(row).at(1) + 1.0/sim;

						}
					}
				}
				row++;
			}
			col++;
		}
	}

	if (debug) { printf("WinsAgainst exiting...\n\n"); }

	clock_t endtime=clock();
	t=double(endtime-starttime)/CLOCKS_PER_SEC;
}
void BestWorstStanding(vector<map<string, Team> > &T, vector<MarginStandings> &MarginStands,double &q,bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("MarginStanding starting...\n"); }

	MarginStands.resize(T.front().size());
	int count=0;

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = T.front().begin(); iterator != T.front().end(); iterator++) {


		string team=iterator->second.TeamName;
		MarginStands.at(count).TeamName=team;

		// Best
		for (int i=0; i<(int)T.size(); i++) {

			bool ob=true;

			if (!MarginStands.at(count).BestLStanding.empty()) {

				if (T.at(i).find(team)->second.Lstand.back() < MarginStands.at(count).BestLStanding.back()) { ob=true; }

				else if (T.at(i).find(team)->second.Lstand.back() == MarginStands.at(count).BestLStanding.back()) {

					double oldr=AVERAGE(T.at(i).find(team)->second.Lstand);
					double newr=AVERAGE(MarginStands.at(count).BestLStanding);

					if (newr<oldr) ob=true;

				} else ob=false;

			}

			if (ob) {

				MarginStands.at(count).BestLStanding=T.at(i).find(team)->second.Lstand;
				MarginStands.at(count).BestCStanding=T.at(i).find(team)->second.Cstand;
				MarginStands.at(count).BestDStanding=T.at(i).find(team)->second.Dstand;

				MarginStands.at(count).BestWin=T.at(i).find(team)->second.Win;
				MarginStands.at(count).BestLoss=T.at(i).find(team)->second.Loss;
				MarginStands.at(count).BestWinC=T.at(i).find(team)->second.ConfWin;
				MarginStands.at(count).BestLossC=T.at(i).find(team)->second.ConfLoss;
				MarginStands.at(count).BestWinD=T.at(i).find(team)->second.DivWin;
				MarginStands.at(count).BestLossD=T.at(i).find(team)->second.DivLoss;

			}

		}

		// Worst
		for (int i=0; i<(int)T.size(); i++) {

			bool ob=true;

			if (!MarginStands.at(count).WorstLStanding.empty()) {

				if (T.at(i).find(team)->second.Lstand.back() > MarginStands.at(count).WorstLStanding.back()) { ob=true; }

				else if (T.at(i).find(team)->second.Lstand.back() == MarginStands.at(count).WorstLStanding.back()) {

					double oldr=AVERAGE(T.at(i).find(team)->second.Lstand);
					double newr=AVERAGE(MarginStands.at(count).WorstLStanding);

					if (newr>oldr) ob=true;

				} else ob=false;

			}

			if (ob) {

				MarginStands.at(count).WorstLStanding=T.at(i).find(team)->second.Lstand;
				MarginStands.at(count).WorstCStanding=T.at(i).find(team)->second.Cstand;
				MarginStands.at(count).WorstDStanding=T.at(i).find(team)->second.Dstand;

				MarginStands.at(count).WorstWin=T.at(i).find(team)->second.Win;
				MarginStands.at(count).WorstLoss=T.at(i).find(team)->second.Loss;
				MarginStands.at(count).WorstWinC=T.at(i).find(team)->second.ConfWin;
				MarginStands.at(count).WorstLossC=T.at(i).find(team)->second.ConfLoss;
				MarginStands.at(count).WorstWinD=T.at(i).find(team)->second.DivWin;
				MarginStands.at(count).WorstLossD=T.at(i).find(team)->second.DivLoss;

			}

		}

		count += 1;

	}

	if (debug) { printf("MarginStanding exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}


