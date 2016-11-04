#include "GroundObj.h"

GroundObj::GroundObj()
{
	setName("Ground");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(0, 160, 32, 32), GameObject::program));
	setAccumulate(true);
}

void GroundObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{
	Tile *t = map->getTile(mouse_pos.y, mouse_pos.x);
	if (t != nullptr && t->getType() == Tile::Void)
	{
		t->setType(Tile::Ground);
		decrementNum();
		glm::vec2 tpos = t->getPosition();
		map->updateTile(tpos.y, tpos.x, Tile::Type::Ground, t->getTexRect());
	}
}
