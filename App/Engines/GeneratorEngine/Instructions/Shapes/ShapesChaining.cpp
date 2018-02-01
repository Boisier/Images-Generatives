#include "ShapesChaining.hpp"

Instruction * ShapesChaining::get()
{
	return new ShapesChaining();
}

/// OK FOR V2

std::vector<VectorImage *> ShapesChaining::execute(std::vector<VectorImage *> &vectorImages)
{
	glm::vec3 bezierPos, bezierDim, lastPos;

	for(VectorImage * vImage : vectorImages)
	{
		vImage->getCursor()->reset();

		for(Shape &shape : *vImage->getShapes())
		{
			shape.getCursor()->reset();
			lastPos = glm::vec3(0, 0, 0);

			for(Bezier &path : *shape.getPaths())
			{
				bezierPos = path.getPosition();
				bezierDim = path.getDimensions();

				//Move bezier to origin
				path.getCursor()
				->reset()
				->translate(-(bezierPos.x + bezierDim.x / 2.0), -(bezierPos.y + bezierDim.y / 2.0), 0);

				//Move bezier start point to origin
				path.getCursor()
				->translate(-path.getStartPoint());

				//Move besier to lastPos
				path.getCursor()
				->translate(lastPos);

				Bezier pathTemp = path;
				pathTemp.applyCursor();

				std::cout << glm::to_string(lastPos) << std::endl;
				lastPos = pathTemp.getEndPoint();
			}
		}
	}

	return vectorImages;
}
