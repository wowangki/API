#pragma once
#include <map>
#include "SingletonBase.h"
#include "ImageModule.h"
class ImageManager : public SingletonBase<ImageManager>
{
private:
	std::map<string, ImageModule*> mImage;
	typedef std::map<string, ImageModule*>::iterator mIter;
public:
	ImageManager();
	~ImageManager();

	void Release(void);
	ImageModule* CreateImage(std::string NickName, std::string FileName, float width = 0.0f, float height = 0.0f);
	ImageModule* CreateFrameImage(std::string NickName, std::string FileName, int MaxFrameX, int MaxFrameY, float width = 0.0f, float height = 0.0f);
	ImageModule* FindImage(std::string NickName);
};

