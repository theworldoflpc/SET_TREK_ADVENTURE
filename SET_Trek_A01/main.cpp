/*
* Filename:         main.cpp
* Project:          PROG2215 - G.A.S. - Assignment - 01 - SET Trek
* Programmer:       Lev Cocarell
* Date:             2017-02-01
* Description:
* Source: Russ' example 
*/


#pragma comment(lib, "d2d1.lib")

#include <Windows.h>
#include "Graphics.h"

Graphics* graphics;



//=============================================================================
// window event callback function
//=============================================================================

/*
Your Mission: Document the following code. What do all these components do?

*/
LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam )
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }
	
//BIG CHANGE! We are not Drawing/rendering here! 
// We've moved this down to the message handling loop below

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}






//=============================================================================
// Starting point for a Windows application
//=============================================================================

// Have you seen a 'main' for a Win32 app before? Please comment this.
int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow
)
{
	//Do a bit of reading - What is this Window Class used for? 
	// What are the major parameters below?
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW; //Alert - This is useful here... what does it do?

	RegisterClassEx(&windowclass);


	RECT rect = { 0, 0, 800, 600 };//Do these numbers look significant to you? What are they?
	AdjustWindowRectEx(&rect, WS_OVERLAPPED, false, WS_EX_OVERLAPPEDWINDOW);

	//Below is another important process to understand... what are we doing?
	//Why is this connected to rect we just defined above?
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "SET_Trek_V_A_1.0", WS_OVERLAPPEDWINDOW, 100, 100, 
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	if (!windowhandle) return -1;

	graphics = new Graphics();
	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}

	ShowWindow(windowhandle, nCmdShow);

#pragma region GameLoop
	//For Demo2, we're going to draw a ball on the screen
	float y = 0.0;
	float ySpeed = 0.0f;

	//Below, we have essentially an infinite loop that will keep the window running and will dispatch/show messages
	//As many people will tell you, most Windows you see are just infinite loops waiting for some kind of work-flow or 
	//system-based interuption.

	//Note - Our message handling has changed from the first demo code.
	//Here, we use a PeekMessage to avoid locking the graphics/windoProc
	//when a message has to be dispatched.
	MSG message;
	message.message = WM_NULL; //Do not have this set to WM_QUIT, which has a specific context
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			//This allows us to send a message to the WindowProc IF there is one
			DispatchMessage(&message);
		else
		{
			//Update Routine... note we're doing math on the circle!
			ySpeed += 1.0f;
			y += ySpeed;
			if (y > 600)
			{
				y = 600; //keep the ball from dropping below the screen
				ySpeed = -30.0f; //What does this do?
			}

			//Render Routine... note we're just drawing the circle here! It moves because of y (see below)
			graphics->BeginDraw();
			graphics->ClearScreen(0.0f, 0.0f, 0.5f);
			graphics->DrawCircle(
				375.0f, y, 50.0f, 1.0f, 1.0f, 1.0f, 1.0f);
			graphics->EndDraw();

		}
	}

#pragma endregion
	delete graphics;
	return 0;
}