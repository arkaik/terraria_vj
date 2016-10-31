#pragma once

#define INV_WIDTH 10
#define INV_HEIGHT 5

#include "GameObjectFactory.h"
#include "Text.h"
#include "RecipeBook.h"
#include <algorithm>
#include <cmath>
#include <set>

class Inventory {
public:
	void init(ShaderProgram &sp);
	void update(int deltatime);
	void render();
	void selectObject(int s);
	GameObject* getSelectedObject();
	void addObject(GameObject *go);
	bool insideOpenedInventory(glm::vec2 p);
	bool insideOpenedRecipe(glm::vec2 p);

private:
	Texture tex;
	ShaderProgram sprogram;
	//Sprites dels backgrounds de l'inventari
	std::vector<vector <Sprite*> > inv_back;
	//Sprites dels objectes accesibles de l'inventari
	std::vector<vector <GameObject*> > inv_obj;
	//Posicions centrals de cada casella de l'inventari
	std::vector<vector<glm::vec2> > inv_mid;
	
	//Set amb els noms dels objectes
	set<string> nameset;
	// Booleà per actualitzar receptes
	bool updateRecipes;
	//Sprites dels backgrounds de les receptes
	vector<Sprite*> rec_back;
	//Posicions centrals de cada casella de les receptes
	vector<glm::vec2> rec_mid;
	//Objectes accesibles per les receptes
	vector<GameObject*> rec_obj;
	// Vector de recetas escogidas
	vector<Recipe*> rec_rec;
	//'Llibre' de receptes
	RecipeBook rb;

	Text obj_name;

	//Inventari obert
	bool opened;
	//Objecte seleccionat
	int selected;
	//Espai lliure, si (-1,-1) no hi ha espai lliure
	glm::ivec2 free_space;
	//Objecte en drag&drop
	glm::vec2 swapObjectPos;

	void updateFreeSpace();
	GameObject* findObject(GameObject *go);
	glm::vec4 openedBounds;
	glm::vec4 recipesBounds;
};