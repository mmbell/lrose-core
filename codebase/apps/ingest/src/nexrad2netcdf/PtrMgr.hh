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
///////////////////////////////////////////////////////
// PtrMgr - class that handles the memory managment
//          associated with data that is to be written
//          out to the netcdf files
//
// Jaimi Yee, RAP, NCAR, P.O.Box 3000, Boulder, CO, 
//   80307-3000, USA
//
// $Id: PtrMgr.hh,v 1.3 2016/03/07 01:23:10 dixon Exp $
//
////////////////////////////////////////////////////////
#ifndef _PTR_MGR_INC_
#define _PTR_MGR_INC_

#include "SweepData.hh"

class PtrMgr 
{
public:

   PtrMgr();
   ~PtrMgr();
   
   void setDataPtrs( int maxCells, int numCells, int numRays, 
                     SweepData* currentSweep );
   
   short* getDz(){ return dz; }
   short* getVe(){ return ve; }
   short* getSw(){ return sw; }
   short* getSnr(){ return snr; }
   short* getPr(){ return pr; }
   
private:

   bool dataCopied;

   short *dz;
   short *ve;
   short *sw;
   short *snr;
   short *pr;
};

#endif
   