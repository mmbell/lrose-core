// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
//////////////////////////////////////////////////////////
// Args.cc : command line args
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// March 1998
//
//////////////////////////////////////////////////////////
//
// Minor modifications made by Niles Oien, Jan 1999 :
//
//     Some instances of argv[i+1] have been replaced with
//     argv[++i]
//
// - Which does not affect functionality, but it does
//   clean up the code a little.
//
/////////////////////////////////////////////////////////

#include <iostream>
#include "Args.hh"
#include <cstring>
#include <toolsa/str.h>
#include <toolsa/umisc.h>
using namespace std;

// Constructor

Args::Args (int argc, char **argv, char *prog_name)

{

  char tmp_str[BUFSIZ];

  // intialize

  OK = TRUE;
  Done = FALSE;
  startTime = 0;
  endTime = 0;
  TDRP_init_override(&override);

  // loop through args
  
  for (int i =  1; i < argc; i++) {

    if (!strcmp(argv[i], "--") ||
	!strcmp(argv[i], "-h") ||
	!strcmp(argv[i], "-help") ||
	!strcmp(argv[i], "-man")) {
      
      usage(prog_name, stdout);
      Done = TRUE;
      
    } else if (!strcmp(argv[i], "-debug")) {
      
      sprintf(tmp_str, "debug = DEBUG_NORM;");
      TDRP_add_override(&override, tmp_str);
      
    } else if (!strcmp(argv[i], "-verbose")) {
      
      sprintf(tmp_str, "debug = DEBUG_VERBOSE;");
      TDRP_add_override(&override, tmp_str);
      
    } else if (!strcmp(argv[i], "-mode")) {
      
      if (i < argc - 1) {
	sprintf(tmp_str, "mode = %s;", argv[++i]); // Was argv[i+1] - Niles.
	TDRP_add_override(&override, tmp_str);
      } else {
	OK = FALSE;
      }
	
    } else if (!strcmp(argv[i], "-trigger")) {
      
      if (i < argc - 1) {
	sprintf(tmp_str, "trigger = %s;", argv[++i]); // Was argv[i+1] - Niles.
	TDRP_add_override(&override, tmp_str);
      } else {
	OK = FALSE;
      }
	
    } else if (!strcmp(argv[i], "-start")) {
      
      if (i < argc - 1) {
	date_time_t start;
	if (sscanf(argv[++i], "%d %d %d %d %d %d",
		   &start.year, &start.month, &start.day,
		   &start.hour, &start.min, &start.sec) != 6) {
	  OK = FALSE;
	} else {
	  uconvert_to_utime(&start);
	  startTime = start.unix_time;
	  sprintf(tmp_str, "mode = ARCHIVE;");
	  TDRP_add_override(&override, tmp_str);
	}
      } else {
	OK = FALSE;
      }
	
    } else if (!strcmp(argv[i], "-end")) {
      
      if (i < argc - 1) {
	date_time_t end;
	if (sscanf(argv[++i], "%d %d %d %d %d %d",
		   &end.year, &end.month, &end.day,
		   &end.hour, &end.min, &end.sec) != 6) {
	  OK = FALSE;
	} else {
	  uconvert_to_utime(&end);
	  endTime = end.unix_time;
	  sprintf(tmp_str, "mode = ARCHIVE;");
	  TDRP_add_override(&override, tmp_str);
	}
      } else {
	OK = FALSE;
      }
    }
    
  } // i

  if (!OK) {
    usage(prog_name, stderr);
  }
    
}

void Args::usage(char *prog_name, FILE *out)
{

  cerr <<  "Usage: " << prog_name <<  " [options as below]\n"
       <<   "options:\n"
       <<   "       [ --, -h, -help, -man ] produce this list.\n"
       <<   "       [ -debug ] print debug messages\n"
       <<   "       [ -end \"yyyy mm dd hh mm ss\"] end time\n"
       <<   "                              ARCHIVE mode only\n"
       <<   "       [ -mdebug level ] set malloc debug level\n"
       <<   "       [ -mode ?] ARCHIVE or REALTIME\n"
       <<   "       [ -start \"yyyy mm dd hh mm ss\"] start time\n"
       <<   "                                  ARCHIVE mode only\n"
       <<   "       [ -trigger ?] TIME_TRIGGER or FILE_TRIGGER\n"
       <<   "       [ -verbose ] print verbosedebug messages\n"
       << endl << endl;

  
  cerr <<   "NOTE: for ARCHIVE mode, you must specify the times using start and end.\n"
       << "      In this case ARCHIVE mode will be automatically invoked." << endl << endl;

  
  TDRP_usage(out);
  
  cerr << endl << endl;

}






