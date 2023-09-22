#pragma once
#include "quadObject.h"
#include "window.h"

class swapChain;
class vertexBuffer;
class quadObject;

class appWindow : public  window
{
public:
	appWindow();
	~appWindow();

	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void onUpdate() override;

	swapChain* getSwapChain();
	vertexBuffer* getVertexBuffer();

	void drawObject();

private:
	swapChain* m_swap_chain;
	//vertexBuffer* m_vertex_buffer;

	void* m_shader_byte_code = nullptr;
	UINT m_size_shader = 0;

	quadObject test1;
	quadObject test2;
	quadObject test3;
};