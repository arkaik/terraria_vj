#ifndef _ATACAR_INCLUDE
#define _ATACAR_INCLUDE

#include "Estado.h"
class Atacar : public Estado {
public:
	static Atacar &instance(const Scene& sc, const glm::ivec2& pe) {
		static Atacar a(sc, pe);
		return a;
	}
	Atacar(const Scene& sc, const glm::ivec2& pe);
	virtual Estado* cambiarEstado();
private:
	//bool jugadorCerca();
};

#endif
