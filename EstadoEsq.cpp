#include "EstadoEsq.h"


EstadoEsq::EstadoEsq(Player* p, glm::ivec2* posEsq, const glm::ivec2& tMD, Sprite* sp, TileMap* m)
{
	player = p;
	setPosition(posEsq);
	setSprite(sp);
	tileMapDisplay = tMD;
	map = m;
	radioDeteccionPlayer = 10.0f*map->getTileSize();
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

bool EstadoEsq::jugadorCerca() {
	//x+y = rdp es la circumferencia si x^2+y^2 <= rdp^2 esta dentro sino fuera

	glm::vec2 posP = player->getPosition();//Coordenadas reales;
	glm::vec2 posE = glm::vec2(posEsq->x + float(tileMapDisplay.x), posEsq->y + float(tileMapDisplay.y));//Coordenadas reales;;
	glm::vec2 pp = glm::vec2(posP.x - posE.x, posP.y - posE.y);
	return pp.x*pp.x + pp.y*pp.y <= radioDeteccionPlayer*radioDeteccionPlayer;
}