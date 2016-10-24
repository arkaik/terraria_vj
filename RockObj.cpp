#include "RockObj.h"

RockObj::RockObj()
{
	setName("Rock");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(32, 160, 32, 32), GameObject::program));
	setAccumulate(true);
}

void RockObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{
	Tile *t = map->getTile(mouse_pos.x, mouse_pos.y);
	if (t != nullptr && t->getType() == Tile::Void)
	{
		t->setType(Tile::Rock);
		decrementNum();
		map->updateLevel();
	}
}
