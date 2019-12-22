//This section written by D O'Connor

// SuspendedConcreteGroundFloor.cpp
// definition file for SuspendedConcreteGroundFloor class
#include "SuspendedConcreteGroundFloor.h"

void SuspendedConcreteGroundFloor::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around SuspendedConcreteGroundFloor for mouse arrow selection purposes
	RECT compTempRECT;							// creating RECT object compTempRECT
	compTempRECT.left=scrX;						// setting left field of compTempRECT struct
	compTempRECT.top=scrY;						// setting top field of compTempRECT struct	
	compTempRECT.right=scrX+(150*GRID_SIZE);		// setting right field of compTempRECT struct
	compTempRECT.bottom=scrY+(3*GRID_SIZE);		// setting bottom field of compTempRECT 
	setComponentRECT(compTempRECT);				// passing compTempRECT to setComponentRECT member function
	
	// alogorithm for drawing SuspendedConcreteGroundFloor 
	// 1 - drawing top line
	MoveToEx(hdc, scrX, scrY, NULL);
	LineTo(hdc,  scrX+(106*GRID_SIZE)-1, scrY);

	// 2 - drawing bottom line
	MoveToEx(hdc, scrX, scrY+(3*GRID_SIZE), NULL);
	LineTo(hdc, scrX+(106*GRID_SIZE)-1, scrY+(3*GRID_SIZE));

	// 3 - drawing left vertical line
	MoveToEx(hdc, scrX, scrY, NULL);
	LineTo(hdc, scrX, scrY+(3*GRID_SIZE));

	// 4 - drawing right vertical line
	MoveToEx(hdc, scrX+(106*GRID_SIZE)-1, scrY, NULL);
	LineTo(hdc, scrX+(106*GRID_SIZE)-1, scrY+(3*GRID_SIZE));

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}
