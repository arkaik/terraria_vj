#include "CopperOreObj.h"

CopperOreObj::CopperOreObj()
{
	setName("Copper Ore");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(128, 160, 32, 32), GameObject::program));
	setAccumulate(true);
}

void CopperOreObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{
}
