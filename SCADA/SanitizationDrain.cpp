// SanitizationDrain.cpp	- Darragh O'Neill
// definition file for SanitizationDrain class
#include "SanitizationDrain.h"

void SanitizationDrain::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around SanitizationDrain for mouse arrow selection purposes
	RECT compTempRECT;								// creating RECT object compTempRECT
	compTempRECT.top= scrY-(5*GRID_SIZE);			// setting top field of compTempRECT struct
	compTempRECT.left = scrX;						// setting left field of compTempRECT struct
	compTempRECT.right = scrX+(9*GRID_SIZE);		// setting right field of compTempRECT 
	compTempRECT.bottom = scrY;						// setting bottom field of compTempRECT struct
	setComponentRECT(compTempRECT);		

	// alogorithm for drawing SanitizationDrain
	// 1 - drawing base line
	MoveToEx(hdc, scrX, scrY, NULL);
	LineTo(hdc, scrX+(GRID_SIZE*8), scrY);

	// 2 - drawing left vertical line
	MoveToEx(hdc, scrX, scrY, NULL);
	LineTo(hdc, scrX, scrY-(4*GRID_SIZE));

	// 3 - drawing right vertical line
	MoveToEx(hdc, scrX+(8*GRID_SIZE), scrY, NULL);
	LineTo(hdc, scrX+(8*GRID_SIZE), scrY-(4*GRID_SIZE));

	// 4 - drawing left edge
	MoveToEx(hdc, scrX, scrY-(4*GRID_SIZE), NULL);
	LineTo(hdc, scrX-GRID_SIZE, scrY-(5*GRID_SIZE));

	// 5 - drawing right edge
	MoveToEx(hdc, scrX+(8*GRID_SIZE), scrY-(4*GRID_SIZE), NULL);
	LineTo(hdc, scrX+(9*GRID_SIZE), scrY-(5*GRID_SIZE));

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}