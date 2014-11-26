/*
 * cholesky.h
 *
 *  Created on: Jan 11, 2013
 *      Author: oosode
 */

#ifndef CHOLESKY_H_
#define CHOLESKY_H_

void choldc(vector<vector<double> > &a, int n, vector<double> &p);
void cholsl(vector<vector<double > > &a, int n, vector<double> &p, vector<double> &b, vector<double> &x);


#endif /* CHOLESKY_H_ */
