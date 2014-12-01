/*
 ============================================================================
 Name        : run.cpp
 Author      : oosode
 Version     : 
 Date        : Dec 23, 2013
 Description : 
 ============================================================================
 */

#include "nba.h"
#include "run.h"
#include "input.h"
#include "season.h"
#include "game.h"


#define MAX_LENGTH 1024

using namespace NBA_NS;

/*-----------------------------------------------------------------
  Constructor
-----------------------------------------------------------------*/

Run::Run(NBA *nba) : Pointers(nba)
{
   // Set defaults
   sim_type   = RUN_ALL_DEFAULT;
   debug      = false;
   nsims      = 1;

/*
   n_monomers = 0;
   n_dimers   = 0;
   fmo_energies      = NULL;
   monomer_energies  = NULL;
   dimer_energies    = NULL;
   fmo_gradients     = NULL;
   monomer_gradients = NULL;
   dimer_gradients   = NULL;
*/
}

/*-----------------------------------------------------------------
  Destructor
-----------------------------------------------------------------*/

Run::~Run()
{
/*
  if (fmo_energies      != NULL) delete [] fmo_energies;
  if (monomer_energies  != NULL) delete [] monomer_energies;
  if (dimer_energies    != NULL) delete [] dimer_energies;
  if (fmo_gradients     != NULL) delete [] fmo_gradients;
  if (monomer_gradients != NULL) delete [] monomer_gradients;
  if (dimer_gradients   != NULL) delete [] dimer_gradients;
*/
}

/*-----------------------------------------------------------------
  Run simulation: Upper level run command
-----------------------------------------------------------------*/
void Run::run_simulation()
{

  // ** Start clock ** //
  MPI_Barrier(nba->world);
  double clock_start = MPI_Wtime();

  // ** Do the calculation ** //
  if (sim_type == RUN_ALL_DEFAULT) {
	run_all(0);
  }
  else if (sim_type == RUN_SEASON_DEFAULT) {
    run_season(0);
  }
  else if (sim_type == RUN_DRAFT_DEFAULT) {

  }
  else if (sim_type == RUN_PLAYOFF_DEFAULT) {

  }

  // ** Stop clock ** //
  MPI_Barrier(nba->world);
  double clock_end = MPI_Wtime();
  double run_time = clock_end - clock_start;
  if (nba->master_rank) {
    printf("\nTotal run time: %20.6f seconds on %d ranks\n", run_time, nba->world_size);
  }
}


void Run::run_all(int TYPE)
{
  run_season(TYPE);
  run_playoffs(TYPE);
  run_draft(TYPE);
}

void Run::run_season(int TYPE)
{
  nba->season->init();
  nba->season->load();
  nba->season->run();

}

void Run::run_playoffs(int TYPE)
{

}

void Run::run_draft(int TYPE)
{


}

