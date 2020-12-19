#pragma once
#include "ShapeMacro.h"
#include "ColorMecro.h"
#include "RandomMacro.h"
#include "CollisionHelper.h"
#include "CullHelper.h"

namespace nString
{
	inline wstring StringToWstring(const string& str) {
		size_t len = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), nullptr, 0);
		wstring Temp(len, 0);

		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &Temp[0], len);

		return Temp;
	}

	inline string WstringToString(const wstring& str) {
		string temp;
		temp.assign(str.begin(), str.end());
		return temp;
	}
}

namespace nSource{
	
	inline string FileSource(string typeFolder, string detailFolder, string FileName) {
		string temp;

		temp.append(typeFolder).append("/").
			append(detailFolder).append("/").
			append(FileName);

		return temp;
	}
}