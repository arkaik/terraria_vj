#include "Inventory.h"
#include <iostream>

void Inventory::init(ShaderProgram sp)
{
	shader = &sp;
	tex.loadFromFile("images/items.png", TEXTURE_PIXEL_FORMAT_RGBA);
	inv_back = std::vector<Sprite>(8);
	for (int i = 0; i < int(inv_back.size()); i++) {
		inv_back[i] = *Sprite::createSprite(tex, glm::vec4(32, 32, 32, 32), shader);
		//inv_back[i] = Sprite(tex, glm::vec4(32, 32, 32, 32), shader);
		inv_back[i].setPosition(glm::vec2(10,10));
	}
	std::cout << "Hello!" << endl;
}

void Inventory::render()
{
	for (int i = 0; i < int(inv_back.size()); i++)
	{
		inv_back[i].render();
	}
}
