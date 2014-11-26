/*
 * funcions.cpp
 *
 *  Created on: Nov 25, 2012
 *      Author: Junior
 */

#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>

#include "functions.h"
#include "team.h"

using std::string;
using std::map;
using std::vector;
using std::cout;
using std::endl;

void findMassCenter(const vector<vector<double> > &mols, const vector<vector<string> > &mols_name, int natoms, int nmol, 
                    vector<double> &center_of_mass, const map<string, double> &Masses) {
	
  double Norm=0.0;

  for (int m=0; m<natoms; m++) {
    double mass=Masses.find(mols_name.at(nmol).at(m))->second;
    Norm+=mass;
    for (int l=0; l<3; l++) {
      center_of_mass[l]+=mols.at(m).at(l)*mass;
    }
  }
  for (int l=0; l<3; l++) {
    center_of_mass[l]/=Norm;
  }
}

void findDipoleCenter(const vector<vector<double> > &mols, const vector<vector<string> > &mols_name, int natoms, int nmol,
                      vector<double> &dipole_center, const map<string, int> &Charges) {
  
  double Norm=0.0;
 
  for (int m=0; m<natoms; m++) {
    double charge=Charges.find(mols_name.at(nmol).at(m))->second;
    Norm+=charge;
    for (int l=0; l<3; l++) {
      dipole_center[l]+=mols.at(m).at(l)*charge;
    }
  }
  for (int l=0; l<3; l++) {
    dipole_center[l]/=Norm;
  }
}

double distance2(const vector<double> &mol1, const vector<double> &mol2) {

  double d2=0.0;
  double dx=0.0;
  for (int l=0; l<3; l++) {
    dx=mol2.at(l)-mol1.at(l);
    d2+=dx*dx;
  }
  return d2;
}

void AssignGlobal(const vector<int> jc, const vector<int> &Nc, int j, int *jg, int *icelljg, int nmols ) {
  
  vector<int> tmp(3,0);
  for (int l=0; l<3; l++) {
    tmp[l]=jc[l];
    if (jc[l]<0) { tmp[l]=jc[l]+Nc[l]; }
  }
  *icelljg=tmp[0]+Nc[0]*(tmp[1]+Nc[1]*tmp[2]);
  *jg=j+nmols*(*icelljg);
}

bool CheckConverged(const vector<vector<double> > &prev, const vector<vector<double> > &curr) {
  double tolerance=0.001;

  for (int i=0; i<(int)prev.size(); i++) {
    for (int j=0; j<(int)prev.at(i).size(); j++) {
      if (curr.at(i).at(j) - prev.at(i).at(j) > tolerance) {
        return false;
      }
    }  
  }  
  return true;
}

bool foundKey(string &str1, const vector<string> &str2) {
  bool found=false;
  for (int i=0; i<(int)str2.size(); i++) {
    if (str1.compare(str2.at(i))==0) {
      found=true;
      return found;
    }
  }  
  return found;
}

void StringExplode(string str, string separator, vector<string> *results) {
    int found;
    results->clear();
    found = str.find_first_of(separator);

    if (separator==" ") {

    	while(found != (int)string::npos){

			if(found > 0){
				results->push_back(str.substr(0,found));
			}
			str = str.substr(found+1);
			found = str.find_first_of(separator);
		}
		if (str.length() > 0){
			results->push_back(str);
		}

    } else {

    	while(found != (int)string::npos){

    		if(found > 0){
				results->push_back(str.substr(0,found));
			} else {
				string placeholder="";
				results->push_back(placeholder);
			}
			str = str.substr(found+1);
			found = str.find_first_of(separator);
		}
		if (str.length() >= 0){
			results->push_back(str);
		}
    }
}

void StringRemove(char separator, string *str) {
    for (int l=str->size()-1; l>=0; l--) {
        if (str->at(l)==separator) {
        	str->erase(l,1);
        }
    }
}

void PrintVector(const vector<double> &V) {
	for (int a=0; a<(int)V.size(); a++) {
	    cout << V.at(a) << " ";
	}
	cout << endl;
}

void PrintVector(const vector<int> &V) {
	for (int a=0; a<(int)V.size(); a++) {
	    cout << V.at(a) << " ";
	}
	cout << endl;
}

