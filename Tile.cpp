#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(glm::vec2 pos, Type t)
{
	position = pos;
	tileType = t;
	needUpdate = false;
}

glm::vec2 Tile::getPosition()
{
	return position;
}

Tile::Type Tile::getType()
{
	return tileType;
}

void Tile::setType(Type t)
{
	tileType = t;
	needUpdate = true;
}

void Tile::setTexRect(glm::vec4 rect)
{
	texRect = rect;
}

glm::vec4 Tile::getTexRect()
{
	return texRect;
}

bool Tile::needsUpdate()
{
	return needUpdate;
}

void Tile::setNeedUpdate(bool b)
{
	needUpdate = b;
}
