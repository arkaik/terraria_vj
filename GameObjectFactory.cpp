#include "GameObjectFactory.h"

GameObject * GameObjectFactory::createTileObject(Tile::Type t)
{
	if (t == Tile::Ground) return new GroundObj();
	else if (t == Tile::Rock) return new RockObj();
	else if (t == Tile::Gold) return new GoldOreObj();
	else if (t == Tile::Iron) return new IronOreObj();
	return nullptr;
}
