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

	//	WIC�� ����ϱ� ���� Factory ��ü ����
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&ImageInfo->pWicFactory));
	Assert(hr == S_OK);

	//	�̹����� �о�´�
	hr = ImageInfo->pWicFactory->CreateDecoderFromFilename(
		this->FileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(ImageInfo->pWicDecoder));

	//	�̹��� �ʱ�ȭ�� �����ϸ� �˾�â ����ش�
	if (FAILED(hr)) {
		TCHAR ErrorStr[256];
		_stprintf_s(ErrorStr, L"�̹��� ������ �߸��Ǿ����ϴ�!\nFileName : %s",
			this->FileName.c_str());

		MessageBox(AppDesc._hWnd, ErrorStr, NULL, MB_OK);
		Release();
		return hr;
	}

	//	ù ��° �������� ����� �� �ִ� ��ü ����
	hr = ImageInfo->pWicDecoder->GetFrame(0, &ImageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//	Factory ��ü�� ����Ͽ� �̹��� ��ȯ ��ü�� ����
	hr = ImageInfo->pWicFactory->CreateFormatConverter(&ImageInfo->pWicConverter);
	Assert(hr == S_OK);

	//	�ý����� ��� ������ ��Ʈ�� �������� ��ȯ
	hr = ImageInfo->pWicConverter->Initialize(
		ImageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//	��ȯ�� �̹��� ������ D2D �� ����� ��Ʈ�� ����
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		ImageInfo->pWicConverter,
		nullptr,
		&ImageInfo->pBitmap
	);

	//	�̹����� ���������� �������� �ʾ��� ���
	if (ImageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//	�̹��� ���� ������� ����ϰ� ���� ���
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

	//	WIC�� ����ϱ� ���� Factory ��ü ����
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&ImageInfo->pWicFactory));
	Assert(hr == S_OK);

	//	�̹����� �о�´�
	hr = ImageInfo->pWicFactory->CreateDecoderFromFilename(
		this->FileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(ImageInfo->pWicDecoder));

	//	�̹��� �ʱ�ȭ�� �����ϸ� �˾�â ����ش�
	if (FAILED(hr)) {
		TCHAR ErrorStr[256];
		_stprintf_s(ErrorStr, L"�̹��� ������ �߸��Ǿ����ϴ�!\nFileName : %s",
			this->FileName.c_str());

		MessageBox(AppDesc._hWnd, ErrorStr, NULL, MB_OK);
		Release();
		return hr;
	}

	//	ù ��° �������� ����� �� �ִ� ��ü ����
	hr = ImageInfo->pWicDecoder->GetFrame(0, &ImageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//	Factory ��ü�� ����Ͽ� �̹��� ��ȯ ��ü�� ����
	hr = ImageInfo->pWicFactory->CreateFormatConverter(&ImageInfo->pWicConverter);
	Assert(hr == S_OK);

	//	�ý����� ��� ������ ��Ʈ�� �������� ��ȯ
	hr = ImageInfo->pWicConverter->Initialize(
		ImageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//	��ȯ�� �̹��� ������ D2D �� ����� ��Ʈ�� ����
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		ImageInfo->pWicConverter,
		nullptr,
		&ImageInfo->pBitmap
	);

	//	�̹����� ���������� �������� �ʾ��� ���
	if (ImageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//	�̹��� ���� ������� ����ϰ� ���� ���
	if (width == 0.0f || height == 0.0f) {
		ImageInfo->ImageSize = ImageInfo->pBitmap->GetSize();
	}
	else {
		ImageInfo->ImageSize.width = width;
		ImageInfo->ImageSize.height = height;
	}

	//	������ �̹��� ���
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x,
		y + _CAM->y,
		x + _CAM->x + ImageInfo->ImageSize.width,
		y + _CAM->y + ImageInfo->ImageSize.height
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x,
		y + _CAM->y,
		x + ScaleX + _CAM->x,
		y + ScaleY + _CAM->y
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + ImageInfo->FrameImageSize.width,
		y + ImageInfo->FrameImageSize.height
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x,
		y + _CAM->y,
		x + ScaleX + _CAM->x,
		y + ScaleY + _CAM->y
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + ScaleX,
		y + ScaleY
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x - (ImageInfo->FrameImageSize.width * 0.5f),
		y + _CAM->y - ImageInfo->FrameImageSize.height,
		x + _CAM->x + (ImageInfo->FrameImageSize.width * 0.5f),
		y + _CAM->y
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x - (ScaleX * 0.5f),
		y + _CAM->y - ScaleY * 0.25f,
		x + _CAM->x + (ScaleX * 0.5f),
		y + _CAM->y + ScaleY * 0.75f
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x - (ImageInfo->FrameImageSize.width * ScaleX), 
		y - (ImageInfo->FrameImageSize.height * ScaleY),
		x + (ImageInfo->FrameImageSize.width * (1 - ScaleX)),
		y + (ImageInfo->FrameImageSize.height * (1 - ScaleY))
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x + _CAM->x - (ScaleX * 0.5f), 
		y + _CAM->y - ScaleY,
		x + _CAM->x + (ScaleX * 0.5f),
		y + _CAM->y
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		pos.x,
		pos.y,
		pos.x + ImageInfo->FrameImageSize.width,
		pos.y + ImageInfo->FrameImageSize.height
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x,
		y,
		x + ScaleX,
		y + ScaleY
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x - (ScaleX * 0.5f),
		y - (ScaleY * 0.5f),
		x + (ScaleX * 0.5f),
		y + (ScaleY * 0.5f)
	);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x - (ImageInfo->FrameImageSize.width * 0.5f),
		y - (ImageInfo->FrameImageSize.height * 0.75f),
		x + (ImageInfo->FrameImageSize.width * 0.5f),
		y + (ImageInfo->FrameImageSize.height * 0.25f)
	);

	//	���� �̹��� ������
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
