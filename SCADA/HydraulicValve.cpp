// HydraulicValve.cpp	- Darragh O'Neill
// definition file for HydraulicValve class
#include "HydraulicValve.h"

void HydraulicValve::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around HydraulicValve for mouse arrow selection purposes
	RECT compTempRECT;							// creating RECT object compTempRECT
	compTempRECT.top=scrY-(3*GRID_SIZE);						// setting top field of compTempRECT struct
	compTempRECT.left=scrX;						// setting left field of compTempRECT struct
	compTempRECT.right=scrX+(6*GRID_SIZE); 		// setting right field of compTempRECT 
	compTempRECT.bottom=scrY+1*GRID_SIZE;		// setting bottom field of compTempRECT struct
	setComponentRECT(compTempRECT);				// passing compTempRECT to setCompRECT member function

	// alogorithm for drawing HydraulicValve
	MoveToEx(hdc, scrX, scrY, NULL);								// move to (0,0)
	LineTo(hdc, scrX+GRID_SIZE*6, scrY);							// line to (6,0)
	MoveToEx(hdc, scrX, scrY+GRID_SIZE, NULL);						// move to (0,1)
	LineTo(hdc, scrX+GRID_SIZE*6, scrY+GRID_SIZE);					// line to (6,1)
	MoveToEx(hdc, scrX+GRID_SIZE*3, (int) scrY+GRID_SIZE*0.5, NULL);		// move to (3,0.5)
	LineTo(hdc, scrX+GRID_SIZE*3, scrY-2*GRID_SIZE);				// line to (3,-2)
	MoveToEx(hdc, scrX+GRID_SIZE*3, scrY-2*GRID_SIZE, NULL);		// move to (3,-2)
	LineTo(hdc, scrX+GRID_SIZE*6, scrY-2*GRID_SIZE);				// line to (6,-2)
	MoveToEx(hdc, scrX+GRID_SIZE*3, scrY-3*GRID_SIZE, NULL);		// move to (3,-3)
	LineTo(hdc, scrX+GRID_SIZE*6, scrY-3*GRID_SIZE);				// line to (6,-3)
	MoveToEx(hdc, scrX+GRID_SIZE*3, scrY-3*GRID_SIZE, NULL);		// move to (3,-3)
	LineTo(hdc, scrX+GRID_SIZE*3, scrY-2*GRID_SIZE);				// line to (6,-2)
	MoveToEx(hdc, scrX+GRID_SIZE*6, scrY-3*GRID_SIZE, NULL);		// move to (6,-3)
	LineTo(hdc, scrX+GRID_SIZE*6, scrY-2*GRID_SIZE);				// line to (6,-2)

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}

/*
void HydraulicValve::animate(HDC hdc)
{
	HPEN hPen;
	HGDIOBJ original;

	original = SelectObject(hdc,GetStockObject(DC_PEN));
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	SelectObject(hdc, hPen);

	//draw the animation

	SelectObject(hdc,original);
	DeleteObject(hPen);
}
*/

