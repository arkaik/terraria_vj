#include "Inventory.h"
#include <iostream>



void Inventory::init(ShaderProgram &sp)
{
	opened = false;
	selected = 0;
	for (int it = 0; it < 8; it++)
		inv_mid.push_back(glm::vec2(32+64*it, 32));

	tex.loadFromFile("images/items.png", TEXTURE_PIXEL_FORMAT_RGBA);
	inv_back = std::vector<Sprite*>(8);
	for (int i = 0; i < int(inv_back.size()); i++) {
		inv_back[i] = Sprite::createSprite(&tex, glm::vec4(0, 96, 64, 64), &sp);
		inv_back[i]->setPosition(inv_mid[i]);
		inv_back[i]->setOrigin(32, 32);
		inv_back[i]->setFixToCamera(true);
	}

	inv_obj = std::vector<Sprite*>();
	inv_obj.push_back(Sprite::createSprite(&tex, glm::vec4(0, 0, 32, 32), &sp));
	inv_obj[0]->setPosition(inv_mid[0]);
	inv_obj[0]->setOrigin(glm::vec2(16, 16));
	inv_obj[0]->setFixToCamera(true);
}

void Inventory::render()
{
	for (int i = 0; i < int(inv_back.size()); i++)
	{
		if (i == selected) inv_back[i]->setScale(glm::vec2(1.2, 1.2));
		inv_back[i]->render();
	}
	inv_obj[0]->render();
}
