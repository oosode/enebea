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

    double gb;
    Team temp1;
    Team temp2;
    
    //** Determines each teams 'games behind' for league standings **//
    ifstream in(League.at(0))->second.c_str());
    temp1.read(&in);
    
	for (int i=0; i<(int)League.size(); i++) {

        ifstream in(League.at(i))->second.c_str());
        ofstream out(League.at(i))->second.c_str());
        
        temp2.read(&in);

        temp2.Lstand.push_back(i+1);
		gb = GamesBack(temp2.Win,temp2.Loss,temp1.Win,temp1.Loss);
		temp2.GamesBehindL = gb;
        
        temp2.write(&out);
        out.flush();
    
	}
    
    //** Determines each teams 'games behind' for eastern standings **//
    ifstream in(Eastern.at(0))->second.c_str());
    temp1.read(&in);
    
    for (int i=0; i<(int)Eastern.size(); i++) {
        
        ifstream in(Eastern.at(i))->second.c_str());
        ofstream out(Eastern.at(i))->second.c_str());
        temp2.read(&in);
        
        temp2.Cstand.push_back(i+1);
        gb = GamesBack(temp2.Win,temp2.Loss,temp1.Win,temp1.Loss);
        temp2.GamesBehindC = gb;
        
        temp2.write(&out);
        out.flush();
        
    }
    
    //** Determines each teams 'games behind' for western standings **//
    ifstream in(Western.at(0))->second.c_str());
    temp1.read(&in);
    
    for (int i=0; i<(int)Western.size(); i++) {
        
        ifstream in(Western.at(i))->second.c_str());
        ofstream out(Western.at(i))->second.c_str());
        temp2.read(&in);
        
        temp2.Cstand.push_back(i+1);
        gb = GamesBack(temp2.Win,temp2.Loss,temp1.Win,temp1.Loss);
        temp2.GamesBehindC = gb;
        
        temp2.write(&out);
        out.flush();
        
    }
    
    //** Determines each teams 'games behind' for atlantic standings **//
    ifstream in(Atlantic.at(0))->second.c_str());
    temp1.read(&in);
    
    for (int i=0; i<(int)Atlantic.size(); i++) {
        
        ifstream in(Atlantic.at(i))->second.c_str());
        ofstream out(Atlantic.at(i))->second.c_str());
        temp2.read(&in);
        
        temp2.Dstand.push_back(i+1);
        gb = GamesBack(temp2.Win,temp2.Loss,temp1.Win,temp1.Loss);
        temp2.GamesBehindD = gb;
        
        temp2.write(&out);
        out.flush();
        
    }
    
    //** Determines each teams 'games behind' for central standings **//
    ifstream in(Central.at(0))->second.c_str());
    temp1.read(&in);
    
    for (int i=0; i<(int)Central.size(); i++) {
        
        ifstream in(Central.at(i))->second.c_str());
        ofstream out(Central.at(i))->second.c_str());
        temp2.read(&in);
        
        temp2.Dstand.push_back(i+1);
        gb = GamesBack(temp2.Win,temp2.Loss,temp1.Win,temp1.Loss);
        temp2.GamesBehindD = gb;
        
        temp2.write(&out);
        out.flush();
        
    }

    //** Determines each teams 'games behind' for southeast standings **//
    ifstream in(Southeast.at(0))->second.c_str());
    temp1.read(&in);
    
    for (int i=0; i<(int)Southeast.size(); i++) {
        
        ifstream in(Southeast.at(i))->second.c_str());
        ofstream out(Southeast.at(i))->second.c_str());
        temp2.read(&in);
        
        temp2.Dstand.push_back(i+1);
        gb = GamesBack(temp2.Win,temp2.Loss,temp1.Win,temp1.Loss);
        temp2.GamesBehindD = gb;
        
        temp2.write(&out);
        out.flush();
        
    }
    
    //** Determines each teams 'games behind' for pacific standings **//
    ifstream in(Pacific.at(0))->second.c_str());
    temp1.read(&in);
    
    for (int i=0; i<(int)Pacific.size(); i++) {
        
        ifstream in(Pacific.at(i))->second.c_str());
        ofstream out(Pacific.at(i))->second.c_str());
        temp2.read(&in);
        
        temp2.Dstand.push_back(i+1);
        gb = GamesBack(temp2.Win,temp2.Loss,temp1.Win,temp1.Loss);
        temp2.GamesBehindD = gb;
        
        temp2.write(&out);
        out.flush();
        
    }
    
    
    //** Determines each teams 'games behind' for northwest standings **//
    ifstream in(Northwest.at(0))->second.c_str());
    temp1.read(&in);
    
    for (int i=0; i<(int)Northwest.size(); i++) {
        
        ifstream in(Northwest.at(i))->second.c_str());
        ofstream out(Northwest.at(i))->second.c_str());
        temp2.read(&in);
        
        temp2.Dstand.push_back(i+1);
        gb = GamesBack(temp2.Win,temp2.Loss,temp1.Win,temp1.Loss);
        temp2.GamesBehindD = gb;
        
        temp2.write(&out);
        out.flush();
        
    }

    //** Determines each teams 'games behind' for southwest standings **//
    ifstream in(Southwest.at(0))->second.c_str());
    temp1.read(&in);
    
    for (int i=0; i<(int)Southwest.size(); i++) {
        
        ifstream in(Southwest.at(i))->second.c_str());
        ofstream out(Southwest.at(i))->second.c_str());
        temp2.read(&in);
        
        temp2.Dstand.push_back(i+1);
        gb = GamesBack(temp2.Win,temp2.Loss,temp1.Win,temp1.Loss);
        temp2.GamesBehindD = gb;
        
        temp2.write(&out);
        out.flush();
        
    }

    //** Determines each teams 'games behind' for midwest standings **//
    ifstream in(MIdwest.at(0))->second.c_str());
    temp1.read(&in);
    
    for (int i=0; i<(int)Midwest.size(); i++) {
        
        ifstream in(Midwest.at(i))->second.c_str());
        ofstream out(Midwest.at(i))->second.c_str());
        temp2.read(&in);
        
        temp2.Dstand.push_back(i+1);
        gb = GamesBack(temp2.Win,temp2.Loss,temp1.Win,temp1.Loss);
        temp2.GamesBehindD = gb;
        
        temp2.write(&out);
        out.flush();
        
    }
}

