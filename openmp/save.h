/*
 * save.h
 *
 *  Created on: Apr 9, 2013
 *      Author: oosode
 */

#ifndef SAVE_H_
#define SAVE_H_

#include <string>
#include <iostream>
#include <time.h>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

void SaveData(string inp, vector<string> fil, string &savedir, double &sprint, bool debug);
void Save(runparams &parms);

#endif /* SAVE_H_ */
