// StorageTank.h	- Darragh O'Neill
// header file for StorageTank class
#include "BaseComponent.h"

#ifndef STORAGETANK_H
#define	STORAGETANK_H
class StorageTank: public BaseComponent
{
public:
	StorageTank():BaseComponent(){}
	StorageTank(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~StorageTank(){}

	void draw(HDC hdc, UINT GRID_SIZE);
};
#endif

