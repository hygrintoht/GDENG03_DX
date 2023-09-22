#pragma once
#include <Windows.h>

class window
{
public:

	window();
	~window();

	bool init();
	bool release();
	bool boadcast();

	bool isRunning();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

protected:
	HWND m_hwnd;
	bool m_is_run;
};