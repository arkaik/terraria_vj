#include "Recipe.h"

Recipe::Recipe()
{
}

Recipe::Recipe(vector<string> vs, vector<int> vq)
{

}

Recipe::Recipe(Item i, vector<Component> vc)
{
	components = vc;
	itobj = i;
}

Recipe::Recipe(vector<Component> vc)
{
	components = vc;
}

Recipe::Recipe(Item i)
{
	itobj = i;
}

void Recipe::addComponent(string p, int q)
{
	Component com;
	com.prod = p;
	com.qty = q;
	components.push_back(com);
}

Item Recipe::getType()
{
	return itobj;
}

bool Recipe::canBuild(vector<vector<GameObject*>> vgo)
{
	for (int c = 0; c < int(components.size()); c++)
	{
		string n = components[c].prod;
		int q = components[c].qty;
		int i = 0;
		int j = 0;
		bool b = true;
		while (i < int(vgo.size()) && b)
		{
			j = 0;
			while (j < int(vgo[0].size()) && b)
			{
				if (vgo[i][j] != nullptr && vgo[i][j]->getName() == n) {
					if (vgo[i][j]->getNumObj() < q) return false;
					else {
						vgo[i][j]->decrementNum(q);
						b = false; 
					}
				}
				
				j++;
			}
			i++;
		}
			
		if (i == int(vgo.size()) + 1 && j == int(vgo[j].size()) + 1) { return false; }

	}

	return true;
}
