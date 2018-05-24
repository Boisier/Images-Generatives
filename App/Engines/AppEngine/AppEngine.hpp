//
//  AppEngine.hpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef AppEngine_hpp
#define AppEngine_hpp

#include "libraries.hpp"

struct keyboard
{
	bool A = false;
	bool B = false;
	bool C = false;
	bool D = false;
	bool E = false;
	bool F = false;
	bool G = false;
	bool H = false;
	bool I = false;
	bool J = false;
	bool K = false;
	bool L = false;
	bool M = false;
	bool N = false;
	bool O = false;
	bool P = false;
	bool Q = false;
	bool R = false;
	bool S = false;
	bool T = false;
	bool U = false;
	bool V = false;
	bool W = false;
	bool X = false;
	bool Y = false;
	bool Z = false;
	bool UP = false;
	bool DOWN = false;
	bool LEFT = false;
	bool RIGHT = false;
	bool ESC = false;
	bool BACKSPACE = false;
	bool ENTER = false;
	bool SPACE = false;
};

struct mouse {
	int scrollY = 0;
	int scrollX = 0;
	bool leftBtn = false;
	bool rightBtn = false;
	glm::vec2 pos;
};

struct window {
	bool resized = false;
};

/**
 Holds key features of the apps such as events, scene execution and rendering, etc.
 */
class AppEngine
{
public:
	/**
	 Create the AppEngine Singleton in the AppObject
	 */
	static void instanciate();

	////////
	//Scenes

	//Catch new events then execute all scenes on the AppObj
	void executeScenes();
	void renderScenes();

	//////////
	//Keyboard

	/**
	 Return the keyboard events struct
	 @return The keyboard structure
	 */
	inline keyboard getKeys() const { return m_keys; };

	/**
	 Return the mouse events struct
	 @return The mouse structure
	 */
	inline mouse getMouse() const { return m_mouse; };

	/**
	 Return the window events struct
	 @return The mouse structure
	 */
	inline window getWindow() const { return m_window; };

	/**
	 Set all keys an not pressed
	 */
	inline void flushKeys() { m_keys = {}; };

	/**
	 Set all keys an not pressed
	 */
	void flushMouse();

private:
	//Singleton
	static bool m_instanciated;
	AppEngine();

	////////
	//Events
	keyboard m_keys;
	mouse m_mouse;
	window m_window;
	void parseEvents();
	void windowEvents(const SDL_Event &event);
	void keyBoardEvents(const SDL_Event &event);
	void mouseEvents(const SDL_Event &event);
};

#endif /* AppEngine_hpp */
