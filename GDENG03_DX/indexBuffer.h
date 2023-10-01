#pragma once
#include <d3d11.h>

class deviceContext;

class indexBuffer
{
public:
	indexBuffer();
	~indexBuffer();

	bool load(void* list_indices, UINT size_list);
	UINT getSizeIndexList();
	bool release();

private:
	UINT m_size_list;
	ID3D11Buffer* m_buffer;

	friend class deviceContext;
};