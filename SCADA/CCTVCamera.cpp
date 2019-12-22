// CCTVCamera.cpp	- Darragh O'Neill
// definition file for CCTVCamera class
#include "CCTVCamera.h"

void CCTVCamera::draw(HDC hdc, UINT GRID_SIZE)
{
	
	// calling createPens function to create pens
	BaseComponent::createPens(hdc, GRID_SIZE);
	
	// creating invisible rectangle around CCTVCamera for mouse arrow selection purposes
	RECT compTempRECT;							// creating RECT object compTempRECT
	compTempRECT.top = scrY;					// setting top field of compTempRECT struct
	compTempRECT.left = scrX; 					// setting left field of compTempRECT struct
	compTempRECT.right = scrX+(3*GRID_SIZE); 	// setting right field of compTempRECT 
	compTempRECT.bottom = scrY+(2*GRID_SIZE);	// setting bottom field of compTempRECT struct
	setComponentRECT(compTempRECT);				// passing compTempRECT to setCompRECT member function
	
	// alogorithm for drawing CCTVCamera 
	// 1 - drawing top line of camera
	MoveToEx(hdc, scrX, scrY, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY);

	// 2 - drawing bottom line of camera
	MoveToEx(hdc, scrX, scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY+GRID_SIZE);

	// 3 - drawing left vertical line of camera
	MoveToEx(hdc, scrX, scrY, NULL);
	LineTo(hdc, scrX, scrY+GRID_SIZE);

	// 4 - drawing right vertical line of camera
	MoveToEx(hdc, scrX+(3*GRID_SIZE), scrY, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE), scrY+GRID_SIZE);

	// 5 - drawing face for camera
	MoveToEx(hdc, scrX+(3*GRID_SIZE/6), scrY, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE/6), scrY+GRID_SIZE);

	// 6 drawing stand for camera
	MoveToEx(hdc, scrX+(3*GRID_SIZE/2), scrY+GRID_SIZE, NULL);
	LineTo(hdc, scrX+(3*GRID_SIZE/2), scrY+(2*GRID_SIZE));


	
	// calling deletePens function to delete pens and release memory
	BaseComponent::deletePens(hdc);
}
