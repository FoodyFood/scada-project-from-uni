//This section written by D O'Connor

// BaseComponent.cpp
// definition file for BaseComponent class
#include "BaseComponent.h"

BaseComponent::BaseComponent(int ID, int iX, int iY, int iorientation, int ifuture0, int ifuture1, int ifuture2)
{
	id=ID;
	x=iX;
	y=iY;
	orientation=iorientation;
	future0=ifuture0;
	future1=ifuture1;
	future2=ifuture2;
	selected=true;
}

// mutators/setters
void BaseComponent::setX(const int iX)
{
	x = iX;
}

void BaseComponent::setY(int iY)
{
	y = iY;
}

void BaseComponent::setOrientation(const int iorientation)
{
	orientation = iorientation;
}

void BaseComponent::setFuture0(const int ifuture0)
{
	future0 = ifuture0;
}

void BaseComponent::setFuture1(const int ifuture1)
{
	future1 = ifuture1;
}

void BaseComponent::setFuture2(const int ifuture2)
{
	future2 = ifuture2;
}

void BaseComponent::setComponentRECT(RECT iCompRECT)
{
	componentRegion = iCompRECT;
}

void BaseComponent::setSelected(BOOL selectComponent)
{
	selected = selectComponent;
}

void BaseComponent::setAnimationPosition(int aPos)
{
	animationPosition=aPos;
};

// accessors/getters
const int BaseComponent::getId(void) const
{
	return id;
}

const int BaseComponent::getX(void) const
{
	return x;
}

const int BaseComponent::getY(void) const
{
	return y;
}

const int BaseComponent::getOrientation(void) const
{
	return orientation;
}

const int BaseComponent::getFuture0(void) const
{
	return future0;
}

const int BaseComponent::getFuture1(void) const
{
	return future1;
}

const int BaseComponent::getFuture2(void) const
{
	return future2;
}

void BaseComponent::getComponentRECT(RECT &retRect)
{
	retRect = componentRegion; 
}

int BaseComponent::isComponentActive(void)
{
	return selected;
}

int BaseComponent::getAnimationPosition(void)
{
	return animationPosition;
}

// virtual member functions
void BaseComponent::draw(HDC hdc, UINT GRID_SIZE)
{

}

void BaseComponent::animate(HDC hdc,UINT GRID_SIZE)
{

}


void BaseComponent::createPens(HDC hdc, UINT GRID_SIZE)
{

	// defining onscreen coordinates
	scrX = (getX()+1)*GRID_SIZE-1;
	scrY = (getY()+1)*GRID_SIZE-1+HeightOfToolbar;
	
	// method for assiging the colour red to represent the component being active
	if(isComponentActive())
	{
		original = SelectObject(hdc,GetStockObject(DC_PEN));
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		SelectObject(hdc, hPen);
	}
}


void BaseComponent::deletePens(HDC hdc)
{
	// restore black colour if it was changed to red and deletes pens
	if(isComponentActive())
	{
		SelectObject(hdc,original);
		DeleteObject(hPen);
		DeleteObject(original);
	}
}
	
	
	
	
	
	
	
	
	
	
	
	

