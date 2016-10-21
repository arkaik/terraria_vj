#pragma once
#include "Sprite.h"
#include "TileMap.h"
class inventario
{
public:
	inventario();
	~inventario();
private:
	glm::ivec2 tileMapDispl, pos;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

