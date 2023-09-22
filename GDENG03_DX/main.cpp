#include "appWindow.h"

int main()
{
	appWindow app;
	if(app.init())
	{
		while(app.isRunning())
		{
			app.boadcast();
		}
	}

	return 0;
}