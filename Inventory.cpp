#include "Inventory.h"

#include <iostream>

#include "Game.h"
#include "Pickaxe.h"
#include "SwordObj.h"

void Inventory::init(ShaderProgram &sp)
{
	rb.init();
	
	rec_mid = std::vector<glm::vec2>(5);
	for (int ix = 0; ix < 5; ix++) {
		rec_mid[ix] = glm::vec2(32+52*ix, 350);
	}

	sprogram = sp;
	updateRecipes = false;
	opened = false;
	selected = 0;
	free_space = glm::ivec2(0, 1);
	inv_mid = std::vector<std::vector<glm::vec2> >(5, std::vector<glm::vec2>(10));

	for (int it = 0; it < INV_HEIGHT; it++)
		for (int jt = 0; jt < INV_WIDTH; jt++)
			inv_mid[it][jt] = glm::vec2(32+52*jt, 56+52*it);

	tex.loadFromFile("images/items.png", TEXTURE_PIXEL_FORMAT_RGBA);
	inv_back = std::vector<std::vector<Sprite*> >(5, std::vector<Sprite*>(10));
	inv_obj = std::vector<std::vector<GameObject*> >(5, std::vector<GameObject*>(10));
	for (int i = 0; i < INV_HEIGHT; i++)
		for (int j = 0; j < INV_WIDTH; j++) {
			inv_back[i][j] = Sprite::createSprite(&tex, glm::vec4(0, 96, 64, 64), &sp);
			inv_back[i][j]->setPosition(inv_mid[i][j]);
			inv_back[i][j]->setScale(glm::vec2(0.9,0.9));
			inv_back[i][j]->setOrigin(32, 32);
			inv_back[i][j]->setFixToCamera(true);

			inv_obj[i][j] = nullptr;
		}

	glm::vec2 iob1 = inv_mid[0][0] - glm::vec2( (52.0 * 0.9) / 2.0 );
	glm::vec2 iob2 = inv_mid[INV_HEIGHT-1][INV_WIDTH-1] + glm::vec2((52.0 * 0.9) / 2.0);
	openedBounds = glm::vec4(iob1, iob2);
	glm::vec2 rob1 = rec_mid[0] - glm::vec2((52.0 * 0.9) / 2.0);
	glm::vec2 rob2 = rec_mid[0] + glm::vec2((52.0 * 0.9) / 2.0);
	recipesBounds = glm::vec4(rob1, rob2);

	if (!obj_name.init("fonts/AndyBold.ttf", &sp))
		cout << "Could not load font!!!" << endl;
	obj_name.setSize(28);
	obj_name.setPosition(glm::vec2(150, 0));

	inv_obj[0][0] = new Pickaxe();
	inv_obj[0][0]->setPosition(inv_mid[0][0]);
	selectObject(0);
	//inv_obj[0][1] = new SwordObj();
	//inv_obj[0][1]->setPosition(inv_mid[0][1]);
	swapObjectPos = glm::vec2(-1);
}

void Inventory::update(int deltatime) {
	// Press E
	if (Game::instance().getReleasedKey(114)) {
		opened = opened ? false : true;
	}
	// Press Number
	for (int k = 0; k < INV_WIDTH; k++) {
		if (Game::instance().getKey(49+k)) {
			selectObject(k);
		}
	}

	if (insideOpenedInventory(Game::instance().getMousePosition()))
	{
		if (Game::instance().getReleasedMouseKey(0))
		{
			glm::vec2 mp = Game::instance().getMousePosition();
			int tx = floor(mp.x/55.00);
			int ty = floor(mp.y/55.00);
			if (swapObjectPos == glm::vec2(-1)) {
				glm::vec2 mt = glm::vec2(tx,ty);
				swapObjectPos = mt;
			}
			else if (glm::vec2(tx,ty) != swapObjectPos){
				int ox = floor(swapObjectPos.x);
				int oy = floor(swapObjectPos.y);
				GameObject* aux = inv_obj[oy][ox];
				inv_obj[oy][ox] = inv_obj[ty][tx];
				inv_obj[ty][tx] = aux;
				if (inv_obj[ty][tx] != nullptr) inv_obj[ty][tx]->setPosition(inv_mid[ty][tx]);
				if (inv_obj[oy][ox] != nullptr) inv_obj[oy][ox]->setPosition(inv_mid[oy][ox]);

				swapObjectPos = glm::vec2(-1);
			}
		}
	}

	if (insideOpenedRecipe(Game::instance().getMousePosition())) {
		if (Game::instance().getReleasedMouseKey(0))
		{
			glm::vec2 mp = Game::instance().getMousePosition() - glm::ivec2(recipesBounds.x, recipesBounds.y);
			int tx = floor(mp.x / 55.00);
			Recipe* r = rec_rec[tx];
			if (r->canBuild(inv_obj)) {
				r->useComponents(inv_obj);
				GameObject* go = rec_obj[tx];
				Item itgo = RecipeBook::stringToItemType(go->getName());
				addObject(GameObjectFactory::instance().createItemObject(itgo));
				//updateRecipes = true;
			}
			
		}
		Game::instance().bubble_event();
	}

	set<string> dead = set<string>();

	for (int y = 0; y < INV_HEIGHT; y++)
		for (int x = 0; x < INV_WIDTH; x++) {
			if (inv_obj[y][x] != nullptr && inv_obj[y][x]->getNumObj() == 0) {
				dead.insert(inv_obj[y][x]->getName());
				delete inv_obj[y][x];
				inv_obj[y][x] = nullptr;
				free_space = glm::vec2(y, x);
				obj_name.setText("");
			}
			else if (inv_obj[y][x] != nullptr){
				set<string>::iterator it = dead.find(inv_obj[y][x]->getName());
				if (it != dead.end())
					dead.erase(*it);
			}
		}

	if (updateRecipes) {

		std::set<string>::iterator at;
		for (at = dead.begin(); at != dead.end(); ++at) {
			string objname = *at;
			nameset.erase(objname);
		}

		rec_obj = vector<GameObject*>();
		rec_rec = vector<Recipe*>();
		int c = 0;
		std::set<string>::iterator it;
		for (it = nameset.begin(); it != nameset.end() && c < 5; ++it) {
			string objname = *it;
			std::vector<Recipe*> vr = rb.getRecipesByName(objname);
			for (int jt = 0; jt < int(vr.size()) && c < 5; ++jt) {
				Item vi = vr[jt]->getType();
				GameObject* gi = GameObjectFactory::instance().createItemObject(vi);
				rec_obj.push_back(gi);
				rec_rec.push_back(vr[jt]);
				c += 1;
			}
		}
		
		rec_back = vector<Sprite*>(c);
		for (int cc = 0; cc < c; cc++) {
			rec_obj[cc]->setPosition(rec_mid[cc]);
			rec_back[cc] = Sprite::createSprite(&tex, glm::vec4(0, 96, 64, 64), &sprogram);
			rec_back[cc]->setPosition(rec_mid[cc]);
			rec_back[cc]->setScale(glm::vec2(0.9, 0.9));
			rec_back[cc]->setOrigin(32, 32);
			rec_back[cc]->setFixToCamera(true);
		}

		glm::vec2 rob1 = rec_mid[0] - glm::vec2((52.0 * 0.9) / 2.0);
		glm::vec2 rob2 = rec_mid[c] + glm::vec2((52.0 * 0.9) / 2.0);
		recipesBounds = glm::vec4(rob1, rob2);
		updateRecipes = false;
	}
}

