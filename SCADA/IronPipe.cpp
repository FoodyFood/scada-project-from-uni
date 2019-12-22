// IronPipe.cpp	- Darragh O'Neill
// definition file for IronPipe class
#include "IronPipe.h"

void IronPipe::draw(HDC hdc, UINT GRID_SIZE)
{
	// calling createPens function to create pens
	createPens(hdc, GRID_SIZE);

	// creating invisible rectangle around IronPipe for mouse arrow selection purposes
	RECT compTempRECT;					// creating RECT object compTempRECT
	compTempRECT.top = scrY;			// setting top field of compTempRECT struct
	compTempRECT.left = scrX;			// setting left field of compTempRECT struct

	// alogorithm for drawing IronPipe
	if(getOrientation() == 0 || getOrientation() == 2)		// if the component is horizontal
	{
		// creating invisible rectangle around IronPipe for mouse arrow selection purposes
		compTempRECT.right=scrX+(getFuture0()*GRID_SIZE);		// setting right field of compTempRECT struct
		compTempRECT.bottom=scrY+GRID_SIZE;			// setting bottom field of compTempRECT struct
		setComponentRECT(compTempRECT);				// passing compTempRECT to setCompRECT member function

		// draw component
		// 1 - drawing first horizontal line
		MoveToEx(hdc, scrX, scrY, NULL);
		LineTo(hdc, scrX+(GRID_SIZE*getFuture0()), scrY);
		
		// 2 - drawing second horizontal parallel line
		MoveToEx(hdc, scrX, scrY+GRID_SIZE, NULL);
		LineTo(hdc, scrX+(GRID_SIZE*getFuture0()), scrY+GRID_SIZE);
	}

	else if(getOrientation() == 1 || getOrientation() == 3)	// if the component is vertical
	{
		// creating invisible rectangle around IronPipe for mouse arrow selection purposes
		compTempRECT.right=scrX+GRID_SIZE;				// setting right field of compTempRECT 
		compTempRECT.bottom=scrY+(getFuture0()*GRID_SIZE);   // setting bottom field of compTempRECT struct
		setComponentRECT(compTempRECT);				// passing compTempRECT to setCompRECT member function

		//draw component
		// 1 - drawing first vertical line 
		MoveToEx(hdc, scrX, scrY, NULL);
		LineTo(hdc, scrX, scrY+(getFuture0()*GRID_SIZE));

		// 2 -drawing second parallel vertical line
		MoveToEx(hdc, scrX+GRID_SIZE, scrY, NULL);
		LineTo(hdc, scrX+GRID_SIZE, scrY+(getFuture0()*GRID_SIZE));
	}

	// calling deletePens function to delete pens and release memory
	deletePens(hdc);
}

void IronPipe::animate(HDC hdc, UINT GRID_SIZE)
{
	// Creating brush of light blue color
	HBRUSH hBrush=CreateSolidBrush(0x00FF6565);	

	// Setting aniamtion length
	int animateLength = 3;

	// Checking if animation is out of bounds
	// and if so setting to zero
	if(getAnimationPosition()>=animateLength 
		|| getAnimationPosition()>getFuture0()
		|| getAnimationPosition()<0)
		setAnimationPosition(0);

	// drawing the animation
	// Creating RECT
	RECT animationRect;
	// Initializing count and setting to zero
	int count=0;

	// Checking if orientation is left or right
	if(getOrientation()==orientation2::left || getOrientation()==orientation2::right)
	{
		while(getAnimationPosition()+count*animateLength<getFuture0())
		{
			// Gettign the componenents bounding rectangle
			getComponentRECT(animationRect);
			// Setting initial animation position
			animationRect.left+=getAnimationPosition()*GRID_SIZE+count*animateLength*GRID_SIZE;
			// Setting bounds for the animation rectangle
			animationRect.right=animationRect.left+GRID_SIZE-1;
			animationRect.bottom=animationRect.top+GRID_SIZE-1;
			animationRect.left+=2;
			animationRect.top+=2;
			// Filling rectangle with a light blue brush
			FillRect(hdc, &animationRect, hBrush);
			// Incrementing count
			count++;
		}
	}
	// otherwise executing this code for pipe in vertical position
	else
	{
		while(getAnimationPosition()+count*animateLength<getFuture0())
		{
			// Gettign the componenents bounding rectangle
			getComponentRECT(animationRect);
			// Setting initial animation position
			animationRect.top+=getAnimationPosition()*GRID_SIZE+count*animateLength*GRID_SIZE;
			// Setting bounds for the animation rectangle
			animationRect.right=animationRect.left+GRID_SIZE-1;
			animationRect.bottom=animationRect.top+GRID_SIZE-1;
			animationRect.left+=2;
			animationRect.top+=2;
			// Filling rectangle with a light blue brush
			FillRect(hdc, &animationRect, hBrush);
			// Incrementing count
			count++;
		}
	}

	setAnimationPosition(getAnimationPosition()+1);
	DeleteObject(hBrush);
}
