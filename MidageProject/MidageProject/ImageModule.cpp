#include "stdafx.h"
#include "ImageModule.h"


ImageModule::ImageModule()
	:ImageInfo(nullptr)
{
}

ImageModule::~ImageModule()
{
}

void ImageModule::Release(void)
{
	SafeRelease(ImageInfo->pBitmap);
	SafeRelease(ImageInfo->pWicFrameDecoder);
	SafeRelease(ImageInfo->pWicDecoder);
	SafeRelease(ImageInfo->pWicConverter);
	SafeRelease(ImageInfo->pWicFactory);

	SafeDelete(ImageInfo);
}

HRESULT ImageModule::CreateImage(string FileName, float width, float height)
{
	if (FileName == "") return E_FAIL;
	this->FileName = StringToWstring(FileName);

	if (ImageInfo != nullptr) Release();
	ImageInfo = new IMAGE_INFO();

	//	WIC를 사용하기 위해 Factory 객체 생성
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&ImageInfo->pWicFactory));
	Assert(hr == S_OK);

	//	이미지를 읽어온다
	hr = ImageInfo->pWicFactory->CreateDecoderFromFilename(
		this->FileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(ImageInfo->pWicDecoder));

	//	이미지 초기화가 실패하면 팝업창 띄어준다
	if (FAILED(hr)) {
		TCHAR ErrorStr[256];
		_stprintf_s(ErrorStr, L"이미지 파일이 잘못되었습니다!\nFileName : %s",
			this->FileName.c_str());

		MessageBox(AppDesc._hWnd, ErrorStr, NULL, MB_OK);
		Release();
		return hr;
	}

	//	첫 번째 프레임을 사용할 수 있는 객체 구성
	hr = ImageInfo->pWicDecoder->GetFrame(0, &ImageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//	Factory 객체를 사용하여 이미지 변환 객체를 생성
	hr = ImageInfo->pWicFactory->CreateFormatConverter(&ImageInfo->pWicConverter);
	Assert(hr == S_OK);

	//	시스템이 사용 가능한 비트맵 형식으로 변환
	hr = ImageInfo->pWicConverter->Initialize(
		ImageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//	변환된 이미지 형식을 D2D 에 사용할 비트맵 생성
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		ImageInfo->pWicConverter,
		nullptr,
		&ImageInfo->pBitmap
	);

	//	이미지가 정상적으로 생성되지 않았을 경우
	if (ImageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//	이미지 원본 사이즈로 사용하고 싶은 경우
	if (width == 0.0f || height == 0.0f) {
		ImageInfo->ImageSize = ImageInfo->pBitmap->GetSize();
	}
	else {
		ImageInfo->ImageSize.width = width;
		ImageInfo->ImageSize.height = height;
	}

	return S_OK;
}

HRESULT ImageModule::CreateFrameImage(string FileName, int MaxFrameX, int MaxFrameY, float width, float height)
{
	if (FileName == "") return E_FAIL;
	this->FileName = StringToWstring(FileName);

	if (ImageInfo != nullptr) Release();
	ImageInfo = new IMAGE_INFO();

	//	WIC를 사용하기 위해 Factory 객체 생성
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&ImageInfo->pWicFactory));
	Assert(hr == S_OK);

	//	이미지를 읽어온다
	hr = ImageInfo->pWicFactory->CreateDecoderFromFilename(
		this->FileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(ImageInfo->pWicDecoder));

	//	이미지 초기화가 실패하면 팝업창 띄어준다
	if (FAILED(hr)) {
		TCHAR ErrorStr[256];
		_stprintf_s(ErrorStr, L"이미지 파일이 잘못되었습니다!\nFileName : %s",
			this->FileName.c_str());

		MessageBox(AppDesc._hWnd, ErrorStr, NULL, MB_OK);
		Release();
		return hr;
	}

	//	첫 번째 프레임을 사용할 수 있는 객체 구성
	hr = ImageInfo->pWicDecoder->GetFrame(0, &ImageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//	Factory 객체를 사용하여 이미지 변환 객체를 생성
	hr = ImageInfo->pWicFactory->CreateFormatConverter(&ImageInfo->pWicConverter);
	Assert(hr == S_OK);

	//	시스템이 사용 가능한 비트맵 형식으로 변환
	hr = ImageInfo->pWicConverter->Initialize(
		ImageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//	변환된 이미지 형식을 D2D 에 사용할 비트맵 생성
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		ImageInfo->pWicConverter,
		nullptr,
		&ImageInfo->pBitmap
	);

	//	이미지가 정상적으로 생성되지 않았을 경우
	if (ImageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//	이미지 원본 사이즈로 사용하고 싶은 경우
	if (width == 0.0f || height == 0.0f) {
		ImageInfo->ImageSize = ImageInfo->pBitmap->GetSize();
	}
	else {
		ImageInfo->ImageSize.width = width;
		ImageInfo->ImageSize.height = height;
	}

	//	프레임 이미지 계산
	ImageInfo->MaxFrameX = MaxFrameX;
	ImageInfo->MaxFrameY = MaxFrameY;
	ImageInfo->FrameImageSize.width = ImageInfo->ImageSize.width / MaxFrameX;
	ImageInfo->FrameImageSize.height = ImageInfo->ImageSize.height / MaxFrameY;

	return S_OK;
}

void ImageModule::Render(float opacity)
{
	if (ImageInfo->pBitmap == nullptr) return;

	D2D1_RECT_F dxLocation = RectF(
		_CAM->x,
		_CAM->y,
		_CAM->x + ImageInfo->ImageSize.width,
		_CAM->y + ImageInfo->ImageSize.height
	);

	D2D1_RECT_F dxSize = RectF(0.0f, 0.0f,
		ImageInfo->ImageSize.width,
		ImageInfo->ImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::Render(float x, float y, float opacity)
{
	if (ImageInfo == nullptr) return;

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x,
		y + _CAM->y,
		x + _CAM->x + ImageInfo->ImageSize.width,
		y + _CAM->y + ImageInfo->ImageSize.height
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(0.0f, 0.0f,
		ImageInfo->ImageSize.width,
		ImageInfo->ImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::Render(float x, float y, float ScaleX, float ScaleY, float opacity)
{
	if (ImageInfo == nullptr) return;

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x,
		y + _CAM->y,
		x + ScaleX + _CAM->x,
		y + ScaleY + _CAM->y
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(0.0f, 0.0f,
		ImageInfo->ImageSize.width,
		ImageInfo->ImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::FrameRender(float x, float y, int CFx, int CFy, float opacity)
{
	if (ImageInfo == nullptr) return;

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + ImageInfo->FrameImageSize.width,
		y + ImageInfo->FrameImageSize.height
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx * ImageInfo->FrameImageSize.width,
		CFy * ImageInfo->FrameImageSize.height,
		(CFx + 1) * ImageInfo->FrameImageSize.width,
		(CFy + 1) * ImageInfo->FrameImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::FrameRender(float x, float y, int CFx, int CFy, float ScaleX, float ScaleY, float opacity)
{
	if (ImageInfo == nullptr) return;

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x,
		y + _CAM->y,
		x + ScaleX + _CAM->x,
		y + ScaleY + _CAM->y
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx * ImageInfo->FrameImageSize.width,
		CFy * ImageInfo->FrameImageSize.height,
		(CFx + 1) * ImageInfo->FrameImageSize.width,
		(CFy + 1) * ImageInfo->FrameImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::FrameRender(float x, float y, int CFx, int CFy, float degree, bool isReverse, float ScaleX, float ScaleY, float opacity)
{
	if (ImageInfo == nullptr) return;
	if (ScaleX == 0.0f || ScaleY == 0.0f) {
		ScaleX = ImageInfo->FrameImageSize.width;
		ScaleY = ImageInfo->FrameImageSize.height;
	}

	D2D_POINT_2F dxPoint = { x + ScaleX / 2.0f, y + ScaleY / 2.0f };
	Matrix3x2F dxMatrix;

	if (isReverse) dxMatrix = Matrix3x2F::Scale(-1.0f, 1.0f, dxPoint) * Matrix3x2F::Rotation(degree, dxPoint);
	else dxMatrix = Matrix3x2F::Rotation(degree, dxPoint);

	_RenderTarget->SetTransform(dxMatrix);

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + ScaleX,
		y + ScaleY
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx * ImageInfo->FrameImageSize.width,
		CFy * ImageInfo->FrameImageSize.height,
		(CFx + 1) * ImageInfo->FrameImageSize.width,
		(CFy + 1) * ImageInfo->FrameImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);

	_RenderTarget->SetTransform(Matrix3x2F::Identity());
}

void ImageModule::CFrameRender(float x, float y, int CFx, int CFy, float opacity)
{
	if (ImageInfo == nullptr) return;

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x - (ImageInfo->FrameImageSize.width * 0.5f),
		y + _CAM->y - ImageInfo->FrameImageSize.height,
		x + _CAM->x + (ImageInfo->FrameImageSize.width * 0.5f),
		y + _CAM->y
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx * ImageInfo->FrameImageSize.width,
		CFy * ImageInfo->FrameImageSize.height,
		(CFx + 1) * ImageInfo->FrameImageSize.width,
		(CFy + 1) * ImageInfo->FrameImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::CFrameRender(float x, float y, int CFx, int CFy, float ScaleX, float ScaleY, float opacity)
{
	if (ImageInfo == nullptr) return;

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x - (ScaleX * 0.5f),
		y + _CAM->y - ScaleY * 0.25f,
		x + _CAM->x + (ScaleX * 0.5f),
		y + _CAM->y + ScaleY * 0.75f
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx * ImageInfo->FrameImageSize.width,
		CFy * ImageInfo->FrameImageSize.height,
		(CFx + 1) * ImageInfo->FrameImageSize.width,
		(CFy + 1) * ImageInfo->FrameImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::CISOFrameRender(float x, float y, int CFx, int CFy, float ScaleX, float ScaleY, float opacity)
{
	if (ImageInfo == nullptr) return;

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x - (ImageInfo->FrameImageSize.width * ScaleX), 
		y - (ImageInfo->FrameImageSize.height * ScaleY),
		x + (ImageInfo->FrameImageSize.width * (1 - ScaleX)),
		y + (ImageInfo->FrameImageSize.height * (1 - ScaleY))
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx * ImageInfo->FrameImageSize.width,
		CFy * ImageInfo->FrameImageSize.height,
		(CFx + 1) * ImageInfo->FrameImageSize.width,
		(CFy + 1) * ImageInfo->FrameImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::CFrameRender(float x, float y, int CFx, int CFy, float degree, bool isReverse, float ScaleX, float ScaleY, float opacity)
{
	if (ImageInfo == nullptr) return;
	if (ScaleX == 0.0f || ScaleY == 0.0f) {
		ScaleX = ImageInfo->FrameImageSize.width;
		ScaleY = ImageInfo->FrameImageSize.height;
	}

	D2D_POINT_2F dxPoint = { x + _CAM->x, y + _CAM->y };
	Matrix3x2F dxMatrix;

	if (isReverse) dxMatrix = Matrix3x2F::Scale(-1.0f, 1.0f, dxPoint) * Matrix3x2F::Rotation(degree, dxPoint);
	else dxMatrix = Matrix3x2F::Rotation(degree, dxPoint);

	_RenderTarget->SetTransform(dxMatrix);

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x - (ScaleX * 0.5f), 
		y + _CAM->y - ScaleY,
		x + _CAM->x + (ScaleX * 0.5f),
		y + _CAM->y
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx * ImageInfo->FrameImageSize.width,
		CFy * ImageInfo->FrameImageSize.height,
		(CFx + 1) * ImageInfo->FrameImageSize.width,
		(CFy + 1) * ImageInfo->FrameImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);

	_RenderTarget->SetTransform(Matrix3x2F::Identity());
}

void ImageModule::EffectFrameRender(POINTF pos, int CFx, int CFy, float opacity)
{
	if (ImageInfo == nullptr) return;

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		pos.x,
		pos.y,
		pos.x + ImageInfo->FrameImageSize.width,
		pos.y + ImageInfo->FrameImageSize.height
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx * ImageInfo->FrameImageSize.width,
		CFy * ImageInfo->FrameImageSize.height,
		(CFx + 1) * ImageInfo->FrameImageSize.width,
		(CFy + 1) * ImageInfo->FrameImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::UiFrameRender(float x, float y, int CFx, int CFy, float ScaleX, float ScaleY, float opacity)
{
	if (ImageInfo == nullptr) return;

	if (ScaleX == 0.0f || ScaleY == 0.0f) {
		ScaleX = ImageInfo->FrameImageSize.width;
		ScaleY = ImageInfo->FrameImageSize.height;
	}

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x,
		y,
		x + ScaleX,
		y + ScaleY
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx * ImageInfo->FrameImageSize.width,
		CFy * ImageInfo->FrameImageSize.height,
		(CFx + 1) * ImageInfo->FrameImageSize.width,
		(CFy + 1) * ImageInfo->FrameImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::CUiFrameRender(float x, float y, int CFx, int CFy, float ScaleX, float ScaleY, float opacity)
{
	if (ImageInfo == nullptr) return;
	if (ScaleX == 0.0f || ScaleY == 0.0f) {
		ScaleX = ImageInfo->FrameImageSize.width;
		ScaleY = ImageInfo->FrameImageSize.height;
	}

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x - (ScaleX * 0.5f),
		y - (ScaleY * 0.5f),
		x + (ScaleX * 0.5f),
		y + (ScaleY * 0.5f)
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx * ImageInfo->FrameImageSize.width,
		CFy * ImageInfo->FrameImageSize.height,
		(CFx + 1) * ImageInfo->FrameImageSize.width,
		(CFy + 1) * ImageInfo->FrameImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::CEditObjectFrameRender(float x, float y, int CFx, int CFy, float opacity)
{
	if (ImageInfo == nullptr) return;

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x - (ImageInfo->FrameImageSize.width * 0.5f),
		y - (ImageInfo->FrameImageSize.height * 0.75f),
		x + (ImageInfo->FrameImageSize.width * 0.5f),
		y + (ImageInfo->FrameImageSize.height * 0.25f)
	);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx * ImageInfo->FrameImageSize.width,
		CFy * ImageInfo->FrameImageSize.height,
		(CFx + 1) * ImageInfo->FrameImageSize.width,
		(CFy + 1) * ImageInfo->FrameImageSize.height
	);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}
