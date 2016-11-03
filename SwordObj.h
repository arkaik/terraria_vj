#pragma once

#include "GameObject.h"

class SwordObj : public GameObject
{
public:
	SwordObj();

	void action(Player *player, glm::vec2 mouse_pos, TileMap *map);
};