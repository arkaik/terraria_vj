#pragma once

#include "GameObject.h"

class IronBarObj : public GameObject
{
public:
	IronBarObj();

	void action(Player *player, glm::vec2 mouse_pos, TileMap *map);

};
