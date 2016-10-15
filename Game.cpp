#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
	rel_keys[key] = true;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	
}

void Game::mousePress(int button, int x, int y)
{
	mouse_btn[button] = true;
	mouse_pos = glm::vec2(x, y);
}

void Game::mouseRelease(int button)
{
	mouse_btn[button] = false;
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

bool Game::getReleasedKey(int key)
{
	bool rel = rel_keys[key];
	if (rel) rel_keys[key] = false;
	
	return rel;
}

bool Game::getMouseKey(int key) const
{
	return mouse_btn[key];
}

glm::ivec2 Game::getMousePosition() {
	return mouse_pos;
}






