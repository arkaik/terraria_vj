#include "SwordObj.h"

SwordObj::SwordObj()
{
	setName("Sword");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(0, 0, 32, 32), GameObject::program));
}

void SwordObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{

}
