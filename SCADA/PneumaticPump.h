// PneumaticPump.h	- Darragh O'Neill
// header file for PneumaticPump class
#include "BaseComponent.h"

#ifndef PNEUMATICPUMP_H
#define PNEUMATICPUMP_H
class PneumaticPump: public BaseComponent
{
public:
	PneumaticPump():BaseComponent(){}
	PneumaticPump(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~PneumaticPump(){}

	void draw(HDC hdc, UINT GRID_SIZE);
};
#endif 