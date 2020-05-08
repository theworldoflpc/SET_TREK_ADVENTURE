/*
* Filename:         Graphics.h
* Project:          PROG2215 - G.A.S. - Assignment - 01 - SET Trek
* Programmer:       Lev Cocarell
* Date:             2017-02-01
* Description:
* Source: Russ' example
*/



#pragma once
#include <Windows.h>
#include <d2d1.h>


class Graphics
{
	//Below, these are all COM interfaces we're using to create D2D resources.
	//We release them as part of the ~Graphics deconstructor... or bad things can happen
	ID2D1Factory* factory; //The factory allows us to create many other types of D2D resources
	ID2D1HwndRenderTarget* rendertarget; //this is typically an area in our GPU memory.. like a back buffer 
	ID2D1SolidColorBrush* brush; //Note this COM interface! Remember to release it!
	
public:
	Graphics();

	~Graphics();

	bool Init(HWND windowHandle);

	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float c, float y, float radius, float r, float g, float b, float a);
	// Hrmmm... r, g, b, a? Where do we know these from?
};
