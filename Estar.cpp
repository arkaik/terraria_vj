#include "Estar.h"
#include "Atacar.h"

Estar::Estar(const Scene& sc,const glm::ivec2& pe):Estado(sc, pe){}

Estado* Estar::cambiarEstado() {
	if (jugadorCerca()) return (Atacar*) this;
}

bool Estar::jugadorCerca() {
	return (posEnemigo.x - 20 < escena.getPlayerPos().x && escena.getPlayerPos().x < posEnemigo.x) ||
		(posEnemigo.x < escena.getPlayerPos().x && escena.getPlayerPos().x < posEnemigo.x + 20) || 
		(posEnemigo.y - 20 < escena.getPlayerPos().y && escena.getPlayerPos().y < posEnemigo.y) || 
		(posEnemigo.y < escena.getPlayerPos().y && escena.getPlayerPos().y < posEnemigo.y + 20);
}