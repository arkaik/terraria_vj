#ifndef _ESTADO_ESQ_INCLUDE
#define _ESTADO_ESQ_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"

class EstadoEsq {
public:
	EstadoEsq(Player* player, glm::ivec2* posEsq, const glm::ivec2& tMD, Sprite* sp, TileMap* m);
	virtual EstadoEsq* cambiarEstado() abstract;
	void setPosition(glm::ivec2* pe);
	void setSprite(Sprite* sp);
	virtual void update(int deltaTime) abstract;
protected:
	Player* player;
	glm::ivec2* posEsq;//pos relativa sin multiplicar por tileSize
	Sprite* spEsq;
	glm::ivec2 tileMapDisplay;
	glm::vec2 getCoordsRealesEsq();
	TileMap* map;
	static const float radioDeteccionPlayer;
	bool jugadorCerca();
};

#endif
