#pragma once

#include "Tile.h"
#include "GroundObj.h"
#include "RockObj.h"
#include "IronOreObj.h"
#include "GoldOreObj.h"

class GameObjectFactory
{
public:

	static GameObjectFactory &instance()
	{
		static GameObjectFactory G;

		return G;
	}

	GameObject* createTileObject(Tile::Type t);

private:

};



