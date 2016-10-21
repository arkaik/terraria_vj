#pragma once

#include "Sprite.h"
#include <vector>

using namespace std;

class Health
{
public:
	void init(ShaderProgram &sp);
	void update(int deltatime);
	void render();
private:
	Texture tex;
	// Sprites dels cor
	std::vector<Sprite*> h_cor;
	//Posicions centrals de cada cor
	std::vector<glm::vec2> h_mid;

};
