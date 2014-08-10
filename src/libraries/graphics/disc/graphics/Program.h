#ifndef DISC_GRAPHICS_PROGRAM_H
#define DISC_GRAPHICS_PROGRAM_H

#include <memory>

namespace disc
{
	namespace graphics
	{
		class GraphicsContext;

		class Program
		{
		public:
			explicit Program(GraphicsContext& context);
			~Program();

			void bind();

		private:
			struct PImpl;
			std::unique_ptr<PImpl> pImpl_;
		};
	}
}

#endif
