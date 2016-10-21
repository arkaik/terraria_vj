#include "Inventory.h"

#include <iostream>

#include "Game.h"
#include "Pickaxe.h"

void Inventory::init(ShaderProgram &sp)
{
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

	glm::vec2 iob1 = inv_mid[0][0] - glm::vec2( (52 * 0.9) / 2.0 );
	glm::vec2 iob2 = inv_mid[INV_HEIGHT-1][INV_WIDTH-1] + glm::vec2((52 * 0.9) / 2.0);
	openedBounds = glm::vec4(iob1, iob2);

	inv_obj[0][0] = new Pickaxe();
	inv_obj[0][0]->setPosition(inv_mid[0][0]);

	// Select which font you want to use
	if (!obj_name.init("fonts/halcyon.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;
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
		if (Game::instance().getPressedMouseKey(0))
		{
			//drag_drop = ;
		}
		else if (Game::instance().getReleasedMouseKey(0))
		{

		}

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
				if (inv_obj[y][x] != nullptr)
					inv_obj[y][x]->render();
			}
	}

	obj_name.render("Videogames!!!", glm::vec2(10, 20), 32, glm::vec4(1, 1, 1, 1));
}

void Inventory::selectObject(int s) {

	inv_back[0][selected]->setScale(glm::vec2(0.9,0.9));
	selected = s;
	inv_back[0][s]->setScale(glm::vec2(1.1, 1.1));
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
