#pragma once
#include "d3d11.h"

class deviceContext;

class constantBuffer
{
public:
	constantBuffer();
	~constantBuffer();
	bool load(void* buffer, UINT size_buffer);
	void update(deviceContext* context, void* buffer);
	bool release();

private:
	ID3D11Buffer* m_buffer;

	friend class deviceContext;
};