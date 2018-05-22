//
//  PathsOrderRandomizer.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsOrderRandomizer.hpp"

#include "Utils/Utils.hpp"

#include <algorithm>

Instruction * PathsOrderRandomizer::get()
{
	return new PathsOrderRandomizer();
}

/// OK FOR V2

std::vector<VectorImage *> PathsOrderRandomizer::execute(std::vector<VectorImage *> &vectorImages)
{
	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			std::random_shuffle(shape.getPaths()->begin(), shape.getPaths()->end(), Utils::rand);
		}
	}

	return vectorImages;
}
