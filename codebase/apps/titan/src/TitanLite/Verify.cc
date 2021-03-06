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
/////////////////////////////////////////////////////////////
// Verify.cc
//
// Verify class.
//
// Creates verification grids and writes out MDV files for debugging.
// The fields in the files are (0) location of all storms and (1)
// location of only valid storms, i.e. those which have the required
// properties to be considered a storm.
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// November 1998
//
///////////////////////////////////////////////////////////////

#include "Verify.hh"
#include "InputMdv.hh"
#include "OutputMdv.hh"
#include "GridClump.hh"
#include <toolsa/umisc.h>
using namespace std;

//////////////
// constructor
//

Verify::Verify(const string &prog_name, const Params &params,
	       const InputMdv &input_mdv) :
  Worker(prog_name, params),
  _inputMdv(input_mdv)

{
  
  _nBytesPlaneAlloc = 0;
  _allStormsGrid = NULL;
  _validStormsGrid = NULL;

}

/////////////
// destructor
//

Verify::~Verify()

{

  if (_allStormsGrid) {
    ufree(_allStormsGrid);
  }
  if (_validStormsGrid) {
    ufree(_validStormsGrid);
  }

}

/////////////////
// prepareGrids()

void Verify::prepareGrids()
  
{
  
  int nbytesPlane =
    _inputMdv.grid.nx * _inputMdv.grid.ny * sizeof(ui08);
  
  // adjust grid allocation as necessary
  
  if (nbytesPlane > _nBytesPlaneAlloc) {
    
    _allStormsGrid = (ui08 *) urealloc ((char *) _allStormsGrid,
				   (ui32) nbytesPlane);
    _validStormsGrid = (ui08 *) urealloc ((char *) _validStormsGrid,
				      (ui32) nbytesPlane);
    _nBytesPlaneAlloc = nbytesPlane;

  } //if (nbytesPlane < _nBytesPlaneAlloc)
    
  // zero out grids

  memset(_allStormsGrid, 0, _nBytesPlaneAlloc);
  memset(_validStormsGrid, 0, _nBytesPlaneAlloc);

}

//////////////////////////////////////////////////
// updateAllStormsGrid()
//
// update the all storms grid with the given clump

void Verify::updateAllStormsGrid(const Clump_order &clump)
  
{
  
  ui08 *allGrid = _allStormsGrid;
  ui08 *compGrid = _inputMdv.compDbz;

  for (int intv = 0; intv < clump.size; intv++) {
    
    Interval *intvl = clump.ptr[intv];
    int offset = (intvl->row_in_plane * _inputMdv.grid.nx +
		  intvl->begin);
    memcpy(allGrid + offset, compGrid + offset, intvl->len);
    
  } // intv

}

//////////////////////////////////////////////////
// updateValidStormsGrid()
//
// update the valid storms grid with the given clump

void Verify::updateValidStormsGrid(const GridClump &grid_clump)

{

  ui08 *validGrid = _validStormsGrid;
  ui08 *compGrid = _inputMdv.compDbz;

  for (int intv = 0; intv < grid_clump.nIntervals; intv++) {
    
    const Interval &intvl = grid_clump.intervals[intv];

    int iy = intvl.row_in_plane + grid_clump.startIy;
    int ix = intvl.begin + grid_clump.startIx;
    int offset = iy * grid_clump.grid.nx + ix;
    memcpy(validGrid + offset, compGrid + offset, intvl.len);
    
  } // intv

}

////////////////////
// writeOutputMdv()
//

int Verify::writeOutputMdv()
  
{

  // set info str

  char info[256];
  sprintf(info, "\nVerification data, dbz threshold %g", 
	  _params.low_dbz_threshold);

  // create output MDV object
  
  OutputMdv out(_progName, _params,
		_inputMdv, info,
		"TITAN verify",
		_params.verify_url);

  // Add the fields

  out.addField("All storms verification",
	       "AllStorms", "dBZ", "dBZ",
	       _inputMdv.dbzScale,
	       _inputMdv.dbzBias,
	       _allStormsGrid);
  
  out.addField("Valid storms verification",
	       "ValidStorms", "dBZ", "dBZ",
	       _inputMdv.dbzScale,
	       _inputMdv.dbzBias,
	       _validStormsGrid);
  
  // write out

  if (out.writeVol()) {
    cerr << "ERROR - Verify::writeOutputMdv" << endl;
    return -1;
  }

  return 0;

}


