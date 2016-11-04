#ifndef _ATACAR_ESQ_INCLUDE
#define _ATACAR_ESQ_INCLUDE

#include "EstadoEsq.h"
class AtacarEsq : public EstadoEsq {
public:
	AtacarEsq(Player* p, glm::ivec2* posEsq, const glm::ivec2& tMD, Sprite* sp, TileMap* t);
	EstadoEsq* cambiarEstado();
	void update(int deltaTime);
private:
	void perseguir(int deltaTime);
	static const float velocidad;
	float direccionX;
	void direccion();
};

#endif
