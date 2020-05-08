/*
* Filename:         Graphics.cpp
* Project:          PROG2215 - G.A.S. - Assignment - 01 - SET Trek
* Programmer:       Lev Cocarell
* Date:             2017-02-01
* Description:
* Source: Russ' example 
*/





#include "Graphics.h"



//=============================================================================
// Constructor
//=============================================================================
//Constructor for Graphics class
Graphics::Graphics()
{
	factory = NULL;
	rendertarget = NULL;
	brush = NULL;

	/*
	direct3d = NULL;
    device3d = NULL;
    fullscreen = false;
    width = GAME_WIDTH;    // width & height are replaced in initialize()
    height = GAME_HEIGHT;	
	*/


}





//=============================================================================
// Destructor
//=============================================================================

//Destructor for Graphics class
//Note that all COM objects we instantiate should be 'released' here 
//Look for comments on COM usage in the corresponding header file.

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (brush) brush->Release();
}




//Provide some comments for each of the methods below.
//Be sure you get a sense of what is happening, and resolve any issues you have understanding these
// methods, their parameters, returns and so on.
bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect); //set the rect's right and bottom properties = the client window's size

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&rendertarget);
	if (res != S_OK) return false;
	
	res = rendertarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;
	return true;
}






void Graphics::ClearScreen(float r, float g, float b) 
{
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}





void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	rendertarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);	
}