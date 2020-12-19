#include "stdafx.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
	
}

void ImageManager::Release(void)
{
	for (mIter iter = mImage.begin(); iter != mImage.end(); iter++) {
		iter->second->Release();
		SafeDelete(iter->second);
	}
}

ImageModule * ImageManager::CreateImage(std::string NickName, std::string FileName, float width, float height)
{
	ImageModule* img = FindImage(NickName);
	if (img != nullptr) return img;
	
	img = new ImageModule;
	img->CreateImage(FileName, width, height);

	mImage.insert(make_pair(NickName, img));

	return img;
}

ImageModule * ImageManager::CreateFrameImage(std::string NickName, std::string FileName, int MaxFrameX, int MaxFrameY, float width, float height)
{
	ImageModule* img = FindImage(NickName);
	if (img != nullptr) return img;

	img = new ImageModule;
	img->CreateFrameImage(FileName, MaxFrameX, MaxFrameY, width, height);

	mImage.insert(make_pair(NickName, img));

	return img;
}

ImageModule * ImageManager::FindImage(std::string NickName)
{
	if (mImage.empty())	return nullptr;
	
	for (mIter iter = mImage.begin(); iter != mImage.end(); iter++) {
		if (iter->first == NickName)
			return iter->second;
	}

	return nullptr;
}
