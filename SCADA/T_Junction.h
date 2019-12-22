// T-Junction.h	- Darragh O'Neill
// header file for T-Junction class
#include "BaseComponent.h"

#ifndef T_JUNCTION_H
#define	T_JUNCTION_H
class T_Junction: public BaseComponent
{
public:
	T_Junction():BaseComponent(){}
	T_Junction(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~T_Junction(){}

	void draw(HDC hdc, UINT GRID_SIZE);
};
#endif

