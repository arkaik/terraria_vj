#include "Atacar.h"

Atacar::Atacar(const Scene& sc, const glm::ivec2& pe) :Estado(sc, pe) {}
Estado* Atacar::cambiarEstado() {
	return this;
}