#pragma once
class ImageModule
{
public:
	ImageModule();
	~ImageModule();

	typedef struct IMAGE_INFO {
		IMAGE_INFO()
			:
			pWicFactory(nullptr),
			pWicConverter(nullptr),
			pWicDecoder(nullptr),
			pWicFrameDecoder(nullptr),
			pBitmap(nullptr),
			ImageSize(D2D1_SIZE_F()),
			BufferSize(1.0f),
			FrameImageSize(D2D1_SIZE_F()),
			MaxFrameX(0), MaxFrameY(0)
		{};

		IWICImagingFactory*		pWicFactory;
		IWICFormatConverter*	pWicConverter;
		IWICBitmapDecoder*		pWicDecoder;
		IWICBitmapFrameDecode*	pWicFrameDecoder;
		ID2D1Bitmap*			pBitmap;

		D2D1_SIZE_F				ImageSize;
		float					BufferSize;

		D2D1_SIZE_F				FrameImageSize;		//	프레임 이미지 한칸 사이즈
		int						MaxFrameX;			//	최대 프레임 X
		int						MaxFrameY;			//	최대 프레임 Y

	}*LPIMAGE_INFO;

private:
	LPIMAGE_INFO ImageInfo;
	wstring FileName;

public:
	void Release(void);


public:		//	CreateImage
	HRESULT CreateImage(string FileName, float width = 0.0f, float height = 0.0f);
	HRESULT CreateFrameImage(string FileName, int MaxFrameX, int MaxFrameY, float width = 0.0f, float height = 0.0f);

public:		//	Render
	
	//Basic Render
	void Render(float opacity = 1.0f);
	//Basic Location Render
	void Render(float x, float y, float opacity = 1.0f);
	//Scale Render
	void Render(float x, float y, float ScaleX, float ScaleY, float opacity = 1.0f);
	//Frame Render
	void FrameRender(float x, float y, int CFx, int CFy, float opacity = 1.0f);
	//Scale Frame Render
	void FrameRender(float x, float y, int CFx, int CFy, float ScaleX, float ScaleY, float opacity = 1.0f);
	//Mirror Frame Render
	void FrameRender(float x, float y, int CFx, int CFy, float degree, bool isReverse, float ScaleX = 0.0f, float ScaleY = 0.0f, float opacity = 1.0f);
	//Frame Center Render
	void CFrameRender(float x, float y, int CFx, int CFy, float opacity = 1.0f);
	//Frame Center Sclae Render
	void CFrameRender(float x, float y, int CFx, int CFy, float ScaleX, float ScaleY, float opacity = 1.0f);
	//ISO FrameRender
	void CISOFrameRender(float x, float y, int CFx, int CFy, float ScaleX = 1.0f, float ScaleY = 1.0f, float opacity = 1.0f);
	//Mirror Frame Center Render
	void CFrameRender(float x, float y, int CFx, int CFy, float degree, bool isReverse, float ScaleX = 0.0f, float ScaleY = 0.0f, float opacity = 1.0f);
	//Effect Render
	void EffectFrameRender(POINTF pos, int CFx, int CFy, float opacity = 1.0f);
	//UI Render
	void UiFrameRender(float x, float y, int CFx, int CFy, float ScaleX = 0.0f, float ScaleY = 0.0f, float opacity = 1.0f);
	//UI CenterRender
	void CUiFrameRender(float x, float y, int CFx, int CFy, float ScaleX = 0.0f, float ScaleY = 0.0f, float opacity = 1.0f);
	void CEditObjectFrameRender(float x, float y, int CFx, int CFy, float opacity = 1.0f);

public:		//	ImageInfo Get Set
	inline float GetWidth() { return ImageInfo->ImageSize.width; }
	inline float GetHeight() { return ImageInfo->ImageSize.height; }

	inline float GetFrameWidth() { return ImageInfo->FrameImageSize.width; }
	inline float GetFrameHeight() { return ImageInfo->FrameImageSize.height; }

	inline int GetMaxFrameX() { return ImageInfo->MaxFrameX; }
	inline int GetMaxFrameY() { return ImageInfo->MaxFrameY; }

	inline D2D_RECT_F GetRect(float x, float y) {
		return RectF(x, y,
			x + ImageInfo->ImageSize.width,
			y + ImageInfo->ImageSize.height);
	}

};

