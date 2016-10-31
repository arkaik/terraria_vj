#pragma once

#include "GameObject.h"

class RockObj : public GameObject
{
public:
	RockObj();

	void action(Player *player, glm::vec2 mouse_pos, TileMap *map);
};