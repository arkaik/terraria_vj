#pragma once

#define INV_WIDTH 10
#define INV_HEIGHT 5

#include "Sprite.h"

class Inventory {
public:
	void init(ShaderProgram &sp);
	void update(int deltatime);
	void render();
	void selectObject(int s);

private:
	Texture tex;
	// Sprites dels backgrounds de l'inventari
	std::vector<vector<Sprite*> > inv_back;
	//Sprites dels objectes accesibles de l'inventari
	std::vector<vector<Sprite*> > inv_obj;
	//Posicions centrals de cada casella de l'inventari
	std::vector<vector<glm::vec2> > inv_mid;

	//Inventari obert
	bool opened;
	//Objecte seleccionat
	int selected;
};