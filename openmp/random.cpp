/*
 * random.cpp
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
#include <cstdlib>
#include <limits>
//#include <random>

#include "random.h"

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;
//using std::default_random_engine;

const double PI = atan(1.0)*4;

void seed() {

	srand(time(NULL));

}

double unifRand() {

	double random;

	do {

		random = (double (rand())  + 1.) / (double (RAND_MAX) + 1.);

	} while (random == 1.0);

	return random;

}

double gaussRand() {

	double rand1 = unifRand();
	double rand2 = unifRand();

	//cout << rand1 << endl;

	double z1 = sin(2.0*PI*rand1)*sqrt(-2.*log(rand2));
	//double z2 = cos(2.0*PI*rand1)*sqrt(-2.*log(rand2));

	return z1;

}

double tRand() { // Student's t distribution

	double t;

	do {
		double rand1 = unifRand();
		double rand2 = unifRand();

		double df = 17.0;
		//double df = 3.0;

		t = sin(2.0*PI*rand1)*sqrt(df*(pow(rand2,-2.0/df)-1.0));

	} while (abs(t) > 10000000);

	return t*7.5;

}

/*
double normalRand() {

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(5.0,2.0);

	return 0;
}
*/
