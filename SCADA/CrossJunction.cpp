// CrossJunction.cpp	- Darragh O'Neill
// definition file for CrossJunction class
#include "CrossJunction.h"

void CrossJunction::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around CrossJunction for mouse arrow selection purposes
	RECT compTempRECT;							// creating RECT object compTempRECT
	compTempRECT.top=scrY-GRID_SIZE;			// setting top field of compTempRECT struct
	compTempRECT.left=scrX;						// setting left field of compTempRECT struct
	compTempRECT.right=scrX+(3*GRID_SIZE);		// setting right field of compTempRECT 
	compTempRECT.bottom=scrY+(2*GRID_SIZE);		// setting bottom field of compTempRECT struct
	setComponentRECT(compTempRECT);				// passing compTempRECT to setCompRECT member function
	
	// alogorithm for drawing CrossJunction 
	// 1 - drawing first line
	MoveToEx(hdc, scrX, scrY, NULL);
	LineTo(hdc, scrX+GRID_SIZE, scrY);

	// 2 - drawing second line parrallel to first line
	MoveToEx(hdc, scrX, scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+GRID_SIZE, scrY+GRID_SIZE);

	// 3 - drawing third line perpendicular to first
	MoveToEx(hdc, scrX+GRID_SIZE, scrY, NULL);
	LineTo(hdc, scrX+GRID_SIZE, scrY-GRID_SIZE);

	// 4 - drawing forth line inverse perpendicular to second
	MoveToEx(hdc, scrX+GRID_SIZE, scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+GRID_SIZE, scrY+(2*GRID_SIZE));

	// 5 - drawing fifth line in parallel with first line on other side
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY);

	// 6 - drawing sixth line in parallel second line on other side
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY+GRID_SIZE);

	// 7 - drawing seventh line perpendicular to fifth line on other side
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY, NULL);
	LineTo(hdc, scrX+(2*GRID_SIZE), scrY-GRID_SIZE);

	// 8 drawing eight line inverse perpendicular to sixth line on other side 
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+(2*GRID_SIZE), scrY+(2*GRID_SIZE));

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}
		
	
	