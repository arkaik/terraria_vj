#pragma once

#include "Text.h"
#include "GameObject.h"
#include <vector>

using namespace std;

class Health
{
public:
	Health();
	~Health();

	void init(ShaderProgram &sp);
	void update(int deltatime);
	void render();

	void decrementLife();
	void decrementLife(int hp);
	void incrementLife();

	int getPoints();
private:
	Texture tex;
	// Sprites dels cor
	std::vector<Sprite*> h_cor;
	//Posicions centrals de cada cor
	std::vector<glm::vec2> h_mid;
	Sprite* thealth;
	int health_points;

};
