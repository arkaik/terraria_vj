#pragma once

#include "GameObject.h"

class CopperOreObj : public GameObject
{
public:
	CopperOreObj();

	void action(Player *player, glm::vec2 mouse_pos, TileMap *map);

};
