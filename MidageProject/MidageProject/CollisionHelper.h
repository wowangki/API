#pragma once
#define PI (float) 3.14159265359f

namespace nCollision {
	bool IsInRect(D2D_RECT_F from, D2D_RECT_F to);
	bool IsInRectPoint(D2D_RECT_F from, POINT to);

	bool IsInCirPoint(float x, float y, D2D1_ELLIPSE cir);
	bool IsRectInCircle(D2D_RECT_F rect, D2D1_ELLIPSE cir);

	bool MouseInRect(D2D_RECT_F rect);
	bool MouseInISO(D2D_POINT_2F pos[]);
	bool ISOInPoint(D2D_POINT_2F from, D2D_POINT_2F to[]);
	bool ISOInISO(D2D_POINT_2F from, D2D_POINT_2F fromRym[], D2D_POINT_2F toRym[]);

	float GetDistance(float StartX, float StartY, float EndX, float EndY);
	float GetAngle(float StartX, float StartY, float EndX, float EndY);
	float DegreeToRadian(float fDegree);
	float RadianToDegree(float fRadian);

}