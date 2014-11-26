/*
 ============================================================================
 Name        : run.h
 Author      : oosode
 Version     : 
 Date        : Nov 9, 2013
 Description : 
 ============================================================================
 */
#ifndef RUN_H_
#define RUN_H_

#include "pointers.h"

// Run type definitions
#define RUN_ALL_DEFAULT     0
#define RUN_ALL_CLEAR       1
#define RUN_SEASON_DEFAULT  2
#define RUN_SEASON_CLEAR    3
#define RUN_PLAYOFF_DEFAULT 4
#define RUN_PLAYOFF_CLEAR   5
#define RUN_DRAFT_DEFAULT   6
#define RUN_DRAFT_CLEAR     7

namespace NBA_NS {

class Run : protected Pointers {
 public:

   // ** Constructor/destructor ** //
   Run(NBA *);
   ~Run();

   // ** Variables ** //
   int sim_type;                // Run type index

   bool debug;					// debugging
   bool save; 					// save data

   // ** Ratings ** //
   int rating_freq;				// rating frequency (games)
   int rating_min;				// minimum rating value (games)
   int rating_memory;			// memory of rating (games/team)
   double rating_init;			// initial rating value

   int nsims;					// number of simulations

   // ** Print Variables ** //
	bool p_histograms;
	bool p_standings;
	bool p_margins;
	bool p_averages;
	bool p_rankings;


   // ** Functions ** //
   void run_simulation();       // General run calculation
   void run_all(int);			//
   void run_season(int);
   void run_playoffs(int);
   void run_draft(int);
   //void calculate_energy();    // Computes energy only
   //void calculate_force();     // Computes energy + force
   //void calculate_moldyn();    // Computes molecular dynamics
   //void do_fmo_calculations(int); // Performs the all FMO calculations in parallel
   //void do_fmo_calculations_env();  // Performs the FMO calculations in parallel, using env approximation
   //void perturb_coords();      // Just to perturb the coordinates slightly randomly

};

}

#endif /* RUN_H_ */
