#ifndef _ESTADO_INCLUDE
#define _ESTADO_INCLUDE

#include <glm/glm.hpp>
#include "Scene.h"

class Estado {
public:
	Estado(const Scene& sc, const glm::ivec2& posEnemigo);
	virtual Estado* cambiarEstado() abstract;
protected:
	Scene escena;
	glm::ivec2 posEnemigo;
};

#endif