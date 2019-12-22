// ThreeWayJunction.cpp	- Darragh O'Neill
// definition file for ThreeWayJunction class
#include "ThreeWayJunction.h"

void ThreeWayJunction::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around ThreeWayJunction for mouse arrow selection purposes
	RECT compTempRECT;							// creating RECT object compTempRECT
	compTempRECT.left=scrX;						// setting left field of compTempRECT struct
	compTempRECT.top=scrY-(2*GRID_SIZE);		// setting top field of compTempRECT struct	
	compTempRECT.right=scrX+(3*GRID_SIZE);		// setting right field of compTempRECT struct
	compTempRECT.bottom=scrY+(3*GRID_SIZE);		// setting bottom field of compTempRECT 
	setComponentRECT(compTempRECT);				// passing compTempRECT to setComponentRECT member function
	
	// alogorithm for drawing ThreeWayJunction 
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

	// 8 - drawing eight line inverse perpendicular to sixth line on other side 
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+(2*GRID_SIZE), scrY+(2*GRID_SIZE));

	// 9 - drawing ninth line parallel to fifth line 
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY-GRID_SIZE, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY-GRID_SIZE);

	// 10 - drawing tenth line parallel to sixth line
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY+(2*GRID_SIZE), NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY+(2*GRID_SIZE));

	// 11 - drawing eleventh line parallel to ninth line
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY-(2*GRID_SIZE), NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY-(2*GRID_SIZE));

	// 12 - drawing twelveth line parallel to tenth line
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY+(3*GRID_SIZE), NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY+(3*GRID_SIZE));

	// 13 - drawing arc on upper portion of 3-Way Split
	MoveToEx(hdc, scrX+(2*GRID_SIZE), scrY-(2*GRID_SIZE), NULL);
	AngleArc(hdc, scrX+(2*GRID_SIZE), scrY-GRID_SIZE, GRID_SIZE, 90, 90);

	// 14 -drawing arc on lower portion of 3-Way split
	MoveToEx(hdc, scrX+GRID_SIZE, scrY+(2*GRID_SIZE), NULL);
	AngleArc(hdc, scrX+(2*GRID_SIZE), scrY+(2*GRID_SIZE), GRID_SIZE, 180, 90);

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}
