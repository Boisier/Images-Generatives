//
//  ImageImporter.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 20/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef ImageImporter_hpp
#define ImageImporter_hpp

/////////////////////
//Forward declaration
class Asset;

#include "Importer.hpp"

/**
 Import an image (PNG, JPG)
 */
class ImageImporter: public Importer
{
public:
	Asset * getAsset(const std::string &path);
	~ImageImporter();
private:
	
};

#endif /* ImageImporter_hpp */
