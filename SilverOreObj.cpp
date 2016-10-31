#include "SilverOreObj.h"

SilverOreObj::SilverOreObj()
{
	setName("Silver Ore");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(64, 160, 32, 32), GameObject::program));
	setAccumulate(true);
}

void SilverOreObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{
}
