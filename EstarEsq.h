#ifndef _ESTAR_ESQ_INCLUDE
#define _ESTAR_ESQ_INCLUDE

#include "EstadoEsq.h"
class EstarEsq : public EstadoEsq {
public:
	EstarEsq(Player* p, glm::ivec2* pe, const glm::ivec2& tMD, Sprite* sp, TileMap* m);
	EstadoEsq* cambiarEstado();
	void update(int deltaTime);
private:
	glm::ivec2 posInicial;
	bool haciaIzq;
	static const float distanciaRecorrido;
};

#endif
