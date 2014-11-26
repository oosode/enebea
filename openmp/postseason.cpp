/*
 * playoffs.cpp
 *
 *  Created on: Apr 7, 2013
 *      Author: oosode
 */

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <stdio.h>
#include <stdlib.h>

#include "random.h"
#include "game.h"
#include "read.h"
#include "team.h"
#include "standing.h"
#include "print.h"
#include "functions.h"
#include "ranking.h"
#include "random.h"

using std::pair;
using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;


void AverageDraft(vector<map<string, Team> > &T, map<string, vector<double> > &AvgDraftPos,double &q,bool debug) {

	if (debug) { printf("AverageDraft starting...\n"); }

	clock_t starttime=clock();

	double denom = double(T.size());
	vector<double> rank(2,0.0);

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = T.front().begin(); iterator != T.front().end(); iterator++) {

		AvgDraftPos.insert(pair<string, vector<double> >(iterator->second.TeamName, rank));

	}

	for (int i=0; i<(int)T.size(); i++) {

		for (it_type iterator = T.at(i).begin(); iterator != T.at(i).end(); iterator++) {

			AvgDraftPos.find(iterator->second.TeamName)->second.at(0) += double(iterator->second.Lottery+1)/denom;
			AvgDraftPos.find(iterator->second.TeamName)->second.at(1) += double(iterator->second.DraftPos+1)/denom;

		}
	}

	if (debug) { printf("AverageDraft exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;
}
void Draft(map<string,Team> &T,double &q,bool debug) {

	clock_t starttime=clock();

	if (debug) { printf("Draft starting...\n"); }

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

		iterator->second.Lottery=30;

	}

	bool pass=false;

	//Pick a random number between 1 and 1000
	int FirstBall=rand() % 1000 + 1;

	// determine draft winner
	if (FirstBall <= 250) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==0) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 250 and FirstBall <= 449) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==1) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 449 and FirstBall <= 605) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==2) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 605 and FirstBall <= 724) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==3) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 724 and FirstBall <= 812) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==4) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 812 and FirstBall <= 875) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==5) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 875 and FirstBall <= 918) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==6) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 918 and FirstBall <= 946) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==7) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 946 and FirstBall <= 963) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==8) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 963 and FirstBall <= 974) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==9) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 974 and FirstBall <= 982) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==10) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 982 and FirstBall <= 989) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==11) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 989 and FirstBall <= 995) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==12) {

				iterator->second.Lottery=0;
				break;

			}
		}

	} else if (FirstBall > 995 and FirstBall <= 1000) {

		for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

			if (iterator->second.DraftPos==13) {

				iterator->second.Lottery=0;
				break;

			}
		}
	}

	//Pick a random number between 1 and 1000
	int SecondBall;

	while (true) {

		pass=false;

		SecondBall=rand() % 1000 + 1;

		// second place
		if (SecondBall <= 216) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==0) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 216 and SecondBall <= 404) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==1) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 404 and SecondBall <= 561) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==2) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 561 and SecondBall <= 687) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==3) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 687 and SecondBall <= 784) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==4) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 784 and SecondBall <= 855) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==5) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 855 and SecondBall <= 904) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==6) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 904 and SecondBall <= 937) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==7) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 937 and SecondBall <= 957) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==8) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 957 and SecondBall <= 970) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==9) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 970 and SecondBall <= 979) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==10) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 979 and SecondBall <= 987) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==11) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 987 and SecondBall <= 994) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==12) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		} else if (SecondBall > 994 and SecondBall <= 1000) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==13) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=1;
					break;

				}
			}

		}
		if (pass) continue;

		break;
	}

	//Pick a random number between 1 and 1000
	int ThirdBall;

	while (true) {

		ThirdBall=rand() % 1000 + 1;

		pass=false;

		// third place
		if (ThirdBall <= 177) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==0) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 177 and ThirdBall <= 348) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==1) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 348 and ThirdBall <= 504) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==2) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 504 and ThirdBall <= 637) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==3) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 637 and ThirdBall <= 744) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==4) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 744 and ThirdBall <= 825) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==5) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 825 and ThirdBall <= 883) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==6) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 883 and ThirdBall <= 922) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==7) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 922 and ThirdBall <= 946) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==8) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 946 and ThirdBall <= 962) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==9) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 962 and ThirdBall <= 974) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==10) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 974 and ThirdBall <= 984) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==11) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 984 and ThirdBall <= 993) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==12) {

					if (iterator->second.Lottery!=30) { pass=true; break;}

					iterator->second.Lottery=2;
					break;

				}
			}

		} else if (ThirdBall > 993 and ThirdBall <= 1000) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==13) {

					if (iterator->second.Lottery!=30) { pass=true; break;} ;

					iterator->second.Lottery=2;
					break;

				}
			}

		}
		if (pass) continue;

		break;
	}

	/*
	 *
	 */

	bool found;

	for (int i=3; i<(int)T.size(); i++) {

		found=false;

		for (int j=0; j<(int)T.size(); j++) {

			for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

				if (iterator->second.DraftPos==j) {

					if (iterator->second.Lottery<i) break;

					else { iterator->second.Lottery=i; found=true; break; }

				}
			}

			if (found) break;
		}
	}

	if (debug) { printf("Draft exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;
}
void Series(vector<Game> &Games, Team &A, Team &B, string &team, int r) {

	int awins=0;
	int bwins=0;
	string awayT;
	string homeT;

	bool normal;

	if (A.WinPercent >= B.WinPercent) {

		normal = true;
		homeT = A.TeamName;
		awayT = B.TeamName;

	} else {

		normal = false;
		awayT = A.TeamName;
		homeT = B.TeamName;

	}

	time_t now = time(0);

	for (int g=0; g<7; g++) {

		if (awins>=4 || bwins>=4) break;

		DayInfo dnf;

		if (g==0 || g==1 || g==4 || g==6) {

			if (normal) {

				dnf.Date = now;
				dnf.Opponent = homeT;
				dnf.IsHome = false;
				dnf.Opp = &A;

				B.PlayoffSchedule.push_back(dnf);

				dnf.Date = now;
				dnf.Opponent = awayT;
				dnf.IsHome = true;
				dnf.Opp = &B;

				A.PlayoffSchedule.push_back(dnf);

				Games.push_back(Game());
				Games.back().Load(&A,&B,g,now,true);
				Games.back().SimPlayoffs(r);

			} else {

				dnf.Date = now;
				dnf.Opponent = awayT;
				dnf.IsHome = true;
				dnf.Opp = &A;

				B.PlayoffSchedule.push_back(dnf);

				dnf.Date = now;
				dnf.Opponent = homeT;
				dnf.IsHome = false;
				dnf.Opp = &B;

				A.PlayoffSchedule.push_back(dnf);

				Games.push_back(Game());
				Games.back().Load(&B,&A,g,now,true);
				Games.back().SimPlayoffs(r);

			}

		} else {

			if (normal) {

				dnf.Date = now;
				dnf.Opponent = homeT;
				dnf.IsHome = true;
				dnf.Opp = &A;

				B.PlayoffSchedule.push_back(dnf);

				dnf.Date = now;
				dnf.Opponent = awayT;
				dnf.IsHome = false;
				dnf.Opp = &B;

				A.PlayoffSchedule.push_back(dnf);

				Games.push_back(Game());
				Games.back().Load(&B,&A,g,now,true);
				Games.back().SimPlayoffs(r);

			} else {

				dnf.Date = now;
				dnf.Opponent = awayT;
				dnf.IsHome = false;
				dnf.Opp = &A;

				B.PlayoffSchedule.push_back(dnf);

				dnf.Date = now;
				dnf.Opponent = homeT;
				dnf.IsHome = true;
				dnf.Opp = &B;

				A.PlayoffSchedule.push_back(dnf);

				Games.push_back(Game());
				Games.back().Load(&A,&B,g,now,true);
				Games.back().SimPlayoffs(r);

			}


		}

		if (r==1) {

			if (A.oneWin==4) { team=A.TeamName; break; }

			else if (B.oneWin==4) { team=B.TeamName; break; }

		} else if (r==2) {

			if (A.twoWin==4) { team=A.TeamName; break; }

			else if (B.twoWin==4) { team=B.TeamName; break; }

		} else if (r==3) {

			if (A.threeWin==4) { team=A.TeamName; break; }

			else if (B.threeWin==4) { team=B.TeamName; break; }

		} else if (r==4) {

			if (A.fourWin==4) { team=A.TeamName; break; }

			else if (B.fourWin==4) { team=B.TeamName; break; }
		}

	}

	//team=A.TeamName;
	//return;

}
void SeriesFinal(vector<Game> &Games, Team &A, Team &B, string &team, int r) {

	int awins=0;
	int bwins=0;
	string awayT;
	string homeT;

	bool normal;

	if (A.WinPercent >= B.WinPercent) {

		normal=true;
		homeT = A.TeamName;
		awayT = B.TeamName;

	} else {

		normal=false;
		awayT = A.TeamName;
		homeT = B.TeamName;

	}

	time_t now = time(0);

	for (int g=0; g<7; g++) {

		if (awins>=4 || bwins>=4) break;

		DayInfo dnf;

		if (g==0 || g==1 || g==5 || g==6) {

			if (normal) {

				dnf.Date = now;
				dnf.Opponent = homeT;
				dnf.IsHome = false;
				dnf.Opp = &A;

				B.PlayoffSchedule.push_back(dnf);

				dnf.Date = now;
				dnf.Opponent = awayT;
				dnf.IsHome = true;
				dnf.Opp = &B;

				A.PlayoffSchedule.push_back(dnf);

				Games.push_back(Game());
				Games.back().Load(&A,&B,g,now,true);
				Games.back().SimPlayoffs(r);

			} else {

				dnf.Date = now;
				dnf.Opponent = awayT;
				dnf.IsHome = true;
				dnf.Opp = &A;

				B.PlayoffSchedule.push_back(dnf);

				dnf.Date = now;
				dnf.Opponent = homeT;
				dnf.IsHome = false;
				dnf.Opp = &B;

				A.PlayoffSchedule.push_back(dnf);

				Games.push_back(Game());
				Games.back().Load(&B,&A,g,now,true);
				Games.back().SimPlayoffs(r);

			}

		} else {

			if (normal) {

				dnf.Date = now;
				dnf.Opponent = homeT;
				dnf.IsHome = true;
				dnf.Opp = &A;

				B.PlayoffSchedule.push_back(dnf);

				dnf.Date = now;
				dnf.Opponent = awayT;
				dnf.IsHome = false;
				dnf.Opp = &B;

				A.PlayoffSchedule.push_back(dnf);

				Games.push_back(Game());
				Games.back().Load(&B,&A,g,now,true);
				Games.back().SimPlayoffs(r);

			} else {

				dnf.Date = now;
				dnf.Opponent = awayT;
				dnf.IsHome = false;
				dnf.Opp = &A;

				B.PlayoffSchedule.push_back(dnf);

				dnf.Date = now;
				dnf.Opponent = homeT;
				dnf.IsHome = true;
				dnf.Opp = &B;

				A.PlayoffSchedule.push_back(dnf);

				Games.push_back(Game());
				Games.back().Load(&A,&B,g,now,true);
				Games.back().SimPlayoffs(r);

			}
		}

		if (r==1) {

			if (A.oneWin==4) { team=A.TeamName; break; }

			else if (B.oneWin==4) { team=B.TeamName; break; }

		} else if (r==2) {

			if (A.twoWin==4) { team=A.TeamName; break; }

			else if (B.twoWin==4) { team=B.TeamName; break; }

		} else if (r==3) {

			if (A.threeWin==4) { team=A.TeamName; break; }

			else if (B.threeWin==4) { team=B.TeamName; break; }

		} else if (r==4) {

			if (A.fourWin==4) { team=A.TeamName; break; }

			else if (B.fourWin==4) { team=B.TeamName; break; }
		}

	}

	return;

}
void Playoffs(vector<Game> &Games, map<string, Team> &T, double &q, bool debug) {

	if (debug) { printf("Playoffs starting...\n"); }

	clock_t starttime=clock();

	// seeding
	string e1,e2,e3,e4,e5,e6,e7,e8;
	string w1,w2,w3,w4,w5,w6,w7,w8;

	typedef map<string, Team>::iterator it_type;
	for (it_type iterator = T.begin(); iterator != T.end(); iterator++) {

		if (iterator->second.Conference=="Eastern") {

			if (iterator->second.PlayoffSeed==0) {

				e1=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==1) {

				e2=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==2) {

				e3=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==3) {

				e4=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==4) {

				e5=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==5) {

				e6=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==6) {

				e7=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==7) {

				e8=iterator->second.TeamName;

			}

		} else if (iterator->second.Conference=="Western") {

			if (iterator->second.PlayoffSeed==0) {

				w1=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==1) {

				w2=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==2) {

				w3=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==3) {

				w4=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==4) {

				w5=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==5) {

				w6=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==6) {

				w7=iterator->second.TeamName;

			} else if (iterator->second.PlayoffSeed==7) {

				w8=iterator->second.TeamName;

			}
		}
	}

	// first round games
	string ea,eb,ec,ed,wa,wb,wc,wd;

	Series(Games,T.find(e1)->second,T.find(e8)->second,ea,1);
	Series(Games,T.find(e2)->second,T.find(e7)->second,eb,1);
	Series(Games,T.find(e3)->second,T.find(e6)->second,ec,1);
	Series(Games,T.find(e4)->second,T.find(e5)->second,ed,1);
	Series(Games,T.find(w1)->second,T.find(w8)->second,wa,1);
	Series(Games,T.find(w2)->second,T.find(w7)->second,wb,1);
	Series(Games,T.find(w3)->second,T.find(w6)->second,wc,1);
	Series(Games,T.find(w4)->second,T.find(w5)->second,wd,1);

	T.find(ea)->second.secondround="east_A";
	T.find(ed)->second.secondround="east_B";
	T.find(eb)->second.secondround="east_D";
	T.find(ec)->second.secondround="east_C";

	T.find(wa)->second.secondround="west_A";
	T.find(wd)->second.secondround="west_B";
	T.find(wb)->second.secondround="west_D";
	T.find(wc)->second.secondround="west_C";

	// second round games
	string ei,ej,wi,wj;

	Series(Games,T.find(ea)->second,T.find(ed)->second,ei,2);
	Series(Games,T.find(eb)->second,T.find(ec)->second,ej,2);
	Series(Games,T.find(wa)->second,T.find(wd)->second,wi,2);
	Series(Games,T.find(wb)->second,T.find(wc)->second,wj,2);

	T.find(ei)->second.conffinals="east_top";
	T.find(ej)->second.conffinals="east_bot";
	T.find(wi)->second.conffinals="west_top";
	T.find(wj)->second.conffinals="west_bot";

	// conference final games
	string ef,wf;

	Series(Games,T.find(ei)->second,T.find(ej)->second,ef,3);
	Series(Games,T.find(wi)->second,T.find(wj)->second,wf,3);

	T.find(ef)->second.finals="east";
	T.find(wf)->second.finals="west";

	// nba final games
	string champ;

	SeriesFinal(Games,T.find(ef)->second,T.find(wf)->second,champ,4);

	if (debug) { printf("Playoffs exiting...\n\n"); }

	clock_t endtime=clock();
	q=double(endtime-starttime)/CLOCKS_PER_SEC;

}