void FinalStanding(map<string, string> &TheTeams, double &q, bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("FinalStanding starting...\n"); }
    
    Team temp1;
    Team temp2;

	typedef map<string, string>::iterator it_type;
	for (it_type iterator = TheTeams.begin(); iterator != TheTeams.end(); iterator++) {
        
        ifstream in(iterator->second.c_str());
        ofstream out(iterator->second.c_str());
        temp1.read(&in);
        
		temp1.CalcBestPercent();
        
        temp1.write(&out);
        out.flush();

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
                
                edge = PlayoffTieBreak(temp1,temp2);
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
                    
                    edge = PlayoffTieBreak(temp1,temp2);
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
                    
                    edge = PlayoffTieBreak(temp1,temp2);
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
                    
                    edge = PlayoffTieBreak(temp1,temp2);
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
                    
                    edge = PlayoffTieBreak(temp1,temp2);
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
                    
                    edge = PlayoffTieBreak(temp1,temp2);
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
                    
                    edge = PlayoffTieBreak(temp1,temp2);
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
                    
                    edge = PlayoffTieBreak(temp1,temp2);
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
                    
                    edge = PlayoffTieBreak(temp1,temp2);
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
                    
                    edge = PlayoffTieBreak(temp1,temp2);
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
            
            ifstream in(TheTeams.find(EastSeeds.at(i)->second.c_str())->second.c_str());
            Team temp2;
            temp2.read(&in);

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



