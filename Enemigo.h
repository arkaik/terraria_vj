#pragma once
#include "Sprite.h"
#include "TileMap.h"
#include "Estado.h"
#include "Scene.h"
#include "EnemigoBase.h"


// Enemigo is basically a Sprite that represents the Enemigo. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Scene;

class Enemigo : public EnemigoBase
{
public:
	Enemigo(Scene* sc, const glm::ivec2 &pos);
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();
	void lastAction();
private:
	glm::ivec2 posEnemigo;
	glm::ivec2  tileMapDispl;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	Estado* estado;
	Scene* sc;
};
