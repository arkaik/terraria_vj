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
};

#endif
