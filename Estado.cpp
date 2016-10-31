#include "Estado.h"

Estado::Estado(Scene* sc, glm::ivec2* pe,const glm::ivec2& tMD, Sprite* sp)
{
	escena = sc;
	setPosition(pe);
	setSprite(sp);
	tileMapDisplay = tMD;
}


void Estado::setPosition(glm::ivec2* pe) {
	posEnemigo = pe;
}

void Estado::setSprite(Sprite* sp) {
	spEnem = sp;
}

glm::vec2 Estado::getCoordsRealesEnem() {
	return glm::vec2(float(tileMapDisplay.x + posEnemigo->x), float(tileMapDisplay.y + posEnemigo->y));
}
