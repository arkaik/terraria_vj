#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Inventory.h"
#include "EnemigoBase.h"
#include "Health.h"
#include <list>


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setInventory(Inventory *inv);
	void setTileMap(TileMap *tileMap);
	void setHealth(Health* h);
	void decrementLife();
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();
	glm::vec2 getMapPosition();
	glm::ivec2 getPlayerPosition();
	void addToInventory(GameObject *go);
	void addEnemy(EnemigoBase* eb);
	std::list<EnemigoBase*> * getCloseEnemies();
	bool overlap(glm::vec4 bound);
	int getHealthPoints();
private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	Inventory *inventory;
	Health* heal;
	void whoOverlap();
	float radius;
	std::list<EnemigoBase*> collisionList;
	std::list<int> delays;
	int delayMax;
};


#endif // _PLAYER_INCLUDE


