#include "disc/graphics/GraphicsContext.h"
#include "disc/graphics/Pipeline.h"
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
		auto geometry = square.generateGeometry(window.getGraphicsContext());
		auto pipeline = window.getGraphicsContext().addPipeline();
		pipeline->addVAO(geometry);
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
