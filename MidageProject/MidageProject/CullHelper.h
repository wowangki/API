#pragma once

namespace nCull {
	
	inline bool IsWindowOut(D2D_RECT_F rc) {

		if (rc.left + _CAM->x >= WINSIZEX || rc.top + _CAM->y >= WINSIZEY ||
			rc.right + _CAM->x <= 0.0f || rc.bottom + _CAM->y <= 0.0f) {
			
			return true;
		}
		return false;
	}

	inline bool UIIsWindowOut(D2D_RECT_F rc) {
		if (rc.left >= WINSIZEX || rc.top >= WINSIZEY ||
			rc.right <= 0.0f || rc.bottom <= 0.0f) {

			return true;
		}
		return false;
	}
}