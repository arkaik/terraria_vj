#include "GoldOreObj.h"

GoldOreObj::GoldOreObj()
{
	setName("Gold Ore");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(96, 160, 32, 32), GameObject::program));
	setAccumulate(true);
}

void GoldOreObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{
}
