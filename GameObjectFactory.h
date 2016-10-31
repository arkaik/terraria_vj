#pragma once

#include "Tile.h"
#include "GroundObj.h"
#include "RockObj.h"
#include "IronOreObj.h"
#include "GoldOreObj.h"
#include "SilverOreObj.h"
#include "CopperOreObj.h"
#include "IronBarObj.h"
#include "GoldBarObj.h"
#include "Item.h"

class GameObjectFactory
{
public:

	static GameObjectFactory &instance()
	{
		static GameObjectFactory G;

		return G;
	}

	GameObject* createTileObject(Tile::Type t);
	GameObject* createItemObject(Item i);
private:

};



