//
//  Igniter.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 21/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Igniter.hpp"

void Igniter::igniteAppObject(std::string appPath)
{
	//Get app path
	FilePath applicationPath(appPath.c_str());

	//Instanciate App
	AppObject::instanciate(applicationPath.dirPath());

	//Instanciate Engines
	AppEngine::instanciate();
	RessourcesEngine::instanciate();
	RenderEngine::instanciate();
}

void Igniter::igniteSDL(float width, float height)
{
	//////////////
	//INIT SDL
	if(0 != SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << SDL_GetError() << std::endl;
		return;
	}

	//Set OpenGL attribute
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8 );

	//Create window
	App->screenWidth = width;
	App->screenHeight = height;

	//TODO: Dynamic definition of title and dimensions
	App->mainWindow = SDL_CreateWindow(
							  "IMACMAN",                  		// window title
							  SDL_WINDOWPOS_UNDEFINED,        // initial x position
							  SDL_WINDOWPOS_UNDEFINED,        // initial y position
							  width,                              // width, in pixels
							  height,                              // height, in pixels
							  SDL_WINDOW_OPENGL                // require OpenGL
							  );

	//Confirm window creation
	if(!App->mainWindow) {
		std::cerr << SDL_GetError() << std::endl;
		return;
	}

	//Set SDL to useOpenGL
	SDL_GLContext glContext = SDL_GL_CreateContext(App->mainWindow);
	SDL_GL_MakeCurrent(App->mainWindow, glContext);

	//Init SDL Image
	int SDL_IMAGE_FLAGS = IMG_INIT_JPG|IMG_INIT_PNG;
	int SDL_IMAGE_LOADED_FLAGS = IMG_Init(SDL_IMAGE_FLAGS);

	if((SDL_IMAGE_LOADED_FLAGS&SDL_IMAGE_FLAGS) != SDL_IMAGE_FLAGS)
		throw std::runtime_error("SDL_image could not be loaded.");
}

void Igniter::igniteOpenGL()
{
	glewExperimental = GL_TRUE;
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
	  return;
	}

	//std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	//std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	glClearColor(0.0,0.0,0.0,0.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}
