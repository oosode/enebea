/*
 * postseason.h
 *
 *  Created on: Apr 8, 2013
 *      Author: oosode
 */


#ifndef POSTSEASON_H_
#define POSTSEASON_H_

#include "game.h"
#include "team.h"

class Game;
class Team;

struct Bracket {

	string East1A;
	int East1Agames;

	string East1B;
	int East1Bgames;

	string East2A;
	int East2Agames;

	string East2B;
	int East2Bgames;

	string East3A;
	int East3Agames;

	string East3B;
	int East3Bgames;

	string East4A;
	int East4Agames;

	string East4B;
	int East4Bgames;

	string East5A;
	int East5Agames;

	string East5B;
	int East5Bgames;

	string East6A;
	int East6Agames;

	string East6B;
	int East6Bgames;

	string East7A;
	int East7Agames;

	string East7B;
	int East7Bgames;

	string West1A;
	int West1Agames;

	string West1B;
	int West1Bgames;

	string West2A;
	int West2Agames;

	string West2B;
	int West2Bgames;

	string West3A;
	int West3Agames;

	string West3B;
	int West3Bgames;

	string West4A;
	int West4Agames;

	string West4B;
	int West4Bgames;

	string West5A;
	int West5Agames;

	string West5B;
	int West5Bgames;

	string West6A;
	int West6Agames;

	string West6B;
	int West6Bgames;

	string West7A;
	int West7Agames;

	string West7B;
	int West7Bgames;


	string FinalA;
	int FinalAgames;

	string FinalB;
	int FinalBgames;

};

void AverageDraft(vector<map<string, Team> > &T, map<string, vector<double> > &AvgDraftPos,double &q,bool debug);
void Draft(map<string,Team> &T,double &q,bool debug);
void Playoffs(vector<Game> &Games, map<string, Team> &T, double &q, bool debug);
void Series(vector<Game> &Games, Team &A, Team &B, string &team, int r);
void SeriesFinal(vector<Game> &Games, Team &A, Team &B, string &team, int r);

#endif /* POSTSEASON_H_ */
