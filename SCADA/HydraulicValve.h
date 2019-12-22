// HydraulicValve.h	- Darragh O'Neill
// header file for HydraulicValve class
#include "BaseComponent.h"

#ifndef HYDRAULICVALVE_H
#define HYDRAULICVALVE_H
class HydraulicValve: public BaseComponent
{
public:
	HydraulicValve(): BaseComponent(){}
	HydraulicValve(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~HydraulicValve(){}

	void draw(HDC hdc, UINT GRID_SIZE);
//	void animate(HDC hdc);
};
#endif