#include "disc/graphics/Rectangular.h"

#include "disc/graphics/ElementArray.h"
#include "disc/graphics/VertexArrayObject.h"
#include "disc/graphics/VertexAttribArray.h"

using namespace disc;
using namespace disc::graphics;

struct Rectangular::PImpl
{
	PImpl(float width, float height, float depth)
		: width_(width)
		, height_(height)
		, depth_(depth)
	{
	}

	float width_;
	float height_;
	float depth_;
};

Rectangular::Rectangular(float width, float height, float depth)
	: pImpl_(new PImpl(width, height, depth))
{
}

Rectangular::~Rectangular()
{
}

void Rectangular::setDepth(float depth)
{
	pImpl_->depth_ = depth;
}

std::shared_ptr<VertexArrayObject> Rectangular::generateGeometry(GraphicsContext& graphicsContext) const
{
	std::unique_ptr<VertexArrayObject> vao(new VertexArrayObject(graphicsContext));
	VertexAttribArray& positions = vao->addVertexAttrib();
	float halfWidth = pImpl_->width_ * 0.5f;
	float halfHeight = pImpl_->height_ * 0.5f;
	float positionData[] = 
	{
		-halfWidth, -halfHeight, pImpl_->depth_, 1.f,
		-halfWidth, +halfHeight, pImpl_->depth_, 1.f,
		+halfWidth, +halfHeight, pImpl_->depth_, 1.f,
		+halfWidth, -halfHeight, pImpl_->depth_, 1.f,
	};
	positions.setData(&positionData[0], sizeof(positionData)/sizeof(float));
	uint8_t indices[] = 
	{
		0, 1, 2,
		2, 3, 0
	};
	vao->getElementArray().setData(&indices[0], sizeof(indices)/sizeof(uint8_t));
	vao->compile();
	return std::shared_ptr<VertexArrayObject>(vao.release());
}
