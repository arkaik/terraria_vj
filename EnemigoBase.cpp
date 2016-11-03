#include "EnemigoBase.h"

EnemigoBase::EnemigoBase(int v) {
	vida = v;
}

int EnemigoBase::getVida() { return vida; }
void EnemigoBase::setVida(int v) { vida = v; }
bool EnemigoBase::estaMuerto() { return vida == 0; }
void EnemigoBase::disminuirVida(int dis) { vida = max(vida-dis,0); }

bool max(int a, int b) { return (a > b) ? a : b; }
