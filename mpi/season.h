/*
 ============================================================================
 Name        : season.h
 Author      : oosode
 Version     : 
 Date        : Dec 24, 2013
 Description : 
 ============================================================================
 */
#ifndef SEASON_H_
#define SEASON_H_

#include "pointers.h"
#include <vector>
#include <string>

namespace NBA_NS {

class Season : protected Pointers {
 public:

   // ** Constructor/destructor ** //
   Season(NBA *);
   ~Season();

   // ** Variables ** //
   char filename[256];
   std::vector<std::string> finput;
   int ngames;
   int nteams;
   int year;
   int days;
   time_t begin;
   time_t end;
   Team *teams;
   Game *games;



   // ** Timings ** //
   double init_start;
   double init_end;
   double init_time;
   double define_start;
   double define_end;
   double define_time;
   double load_start;
   double load_end;
   double load_time;

/*
   int    nTimeSteps;             // Number of time steps to take
   int    iCurrentStep;           // The current step we are on
   double dt;                     // Time step increment [atomic units]
   int    vOption;                // Option for starting velocity
   int    iThermostat;            // Thermostat option selected
   double targetTemperature;      // Target temperature of the run (Kelvin)
   double currentTemperature;     // The current instantaneous temperature (Kelvin)
   double EPotential;             // Total potential energy
   double EKinetic;               // Total nuclear kinetic energy (does not include electron kinetic energy)
   double ETotal;                 // EPotential + EKinetic
   int    vseed;                  // RNG seed for random velocities
   char   trajFile[256];          // File to write trajectory to
   double tau;                    // Thermostat time constant, used in Berendsen and Langevin
*/
   // ** Functions ** //
   void   init();                   // Initializer function, calls others to set up MD run
   void   define();
   void   load();
   void   run();

/*
   void   setVelocities();          // Set velocities based on vOption
   double computeKE();              // Compute the kinetic energy
   double computeTemperature();     // Compute the temperature
   void   runMolecularDynamics();   // Runs MD
   void   stepPosition();           // Move positions forward one step
   void   halfStepVelocity(int);    // Propagate the velocities forward half a step
   void   stepReport(int);          // Print out stuff for time step
   void   writeTrajCoords(int);     // Write the current coordinates to trajectory file
   void   removeTransRotFromVelocity();  // Remove translation and rotation of atoms from velocity
   void   removeTransRotFromGradient();  // Remove translation and rotation of atoms from gradient
   void   applyThermostat();        // General function for applying thermostat for NVT dynamics
   void   thermostatLangevin();     // Langevin thermostat
   void   thermostatBerendsen();    // Berendsen thermostat
*/
};

}

#endif /* SEASON_H_ */
