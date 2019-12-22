// CornerPipe.h	- Darragh O'Neill
// header file for CornerPipe class
#include "BaseComponent.h"

#ifndef CORNERPIPE_H
#define CORNERPIPE_H
class CornerPipe: public BaseComponent
{
public:
	CornerPipe():BaseComponent(){}
	CornerPipe(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~CornerPipe(){}

	void draw(HDC hdc, UINT GRID_SIZE);
	void animate(HDC hdc, UINT GRID_SIZE);
};
#endif 