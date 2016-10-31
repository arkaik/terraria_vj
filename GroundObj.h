#pragma once

#include "GameObject.h"

class GroundObj : public GameObject
{
public:
	GroundObj();

	void action(Player *player, glm::vec2 mouse_pos, TileMap *map);
};