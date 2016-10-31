#pragma once

#include <vector>
#include <string>
#include <map>
#include "Recipe.h"
#include "GameObject.h"
#include "Item.h"

using namespace std;

class RecipeBook
{
public:
	RecipeBook();
	
	void init();

	vector<Recipe*> getRecipesByObject(GameObject* go);
	vector<Recipe*> getRecipesByName(string ngo);

	static Item stringToItemType(string s);
private:
	vector< vector<string> > compoMatrix;
	map<string, Recipe*> recipeList;

	void initMatrix();
	void initRecipes();
};
