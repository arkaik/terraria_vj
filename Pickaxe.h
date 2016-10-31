#pragma once

#include "GameObject.h"

class Pickaxe : public GameObject
{
public:
	Pickaxe();

	void action(Player *player, glm::vec2 mouse_pos, TileMap *map);
};