#ifndef _ESTADO_INCLUDE
#define _ESTADO_INCLUDE

#include <glm/glm.hpp>
#include "Scene.h"
#include "Sprite.h"

class Estado {
public:
	Estado(Scene* sc, glm::ivec2* posEnemigo,const glm::ivec2& tMD, Sprite* sp);
	virtual Estado* cambiarEstado() abstract;
	void setPosition(glm::ivec2* pe);
	void setSprite(Sprite* sp);
	virtual void update(int deltaTime) abstract;
protected:
	Scene* escena;
	glm::ivec2* posEnemigo;//pos relativa sin multiplicar por tileSize
	Sprite* spEnem;
	glm::ivec2 tileMapDisplay;
	glm::vec2 getCoordsRealesEnem();
};

#endif