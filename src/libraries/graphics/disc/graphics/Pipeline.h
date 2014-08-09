#ifndef DISC_GRAPHICS_PIPELINE_H
#define DISC_GRAPHICS_PIPELINE_H

#include <memory>

namespace disc
{
	namespace graphics
	{
		class VertexArrayObject;

		class Pipeline
		{
		public:
			Pipeline();
			~Pipeline();

			void addVAO(std::shared_ptr<VertexArrayObject> vao);
			void render() const;

		private:
			struct PImpl;
			std::unique_ptr<PImpl> pImpl_;
		};
	}
}

#endif
