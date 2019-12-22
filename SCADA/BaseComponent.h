// BaseComponent.h		- Darragh O'Neill
// header file for BaseComponent class

#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

// global scope declarations
#include "Constants.h"
#include "stdafx.h"
#include "windows.h"
enum orientation2 { left, top, right, bottom };

class BaseComponent
{
public:
	// default constructor, overloaded constructor, destructor
	BaseComponent(){id=0;x=0;y=0;orientation=0;future0=0;future1=0;future2=0;selected=true;}
	BaseComponent(int ID, int iX, int iY, int iorientation, int ifuture0, int ifuture1, int ifuture2);
	~BaseComponent(){}

	// mutators/setters
	void setX(const int iX);
	void setY(const int iY);
	void setOrientation(const int iorientation);
	void setFuture0(const int ifuture0);
	void setFuture1(const int ifuture1);
	void setFuture2(const int ifuture2);
	void setComponentRECT(RECT iCompRECT);
	void setSelected(BOOL selectComponent);
	void setAnimationPosition(const int aPos);
	

	// accessors/getters
	const int getId(void) const;
	const int getX(void) const;
	const int getY(void) const;
	const int getOrientation(void) const;
	const int getFuture0(void) const;
	const int getFuture1(void) const;
	const int getFuture2(void) const;
	void getComponentRECT(RECT &retRect);
	BOOL isComponentActive(void);
	int getAnimationPosition(void);

	// virutal draw function
	virtual void draw(HDC hdc, UINT GRID_SIZE)=0;
	// virtual animate function
	virtual void animate(HDC hdc, UINT GRID_SIZE);
	

protected:
	// create pens function
	void createPens(HDC hdc, UINT GRID_SIZE);
	// delete pens function
	void deletePens(HDC hdc);

	// variable declarations [if number of variables changes, edit constants.h]
	int id;					// component identity
	int x;					// relative x-coordinate
	int y;					// relative y-coordinate
	int orientation;		// orientation [4 possible values 0,1,2,3 i.e. left,right,top,bottom]
	int future0;			// future use
	int future1;			// future use 
	int future2;			// future use 
	RECT componentRegion;	// to be set each time component is drawn
	BOOL selected;			// if component is selected, bool is true
	int  animationPosition;	// position of animation
	HPEN hPen;				// pen	
	HGDIOBJ original;		// handle to a graphics device interface object
	int scrX;				// absolute horizontal screen coordinate 
	int scrY;				// absolute vertical screen coordiante
};
#endif