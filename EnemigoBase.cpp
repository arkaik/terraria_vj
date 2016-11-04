#include "EnemigoBase.h"

EnemigoBase::EnemigoBase()
{
	inCollisionList = false;
}

EnemigoBase::EnemigoBase(int v) {
	vida = v;
}

int EnemigoBase::getVida() { return vida; }
void EnemigoBase::setVida(int v) { vida = v; }
bool EnemigoBase::estaMuerto() { return vida == 0; }
void EnemigoBase::disminuirVida(int dis) { 
	vida = vida-dis;
	if (vida < 0) vida = 0;
}

glm::vec2 EnemigoBase::getPosition()
{
	return posEnemigo;
}

std::string EnemigoBase::getName()
{
	return name;
}

void EnemigoBase::lastAction()
{

}

