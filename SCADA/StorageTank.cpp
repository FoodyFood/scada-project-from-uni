// StorageTank.cpp	- Darragh O'Neill
// definition file for StorageTank class
#include "StorageTank.h"

void StorageTank::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around StorageTank for mouse arrow selection purposes
	RECT compTempRECT;								// creating RECT object compTempRECT
	compTempRECT.top = scrY-(4*GRID_SIZE);			// setting top field of compTempRECT struct
	compTempRECT.left = scrX;						// setting left field of compTempRECT struct
	compTempRECT.right = scrX+(20*GRID_SIZE);		// setting right field of compTempRECT 
	compTempRECT.bottom = scrY+(8*GRID_SIZE);						// setting bottom field of compTempRECT struct
	setComponentRECT(compTempRECT);					// passing compTempRECT to setCompRECT member function

	// alogorithm for drawing StorageTank
	RoundRect(hdc, scrX, scrY, scrX+(20*GRID_SIZE), scrY+(8*GRID_SIZE), GRID_SIZE, GRID_SIZE);

	MoveToEx(hdc, scrX+(5*GRID_SIZE), scrY, NULL);
	LineTo(hdc, scrX+(5*GRID_SIZE), scrY-(4*GRID_SIZE));
	MoveToEx(hdc, scrX+(6*GRID_SIZE), scrY, NULL);
	LineTo(hdc, scrX+(6*GRID_SIZE), scrY-(4*GRID_SIZE));

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}
