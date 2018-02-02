//
//  FontImporter.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 28/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef FontImporter_hpp
#define FontImporter_hpp

/////////////////////
//Forward declaration
class Asset;

#include "Importer.hpp"

/**
 Import font file (TTF, OTF)
 */
class FontImporter: public Importer
{
public:
	Asset * getAsset(const std::string &path);
	~FontImporter();

private:

};

#endif /* FontImporter_hpp */
