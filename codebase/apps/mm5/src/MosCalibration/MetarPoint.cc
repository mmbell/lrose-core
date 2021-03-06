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
////////////////////////////////////////////////////////////////////
//
// MetarPoint - class that contains the metar data for a given point
//
// $Id: MetarPoint.cc,v 1.10 2016/03/07 01:33:50 dixon Exp $
//
////////////////////////////////////////////////////////////////////
#include <values.h>
#include <toolsa/DateTime.hh>
#include "MetarPoint.hh"
#include "MosCalibration.hh"
using namespace std;

//
// Constants
//
const double MetarPoint::MISSING_VAL = MAXDOUBLE;

MetarPoint::MetarPoint( time_t ptime, double lat, double lon ) 
{
   pointTime   = ptime;
   latitude    = lat;
   longitude   = lon;
   
   u           = MISSING_VAL;
   v           = MISSING_VAL;
   wspd        = MISSING_VAL;
   temperature = MISSING_VAL;
   pressure    = MISSING_VAL;
   relativeHum = MISSING_VAL;
   ceiling     = MISSING_VAL;
   visibility  = MISSING_VAL;
}

///////////////
// print object

void MetarPoint::print(ostream &out, string spacer /* = ""*/ ) const

{
  
  cerr << spacer << "pointTime: " << DateTime::strm(pointTime) << endl;
  cerr << spacer << "latitude: " << latitude << endl;
  cerr << spacer << "longitude: " << longitude << endl;
  cerr << spacer << "u: " << u << endl;
  cerr << spacer << "v: " << v << endl;
  cerr << spacer << "wspd: " << wspd << endl;
  cerr << spacer << "temperature: " << temperature << endl;
  cerr << spacer << "pressure: " << pressure << endl;
  cerr << spacer << "relativeHum: " << relativeHum << endl;
  cerr << spacer << "ceiling: " << ceiling << endl;
  cerr << spacer << "visibility: " << visibility << endl;
   
}

