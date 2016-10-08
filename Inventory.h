#pragma once

#include "Node.h"
#include "Sprite.h"

class Inventory : public Node {
public:
	void init(ShaderProgram sp);
	void render();

private:
	std::vector<Sprite> inv_back;
	std::vector<Sprite> inv_obj;
	Texture tex;
};