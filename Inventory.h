#pragma once

#define INV_WIDTH 10
#define INV_HEIGHT 5

#include "GameObject.h"
#include "Text.h"
#include <algorithm>

class Inventory {
public:
	void init(ShaderProgram &sp);
	void update(int deltatime);
	void render();
	void selectObject(int s);
	GameObject* getSelectedObject();
	void addObject(GameObject *go);
	bool insideOpenedInventory(glm::vec2 p);

private:
	Texture tex;
	// Sprites dels backgrounds de l'inventari
	std::vector<vector <Sprite*> > inv_back;
	//Sprites dels objectes accesibles de l'inventari
	std::vector<vector <GameObject*> > inv_obj;
	//Posicions centrals de cada casella de l'inventari
	std::vector<vector<glm::vec2> > inv_mid;

	Text obj_name;

	//Inventari obert
	bool opened;
	//Objecte seleccionat
	int selected;
	//Espai lliure, si (-1,-1) no hi ha espai lliure
	glm::ivec2 free_space;
	//Objecte en drag&drop
	GameObject *drag_drop;

	void updateFreeSpace();
	GameObject* findObject(GameObject *go);
	glm::vec4 openedBounds;
};