#include "EstadoEsq.h"

EstadoEsq::EstadoEsq(glm::vec2* posP, glm::ivec2* posEsq, const glm::ivec2& tMD, Sprite* sp, TileMap* m)
{
	posPlayer = posP;
	setPosition(posEsq);
	setSprite(sp);
	tileMapDisplay = tMD;
	map = map;
}


void EstadoEsq::setPosition(glm::ivec2* pe) {
	posEsq = pe;
}

void EstadoEsq::setSprite(Sprite* sp) {
	spEsq = sp;
}

glm::vec2 EstadoEsq::getCoordsRealesEsq() {
	return glm::vec2(float(tileMapDisplay.x + posEsq->x), float(tileMapDisplay.y + posEsq->y));
}