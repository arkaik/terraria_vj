#pragma once

#include "GameObject.h"

class GoldOreObj : public GameObject
{
public:
	GoldOreObj();

	void action(Player *player, glm::vec2 mouse_pos, TileMap *map);
};