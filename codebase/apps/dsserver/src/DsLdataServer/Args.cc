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
// May 2002
//
//////////////////////////////////////////////////////////

#include "Args.hh"
#include "Params.hh"
#include <cstdio>
#include <iostream>
#include <toolsa/str.h>
#include <cstdlib>
using namespace std;

// Constructor

Args::Args()

{
  TDRP_init_override(&override);
}

// destructor

Args::~Args()

{
  TDRP_free_override(&override);
}

// parse command line

int Args::parse (int argc, char **argv, const char *prog_name)

{

  char tmp_str[BUFSIZ];

  // intialize

  int iret = 0;
  
  // loop through args
  
  for (int i =  1; i < argc; i++) {

    if (!strcmp(argv[i], "--") ||
	!strcmp(argv[i], "-h") ||
	!strcmp(argv[i], "-help") ||
	!strcmp(argv[i], "-man")) {
      
      _usage(prog_name, cout);
      exit(0);
      
    } else if (!strcmp(argv[i], "-debug")) {
      
      sprintf(tmp_str, "debug = DEBUG_NORM;");
      TDRP_add_override(&override, tmp_str);
      
    } else if (!strcmp(argv[i], "-verbose")) {
      
      sprintf(tmp_str, "debug = DEBUG_VERBOSE;");
      TDRP_add_override(&override, tmp_str);

    } else if (!strcmp(argv[i], "-noThreads")) {
      
      sprintf(tmp_str, "no_threads = TRUE;");
      TDRP_add_override(&override, tmp_str);

    } else if (!strcmp(argv[i], "-port")) {
      
      if (i < argc - 1) {
	sprintf(tmp_str, "port = %s;", argv[++i]);
	TDRP_add_override(&override, tmp_str);
      } else {
	iret = -1;
      }

    } else if (!strcmp(argv[i], "-qmax")) {
      
      if (i < argc - 1) {
	sprintf(tmp_str, "qmax = %s;", argv[++i]);
	TDRP_add_override(&override, tmp_str);
      } else {
	iret = -1;
      }

    } else if (!strcmp(argv[i], "-instance")) {
      
      if (i < argc - 1) {
	sprintf(tmp_str, "instance = %s;", argv[++i]);
	TDRP_add_override(&override, tmp_str);
      } else {
	iret = -1;
      }
      
    } else if (!strcmp(argv[i], "-secure")) {
      
      sprintf(tmp_str, "run_secure = TRUE;");
      TDRP_add_override(&override, tmp_str);

    } // if
    
  } // i

  if (iret) {
    _usage(prog_name, cerr);
  }
  return iret;
    
}

void Args::_usage(const char *prog_name, ostream &out)
{
  
  out << "Usage: " << prog_name << " [options as below]\n"
      << "options:\n"
      << "       [ --, -h, -help, -man ] produce this list.\n"
      << "       [ -debug ] print debug messages.\n"
      << "       [ -instance ? ] override instance.\n"
      << "         Default is port number.\n"
      << "       [ -noThreads ] force single-threaded operation.\n"
      << "       [ -port ? ] set port number.\n"
      << "       [ -qmax ? ] set max quiescent period (secs).\n"
      << "       [ -secure ] run in secure mode.\n"
      << "         No puts to absolute paths, i.e. starting with '/'\n"
      << "                 or paths containing '..'\n"
      << "       [ -verbose ] print verbose debug messages.\n"
      << endl;
  
  out << "Note: " << prog_name << " listens on port 5440 by default."
      << endl << endl;

  Params::usage(out);

}






