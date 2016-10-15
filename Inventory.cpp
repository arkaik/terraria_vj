#include "Inventory.h"

#include <iostream>

#include "Game.h"

void Inventory::init(ShaderProgram &sp)
{
	opened = false;
	selected = 0;
	inv_mid = std::vector<std::vector<glm::vec2> >(5, std::vector<glm::vec2>(10));

	for (int it = 0; it < INV_HEIGHT; it++)
		for (int jt = 0; jt < INV_WIDTH; jt++)
			inv_mid[it][jt] = glm::vec2(32+52*jt, 56+52*it);

	tex.loadFromFile("images/items.png", TEXTURE_PIXEL_FORMAT_RGBA);
	inv_back = std::vector<std::vector<Sprite*> >(5, std::vector<Sprite*>(10));
	for (int i = 0; i < INV_HEIGHT; i++)
		for (int j = 0; j < INV_WIDTH; j++) {
			inv_back[i][j] = Sprite::createSprite(&tex, glm::vec4(0, 96, 64, 64), &sp);
			inv_back[i][j]->setPosition(inv_mid[i][j]);
			inv_back[i][j]->setScale(glm::vec2(0.9,0.9));
			inv_back[i][j]->setOrigin(32, 32);
			inv_back[i][j]->setFixToCamera(true);
		}

	inv_obj = std::vector<std::vector<Sprite*> >(5, std::vector<Sprite*>(10));
	inv_obj[0][0] = Sprite::createSprite(&tex, glm::vec4(0, 0, 32, 32), &sp);
	inv_obj[0][0]->setPosition(inv_mid[0][0]);
	inv_obj[0][0]->setOrigin(glm::vec2(16, 16));
	inv_obj[0][0]->setFixToCamera(true);
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
	
}

void Inventory::render()
{
	for (int i = 0; i < INV_WIDTH; i++)
		inv_back[0][i]->render();
	inv_obj[0][0]->render();

	if (opened) {
		for (int y = 1; y < INV_HEIGHT; y++)
			for (int x = 0; x < INV_WIDTH; x++)
				inv_back[y][x]->render();
	}
}

void Inventory::selectObject(int s) {

	inv_back[0][selected]->setScale(glm::vec2(0.9,0.9));
	selected = s;
	inv_back[0][s]->setScale(glm::vec2(1.1, 1.1));
}