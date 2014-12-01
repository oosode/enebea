/*
 ============================================================================
 Name        : nba.cpp
 Author      : oosode
 Version     : 
 Date        : Nov 9, 2013
 Description : 
 ============================================================================
 */

#include "nba.h"
#include "stdio.h"
#include "string.h"
#include "run.h"
#include "season.h"
#include "input.h"
#include "game.h"
#include "team.h"
#include <unistd.h>
//#include "fmr_math.h"

using namespace NBA_NS;

/*-----------------------------------------------------------------
  Constructor
-----------------------------------------------------------------*/

NBA::NBA(int argc, char **argv, MPI_Comm communicator)
{

  // Handle MPI stuff
  world = communicator;
  MPI_Comm_size(world, &world_size);
  MPI_Comm_rank(world, &my_rank);
  master_rank = (my_rank == MASTER_RANK) ? 1 : 0;
  if (master_rank) {

	printf("\n\n\n");
	printf("                                        888                      \n");
	printf("                 ,e e,  888 8e   ,e e,  888 88e   ,e e,   ,'Y88b \n");
	printf("                d88 88b 888 88b d88 88b 888 888b d88 88b '8' 888 \n");
	printf("                888   , 888 888 888   , 888 888P 888   , ,ee 888 \n");
	printf("                 'YeeP' 888 888  'YeeP' 888 88'   'YeeP' '88 888 \n");
	printf("\n\n");

	usleep(100000);

    printf("enebea on %d MPI ranks.\n\n", world_size);
  }

  // Create some of the basic pointers
  run        = new Run(this);
  input      = new Input(this);
  season     = new Season(this);
  game       = new Game(this);
  team       = new Team(this);
  //math       = new Math(this);


  print_level = 0;

  // Parse the command line input
  parse_command_line(argc, argv);

}

/*-----------------------------------------------------------------
  Destructor
-----------------------------------------------------------------*/

NBA::~NBA()
{
  //if (matrix   != NULL) delete matrix;
  if (input    != NULL) delete input;
  if (run      != NULL) delete run;
  if (season   != NULL) delete season;
  if (game     != NULL) delete game;
  if (team     != NULL) delete team;
  //if (dynamics != NULL) delete dynamics;
  // NOTE: atom destrcutor must come last b/c other destructors need to know it's info in their destructors
  //if (atom     != NULL) delete atom;

  // ** Final printing ** //
  if (master_rank) {

	printf("\n\n\n");
	printf("                                        888                      \n");
	printf("                 ,e e,  888 8e   ,e e,  888 88e   ,e e,   ,'Y88b \n");
	printf("                d88 88b 888 88b d88 88b 888 888b d88 88b '8' 888 \n");
	printf("                888   , 888 888 888   , 888 888P 888   , ,ee 888 \n");
	printf("                 'YeeP' 888 888  'YeeP' 888 88'   'YeeP' '88 888 \n");
	printf("\n\n");
  }
}


/*-----------------------------------------------------------------
  Parse command line input
-----------------------------------------------------------------*/
void NBA::parse_command_line(int argc, char **argv)
{

  bool print_help = false;
  if (argc <= 1) {
    print_help = true;
  } else {
    if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"h") == 0) {
      print_help = true;
    }
  }

  // Crash with help menu if detected error
  if (print_help) {
    if (master_rank) {
      printf("----- ENEBEA Help -----\n");
      printf("Command syntax:\n");
      printf("enebea.exe [input filename]\n");
      printf("\n\n");
      printf("Exiting...\n");
    }
    MPI_Barrier(world);
    MPI_Finalize();
    exit(1);
  }

  if (argc > 1) {
    // Get input file name and store it
    sprintf(input->input_name, "%s", argv[1]);
  }
  else {
    // Assume default file names
    if (master_rank) {
      printf("Assuming default file names.\n");
    }
  }

}

/*-----------------------------------------------------------------
  Crash with error message
-----------------------------------------------------------------*/

void NBA::error(const char *file, int line, const char *str)
{
  // Controlled error crash
  printf("Error on rank: %d   File: %s   Line: %d   Message: %s\n",
         my_rank, file, line, str);
  MPI_Abort(world,1);
}

/*-----------------------------------------------------------------
  Execute function
-----------------------------------------------------------------*/
void NBA::execute()
{

  // ** Read input file to get run specs first ** //
  input->read_input_file();
/*
  // ** Get atom information ** //
  if (input->read_restart) {
    // ** Load data from restart file ** //
    input->read_restart_file();
  } else {
    // ** Load data from file ** //
    input->read_atoms_file();
  }
*/
  // ** Run the requested calculation ** //
  run->run_simulation();

}

