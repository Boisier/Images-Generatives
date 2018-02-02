//
//  RessourcesEngine.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 20/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "RessourcesEngine.hpp"

#include "Core/AppObject.hpp"
#include "Importers/Importer.hpp"
#include "Elements/Asset.hpp"

#include <iostream>
#include <fstream>
#include <string>


bool RessourcesEngine::m_instanciated = false;

/**
 * Instanciate the engine as a Singleton
 */
void RessourcesEngine::instanciate()
{
	if(m_instanciated)
		return;

	App->ressourcesEngine = new RessourcesEngine();

	m_instanciated = true;
}


RessourcesEngine::RessourcesEngine()
{
	//Init FreeType Library
	if(FT_Init_FreeType( &m_FTLibrary ))
	{
		throw std::runtime_error("Could not load FreeType.");
	}
}



rId RessourcesEngine::loadAsset(const std::string &path, const ressourceType &type)
{
	std::string assetPath = buildPath(path, type);

	//Is this asset already loaded ?
	if(m_loadedPaths.find(assetPath) != m_loadedPaths.end())
		return m_loadedPaths[assetPath];

	//Load the asset
	//check if file is present
	if(!fileExist(assetPath))
		throw std::runtime_error("Error loading " + path + "\nThe file could not be found at " + assetPath + "\n");

	//Get importer for the asset
	Importer * importer = getImporter(type);

	//Import the asset
	Asset * newAsset = importer->getAsset(assetPath);

	//Free the importer
	delete importer;

	//store the asset
	rId newAssetId = App->genUUID();

	m_assets.insert(std::pair<rId, Asset *>(newAssetId, newAsset));
	m_loadedPaths.insert(std::pair<std::string, rId>(assetPath, newAssetId));

	//return the asset ID
	return newAssetId;
}

Asset * RessourcesEngine::getAsset(const rId &assetID)
{
	//Is this asset already loaded ?
	if(m_assets.find(assetID) == m_assets.end())
		throw std::runtime_error("Error fetching ressource. The ressource #" + boost::uuids::to_string(assetID) + " does not exist.");

	return m_assets[assetID];
}

bool RessourcesEngine::fileExist(const std::string &filePath)
{
	std::ifstream file(filePath);

	if(file)
		return true;

	return false;
}

void RessourcesEngine::removeAsset(const rId &assetID)
{
	//Is this asset loaded ?
	if(m_assets.find(assetID) == m_assets.end())
		throw std::runtime_error("Error removing ressource. The ressource #" + boost::uuids::to_string(assetID) + " does not exist.");

	//Free the asset
	delete m_assets[assetID];
	m_assets[assetID] = nullptr;

	//Erase from engine
	m_assets.erase(assetID);

	for(std::map<std::string, rId>::const_iterator entry = m_loadedPaths.begin(); entry != m_loadedPaths.end(); ++entry)
	{
		if(entry->second != assetID)
			continue;

		m_loadedPaths.erase(entry);
		return;
	}
}

RessourcesEngine::~RessourcesEngine()
{
	for(std::map<rId, Asset *>::iterator it = m_assets.begin(); it != m_assets.end(); ++it)
	{
		delete (*it).second;
	}
}




/////////
//PRIVATE

Importer * RessourcesEngine::getImporter(const ressourceType &type)
{
	switch (type)
	{
		case  IMAGE: return new ImageImporter();  break;
		case SHADER: return new ShaderImporter(); break;
		case  SOUND: return new ImageImporter();  break;
		case   MESH: return new MeshImporter();   break;
		case   FONT: return new FontImporter();   break;
		case VECTOR: return new SVGImporter();    break;
		case   JSON: return new JSONImporter();	  break;
		default: throw std::runtime_error("No Importer Found !"); break;
	}
}


std::string RessourcesEngine::buildPath(const std::string &file, const ressourceType &type)
{
	std::string prefix;

	switch (type)
	{
		case IMAGE: prefix = "assets/images/"; break;
		case SHADER: prefix = "assets/shaders/"; break;
		case SOUND: prefix = "assets/sounds/"; break;
		case MESH: prefix = "assets/meshs/"; break;
		case FONT: prefix = "assets/fonts/"; break;
		case VECTOR: prefix = "assets/SVG/"; break;
		case JSON: prefix ="assets/JSON/"; break;
	}

	return App->getAppPath() + prefix + file;
}
