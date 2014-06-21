/*
 ============================================================================
 Name        : input.h
 Author      : oosode
 Version     : 
 Date        : Nov 9, 2013
 Description : 
 ============================================================================
 */
#ifndef INPUT_H_
#define INPUT_H_

#include "pointers.h"
#include <vector>
#include <string>

namespace NBA_NS {

class Input : protected Pointers {
 public:

   // ** Constructor/destructor ** //
   Input(NBA *);
   ~Input();

   // ** Variables ** //
   char input_name[256];
   char season_name[256];
   char playoff_name[256];
   char atoms_file[256];
   char restart_file[256];
   double clock_start;
   double clock_end;
   double run_time;
   std::vector<std::string> input_file;

   // ** Functions ** //
   void read_input_file();
   void read_atoms_file();
   void read_restart_file();
   void write_restart_file();

};

}

#endif /* INPUT_H_ */
