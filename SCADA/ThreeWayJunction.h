// 3WayJunction.h	- Darragh O'Neill
// header file for 3WayJunction class
#include "BaseComponent.h"

#ifndef THREEWAYJUNCTION_H
#define THREEWAYJUNCTION_H
class ThreeWayJunction: public BaseComponent
{
public:
	ThreeWayJunction():BaseComponent(){}
	ThreeWayJunction(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~ThreeWayJunction(){}
	
	void draw(HDC hdc, UINT GRID_SIZE);
};
#endif