#include "disc/graphics/Rectangular.h"
#include "disc/graphics/VertexArrayObject.h"
#include "disc/graphics/Window.h"

#include <iostream>

int main(int arcg, void**argv)
{
	try
	{
		disc::graphics::Rectangular square(10.f, 10.f, -50.f);
		disc::graphics::Window window;
		window.show();
		std::shared_ptr<disc::graphics::VertexArrayObject> geometry = square.generateGeometry(window.getGraphicsContext());
		while (! window.aboutToClose())
		{
			window.processMessages();
			window.render();
			geometry->render();
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Uncatched exception: " << e.what() << std::endl;
	}
	return 0;
}
