#ifndef _ESTAR_INCLUDE
#define _ESTAR_INCLUDE

#include "Estado.h"
class Estar : public Estado {
public:
	static Estar &instance(const Scene& sc, const glm::ivec2& pe) {
		static Estar e(sc, pe);
		return e;
	}
	Estar(const Scene& sc, const glm::ivec2& pe);
	virtual Estado* cambiarEstado();
private:
	bool jugadorCerca();

};

#endif
