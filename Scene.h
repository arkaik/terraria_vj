#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Inventory.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class Enemigo;

class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	glm::vec2 getPlayerPos();
	int radioDeteccionPlayer;
private:
	void initShaders();

private:
	Inventory *gui;
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	glm::mat4 ftcMatrix;
	Enemigo* enemigo;
};


#endif // _SCENE_INCLUDE

