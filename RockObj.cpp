#include "RockObj.h"

RockObj::RockObj()
{
	setName("Rock");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(32, 160, 32, 32), GameObject::program));
	setAccumulate(true);
}

void RockObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{
}
