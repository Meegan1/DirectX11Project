#pragma once

//Include and link appropriate libraries and headers//
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#pragma comment (lib, "D3D10_1.lib")
#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "D2D1.lib")
#pragma comment (lib, "dwrite.lib")

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>

#include <D3D10_1.h>
#include <DXGI.h>
#include <D2D1.h>
#include <sstream>
#include <dwrite.h>

#include <dinput.h>

#include <iostream>
#include "hrt.h"

#include <vector>
using std::cout;

class Renderer
{
public:
	Renderer(HWND hWindow, HINSTANCE hInstance, int Width, int Height);
	~Renderer();

	bool InitializeDirect3d11App(HINSTANCE hInstance);
	void ReleaseObjects();
	bool InitScene();
	void UpdateScene(double time);
	void DrawScene();

	bool InitD2D_D3D101_DWrite(IDXGIAdapter1 *Adapter);
	void InitD2DScreenTexture();
	void RenderText(std::wstring text);

	bool InitDirectInput(HINSTANCE hInstance);
	void DetectInput(double time);

	void UpdateCamera();

	void CreateSphere(int LatLines, int LongLines);

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
	ID3D11Buffer* cbPerFrameBuffer;

	ID3D11BlendState* Transparency;
	ID3D11RasterizerState* CCWcullMode;
	ID3D11RasterizerState* CWcullMode;

	//===============[SkyBox]========================
	ID3D11Buffer* sphereIndexBuffer;
	ID3D11Buffer* sphereVertBuffer;

	ID3D11VertexShader* SKYMAP_VS;
	ID3D11PixelShader* SKYMAP_PS;
	ID3D10Blob* SKYMAP_VS_Buffer;
	ID3D10Blob* SKYMAP_PS_Buffer;

	ID3D11ShaderResourceView* smrv;

	ID3D11DepthStencilState* DSLessEqual;
	ID3D11RasterizerState* RSCullNone;

	int NumSphereVertices;
	int NumSphereFaces;

	XMMATRIX sphereWorld;

	XMMATRIX Rotationx;
	XMMATRIX Rotationy;
	XMMATRIX Rotationz;

	// =============[Direct Input]===================
	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;

	DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;

	XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMMATRIX camRotationMatrix;
	XMMATRIX groundWorld;

	float moveLeftRight = 0.0f;
	float moveBackForward = 0.0f;

	float camYaw = 0.0f;
	float camPitch = 0.0f;

	// ===============[2D Font]=================
	ID3D10Device1 *d3d101Device;
	IDXGIKeyedMutex *keyedMutex11;
	IDXGIKeyedMutex *keyedMutex10;
	ID2D1RenderTarget *D2DRenderTarget;
	ID2D1SolidColorBrush *Brush;
	ID3D11Texture2D *BackBuffer11;
	ID3D11Texture2D *sharedTex11;
	ID3D11Buffer *d2dVertBuffer;
	ID3D11Buffer *d2dIndexBuffer;
	ID3D11ShaderResourceView *d2dTexture;
	IDWriteFactory *DWriteFactory;
	IDWriteTextFormat *TextFormat;

	std::wstring printText;


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
		XMMATRIX World;
	};
	cbPerObject cbPerObj;

	struct Light
	{
		Light()
		{
			ZeroMemory(this, sizeof(Light));
		}
		XMFLOAT3 dir;
		float pad;
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
	};

	Light light;

	struct cbPerFrame
	{
		Light  light;
	};
	cbPerFrame constbuffPerFrame;

	//Vertex Structure and Vertex Layout (Input Layout)//
	struct Vertex    //Overloaded Vertex Structure
	{
		Vertex() {}
		Vertex(float x, float y, float z,
			float u, float v,
			float nx, float ny, float nz)
			: pos(x, y, z), texCoord(u, v), normal(nx, ny, nz) {}

		XMFLOAT3 pos;
		XMFLOAT2 texCoord;
		XMFLOAT3 normal;
	};

	D3D11_INPUT_ELEMENT_DESC layout[3] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
};