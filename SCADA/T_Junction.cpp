// T-Junction.cpp	- Darragh O'Neill
// definition file for T-Junction class
#include "T_Junction.h"

void T_Junction::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around T_Junction for mouse arrow selection purposes
	RECT compTempRECT;							// creating RECT object compTempRECT
	compTempRECT.top=scrY			;			// setting top field of compTempRECT struct
	compTempRECT.left=scrX;						// setting left field of compTempRECT struct
	compTempRECT.right=scrX+(3*GRID_SIZE);		// setting right field of compTempRECT 
	compTempRECT.bottom=scrY+(2*GRID_SIZE);		// setting bottom field of compTempRECT struct
	setComponentRECT(compTempRECT);				// passing compTempRECT to setCompRECT member function
	
	// alogorithm for drawing T_Junction 
	// 1 - drawing first line
	MoveToEx(hdc, scrX, scrY, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY);

	// 2 - drawing second line on left hand side below first line
	MoveToEx(hdc, scrX, scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+GRID_SIZE, scrY+GRID_SIZE);
	
	// 3 - drawing third line on right hand side below second line
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY+GRID_SIZE);
	
	// 4 - drawing forth line perpenduclar to second line
	MoveToEx(hdc, scrX+GRID_SIZE, scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+GRID_SIZE, scrY+(2*GRID_SIZE));

	// 5 - drawing fifth line perpenduclar to third line
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+(2*GRID_SIZE), scrY+(2*GRID_SIZE));

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}
		
	
	