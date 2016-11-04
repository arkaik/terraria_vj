#ifndef _ESQUELETILLO_INCLUDE
#define _ESQUELETILLO_INCLUDE

#include "ShaderProgram.h"
#include "TileMap.h"
#include "Sprite.h"
#include "EstadoEsq.h"
#include "Player.h"

class Esqueletillo : public EnemigoBase
{
public:
	Esqueletillo(Player* p, const glm::ivec2& peq, int vida);
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getMapPosition();
	glm::ivec2 getPosition();
	glm::vec2 getRealPosition();
private:
	glm::ivec2 tileMapDispl, posEsq;
	Player* player;
	Texture spritesheet;
	TileMap* map;
	EstadoEsq* estado;
};
#endif
