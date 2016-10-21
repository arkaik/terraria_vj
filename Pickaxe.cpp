#include "Pickaxe.h"
#include "Player.h"
#include "GameObjectFactory.h"

Pickaxe::Pickaxe()
{
	setName("Iron Pickaxe");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(32, 0, 32, 32), GameObject::program));
}

void Pickaxe::action(Player *player, glm::vec2 mouse_pos, TileMap *map)
{
	Tile *t = map->getTile(mouse_pos.x, mouse_pos.y);
	if (t != nullptr && t->getType() != Tile::Void )	{
 		GameObject* go = GameObjectFactory::instance().createTileObject(t->getType());
		if (go != nullptr) {
			player->addToInventory(go);
			t->setType(Tile::Type::Void);
			map->updateLevel();
		}
	}
}

