#include "stdafx.h"
#include "CollisionHelper.h"

namespace nCollision {

	bool IsInRect(D2D_RECT_F from, D2D_RECT_F to)
	{
		if ((from.left <= to.right && from.right >= to.left) &&
			(from.top <= to.bottom && from.bottom >= to.top)) {
			return true;
		}
		return false;
	}

	bool IsInRectPoint(D2D_RECT_F from, POINT to)
	{
		if ((from.left <= to.x && from.right >= to.x) &&
			from.top <= to.y && from.bottom >= to.y) {
			return true;
		}
		return false;
	}

	bool IsInCirPoint(float x, float y, D2D1_ELLIPSE cir)
	{
		float dx = cir.point.x - x;
		float dy = cir.point.y - y;

		float p = sqrtf(pow(dx, 2) + pow(dy, 2));


		return (p < cir.radiusX) ? true : false;
	}

	bool IsRectInCircle(D2D_RECT_F rect, D2D1_ELLIPSE cir)
	{
		if ((rect.left <= cir.point.x && rect.right >= cir.point.x) ||
			(rect.top <= cir.point.y && rect.bottom >= cir.point.y))
		{
			D2D_RECT_F temp =
			{
				rect.left - cir.radiusX,
				rect.top - cir.radiusX,
				rect.right + cir.radiusX,
				rect.bottom + cir.radiusX
			};

			if ((temp.left <= cir.point.x && temp.right >= cir.point.x) &&
				(temp.top <= cir.point.y && temp.bottom >= cir.point.y))
				return true;
		}
		else {
			if (IsInCirPoint(rect.left, rect.top, cir)) return true;
			if (IsInCirPoint(rect.left, rect.bottom, cir)) return true;
			if (IsInCirPoint(rect.right, rect.top, cir)) return true;
			if (IsInCirPoint(rect.right, rect.bottom, cir)) return true;
		}
		return false;
	}

	bool MouseInRect(D2D_RECT_F rect)
	{
		if (AppMouse.x > rect.left && AppMouse.x < rect.right &&
			AppMouse.y > rect.top && AppMouse.y < rect.bottom)
		{
			return true;
		}
		return false;
	}

