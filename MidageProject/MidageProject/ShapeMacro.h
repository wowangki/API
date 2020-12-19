#pragma once

inline D2D_RECT_F FRectMake(float x, float y, float width, float height) {
	D2D_RECT_F temp = RectF(x, y, x + width, y + height);

	return temp;
}

inline D2D_RECT_F FRectMakeCenter(float x, float y, float width, float height) {
	D2D_RECT_F temp = RectF(x - width * 0.5f, y - height * 0.5f, x + width * 0.5f, y + height * 0.5f);

	return temp;
}

inline D2D_RECT_U URectMake(UINT x, UINT y, UINT width, UINT height) {
	D2D_RECT_U temp = RectU(x, y, x + width, y + height);

	return temp;
}

inline D2D_RECT_U URectMakeCenter(float x, float y, float width, float height) {
	D2D_RECT_U temp = RectU(x - width * 0.5f, y - height * 0.5f, x + width * 0.5f, y + height * 0.5f);

	return temp;
}

inline D2D1_ELLIPSE CircleMake(float x, float y, float radianX, float radianY = 0.0f) {
	
	if (radianY == 0.0f) radianY = radianX;
	
	D2D1_ELLIPSE temp = { x,y,radianX, radianY };

	return temp;
}

inline D2D_POINT_2F ISOPointMake(D2D_POINT_2L id, D2D_SIZE_F offset)
{
	D2D_POINT_2F temp;
	temp.x = ((id.x - id.y) * offset.width * 0.5f);
	temp.y = ((id.x + id.y) * offset.height * 0.27f);

	return temp;

}

inline D2D_POINT_2F ISOPointMake(D2D_POINT_2F id, D2D_SIZE_F offset)
{
	D2D_POINT_2F temp;
	temp.x = ((id.x - id.y) * offset.width * 0.5f);
	temp.y = ((id.x + id.y) * offset.height * 0.27f);

	return temp;
}

inline void RymBusPointMake(D2D_POINT_2F pos, D2D_POINT_2F* rymPos, D2D_SIZE_F offset)
{
	rymPos[0].x = pos.x;
	rymPos[0].y = pos.y - (offset.height * 0.27f);
	rymPos[1].x = pos.x - (offset.width * 0.5f);
	rymPos[1].y = pos.y;
	rymPos[2].x = pos.x;
	rymPos[2].y = pos.y + (offset.height * 0.27f);
	rymPos[3].x = pos.x + (offset.width * 0.5f);
	rymPos[3].y = pos.y;
}

inline D2D_POINT_2L ISOtoPoint(D2D_POINT_2F pos, D2D_SIZE_F offset, float camX = 0, float camY = 0)
{
	D2D_POINT_2L tID;
	int tX;
	int tY;

	tX = ((pos.x - camX) / (offset.width * 0.5f));
	tY = ((pos.y + camY) / (offset.height * 0.27f));

	tID.x = ceil((tX + tY) * 0.5f);
	tID.y = ceil((tX - tY) * -0.5f);

	return tID;
}

inline void DrawISO(D2D_POINT_2F* rymPos, string brush) {
	_RenderTarget->DrawLine({rymPos[0].x + _CAM->x, rymPos[0].y + _CAM->y}, {rymPos[1].x + _CAM->x, rymPos[1].y + _CAM->y}, _BRUSH->GetBrush(brush));
	_RenderTarget->DrawLine({rymPos[0].x + _CAM->x, rymPos[0].y + _CAM->y}, {rymPos[3].x + _CAM->x, rymPos[3].y + _CAM->y}, _BRUSH->GetBrush(brush));
	_RenderTarget->DrawLine({rymPos[1].x + _CAM->x, rymPos[1].y + _CAM->y}, {rymPos[2].x + _CAM->x, rymPos[2].y + _CAM->y}, _BRUSH->GetBrush(brush));
	_RenderTarget->DrawLine({rymPos[2].x + _CAM->x, rymPos[2].y + _CAM->y}, {rymPos[3].x + _CAM->x, rymPos[3].y + _CAM->y}, _BRUSH->GetBrush(brush));
}