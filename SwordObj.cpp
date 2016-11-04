#include "SwordObj.h"
#include "Player.h"

SwordObj::SwordObj()
{
	setName("Sword");
	setSprite(Sprite::createSprite("images/items.png", glm::vec4(0, 0, 32, 32), GameObject::program));
}

void SwordObj::action(Player * player, glm::vec2 mouse_pos, TileMap * map)
{
	list<EnemigoBase*> ce = *(player->getCloseEnemies());
	for (list<EnemigoBase*>::iterator i = ce.begin(); i != ce.end(); i++) {
		glm::vec2 ppos = player->getPosition();
		glm::vec2 epos = (*i)->getPosition();
		glm::ivec2 diff = glm::ivec2(std::abs(ppos.x - epos.x), std::abs(ppos.y - epos.y));
		float dist = std::sqrt(diff.x*diff.x + diff.y*diff.y);
		if (dist < 128) {
			(*i)->disminuirVida(3);
			if ((*i)->estaMuerto()) {
				(*i)->lastAction();
			}
		}
		else {
			(*i)->setInCollisionList(false);
			player->getCloseEnemies()->remove(*i);
		}
	}
}
