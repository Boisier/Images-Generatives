//
//  ShapeSymY.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ShapeSymY.hpp"

Instruction * ShapeSymY::get()
{
	return new ShapeSymY();
}

std::vector<VectorImage *> ShapeSymY::execute(const std::vector<VectorImage *> &vectorImages)
{
	/*
	for()
		shape.getCursor()->rotate(180,0,1,0);
		shape.applyCursor();
	*/
	vectorImages[0]->applyCursor();
	std::vector<Shape> shapes=vectorImages[0]->getShapes();
/*
	std::cout<<"nombre de shapes récupéré: "<<shapes.size()<<std::endl;
	std::vector<Bezier> paths,buffer;
	std::vector<glm::vec3> points,transformed;
*/
	VectorImage* svg=new VectorImage();

/*
	glm::vec3 projected,projection,sympoint,
	symline=glm::vec3(1,0,0); // axe de symétrie
	float hauteur;
*/
	for(Shape shape:shapes){
		
		shape.getCursor()->rotate(180,0,1,0);
		shape.applyCursor();
		*svg<<shape;
	
/*
		paths = shape.getPaths();
		for(Bezier path : paths)
		{
			//path.applyCursor();
			points = {path.getStartPoint(),path.getStartHandle(),path.getEndHandle(),path.getEndPoint()};
	
			for(glm::vec3 point:points){
				hauteur=point.y;
				projected=glm::dot(symline,point)*symline;
				projection=projected-point;
				sympoint=point +2*projection;
				transformed.push_back(sympoint);//ici ca merde		
			}
			path= Bezier(transformed[0],transformed[1],
				transformed[2],transformed[3]);
			buffer.push_back(path);
			transformed.clear();
		}
		shape=Shape(buffer);
		*svg << shape;
		buffer.clear();
*/
	}
	

	return {svg};
}