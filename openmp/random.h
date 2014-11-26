/*
 * random.h
 *
 *  Created on: Nov 13, 2012
 *      Author: Junior
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <limits>

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;


void seed();

double unifRand();

double gaussRand();

double tRand();

#endif /* RANDOM_H_ */
