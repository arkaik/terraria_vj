#pragma once
#include <cmath>
#include <glm/glm.hpp>
#include <string>
#include "Sprite.h"

class EnemigoBase {
public:
	EnemigoBase();
	EnemigoBase(int vida);
	int getVida();
	void setVida(int vida);
	bool estaMuerto();
	void disminuirVida(int dis);
	glm::vec2 getPosition();
	std::string getName();
	virtual void lastAction();
	int getMaxVida();
	void setInCollisionList(bool b);
	virtual float getWidth();
	virtual float getHeight();
protected:
	int vidaMax;
	int vida;
	glm::vec2 posEnemigo;
	std::string name;
	bool inCollisionList;
	Sprite* sprite;
};

