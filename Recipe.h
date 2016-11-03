#pragma once

#include <vector>
#include <string>
#include "Item.h"
#include "GameObject.h"

using namespace std;

struct Component
{
	string prod;
	int qty;
};

class Recipe
{
public:
	Recipe();
	Recipe(vector<string> vs, vector<int> vq);
	Recipe(Item i, vector<Component> vc);
	Recipe(vector<Component> vc);
	Recipe(Item i);
	~Recipe();

	void setComponents(vector<string> vs, vector<int> vq);
	void setComponents(vector<Component> vc);
	void addComponent(string p, int q);
	Item getType();
	bool canBuild(vector<vector<GameObject*> > vgo);
	void useComponents(vector<vector<GameObject*> > vgo);

private:
	vector<Component> components;
	Item itobj;
};
