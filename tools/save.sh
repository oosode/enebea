#!/bin/bash

mkdir -p saved/run000
rundir=saved/run$(cd saved; /bin/ls -1 | tail -1 | sed -e 's/run//' | awk '{printf("%03d",$1+1)}')
mkdir $rundir
rmdir saved/run000

echo Saving run in $rundir

mv *conference.csv *league.csv *division.csv ratings.csv average_standing.csva*.kml _concurrent *.swiftx CONF PAR VMD RMSD OUT $rundir 2>/dev/null
