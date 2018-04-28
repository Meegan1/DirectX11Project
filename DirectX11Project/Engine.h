#pragma once
#include <windows.h>
#include "Version.hpp"
#include <iostream>
#include <string>
#include "Renderer.h"
#include "hrt.h"

using std::cout;

LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

class Engine
{
public:

	Engine(HINSTANCE hInstance, int nShowCmd);
	~Engine();
	bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed);
	bool AttachConsole();
	int Run();

private:
	LPCTSTR WndClassName = L"firstwindow"; // window class name
	HWND hwnd = nullptr; // window handler

	const int Width = 800; // define width of window
	const int Height = 600; // define height of window

	Renderer *renderer;
};

