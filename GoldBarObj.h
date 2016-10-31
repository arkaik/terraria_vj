#pragma once

#include "GameObject.h"

class GoldBarObj : public GameObject
{
public:
	GoldBarObj();

	void action(Player *player, glm::vec2 mouse_pos, TileMap *map);

};
