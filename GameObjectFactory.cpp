#include "GameObjectFactory.h"

GameObject * GameObjectFactory::createTileObject(Tile::Type t)
{
	if (t == Tile::Ground) return new GroundObj();
	else if (t == Tile::Rock) return new RockObj();
	else if (t == Tile::Gold) return new GoldOreObj();
	else if (t == Tile::Iron) return new IronOreObj();
	else if (t == Tile::Silver) return new SilverOreObj();
	else if (t == Tile::Copper) return new CopperOreObj();
	return nullptr;
}

GameObject * GameObjectFactory::createItemObject(Item i)
{
	if (i == Item::Ground) return new GroundObj();
	else if (i == Item::Rock) return new RockObj();
	else if (i == Item::Gold) return new GoldOreObj();
	else if (i == Item::Iron) return new IronOreObj();
	else if (i == Item::Silver) return new SilverOreObj();
	else if (i == Item::Copper) return new CopperOreObj();
	else if (i == Item::IronBar) return new IronBarObj();
	else if (i == Item::GoldBar) return new GoldBarObj();
	else if (i == Item::Sword) return new SwordObj();
	return nullptr;
}
