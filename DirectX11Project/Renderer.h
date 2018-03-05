#pragma once

//Include and link appropriate libraries and headers//
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>

#include <iostream>
using std::cout;

class Renderer
{
public:
	Renderer(HWND hWindow, HINSTANCE hInstance, int Width, int Height);
	~Renderer();

	bool InitializeDirect3d11App(HINSTANCE hInstance);
	void ReleaseObjects();
	bool InitScene();
	void UpdateScene();
	void DrawScene();

private:
	IDXGISwapChain * SwapChain;
	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* d3d11DevCon;
	ID3D11RenderTargetView* renderTargetView;

	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	int colormodr = 1;
	int colormodg = 1;
	int colormodb = 1;

	HWND hwnd;
	const int Width, Height;
};

