#include "disc/graphics/Window.h"

#include <iostream>

int main(int arcg, void**argv)
{
	try
	{
		disc::graphics::Window window;
		window.show();
		while (! window.aboutToClose())
		{
			window.processMessages();
			window.render();
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Uncatched exception: " << e.what() << std::endl;
	}
	return 0;
}
