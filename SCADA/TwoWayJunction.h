// 2WayJunction.h	- Darragh O'Neill
// header file for 2WayJunction class
#include "BaseComponent.h"

#ifndef TWOWAYJUNCTION_H
#define TWOWAYJUNCTION_H
class TwoWayJunction: public BaseComponent
{
public:
	TwoWayJunction():BaseComponent(){}
	TwoWayJunction(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~TwoWayJunction(){}

	void draw(HDC hdc, UINT GRID_SIZE);
};
#endif 