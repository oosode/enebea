/*
 * save.cpp
 *
 *  Created on: Apr 9, 2013
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
#include <fstream>
#include <sstream>


using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;
using std::ofstream;
using std::ios;


void Timings(double tread, double tprint, double tschedule) {

    printf("     TIMINGS| ReadInput finished in     %50.10f\n", tread);
    printf("     TIMINGS| PrintLevel finished in    %50.10f\n", tprint);
    printf("     TIMINGS| ReadSchedule finished in  %50.10f\n", tschedule);

}