void PrintVector(const vector<string> &V) {
	for (int a=0; a<(int)V.size(); a++) {
	    cout << V.at(a) << " ";
	}
	cout << endl;
}

void PrintVector(const vector<Team> &V) {
	for (int a=0; a<(int)V.size(); a++) {
	    cout << V.at(a).Lottery << " ";
	}
	cout << endl;
}

void PrintMatrix(const vector<vector<double> > &M) {
	for (int a=0; a<(int)M.size(); a++) {
		for (int b=0; b<(int)M.at(a).size(); b++) {
			printf("%5.1f ",M.at(a).at(b));
		}
		printf("\n");
	}
}

void PrintMatrix(const vector<vector<int> > &M) {
	for (int a=0; a<(int)M.size(); a++) {
		for (int b=0; b<(int)M.at(a).size(); b++) {
			printf("%4d ",M.at(a).at(b));
		}
		printf("\n");
	}
}

void PrintMatrix(const vector<vector<string> > &M) {
	for (int a=0; a<(int)M.size(); a++) {
		for (int b=0; b<(int)M.at(a).size(); b++) {
			printf("%s ",M.at(a).at(b).c_str());
		}
		printf("\n");
	}
}

void AtomIdx(const vector<vector<vector<double> > >&mols, int i, int &idx) {
  idx=0;
  for (int imol=0; imol<(int)mols.size(); imol++) {
	if (imol==i) {
      break;
	}
	idx+=mols.at(imol).size();
  }
}

int MAX(int a, int b) {
	if (a >= b) {
		return a;
	} else {
		return b;
	}
}

double MAX(double a, double b) {
	if (a >= b) {
		return a;
	} else {
		return b;
	}
}

int SUM(const vector<int> a) {

	int s=0;
	for (int i=0; i<(int)a.size(); i++) s+=a.at(i);
	return s;
}

double SUM(const vector<double> a) {

	double s=0;
	for (int i=0; i<(int)a.size(); i++) s+=a.at(i);
	return s;

}
int SUM(map<string,int> a) {

	double s=0;
	typedef map<string,int>::iterator iter;
	for (iter ir=a.begin(); ir!=a.end(); ir++) s+=ir->second;
	return s;
}
double SUM(map<string,double> a) {

	double s=0.0;
	typedef map<string,double>::iterator iter;
	for (iter ir=a.begin(); ir!=a.end(); ir++) s+=ir->second;
	return s;
}
double AVERAGE(map<string,double> a) {

	double s=0.0;
	typedef map<string,double>::iterator iter;
	for (iter ir=a.begin(); ir!=a.end(); ir++) s+=ir->second/double(a.size());
	return s;

}

double AVERAGE(const vector<double> a) {

	double s=0; double size=(double)a.size();
	for (int i=0; i<(int)a.size(); i++) s+=a.at(i)/size;
	return s;
}

double AVERAGE(const vector<int> a) {

	double s=0; double size=(double)a.size();
	for (int i=0; i<(int)a.size(); i++) s+=a.at(i)/size;
	return s;
}
double WeightedSum(double a, double b, double c) {

	return 6.0*a+3.0*b+1.0*c;
}
int WeightedSum(int a, int b, int c) {

	return 6*a+3*b+1*c;
}

/*
vector<double> SymApply(vector<vector<double> > rotation, vector<double> translation, vector<double> c) {

	vector<double> cnew(3,0.0);

	for (int i=0; i<3; i++) {
		cnew[i]=0.0;
		for (int j=0; j<3; j++) {
			cnew.at(i)+=rotation.at(i).at(j)*c.at(j);
		}
	}
	for (int i=0; i<3; i++) {
		cnew.at(i)+=translation.at(i);
	}
	return cnew;
}

vector<vector<double> > SymApplyMol(vector<vector<double> > rotation, vector<double> translation, vector<vector<double> > mol) {

	vector<vector<double> > molnew;
	molnew.resize(mol.size());

	for (int i=0; i<(int)mol.size(); i++) {

		vector<double> atomnew=SymApply(rotation,translation,mol.at(i));
		molnew.at(i)=atomnew;

	}
	return molnew;
}

int MulSize(int mul_order) {
	return ((mul_order+1)*(mul_order+2)*(mul_order+3))/6;
}
*/

