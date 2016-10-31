#pragma once

#include "GameObject.h"

class SilverOreObj : public GameObject
{
public:
	SilverOreObj();

	void action(Player * player, glm::vec2 mouse_pos, TileMap * map);

};
