#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "BasicScene.h"
#include "SoundController.h"
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Inventory.h"
#include "Health.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class Enemigo;

class Scene : public BasicScene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	BasicScene* changeState();
	glm::vec2 getPlayerPos();
	glm::ivec2 getPlayerPosition();
	int radioDeteccionPlayer;
private:
	void initShaders();

private:
	Inventory *gui;
	Health *gui2;
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	glm::mat4 ftcMatrix;
	Enemigo* enemigo;

	Sprite* background;
};


#endif // _SCENE_INCLUDE

