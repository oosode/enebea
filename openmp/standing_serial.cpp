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

void Standing(map<string, string> &TheTeams) {

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

	typedef map<string, string>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {

        ifstream in(iterator->second.c_str());
        Team temp1;
        temp1.read(&in);
        
		//League
		bool lfound = false;
		for (int i=0; i<(int)League.size(); i++) {
            
            ifstream in(League.at(i))->second.c_str());
            Team temp2;
            temp2.read(&in);

			if (temp1.WinPercent > temp2.WinPercent) {

				League.insert(League.begin()+i,temp1.TeamName);
				lfound = true;
				break;

			} else if (temp1.WinPercent==temp2.WinPercent) {

				edge = TieBreak(temp1,temp2);
				if (edge) {

				    League.insert(League.begin()+i,temp1.TeamName);
				    lfound = true;
				    break;

				} 
			}

		}
		if (!lfound) {

			League.push_back(temp1.TeamName);
		}

		/*
		 *
		 */

		// Eastern
		if (iterator->second.Conference=="Eastern") {

			bool efound = false;
			for (int i=0; i<(int)Eastern.size(); i++) {
                
                ifstream in(Eastern.at(i))->second.c_str());
                Team temp2;
                temp2.read(&in);

				if (temp1.WinPercent > temp2.WinPercent) {

					Eastern.insert(Eastern.begin()+i,temp1.TeamName);
					efound = true;
					break;

				} else if (temp1.WinPercent==temp2.WinPercent) {

					edge = TieBreak(temp1,temp2);
					if (edge) {

						Eastern.insert(Eastern.begin()+i,temp1.TeamName);
						efound = true;
					    break;

					}
				}
			}
			if (!efound) {

				Eastern.push_back(temp1.TeamName);

			}
		}

		/*
		 *
		 */

		// Western
		if (iterator->second.Conference=="Western") {

			bool wfound = false;
			for (int i=0; i<(int)Western.size(); i++) {
                
                ifstream in(Western.at(i))->second.c_str());
                Team temp2;
                temp2.read(&in);

				if (temp1.WinPercent > temp2.WinPercent) {

					Western.insert(Western.begin()+i,temp1.TeamName);
					wfound = true;
					break;

				} else if (temp1.WinPercent==temp2.WinPercent) {

					edge = TieBreak(temp1,temp2);
					if (edge) {

						Western.insert(Western.begin()+i,temp1.TeamName);
						wfound = true;
						break;

					}
				}
			}
			if (!wfound) {

				Western.push_back(temp1.TeamName);

			}
		}

		/*
		 *
		 */

		// Atlantic
		if (iterator->second.Division == "Atlantic") {

			bool afound = false;
			for (int i=0; i<(int)Atlantic.size(); i++) {
                
                ifstream in(Atlantic.at(i))->second.c_str());
                Team temp2;
                temp2.read(&in);

				if (temp1.WinPercent > temp2.WinPercent) {

					Atlantic.insert(Atlantic.begin()+i,temp1.TeamName);
					afound = true;
					break;

				} else if (temp1.WinPercent==temp2.WinPercent) {

					edge = TieBreak(temp1,temp2);
					if (edge) {

						Atlantic.insert(Atlantic.begin()+i,temp1.TeamName);
						afound = true;
						break;

					}
				}
			}
			if (!afound) {

				Atlantic.push_back(temp1.TeamName);

			}
		}

		/*
		 *
		 */

		// Central
		if (iterator->second.Division == "Central") {

			bool cfound = false;
			for (int i=0; i<(int)Central.size(); i++) {
                
                ifstream in(Central.at(i))->second.c_str());
                Team temp2;
                temp2.read(&in);

				if (temp1.WinPercent > temp2.WinPercent) {

					Central.insert(Central.begin()+i,temp1.TeamName);
					cfound = true;
					break;

				} else if (temp1.WinPercent==temp2.WinPercent) {

					edge = TieBreak(temp1,temp2);
					if (edge) {

						Central.insert(Central.begin()+i,temp1.TeamName);
						cfound = true;
						break;

					}
				}
			}
			if (!cfound) {

				Central.push_back(temp1.TeamName);

			}
		}

		/*
		 *
		 */

		// Southeast
		if (iterator->second.Division == "Southeast") {

			bool sefound = false;
			for (int i=0; i<(int)Southeast.size(); i++) {
                
                ifstream in(Southeast.at(i))->second.c_str());
                Team temp2;
                temp2.read(&in);

				if (temp1.WinPercent > temp2.WinPercent) {

					Southeast.insert(Southeast.begin()+i,temp1.TeamName);
					sefound = true;
					break;

				} else if (temp1.WinPercent==temp2.WinPercent) {

					edge = TieBreak(temp1,temp2);
					if (edge) {

						Southeast.insert(Southeast.begin()+i,temp1.TeamName);
						sefound = true;
						break;

					}
				}
			}
			if (!sefound) {

				Southeast.push_back(temp1.TeamName);

			}
		}

		/*
		 *
		 */

		// Northwest
		if (iterator->second.Division == "Northwest") {

			bool nfound = false;
			for (int i=0; i<(int)Northwest.size(); i++) {
                
                ifstream in(Northwest.at(i))->second.c_str());
                Team temp2;
                temp2.read(&in);

				if (temp1.WinPercent > temp2.WinPercent) {

					Northwest.insert(Northwest.begin()+i,temp1.TeamName);
					nfound = true;
					break;

				} else if (temp1.WinPercent==temp2.WinPercent) {

					edge = TieBreak(temp1,temp2);
					if (edge) {

						Northwest.insert(Northwest.begin()+i,temp1.TeamName);
						nfound = true;
						break;

					}
				}
			}
			if (!nfound) {

				Northwest.push_back(temp1.TeamName);

			}
		}


		/*
		 *
		 */

		// Pacific
		if (iterator->second.Division == "Pacific") {

			bool pfound = false;
			for (int i=0; i<(int)Pacific.size(); i++) {
                
                ifstream in(Pacific.at(i))->second.c_str());
                Team temp2;
                temp2.read(&in);

				if (temp1.WinPercent > temp2.WinPercent) {

					Pacific.insert(Pacific.begin()+i,temp1.TeamName);
					pfound = true;
					break;

				} else if (temp1.WinPercent==temp2.WinPercent) {

					edge = TieBreak(temp1,temp2);
					if (edge) {

						Pacific.insert(Pacific.begin()+i,temp1.TeamName);
						pfound = true;
						break;

					}
				}
			}
			if (!pfound) {

				Pacific.push_back(temp2.TeamName);

			}
		}

		/*
		 *
		 */

		// Southwest
		if (iterator->second.Division == "Southwest") {

			bool swfound = false;
			for (int i=0; i<(int)Southwest.size(); i++) {
                
                ifstream in(Southwest.at(i))->second.c_str());
                Team temp2;
                temp2.read(&in);

				if (temp1.WinPercent > temp2.WinPercent) {

					Southwest.insert(Southwest.begin()+i,temp1.TeamName);
					swfound = true;
					break;

				} else if (temp1.WinPercent==temp2.WinPercent) {

					edge = TieBreak(temp1,temp2);
					if (edge) {

						Southwest.insert(Southwest.begin()+i,temp1.TeamName);
						swfound = true;
						break;

					}
				}
			}
			if (!swfound) {

				Southwest.push_back(temp1.TeamName);

			}
		}


		/*
		 *
		 */

		// Midwest
		if (iterator->second.Division == "Midwest") {

			bool mwfound = false;
			for (int i=0; i<(int)Midwest.size(); i++) {
                
                ifstream in(Midwest.at(i))->second.c_str());
                Team temp2;
                temp2.read(&in);

				if (temp1.WinPercent > temp2.WinPercent) {

					Midwest.insert(Midwest.begin()+i,temp1.TeamName);
					mwfound = true;
					break;

				} else if (temp1.WinPercent==temp2.WinPercent) {

					edge = TieBreak(temp1,temp2);
					if (edge) {

						Midwest.insert(Midwest.begin()+i,temp1.TeamName);
						mwfound = true;
						break;

					}
				}
			}
			if (!mwfound) {

				Midwest.push_back(temp1.TeamName);

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



