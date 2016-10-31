#pragma once

#include "GameObject.h"

class IronOreObj : public GameObject
{
public:
	IronOreObj();

	void action(Player *player, glm::vec2 mouse_pos, TileMap *map);
};