#pragma once

#include <glm\glm.hpp>

class Tile
{
public:
	enum Type {
		Void,
		Ground,
		Rock,
		Iron,
		Gold
	};

	Tile();
	Tile(glm::vec2 pos, Type t);

	glm::vec2 getPosition();
	Type getType();
	void setType(Type t);
	void setTexRect(glm::vec4 rect);
	glm::vec4 getTexRect();
	
	bool needsUpdate();

private:
	glm::vec2 position;
	Type tileType;
	glm::vec4 texRect;
	bool needUpdate;
};
