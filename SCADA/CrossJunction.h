// CrossJunction.h	- Darragh O'Neill
// header file for CrossJunction class
#include "BaseComponent.h"

#ifndef CROSSJUNCTION_H
#define CROSSJUNCTION_H
class CrossJunction: public BaseComponent
{
public:
	CrossJunction():BaseComponent(){}
	CrossJunction(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~CrossJunction(){}

	void draw(HDC hdc, UINT GRID_SIZE);
};
#endif 

	