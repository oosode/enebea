/*
 ============================================================================
 Name        : input.cpp
 Author      : oosode
 Version     : 
 Date        : Nov 9, 2013
 Description : 
 ============================================================================
 */

#include "nba.h"
#include "input.h"
#include "run.h"
#include <vector>
#include <string>


#define MAX_LENGTH   256
#define SMALL_LENGTH 128

using namespace NBA_NS;

/*-----------------------------------------------------------------
  Constructor
-----------------------------------------------------------------*/

Input::Input(NBA *nba) : Pointers(nba)
{
  // Default file names
  sprintf(input_name, "%s", "info.inp");
  //sprintf(atoms_file, "%s", "fmr.atoms");
  //sprintf(restart_file, "%s", "fmr.restart");
}

/*-----------------------------------------------------------------
  Destructor
-----------------------------------------------------------------*/

Input::~Input()
{

}


/*-----------------------------------------------------------------
  Read input file to get all the run specs
-----------------------------------------------------------------*/
void Input::read_input_file()
{
  // Only the master rank reads the input for FMR here
  // Specs are broadcast subsequently
  if (nba->master_rank) {

	clock_start = MPI_Wtime();

	printf("     INPUT| Reading input file     %55s\n",input_name);
	printf("INPUT| Reading input file     %55s\n",input_name);

/*
    FILE *fs = fopen(input_file, "r");
    if (fs == NULL) {
      nba->error(FLERR, "Failure to read input file.\n");
    }

    std::vector<std::string> input_lines;

    // Go through each line of input_file until end of file

    char line[MAX_LENGTH];
    while ( fgets(line, MAX_LENGTH, fs) != NULL ) {

      char arg0[SMALL_LENGTH];
      char arg1[SMALL_LENGTH];
      char arg2[SMALL_LENGTH];
      char arg3[SMALL_LENGTH];

      if ( sscanf(line, "%s", arg0) == 1) {
        // Four argument line

        if ( strcmp(arg0, "&analysis") == 0 ) {

        	while ( fgets(line, MAX_LENGTH, fs) != NULL ) {

        		if (sscanf(line, "%s %s %s %s", arg0, arg1, arg2, arg3) == 4) {
        			if ( strcmp(arg0, "season") == 0 ) {

        				break;
        			} else if ( strcmp(arg0, "player") == 0 ) {

        			} else if ( strcmp(arg0, "team") == 0 ) {

        			}

        		} else if (sscanf(line, "%s %s %s", arg0, arg1, arg2) == 3) {


        		} else if (sscanf(line, "%s %s", arg0, arg1) == 2) {
        			if ( strcmp(arg0, "website") == 0 ) {


        		    }
        		} else if ( sscanf(line, "%s", arg0) == 1) {
        			if ( strcmp(arg0, "&analysis") == 0 ) break;
        		}
        	}


        } else if (strcmp(arg0, "&simulation") == 0 ) {
        	if (sscanf(line, "%s %s %s", arg0, arg1, arg2) == 3) {
        		if ( strcmp(arg0, "run") == 0 ) {
        			if (strcmp(arg1, "nsims") == 0) nba->run->nsims=atoi(arg2);
        		}
        	} else if (sscanf(line, "%s", arg0) == 0) {
        		if ( strcmp(arg0, "&simulation") == 0 ) break;
        	}

        }


      }
    }
    fclose(fs);
*/
    nba->run->debug=true;
    nba->run->nsims=10;
    nba->run->sim_type=0;
/*
	std::string temp;
	std::vector<std::string> tmp;
	std::vector<std::string> tmp0;

	char line[1024];

	while (fgets(line, sizeof(line), stdin)) {
	    input_file.push_back(line);
	}

	for (int i=0; i<(int)input_file.size(); i++) {

		if (input_file.at(i).find("&filename")!=std::string::npos) {

			StringExplode(input_file.at(i+1),"\n",&tmp);
			input_file=tmp.at(0);
			continue;

		} else if (parms.flnm.at(i).find("&analysis")!=string::npos) {

			for (int x=i; x<100+i; x++) {

				StringExplode(parms.flnm.at(x+1),"\n",&tmp);
				vector<string> tmp2;
				StringExplode(tmp.at(0)," ",&tmp2);

				if (tmp.at(0).empty()) continue;

				if (tmp2.at(0)== "/") break;

				if (tmp2.at(0)=="team") parms.analysis=true;

				else if (tmp2.at(0)=="player") parms.analysis=true;

				else if (tmp2.at(0)=="season") parms.analysis=true;

				else if (tmp2.at(0)=="website") { parms.website=tmp2.at(1); }

				//
				//player analysis
				if (tmp2.at(0)=="player") {

					if (tmp2.size()>=4) {

						if (tmp2.at(1)=="analysis") {

							parms.player_analysis=true;

							if (tmp2.at(2)=="print") parms.print_player_analysis=tmp2.at(3);

							else if (tmp2.at(2)=="read") parms.read_player_analysis=tmp2.at(3);

							else if (tmp2.at(2)=="stat") parms.player_analysis_stat=tmp2.at(3);

							else if (tmp2.at(2)=="begin") parms.begin_player_analysis=atoi(tmp2.at(3).c_str());

							else if (tmp2.at(2)=="end") parms.end_player_analysis=atoi(tmp2.at(3).c_str());

						} else if (tmp2.at(1)=="update") {

							parms.player_update=true;

							if (tmp2.at(2)=="print") parms.print_player_update=tmp2.at(3);

							else if (tmp2.at(2)=="read") parms.read_player_update=tmp2.at(3);

							else if (tmp2.at(2)=="year") parms.player_update_year=atoi(tmp2.at(3).c_str());

						} else if (tmp2.at(1)=="download") {

							parms.player_download=true;

							if (tmp2.at(2)=="print") parms.print_player_download=tmp2.at(3);

						}

					} else if (tmp2.size()>=2) {

						if (tmp2.at(1)=="update") { parms.player_update=true; }

						else if (tmp2.at(1)=="download") { parms.player_download=true; }

					} else { fprintf(stderr, "error: incorrect number of player analysis parameters\n\n");	}


				//team analysis
				} else if (tmp2.at(0)=="team") {

					if (tmp2.size()>=4) {

						if (tmp2.at(1)=="download") {

							parms.team_download=true;

							if (tmp2.at(2)=="print") parms.print_team_download=tmp2.at(3);

							else if (tmp2.at(2)=="year") parms.team_download_year=atoi(tmp2.at(3).c_str());

							else if (tmp2.at(2)=="read") parms.read_team_download=tmp2.at(3);

						} else if (tmp2.at(1)=="update") {

							parms.team_update=true;

							if (tmp2.at(2)=="print") parms.print_team_update=tmp2.at(3);

							else if (tmp2.at(2)=="year") parms.team_update_year=atoi(tmp2.at(3).c_str());

							else if (tmp2.at(2)=="type") parms.team_update_type=tmp2.at(3);

							else if (tmp2.at(2)=="read") {

								if (tmp2.at(3)=="team") parms.read_team_update_team=tmp2.at(4);

								else if (tmp2.at(3)=="player") parms.read_team_update_player=tmp2.at(4);
							}
						}

					} else if (tmp2.size()>=2) {

						if (tmp2.at(1)=="download") { parms.team_download=true; }

						else if (tmp2.at(1)=="update") { parms.team_update=true; }

					} else { fprintf(stderr, "error: incorrect number of team analysis parameters\n\n"); }

				//season analysis
				} else if (tmp2.at(0)=="season") {

					if (tmp2.size()>=4) {

						if (tmp2.at(1)=="update") {

							parms.season_update=true;

							if (tmp2.at(2)=="print") parms.print_season_update=tmp2.at(3);

							else if (tmp2.at(2)=="begin") parms.begin_season_update=tmp2.at(3);

							else if (tmp2.at(2)=="end") parms.finish_season_update=tmp2.at(3);

							else if (tmp2.at(2)=="read") parms.read_season_update=tmp2.at(3);

						} else if (tmp2.at(1)=="download") {

							parms.season_download=true;

							if (tmp2.at(2)=="print") parms.print_season_download=tmp2.at(3);

							else if (tmp2.at(2)=="year") parms.season_download_year=atoi(tmp2.at(3).c_str());

						}

					} else if (tmp2.size()==2) {

						if (tmp2.at(1)=="update") { parms.season_update=true; }

						else if (tmp2.at(1)=="download") { parms.season_download=true; }

					} else { fprintf(stderr, "error: incorrect number of season analysis parameters\n\n"); }
				}
			}
			continue;

		} else if (parms.flnm.at(i).find("&simulation")!=string::npos) {

			for (int x=i; x<100+i; x++) {

				StringExplode(parms.flnm.at(x+1),"\n",&tmp);
				vector<string> tmp2;
				StringExplode(tmp.at(0)," ",&tmp2);

				if (tmp.at(0).empty()) continue;

				if (tmp2.at(0)== "/") break;

				if (tmp2.at(0)=="run") parms.simulation=true;

				//
				if (tmp2.at(0)=="run") {

					if (tmp2.size()>=3) {

						if (tmp2.at(1)=="runtype") parms.runtype=tmp2.at(2);

						else if (tmp2.at(1)=="read") parms.filename=tmp2.at(2);

						else if (tmp2.at(1)=="ratingrestart") parms.ratingrestart=tmp2.at(2);

						else if (tmp2.at(1)=="ratingmin") parms.ratingmin=atoi(tmp2.at(2).c_str());

						else if (tmp2.at(1)=="ratingmemory") parms.ratingmemory=atoi(tmp2.at(2).c_str());

						else if (tmp2.at(1)=="ratinginit") parms.ratinginit=atoi(tmp2.at(2).c_str());

						else if (tmp2.at(1)=="ratingfreq") parms.ratingfreq=atoi(tmp2.at(2).c_str());

						else if (tmp2.at(1)=="nsims") parms.nsims=atoi(tmp2.at(2).c_str());

					} else { fprintf(stderr, "error: incorrect number of player analysis parameters\n\n");	}

				}
			}
*/
/*
		} else if (parms.flnm.at(i).find("&nsims")!=string::npos) {

			StringExplode(parms.flnm.at(i+1),"\n",&tmp);
			parms.nsims=atoi(tmp.at(0).c_str());
			continue;
*/
/*
		} else if (parms.flnm.at(i).find("&parallel")!=string::npos) {

			StringExplode(parms.flnm.at(i+1),"\n",&tmp);
			parms.threads=atoi(tmp.at(0).c_str());
			continue;

		} else if (parms.flnm.at(i).find("&save")!=string::npos) {

			StringExplode(parms.flnm.at(i+1),"\n",&tmp);
			if (tmp.at(0)=="true" || tmp.at(0)=="True") { parms.save=true; continue; }

			else if (tmp.at(0) =="false" || tmp.at(0)=="False") { parms.save=false; continue; }

		} else if (parms.flnm.at(i).find("&print")!=string::npos) {

			parms.pl=0;
			int iter=1;

			while (parms.flnm.at(i+iter).find("/")==string::npos) {

				StringExplode(parms.flnm.at(i+iter),"\n",&tmp);
				if (tmp.at(0)=="standings") parms.pl += 1;

				else if (tmp.at(0)=="histograms") parms.pl += 2;

				else if (tmp.at(0)=="rankings") parms.pl += 4;

				else if (tmp.at(0)=="averages") parms.pl += 8;

				else if (tmp.at(0)=="margins") parms.pl += 16;

				iter+=1;
			}

		} else if (parms.flnm.at(i).find("&debug")!=string::npos) {

			parms.debug=false;
			StringExplode(parms.flnm.at(i+1),"\n",&tmp);
			if (tmp.at(0)=="true" || tmp.at(0)=="True") { parms.debug=true; continue; }

		}

	}

	if (parms.filename.size()==0) {

		fprintf(stderr, "error: no filename\n\n");
		//exit(1);

	}

	if (parms.simulation) {

		printf("     INPUT| filename               %55s\n",parms.filename.c_str());
		printf("     INPUT| runtype                %55s\n",parms.runtype.c_str());
		printf("     INPUT| number of sims         %55d\n",parms.nsims);

		if (parms.save) printf("     INPUT| save                   %55s\n","true");
		else printf("     INPUT| save                   %55s\n","false");

		printf("     INPUT| number of threads      %55d\n",parms.threads);
		printf("     INPUT| print level            %55d\n",parms.pl);
		printf("     INPUT| rating update frequency %54d\n",parms.ratingfreq);
		printf("     INPUT| rating update minimum  %55d\n",parms.ratingmin);
		printf("     INPUT| rating memory          %55d\n",parms.ratingmemory);
		if (!parms.ratingrestart.empty()) printf("     INPUT| rating restart file    %55s\n",parms.ratingrestart.c_str());
		if (parms.ratinginit>0 && parms.ratingrestart.empty()) printf("     INPUT| rating initial value   %55f\n",parms.ratinginit);

	}


	if (parms.analysis) {

		if (!parms.website.empty()) { printf("\n"); printf("     INPUT| analysis website       %55s\n",parms.website.c_str()); }

		if (parms.player_download) {

			printf("\n");
			printf("     INPUT| analysis player download print %47s\n",parms.print_player_download.c_str());

		}
		if (parms.player_update) {

			printf("\n");
			printf("     INPUT| analysis player update print %49s\n",parms.print_player_update.c_str());
			printf("     INPUT| analysis player update read  %49s\n",parms.read_player_update.c_str());
			printf("     INPUT| analysis player update year  %49d\n",parms.player_update_year);

		}
		if (parms.team_download) {

			printf("\n");
			printf("     INPUT| analysis team download print %49s\n",parms.print_team_download.c_str());
			printf("     INPUT| analysis team download read  %49s\n",parms.read_team_download.c_str());
			printf("     INPUT| analysis team download year  %49d\n",parms.team_download_year);

		}
		if (parms.team_update) {

			printf("\n");
			printf("     INPUT| analysis team update print   %49s\n",parms.print_team_update.c_str());
			printf("     INPUT| analysis team update read team   %45s\n",parms.read_team_update_team.c_str());
			printf("     INPUT| analysis team update read player %45s\n",parms.read_team_update_player.c_str());

		}
		if (parms.season_download) {

			printf("\n");
			printf("     INPUT| analysis season download print %47s\n",parms.print_season_download.c_str());
			printf("     INPUT| analysis season download year  %47d\n",parms.season_download_year);

		}
		if (parms.season_update) {

			printf("\n");
			printf("     INPUT| analysis season update print %49s\n",parms.print_season_update.c_str());
			printf("     INPUT| analysis season update read  %49s\n",parms.read_season_update.c_str());
			printf("     INPUT| analysis season update begin %49s\n",parms.begin_season_update.c_str());
			printf("     INPUT| analysis season update end   %49s\n",parms.finish_season_update.c_str());

		}
	}
*/
	printf("\n");

	clock_end = MPI_Wtime();
	run_time = clock_end - clock_start;

  }

  MPI_Barrier(nba->world);

  // Communicate run specs to all other ranks
  MPI_Bcast(&nba->run->sim_type, 1, MPI_INT, MASTER_RANK, nba->world);
  MPI_Bcast(&nba->run->debug, 1, MPI_C_BOOL, MASTER_RANK, nba->world);
  MPI_Bcast(&nba->run->nsims, 1, MPI_INT, MASTER_RANK, nba->world);
/*  MPI_Bcast(&nba->sim->qchem_scratch, MAX_LENGTH, MPI_CHAR, MASTER_RANK, nba->world);
  MPI_Bcast(&nba->sim->basis, MAX_LENGTH, MPI_CHAR, MASTER_RANK, nba->world);
  MPI_Bcast(&nba->sim->correlation, MAX_LENGTH, MPI_CHAR, MASTER_RANK, nba->world);
  MPI_Bcast(&nba->sim->exchange, MAX_LENGTH, MPI_CHAR, MASTER_RANK, nba->world);
  MPI_Bcast(&atoms_file, MAX_LENGTH, MPI_CHAR, MASTER_RANK, nba->world);
  MPI_Bcast(&nba->sim->FMO_only, 1, MPI_INT, MASTER_RANK, nba->world);
  MPI_Bcast(&nba->sim->EnvApprox, 1, MPI_INT, MASTER_RANK, nba->world);
  MPI_Bcast(&nba->state->max_hops, 1, MPI_INT, MASTER_RANK, nba->world);
  MPI_Bcast(&nba->print_level, 1, MPI_INT, MASTER_RANK, nba->world);
*/

}


