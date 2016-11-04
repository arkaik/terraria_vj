#include "RockObj.h"

RockObj::RockObj()
{
	setName("Rock");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(32, 160, 32, 32), GameObject::program));
	setAccumulate(true);
}

void RockObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{
	Tile *t = map->getTile(mouse_pos.y, mouse_pos.x);
	if (t != nullptr && t->getType() == Tile::Void)
	{
		t->setType(Tile::Rock);
		decrementNum();
		glm::vec2 tpos = t->getPosition();
		map->updateTile(tpos.x, tpos.y, Tile::Type::Rock, t->getTexRect());
	}
}
