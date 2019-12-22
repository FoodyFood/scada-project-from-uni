// CornerPipe.cpp	- Darragh O'Neill
// definition file for CornerPipe class
#include "CornerPipe.h"

void CornerPipe::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around CornerPipe for mouse arrow selection purposes
	RECT compTempRECT;							// creating RECT object compTempRECT
	compTempRECT.top = scrY;					// setting top field of compTempRECT struct
	compTempRECT.left = scrX;					// setting left field of compTempRECT struct
	compTempRECT.right = scrX+2*GRID_SIZE;		// setting right field of compTempRECT 
	compTempRECT.bottom = scrY+2*GRID_SIZE;		// setting bottom field of compTempRECT struct
	setComponentRECT(compTempRECT);				// passing compTempRECT to setCompRECT member function

	// alogorithm for drawing CornerPipe
	orientation2 orient = (orientation2)getOrientation();
	switch (orientation2(getOrientation()))
	{
	case orientation2::left:
		MoveToEx(hdc, scrX+GRID_SIZE*2, scrY+GRID_SIZE*2, NULL);
		AngleArc(hdc, scrX, scrY+GRID_SIZE*2, GRID_SIZE*2, 0, 90);
		MoveToEx(hdc, scrX+GRID_SIZE, scrY+GRID_SIZE*2, NULL);
		AngleArc(hdc, scrX, scrY+GRID_SIZE*2, GRID_SIZE, 0, 90);
		break;
	case orientation2::top:
		MoveToEx(hdc, scrX, scrY+GRID_SIZE*2, NULL);
		AngleArc(hdc, scrX, scrY, GRID_SIZE*2, 270, 90);
		MoveToEx(hdc, scrX, scrY+GRID_SIZE, NULL);
		AngleArc(hdc, scrX, scrY, GRID_SIZE, 270, 90);
		break;
	case orientation2::right:
		MoveToEx(hdc, scrX, scrY, NULL);
		AngleArc(hdc, scrX+GRID_SIZE*2, scrY, GRID_SIZE*2, 180, 90);
		MoveToEx(hdc, scrX+GRID_SIZE, scrY, NULL);
		AngleArc(hdc, scrX+GRID_SIZE*2, scrY, GRID_SIZE, 180, 90);
		break;
	case orientation2::bottom:
		MoveToEx(hdc, scrX+GRID_SIZE*2, scrY, NULL);
		AngleArc(hdc, scrX+GRID_SIZE*2, scrY+GRID_SIZE*2, GRID_SIZE*2, 90, 90);
		MoveToEx(hdc, scrX+GRID_SIZE*2, scrY+GRID_SIZE, NULL);
		AngleArc(hdc, scrX+GRID_SIZE*2, scrY+GRID_SIZE*2, GRID_SIZE, 90, 90);
		break;
	default:	//A message box to warn of an error //only during debug
		break;
	}

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}

void CornerPipe::animate(HDC hdc, UINT GRID_SIZE)
{
	// Creating brush of light blue color

	original = SelectObject(hdc,GetStockObject(DC_BRUSH));
	HBRUSH hBrush=CreateSolidBrush(0x00FF6565);	
	SelectObject(hdc, hBrush);

	original = SelectObject(hdc,GetStockObject(DC_PEN));
	hPen = CreatePen(PS_SOLID, 1, RGB(101, 101, 255));
	SelectObject(hdc, hPen);

	RECT comp;
	getComponentRECT(comp);

	if(getAnimationPosition()>2 ||getAnimationPosition() < 0)
		setAnimationPosition(0);

	int size = GRID_SIZE/1.5;
	if(!size) size = 1;

	// drawing the animation
	if(getAnimationPosition()==1)
		Ellipse(hdc, comp.left+size+1, comp.top+size+1, comp.right-size, comp.bottom-size);

	setAnimationPosition(getAnimationPosition()+1);

	SelectObject(hdc,original);
	DeleteObject(hBrush);
	DeleteObject(original);

	SelectObject(hdc,original);
	DeleteObject(hPen);
	DeleteObject(original);
}