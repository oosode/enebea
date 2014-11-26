/*
 ============================================================================
 Name        : main.cpp
 Author      : oosode
 Version     :
 Copyright   : 
 Description :
 ============================================================================
 */
#include "nba.h"

using namespace NBA_NS;

int main(int argc, char **argv)
{

  MPI_Init(&argc, &argv);

  NBA *nba = new NBA(argc, argv, MPI_COMM_WORLD);
  nba->execute();
  delete nba;

  MPI_Finalize();
  return 0;
}