	//수정하기
	bool MouseInISO(D2D_POINT_2F pos[])
	{
		/*
		D2D_POINT_2F tempPos[4];

		tempPos[0].x = pos.x - offset.width * 0.5f;
		tempPos[0].y = pos.y + offset.height * 0.25f;
		tempPos[1].x = pos.x;
		tempPos[1].y = pos.y;
		tempPos[2].x = pos.x + offset.width * 0.5f;
		tempPos[2].y = pos.y + offset.height * 0.25f;
		tempPos[3].x = pos.x;
		tempPos[3].y = pos.y + offset.height * 0.5f;
		*/
		float tempLine[4];
		float tempIntercept[4];

		//기울기 구하기 (y의 증가량 / x의 증가량)
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)
			{
				tempLine[i] = ((pos[i].y + _CAM->y) - (pos[i + 1].y + _CAM->y)) / ((pos[i].x + _CAM->x) - (pos[i + 1].x + _CAM->x));
			}
			else {
				tempLine[i] = ((pos[i].y + _CAM->y) - (pos[0].y + _CAM->y)) / ((pos[i].x + _CAM->x) - (pos[0].x + _CAM->x));
			}
		}
		//절편 구하기
		for (int i = 0; i < 4; i++)
		{
			tempIntercept[i] = (pos[i].y + _CAM->y) - (tempLine[i] * (pos[i].x + _CAM->x));
		}

		if (AppMouse.y >= tempLine[0] * AppMouse.x + tempIntercept[0] &&
			AppMouse.y <= tempLine[1] * AppMouse.x + tempIntercept[1] &&
			AppMouse.y <= tempLine[2] * AppMouse.x + tempIntercept[2] &&
			AppMouse.y >= tempLine[3] * AppMouse.x + tempIntercept[3])
		{
			return true;
		}
		return false;
	}

	bool ISOInPoint(D2D_POINT_2F from, D2D_POINT_2F to[])
	{
		// y = ax + b (일차방정식) 사용

		float tempLine[4];		//탐색할 ISO Metric의 대각선
		float tempIntercept[4];	//탐색할 ISO Metric의 절편
		float result[4];		//탐색한 ISO Metric의 해

		//기울기 구하기 (y의 증가량 / x의 증가량) a = y/x
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)
			{
				tempLine[i] = (to[i].y - to[i + 1].y) / (to[i].x - to[i + 1].x);
			}
			else {
				tempLine[i] = (to[i].y - to[0].y) / (to[i].x - to[0].x);
			}
		}
		//절편 구하기 (b = y - ax)
		for (int i = 0; i < 4; i++)
		{
			tempIntercept[i] = to[i].y - (tempLine[i] * to[i].x);
		}
		// 탐색한 일차 방정식의 해 (y = ax + b)
		for (int i = 0; i < 4; i++)
		{
			result[i] = tempLine[i] * from.x + tempIntercept[i];
		}

		// 일차방정식의 해의 값과 탐색 기준 좌표간의 비교 (y >= ax + b && y <= ax + b)
		if (from.y >= result[0] &&
			from.y <= result[1] &&
			from.y <= result[2] &&
			from.y >= result[3])
		{
			return true;
		}
		return false;
	}

	bool ISOInISO(D2D_POINT_2F from, D2D_POINT_2F fromRym[], D2D_POINT_2F toRym[])
	{
		// y = ax + b (일차방정식) 사용
		float fromTempLine[4];			//탐색 기준 ISO Metric의 대각선
		float fromTempIntercept[4];		//탐색 기준 ISO Metric의 절편
		float fromResult[4];			//탐색 기준 ISO Metric의 해
		float toTempLine[4];			//탐색할 ISO Metric의 대각선
		float toTempIntercept[4];		//탐색할 ISO Metric의 절편
		float toResult[4];				//탐색할 ISO Metric의 해
		
		//FROM
		//기울기 구하기 (y의 증가량 / x의 증가량) (a = y/x)
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)
			{
				fromTempLine[i] = (fromRym[i].y - fromRym[i + 1].y) / (fromRym[i].x - fromRym[i + 1].x);
			}
			else {
				fromTempLine[i] = (fromRym[i].y - fromRym[0].y) / (fromRym[i].x - fromRym[0].x);
			}
		
		}
		//절편 구하기 (b = y - ax)
		for (int i = 0; i < 4; i++)
		{
			fromTempIntercept[i] = fromRym[i].y - (fromTempLine[i] * fromRym[i].x);
		}
		// 탐색 기준 ISO Metric의 일차방정식의 해 (y = ax + b)
		for (int i = 0; i < 4; i++)
		{
			fromResult[i] = (fromTempLine[i] * from.x) + (fromTempIntercept[i] - from.y);
		}
		
		//TO
		//기울기 구하기 (y의 증가량 / x의 증가량) (a = y/x)
		for (int i = 0; i < 4; i++)
		{
			if (i < 3)
			{
				toTempLine[i] = (toRym[i].y - toRym[i + 1].y) / (toRym[i].x - toRym[i + 1].x);
			}
			else {
				toTempLine[i] = (toRym[i].y - toRym[0].y) / (toRym[i].x - toRym[0].x);
			}
		}
		//절편 구하기 (b = y - ax)
		for (int i = 0; i < 4; i++)
		{
			toTempIntercept[i] = toRym[i].y - (toTempLine[i] * toRym[i].x);
		}
		// 탐색할 ISO Metric의 일차방정식의 해 (y= ax + b)
		for (int i = 0; i < 4; i++)
		{
			toResult[i] = (toTempLine[i] * from.x) + (toTempIntercept[i] - from.y);
		}
		
		// 탐색기준 ISO Metric과 탐색할 ISO Metric의 일차방정식 해의 비교
		if (fromResult[0] <= toResult[2] &&
			fromResult[1] >= toResult[3] &&
			fromResult[2] >= toResult[0] &&
			fromResult[3] <= toResult[1]) {
			return true;
		}

		return false;
	}

	float GetDistance(float StartX, float StartY, float EndX, float EndY)
	{
		return sqrtf(pow(StartX - EndX, 2) + pow(StartY - EndY, 2));
	}

	int GetDistance(int StartX, int StartY, int EndX, int EndY)
	{
		return sqrtf(pow(StartX - EndX, 2) + pow(StartY - EndY, 2));
	}

	float GetAngle(float StartX, float StartY, float EndX, float EndY)
	{
		float x = EndX - StartX;
		float y = EndY - StartY;

		float angle = atan2(y, x) * (180.0f / PI);
		if (angle < 0.0f) angle += 360.0f;

		return DegreeToRadian(angle);
	}

	float DegreeToRadian(float fDegree)
	{
		return fDegree * (PI / 180.0f);
	}

	float RadianToDegree(float fRadian)
	{
		return fRadian * (180.0f / PI);
	}

}
