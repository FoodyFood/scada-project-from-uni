//This section written by D O'Connor

// SuspendedConcreteGroundFloor.h
// header file for SuspendedConcreteGroundFloor class
#include "BaseComponent.h"

#ifndef SUSPENDEDCONCRETEGROUNDFLOOR_H
#define SUSPENDEDCONCRETEGROUNDFLOOR_H
class SuspendedConcreteGroundFloor: public BaseComponent
{
public:
	SuspendedConcreteGroundFloor():BaseComponent(){}
	SuspendedConcreteGroundFloor(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~SuspendedConcreteGroundFloor(){}
	
	void draw(HDC hdc, UINT GRID_SIZE);
};
#endif