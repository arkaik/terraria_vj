#include "IronOreObj.h"

IronOreObj::IronOreObj()
{
	setName("Iron Ore");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(160, 160, 32, 32), GameObject::program));
	setAccumulate(true);
}

void IronOreObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{
}
