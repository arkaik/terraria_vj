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
	if (t != nullptr) {
		glm::vec2 tpos = t->getPosition();
		glm::vec2 ppos = player->getMapPosition() + glm::vec2(1, 1);
		glm::ivec2 dist = glm::vec2(abs(ppos.x - tpos.x), abs(ppos.y - tpos.y));
		bool lessdist = dist.x <= 3 && dist.y <= 3;
		if ( t->getType() != Tile::Void && lessdist) {
			SoundController::instance().playSound("../sounds/Dig_1.wav");
			GameObject* go = GameObjectFactory::instance().createTileObject(t->getType());
			if (go != nullptr) {
				player->addToInventory(go);
				t->setType(Tile::Type::Void);
				glm::vec2 tpos = t->getPosition();
				map->updateTile(tpos.y, tpos.x, Tile::Type::Void, glm::vec4(0.f));
			}
		}
	}
	
}

