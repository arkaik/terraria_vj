#ifndef _ABEJA_INCLUDE
#define _ABEJA_INCLUDE

#include "ShaderProgram.h"
#include "TileMap.h"
#include "Sprite.h"
#include "EstadoEsq.h"
#include "Player.h"

class Abeja : public EnemigoBase
{
public:
	Abeja(Player* p, const glm::ivec2& peq, int vida);
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, TileMap* m);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::ivec2 &pos);
	glm::vec2 getMapPosition();
	glm::ivec2 getPosition();
	glm::vec2 getRealPosition();
	float getWidth();
	float getHeight();
private:
	glm::ivec2 tileMapDispl, posAb;
	Player* player;
	Texture spritesheet;
	TileMap* map;
	bool Abeja::jugadorCerca();
	float radioDeteccionPlayer;
	int state;
	bool haAtacado;
	void hacerAtaque(int deltaTime);
	float velocidad;
	glm::vec2 direccion;
	glm::ivec2 posPlayerAnterior, posEnemigoAnterior;
	bool tocado;//Para cambiar solo una vez la aceleracion
	bool distanciaActualVsDistanciaAnterior(const glm::vec2 posP);
	int delay, delayMax;
};
#endif
