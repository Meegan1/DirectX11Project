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

	ID3D11Buffer* squareIndexBuffer;
	ID3D11Buffer* squareVertBuffer;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11VertexShader* VS;
	ID3D11PixelShader* PS;
	ID3D10Blob* VS_Buffer;
	ID3D10Blob* PS_Buffer;
	ID3D11InputLayout* vertLayout;
	ID3D11Buffer* cbPerObjectBuffer;

	ID3D11ShaderResourceView* CubesTexture;
	ID3D11SamplerState* CubesTextSamplerState;

	ID3D11BlendState* Transparency;
	ID3D11RasterizerState* CCWcullMode;
	ID3D11RasterizerState* CWcullMode;


	HWND hwnd;
	const int Width, Height;
	
	HRESULT hr;

	XMMATRIX WVP, World, camView, camProjection;
	XMVECTOR camPosition, camTarget, camUp;

	XMMATRIX cube1World, cube2World, Rotation, Scale, Translation;

	float rot = 0.01f;

	//Create effects constant buffer's structure//
	struct cbPerObject
	{
		XMMATRIX WVP;
	};
	cbPerObject cbPerObj;

	//Vertex Structure and Vertex Layout (Input Layout)//
	struct Vertex	//Overloaded Vertex Structure
	{
		Vertex() {}
		Vertex(float x, float y, float z, float u, float v)
			: pos(x, y, z), texCoord(u, v) {}

		XMFLOAT3 pos;
		XMFLOAT2 texCoord;
	};
	D3D11_INPUT_ELEMENT_DESC layout[2] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
};