#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <time.h>

#include "team.h"
#include "functions.h"

using std::string;
using std::map;
using std::vector;

double distance2(const vector<double> &mol1, const vector<double> &mol2);
void findDipoleCenter(const vector<vector<double> > &mols, const vector<vector<string> > &mols_name, int natoms, int nmol,
                      vector<double> &dipole_center, const map<string, int> &Charges);
void findMassCenter(const vector<vector<double> > &mols, const vector<vector<string> > &mols_name, int natoms, int nmol,
                    vector<double> &center_of_mass, const map<string, double> &Masses);
void AssignGlobal(const vector<int> jc, const vector<int> &Nc, int j, int *jg, int *icelljg, int nmols );
bool CheckConverged(const vector<vector<double> > &prev, const vector<vector<double> > &curr);
bool foundKey(string &str1, const vector<string> &str2);
void StringExplode(string str, string separator, vector<string> *results);
void StringRemove(char separator, string *str);
void PrintVector(const vector<double> &V);
void PrintVector(const vector<int> &V);
void PrintVector(const vector<string> &V);
void PrintVector(const vector<Team> &V);
void PrintMatrix(const vector<vector<double> > &M);
void AtomIdx(const vector<vector<vector<double> > > &mols, int i, int &idx);
int MAX(int a, int b);
double MAX(double a, double b);
int SUM(const vector<int> a);
double SUM(const vector<double> a);
double SUM(const map<string,double> a);
int SUM(const map<string,int> a);
double AVERAGE(map<string,double> a);
double AVERAGE(const vector<double> a);
double AVERAGE(const vector<int> a);
double WeightedSum(double a, double b, double c);
int WeightedSum(int a, int b, int c);

vector<double> SymApply(vector<vector<double> > rotation, vector<double> translation, vector<double> c);
vector<vector<double> > SymApplyMol(vector<vector<double> > rotation, vector<double> translation, vector<vector<double> > mol);
int MulSize(int mul_order);

#endif /* FUNCTIONS_H_ */
