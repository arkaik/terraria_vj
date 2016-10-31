#include "IronBarObj.h"

IronBarObj::IronBarObj()
{
	setName("Iron Bar");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(96, 64, 32, 32), GameObject::program));
	setAccumulate(true);
}

void IronBarObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{
}
