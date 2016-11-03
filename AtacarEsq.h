#ifndef _ATACAR_ESQ_INCLUDE
#define _ATACAR_ESQ_INCLUDE

#include "EstadoEsq.h"
class AtacarEsq : public EstadoEsq {
public:
	AtacarEsq(glm::vec2* posPlayer, glm::ivec2* posEsq, const glm::ivec2& tMD, Sprite* sp, TileMap* t);
	EstadoEsq* cambiarEstado();
	void update(int deltaTime);
private:
	static const int numAtaques = 3;
	int ataquesRealizados;
	void hacerAtaque(int deltaTime);
	float velocidad;
	glm::vec2 direccion;
	glm::ivec2 posPlayerAnterior, posEnemigoAnterior;
	bool tocado;//Para cambiar solo una vez la aceleracion
};

#endif
