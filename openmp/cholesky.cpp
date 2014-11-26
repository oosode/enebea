/*
 * cholesky.cpp
 *
 *  Created on: Jan 8, 2013
 *      Author: oosode
 */

/* Take the cholesky decomposition in the manner described in FA Graybill
   (1976).
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
#include <math.h>

using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::cin;

void choldc(vector<vector<double> > &a, int n, vector<double> &p) {

	//void nrerror(char error_text[]);
	int i,j,k;
	double sum;

	for (i=1;i<=n;i++) {
		for (j=i;j<=n;j++) {
			for (sum=a[i-1][j-1],k=i-1;k>=1;k--) sum -= a[i-1][k-1]*a[j-1][k-1];

			if (i == j) {

				if (sum <= 0.0) printf("choldc failed");
				p[i-1]=sqrt(sum);

			} else a[j-1][i-1]=sum/p[i-1];
		}
	}
}

void cholsl(vector<vector<double > > &a, int n, vector<double> &p, vector<double> &b, vector<double> &x) {

	int i,k;
	double sum;

	for (i=1;i<=n;i++) {
		for (sum=b[i-1],k=i-1;k>=1;k--) sum -= a[i-1][k-1]*x[k-1];
		x[i-1]=sum/p[i-1];
	}

	for (i=n;i>=1;i--) {
		for (sum=x[i-1],k=i+1;k<=n;k++) sum -= a[k-1][i-1]*x[k-1];
		x[i-1]=sum/p[i-1];
	}
}


