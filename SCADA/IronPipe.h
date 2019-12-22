// IronPipe.h	- Darragh O'Neill
// header file for IronPipe class
#include "BaseComponent.h"

#ifndef IRONPIPE_H
#define	IRONPIPE_H
class IronPipe: public BaseComponent
{
public:
	IronPipe():BaseComponent(){}
	IronPipe(int ID, int iX, int iY, int ival0, int ival1, int ival2, int ival3):
		BaseComponent(ID, iX, iY, ival0, ival1, ival2, ival3){}
	~IronPipe(){}

	void draw(HDC hdc, UINT GRID_SIZE);
	void animate(HDC hdc, UINT GRID_SIZE);
};
#endif


