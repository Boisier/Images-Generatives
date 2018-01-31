//
//  PathsOrientRandomizer.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsOrientRandomizer.hpp"
#include "Utils/Utils.hpp"

Instruction * PathsOrientRandomizer::get()
{
	return new PathsOrientRandomizer();
}

std::vector<VectorImage *> PathsOrientRandomizer::execute(const std::vector<VectorImage *> &vectorImages)
{
	vectorImages[0]->applyCursor();

	std::vector<Bezier> paths = vectorImages[0]->getBeziers();

	Shape shape;

	for(Bezier path : paths)
	{
		
		path.getCursor()->rotate(5.0 - Utils::rand(10),0,0,1);
		path.applyCursor();

		shape << path;
	}

	return {new VectorImage(shape)};
}
