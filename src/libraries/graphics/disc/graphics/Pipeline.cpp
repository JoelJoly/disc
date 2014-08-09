#include "disc/graphics/Pipeline.h"

#include "disc/graphics/VertexArrayObject.h"

#include <deque>

using namespace disc;
using namespace disc::graphics;

struct Pipeline::PImpl
{
	std::deque<std::shared_ptr<VertexArrayObject>> vaos_;
};

Pipeline::Pipeline()
	: pImpl_(new PImpl())
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::addVAO(std::shared_ptr<VertexArrayObject> vao)
{
	pImpl_->vaos_.emplace_back(vao);
}

void Pipeline::render() const
{
	for (const auto& vao : pImpl_->vaos_)
	{
		vao->render();
	}
}
