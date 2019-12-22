//This section written by D O'Connor

// SanitizationDrain.h
// header file for SanitizationDrain class
#include "BaseComponent.h"

#ifndef SANITIZATIONDRAIN_H
#define	SANITIZATIONDRAIN_H
class SanitizationDrain: public BaseComponent
{
public:
	SanitizationDrain():BaseComponent(){}
	SanitizationDrain(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~SanitizationDrain(){}

	void draw(HDC hdc, UINT GRID_SIZE);
};
#endif


