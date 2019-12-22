// 2WayJunction.cpp	- Darragh O'Neill
// definition file for 2WayJunction class
#include "TwoWayJunction.h"

void TwoWayJunction::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around TwoWayJunction for mouse arrow selection purposes
	RECT compTempRECT;								// creating RECT object compTempRECT
	compTempRECT.top = scrY-GRID_SIZE;				// setting top field of compTempRECT struct
	compTempRECT.left = scrX;						// setting left field of compTempRECT struct
	compTempRECT.right = scrX+(3*GRID_SIZE);		// setting right field of compTempRECT 
	compTempRECT.bottom = scrY+(2*GRID_SIZE);		// setting bottom field of compTempRECT struct
	setComponentRECT(compTempRECT);					// passing compTempRECT to setCompRECT member function
	
	// alogorithm for drawing TwoWayJunction 
	// 1 - drawing first line 
	MoveToEx(hdc, scrX, scrY, NULL);
	LineTo(hdc, scrX+GRID_SIZE, scrY);

	// 2 - drawing second line parallel
	MoveToEx(hdc, scrX, scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+GRID_SIZE, scrY+GRID_SIZE);

	// 3 - drawing third line opposite
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY);

	// 4 - drawing forth line perpendicular to third
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY, NULL);
	LineTo(hdc, scrX+(2*GRID_SIZE), scrY+GRID_SIZE);

	// 5 - drawing fifth line parallel to third
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY+(GRID_SIZE), NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY+(GRID_SIZE));

	// 6 - drawing sixth line above third line parallel to it
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY-GRID_SIZE, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY-GRID_SIZE);

	// 7 - drawing seventh line below forth line parallel to it
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY+(2*GRID_SIZE), NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY+(2*GRID_SIZE));

	// 8 - drawing arc on top portion of 2-way split
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY-GRID_SIZE, NULL);
	AngleArc(hdc, scrX+(2*GRID_SIZE), scrY, GRID_SIZE, 90, 90);

	// 9 - drawing arc on bottom portion of 2-way split
	MoveToEx(hdc, scrX+GRID_SIZE, scrY+GRID_SIZE, NULL);
	AngleArc(hdc, scrX+(2*GRID_SIZE), scrY+GRID_SIZE, GRID_SIZE, 180, 90);

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}