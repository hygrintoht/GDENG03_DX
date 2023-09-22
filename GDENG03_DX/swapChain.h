#pragma once
#include <d3d11.h>

class deviceContext;

class swapChain
{
public:
	swapChain();
	~swapChain();

	bool init(HWND hwnd, UINT width, UINT height);
	bool release();

	bool present(bool vsync);

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;

	friend class deviceContext;
};

 