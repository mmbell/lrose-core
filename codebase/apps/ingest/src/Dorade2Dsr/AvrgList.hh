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
/* 	$Id: AvrgList.hh,v 1.3 2016/03/07 01:23:00 dixon Exp $	 */

# ifndef AVRGLIST_HH
# define AVRGLIST_HH

#include "WhichFloat.hh"
using namespace std;

// c---------------------------------------------------------------------------

class AvrgList {

    // keeps a running average/sum that is always updated so that
    // either the current average or just the sum can be returned

private:
    int counter;
    int ndxNext;
    int sizeofList;
    int downCounter;
    Xfloat rcpSize;
    Xfloat sum;
    Xfloat * values;

    inline void incNdxNext()
    {
	if(++ndxNext >= sizeofList) { ndxNext -= sizeofList; }
    }

    inline Xfloat rcpDenomenater()
    {
	if(counter >= sizeofList)
	    { return rcpSize; }
	else if(!counter)
	    { return 1.; }

	return 1./(Xfloat)counter;
    }

public:
    AvrgList(int size)
    {
	sizeofList = size > 1 ? size : 2;
	rcpSize = 1./(Xfloat)sizeofList;
	values = new Xfloat [sizeofList];
	this->reset();
    }
    ~AvrgList() { delete values; }

    inline int returnSize() { return sizeofList; }
    inline Xfloat returnSum() { return sum; }
    inline Xfloat returnAvrg() { return sum * rcpDenomenater(); }

    inline Xfloat replaceNext(Xfloat value)
    {
	counter++;
	sum -= *(values + ndxNext);
	*(values + ndxNext) = value;
	sum += value;
	incNdxNext();
	return sum * rcpDenomenater();
    }

    inline Xfloat updateSum(Xfloat value)
    {
	counter++;
	sum -= *(values + ndxNext);
	*(values + ndxNext) = value;
	sum += value;
	incNdxNext();
	return sum;
    }

    inline Xfloat taperDownAvrg()
    {
	if(downCounter <= 1) { return 0; }
	downCounter--;
	sum -= *(values + ndxNext);
	*(values + ndxNext) = 0;
	incNdxNext();

	return sum/(Xfloat)downCounter;
    }

    void reset()
    {
	counter = ndxNext = 0;    sum = 0;
	downCounter = sizeofList;
	for(int ii = 0; ii < sizeofList; *(values + ii++) = 0);
    }
};

// c---------------------------------------------------------------------------

class SplitSums {

    // keeps two running sums that are always updated
    // one for the first half of the list and one for the remainder

private:
    int counter;
    int ndxNext;
    int offsetSum2;
    int sizeofList;
    Xfloat sum;
    Xfloat sum2;
    Xfloat * values;

    inline void incNdxNext()
    {
	if(++ndxNext >= sizeofList) { ndxNext -= sizeofList; }
    }

    inline int ndxSum2()
    {
	int ndx = ndxNext + offsetSum2;
	if(ndx >= sizeofList) { ndx -= sizeofList; }
	return ndx;
    }


public:
    SplitSums(int size)
    {
	sizeofList = size > 1 ? size : 2;
	values = new Xfloat [sizeofList];
	offsetSum2 = sizeofList/2;
	this->reset();
    }
    ~SplitSums() { delete values; }

    inline int returnSize() { return sizeofList; }
    inline int returnCounter() { return counter; }
    inline Xfloat returnSum() { return sum; }
    inline Xfloat returnSum2() { return sum2; }

    inline Xfloat updateSums(Xfloat value)
    {
	counter++;
	sum -= *(values + ndxNext); // remove oldest value
	int ndx = ndxSum2();
	sum += *(values + ndx);	// shift value across the boundary
	sum2 -= *(values + ndx);
	*(values + ndxNext) = value; // add newest value
	sum2 += value;
	incNdxNext();
	return sum;		// returns the first of the two split sums
    }


    void reset()
    {
	counter = ndxNext = 0;
	sum = sum2 = 0;
	for(int ii = 0; ii < sizeofList; *(values + ii++) = 0);
    }
};

# endif //  AVRGLIST_HH


