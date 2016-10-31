#include "Estar.h"
#include "Atacar.h"
#include "Enemigo.h"
#include <iostream>

Estar::Estar(Scene* sc,glm::ivec2* pe, const glm::ivec2& tMD, Sprite* sp):Estado(sc, pe,tMD, sp){}
Estado* Estar::cambiarEstado() {
	if (jugadorCerca()) {
		std::cout << "cambio a atacar" << std::endl;
		return new Atacar(escena, posEnemigo,tileMapDisplay,spEnem);
	}
	return this;
}

bool Estar::jugadorCerca() {
	int rdp = escena->radioDeteccionPlayer;
	//x+y = rdp es la circumferencia si x^2+y^2 <= rdp^2 esta dentro sino fuera
	glm::vec2 posP = escena->getPlayerPos();
	glm::vec2 posEnem = getCoordsRealesEnem();
	glm::vec2 pp = glm::vec2(posP.x - posEnem.x, posP.y - posEnem.y);
	return pp.x*pp.x + pp.y*pp.y <= rdp*rdp;
}

void Estar::update(int deltaTime) {

}