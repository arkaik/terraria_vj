#ifndef _ESTAR_INCLUDE
#define _ESTAR_INCLUDE

#include "Estado.h"
class Estar : public Estado {
public:
	Estar(Scene* sc, glm::ivec2* pe,const glm::ivec2& tMD, Sprite* sp);
	Estado* cambiarEstado();
	void update(int deltaTime);
private:
	bool jugadorCerca();
	//TODO: crear movimiento ciclico 
	glm::vec2 posInicial;
	static const int numCiclos = 2;
	int numVueltas;
	static const int distanciaCentro = 30;
	float angulo;
};

#endif
