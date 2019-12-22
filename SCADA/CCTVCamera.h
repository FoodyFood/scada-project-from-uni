// CCTVCamera.h	- Darragh O'Neill
// header file for CCTVCamera class
#include "BaseComponent.h"

#ifndef CCTVCAMERA_H
#define CCTVCAMERA_H
class CCTVCamera: public BaseComponent
{
public:
	CCTVCamera():BaseComponent(){}
	CCTVCamera(int ID, int iX, int iY, int iorientation, int ifuture0, int ifuture1, int ifuture2):
		BaseComponent(ID, iX, iY, iorientation, ifuture0, ifuture1, ifuture2){}
	~CCTVCamera(){}

	void draw(HDC hdc, UINT GRID_SIZE);
};
#endif 