// PneumaticPump.cpp	- Darragh O'Neill
// definition file for PneumaticPump class
#include "PneumaticPump.h"

void PneumaticPump::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around PneumaticPump for mouse arrow selection purposes
	RECT compTempRECT;							// creating RECT object compTempRECT
	compTempRECT.top=scrY-(3*GRID_SIZE);		// setting top field of compTempRECT struct
	compTempRECT.left=scrX;						// setting left field of compTempRECT struct
	compTempRECT.right=scrX+(3*GRID_SIZE);		// setting right field of compTempRECT 
	compTempRECT.bottom=scrY+GRID_SIZE;			// setting bottom field of compTempRECT struct
	setComponentRECT(compTempRECT);				// passing compTempRECT to setCompRECT member function
	
	// alogorithm for drawing PneumaticPump 
	// 1 - drawing first line
	MoveToEx(hdc, scrX, scrY, NULL);
	LineTo(hdc, scrX+GRID_SIZE, scrY);

	// 2 - drawing second line opposite first
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY);

	// 3 - drawing base line of pump
	MoveToEx(hdc, scrX, scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY+GRID_SIZE);

	// 4 - drawing line perpendicular to first line
	MoveToEx(hdc, scrX+GRID_SIZE, scrY, NULL);
	LineTo(hdc, scrX+GRID_SIZE, scrY-(2*GRID_SIZE));

	// 5 - drawing line perpendicular to second line
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY, NULL);
	LineTo(hdc, scrX+(2*GRID_SIZE), scrY-(2*GRID_SIZE));

	// 6 - drawing line parallel to base on the left top part of pump
	MoveToEx(hdc, scrX/*+GRID_SIZE*/, scrY-(2*GRID_SIZE), NULL);
	LineTo(hdc, scrX+GRID_SIZE, scrY-(2*GRID_SIZE));

	// 7 - drawing line parallel to base on the right top part of pump
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY-(2*GRID_SIZE), NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY-(2*GRID_SIZE));

	// 8 - drawing line perpendicular to line created in step 6
	MoveToEx(hdc, scrX, scrY-(2*GRID_SIZE), NULL);
	LineTo(hdc, scrX, scrY-(3*GRID_SIZE));

	// 9 - drawing line perpendicular to line created in step 7
	MoveToEx(hdc, scrX+(3*GRID_SIZE), scrY-(2*GRID_SIZE), NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY-(3*GRID_SIZE));

	// 10 - drawing top line of pump
	MoveToEx(hdc, scrX, scrY-(3*GRID_SIZE), NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY-(3*GRID_SIZE));

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}
		
	
	