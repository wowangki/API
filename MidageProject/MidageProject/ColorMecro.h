#pragma once

D2D_COLOR_F SetColorF(int r, int g, int b, float opacity = 1.0f) {
	float R = (r / 255.0f);
	float B = (b / 255.0f);
	float G = (g / 255.0f);

	return ColorF(R, G, B, opacity);
}