#ifndef _ESTAR_ESQ_INCLUDE
#define _ESTAR_ESQ_INCLUDE

#include "EstadoEsq.h"
class EstarEsq : public EstadoEsq {
public:
	EstarEsq(glm::vec2* posP, glm::ivec2* pe, const glm::ivec2& tMD, Sprite* sp, TileMap* m);
	EstadoEsq* cambiarEstado();
	void update(int deltaTime);
private:
	bool jugadorCerca();
	glm::ivec2 posInicial;
	static const float radioDeteccionPlayer;
	bool haciaIzq;
	static const float distanciaRecorrido;
};

#endif
