// WaterSource.cpp	- Darragh O'Neill
// definition file for WaterSource class
#include "WaterSource.h"

void WaterSource::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around WaterSource for mouse arrow selection purposes
	RECT compTempRECT;							// creating RECT object compTempRECT
	compTempRECT.top=scrY;						// setting top field of compTempRECT struct
	compTempRECT.left=scrX;						// setting left field of compTempRECT struct
	compTempRECT.right=scrX+(20*GRID_SIZE);		// setting right field of compTempRECT 
	compTempRECT.bottom=scrY+(8*GRID_SIZE);		// setting bottom field of compTempRECT struct
	setComponentRECT(compTempRECT);				// passing compTempRECT to setCompRECT member function

	// alogorithm for drawing WaterSource
	RoundRect(hdc, scrX, scrY, scrX+(20*GRID_SIZE), scrY+(8*GRID_SIZE), GRID_SIZE, GRID_SIZE);

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}

