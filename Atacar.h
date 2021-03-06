#ifndef _ATACAR_INCLUDE
#define _ATACAR_INCLUDE

#include "Estado.h"
class Atacar : public Estado {
public:
	Atacar(Scene* sc, glm::ivec2* pe, const glm::ivec2& tMD, Sprite* sp, int* vida);
	Estado* cambiarEstado();
	void update(int deltaTime);
	static const int radioTocaJugador = 2;
private:
	static const int numAtaques = 3;
	int ataquesRealizados;
	void hacerAtaque(int deltaTime);
	float velocidad, velocidadFuria;
	glm::vec2 direccion;
	glm::ivec2 posPlayerAnterior, posEnemigoAnterior;
	bool tocado;//Para cambiar solo una vez la aceleracion
	bool distanciaActualVsDistanciaAnterior(const glm::vec2 posP);
	bool furioso;
};

#endif
