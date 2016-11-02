#include "GoldBarObj.h"

GoldBarObj::GoldBarObj()
{
	setName("Gold Bar");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(32, 64, 32, 32), GameObject::program));
	setAccumulate(true);
}

void GoldBarObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{

}
