// WaterSource.h	- Darragh O'Neill
// header file for WaterSource class
#include "BaseComponent.h"

#ifndef WATERSOURCE_H
#define WATERSOURCE_H
class WaterSource: public BaseComponent
{
public:
	WaterSource():BaseComponent(){}
	WaterSource(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~WaterSource(){}
	
	void draw(HDC hdc, UINT GRID_SIZE);
};
#endif