void Inventory::render()
{
	
	for (int i = 0; i < INV_WIDTH; i++) {
		inv_back[0][i]->render();
		if (inv_obj[0][i] != nullptr)
			inv_obj[0][i]->render();
	}

	if (opened) {
		for (int y = 1; y < INV_HEIGHT; y++)
			for (int x = 0; x < INV_WIDTH; x++) {
				inv_back[y][x]->render();
				
				if (inv_obj[y][x] != nullptr) {
					inv_obj[y][x]->render();
				}	
			}

		for (int c = 0; c < int(rec_back.size()); c++) {
			rec_back[c]->render();
			rec_obj[c]->render();
		}
	}

	obj_name.render();

}

void Inventory::selectObject(int s) {

	inv_back[0][selected]->setScale(glm::vec2(0.9,0.9));
	selected = s;
	inv_back[0][s]->setScale(glm::vec2(1.1, 1.1));
	if (inv_obj[0][s] != nullptr) {
		obj_name.setText(inv_obj[0][s]->getName());
	}
	else {
		obj_name.setText("");
	}
	
}

GameObject * Inventory::getSelectedObject()
{
	return inv_obj[0][selected];
}

void Inventory::addObject(GameObject *go)
{
	GameObject* it = findObject(go);
	if (it != nullptr) {
		GameObject *g = (it);
		if (g->canAccumulate() && g->getNumObj() < 64)
			it->incrementNum();
		else if (free_space != glm::ivec2(-1, -1)) {
			inv_obj[free_space.x][free_space.y] = go;
			inv_obj[free_space.x][free_space.y]->setPosition(inv_mid[free_space.x][free_space.y]);
			updateFreeSpace();
		}
	}
	else if (free_space != glm::ivec2(-1, -1)) {
		inv_obj[free_space.x][free_space.y] = go;
		inv_obj[free_space.x][free_space.y]->setPosition(inv_mid[free_space.x][free_space.y]);
		updateFreeSpace();
	}

	nameset.insert(go->getName());
	updateRecipes = true;
}

bool Inventory::insideOpenedInventory(glm::vec2 p)
{
	bool b1 = p.x > openedBounds.x;
	bool b2 = p.x < openedBounds.z;
	bool b3 = p.y > openedBounds.y;
	bool b4 = p.y < openedBounds.w;
	bool inside = (b1 && b2 && b3 && b4);
	return opened && inside;
}

bool Inventory::insideOpenedRecipe(glm::vec2 p)
{
	bool b1 = p.x > recipesBounds.x;
	bool b2 = p.x < recipesBounds.z;
	bool b3 = p.y > recipesBounds.y;
	bool b4 = p.y < recipesBounds.w;
	bool inside = (b1 && b2 && b3 && b4);
	return opened && inside;
}

void Inventory::updateFreeSpace()
{
	if (free_space.y < int(inv_obj[0].size())-1) free_space.y += 1;
	else if (free_space.x < int(inv_obj.size())-1) free_space = glm::ivec2(free_space.x + 1, 0);
	else free_space = glm::ivec2(-1, -1);
}

GameObject * Inventory::findObject(GameObject * go)
{
	bool b = true;
	int i = 0;
	GameObject *ptr = nullptr;
	while (b && i < int(inv_obj[0].size())) {
		
		if (inv_obj[0][i] != nullptr && 
			inv_obj[0][i]->getName() == go->getName() &&
			inv_obj[0][i]->getNumObj() < 64-1) {
			ptr = inv_obj[0][i];
			b = false;
		}

		i++;
	}
	return ptr;
}
