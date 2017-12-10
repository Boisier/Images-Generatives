//
//  main.hpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef main_h
#define main_h

#define FRAMERATE 30

//System includes
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

//OpenGL and friends
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>

//App core
#include "Core/AppObject.hpp"
#include "Core/Core.hpp"

//App Engines
#include "Engines/AppEngine/AppEngine.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"

#endif /* main_h */
