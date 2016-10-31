#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button, int x, int y);
	void mouseRelease(int button, int x, int y);
	void bubble_event();
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	bool getReleasedKey(int key);
	bool getMouseKey(int key) const;
	bool getPressedMouseKey(int key);
	bool getReleasedMouseKey(int key);
	glm::ivec2 getMousePosition();

private:
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	bool rel_keys[256]; //Release keys
	glm::ivec2 mouse_pos;
	bool mouse_btn[3];
	bool pres_mouse_btn[3];
	bool rel_mouse_btn[3];
	bool bubble_mouse_event;
};


#endif // _GAME_INCLUDE


