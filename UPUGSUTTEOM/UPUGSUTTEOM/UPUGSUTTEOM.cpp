// UPUGSUTTEOM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <objidl.h>
#include <Gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
#include <stdio.h>
#include <tchar.h>
#include <assert.h>

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
void Draw(Graphics* g, BOOL background = TRUE);

int main(void)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CLSID pngClsid;

	GetEncoderClsid(L"image/png", &pngClsid);

	{
		Bitmap* bitmap = new Bitmap(1000, 1000, PixelFormat32bppARGB);
		Graphics* g = Graphics::FromImage(bitmap);

		Draw(g);

		bitmap->Save(L"ImageF.png", &pngClsid, NULL);

		delete g;
		delete bitmap;
	}
	
	{
		Bitmap* bitmap = new Bitmap(1000, 1000, PixelFormat32bppARGB);
		Graphics* g = Graphics::FromImage(bitmap);

		Draw(g, FALSE);

		bitmap->Save(L"ImageCO.png", &pngClsid, NULL);

		delete g;
		delete bitmap;
	}

    return 0;
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;
	UINT  size = 0;

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}

	free(pImageCodecInfo);
	return -1;
}

void Draw(Graphics* g, BOOL background)
{
	if(background){// background
		LinearGradientBrush* bk = new LinearGradientBrush(Rect(0, 0, 1000, 1000), Color(0xff, 0xff, 0xc7, 0xe8), Color(0xff, 0xd0, 0x67, 0xd8), 45, 1);
		g->FillRectangle(bk, 0, 0, 1000, 1000);
		delete bk;

		//rainbow
		Pen* violet = new Pen(Color(0xff, 0x94, 0x00, 0xd3), 50);
		Pen* indigo = new Pen(Color(0xff, 0x4b, 0x00, 0x82), 50);
		Pen* blue = new Pen(Color(0xff, 0x00, 0x00, 0xff), 50);
		Pen* green = new Pen(Color(0xff, 0x00, 0xff, 0x00), 50);
		Pen* yellow = new Pen(Color(0xff, 0xff, 0xff, 0x00), 50);
		Pen* orange = new Pen(Color(0xff, 0xff, 0x7f, 0x00), 50);
		Pen* red = new Pen(Color(0xff, 0xff, 0x00, 0x00), 50);
		g->DrawArc(violet, 0, 0, 2000, 2000, 90, 180);
		g->DrawArc(indigo, 36, 36, 2000, 2000, 90, 180);
		g->DrawArc(blue, 72, 72, 2000, 2000, 90, 180);
		g->DrawArc(green, 108, 108, 2000, 2000, 90, 180);
		g->DrawArc(yellow, 144, 144, 2000, 2000, 90, 180);
		g->DrawArc(orange, 180, 180, 2000, 2000, 90, 180);
		g->DrawArc(red, 216, 216, 2000, 2000, 90, 180);
		delete violet;
		delete indigo;
		delete blue;
		delete green;
		delete yellow;
		delete orange;
		delete red;
	}

	{// body
		SolidBrush* body = new SolidBrush(Color(0xff, 0xf0, 0xf0, 0xf0));
		Point points[]
		{
			Point(250, 250),
			Point(750, 250),
			Point(750, 750),
			Point(250, 750)
		};
		g->FillClosedCurve(body, points, 4);
		delete body;
	}

	{// eyes
		SolidBrush* eyes = new SolidBrush(Color(0xff, 0x0, 0x0, 0x0));
		SolidBrush* bright = new SolidBrush(Color(0xff, 0xff, 0xff, 0xff));
		//left
		g->FillEllipse(eyes, 350, 350, 100, 100);
		g->FillEllipse(bright, 405, 360, 35, 35);

		//right
		g->FillEllipse(eyes, 550, 350, 100, 100);
		g->FillEllipse(bright, 605, 360, 35, 35);

		delete bright;
		delete eyes;
	}

	{// mouth
		Pen* mouth = new Pen(Color(0xff, 0x60, 0x0, 0x0), 5);
		Point points[]{
			Point(370, 580),
			Point(400, 650),
			Point(470, 650),
			Point(500, 580),
			Point(530, 650),
			Point(600, 650),
			Point(630, 580)
		};
		g->DrawBeziers(mouth, points, 7);
		delete mouth;
	}

	{// cheek
		for (int i = 0; i < 20; i++)
		{
			SolidBrush* cheek = new SolidBrush(Color(0xff /40, 0xf0, 0xa0, 0xa0));
			g->FillEllipse(cheek, 250 + i, 500 + i, 100 - i * 2, 100 - i * 2);
			g->FillEllipse(cheek, 650 + i, 500 + i, 100 - i * 2, 100 - i * 2);
			delete cheek;
		}
	}
}
