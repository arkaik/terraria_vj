#include "RecipeBook.h"

RecipeBook::RecipeBook()
{
}

void RecipeBook::init()
{
	
	initMatrix();
	initRecipes();
}

void RecipeBook::initMatrix()
{
	compoMatrix = vector<vector<string> >(int(Item::Size), vector<string>(int(Item::Size)));
	compoMatrix[int(Item::Iron)][int(Item::Iron)] = "Iron Bar";
	compoMatrix[int(Item::Gold)][int(Item::Gold)] = "Gold Bar";
	compoMatrix[int(Item::IronBar)][int(Item::GoldBar)] = "Sword";
}

void RecipeBook::initRecipes()
{
	recipeList = map<string, Recipe*>();
	
	Recipe* ironbar = new Recipe(Item::IronBar);
	ironbar->addComponent("Iron Ore", 3);
	recipeList.insert(pair<string, Recipe*>(string("Iron Bar"), ironbar));
	
	Recipe* goldbar = new Recipe(Item::GoldBar);
	goldbar->addComponent("Gold Ore", 3);
	recipeList.insert(pair<string, Recipe*>(string("Gold Bar"), goldbar));

	Recipe* sword = new Recipe(Item::Sword);
	sword->addComponent("Iron Bar", 1);
	sword->addComponent("Gold Bar", 1);
	recipeList.insert(pair<string, Recipe*>(string("Sword"), sword));
}

vector<Recipe*> RecipeBook::getRecipesByObject(GameObject * go)
{
	vector<Recipe*> res = vector<Recipe*>();
	Item tc = RecipeBook::stringToItemType(go->getName());
	for (int i = 0; i < int(Item::Size); i++) {
		if (compoMatrix[int(tc)][i] != "")
		{
			Recipe *r = recipeList.at(compoMatrix[int(tc)][i]);
			res.push_back(r);
		}
	}

	return res;
}

vector<Recipe*> RecipeBook::getRecipesByName(string ngo)
{
	vector<Recipe*> res = vector<Recipe*>();
	Item tc = RecipeBook::stringToItemType(ngo);
	for (int i = 0; i < int(Item::Size); i++) {
		if (compoMatrix[int(tc)][i] != "")
		{
			string krec = compoMatrix[int(tc)][i];
			Recipe *r = recipeList.at(krec);
			res.push_back(r);
		}
	}

	return res;
}

Item RecipeBook::stringToItemType(string s)
{
	if (s == "Ground") return Item::Ground;
	if (s == "Rock") return Item::Rock;
	if (s == "Iron Ore") return Item::Iron;
	if (s == "Gold Ore") return Item::Gold;
	if (s == "Silver Ore") return Item::Silver;
	if (s == "Copper Ore") return Item::Copper;
	if (s == "Iron Bar") return Item::IronBar;
	if (s == "Gold Bar") return Item::GoldBar;
	if (s == "Sword") return Item::Sword;
	return Item();
}
