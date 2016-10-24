#include "GameObject.h"

#include "Player.h"

GameObject::GameObject() {
	accumulate = false;
	num_obj = 1;
	name = "";
	num_text = new Text();
	if (!num_text->init("fonts/AndyBold.ttf", GameObject::program))
		std::cout << "Could not load font!!!" << endl;
	num_text->setSize(18);
}

GameObject::~GameObject()
{
}

void GameObject::action(Player *player, glm::vec2 mouse_pos, TileMap *map)
{

}

void GameObject::render()
{
	sprite->render();
	if (num_obj > 1) num_text->render();
}

void GameObject::setSprite(Sprite * spr)
{
	sprite = spr;
	sprite->setOrigin(16, 16);
	sprite->setFixToCamera(true);
	num_text->setPosition(sprite->getPosition() + glm::vec2(8, 4));
}

void GameObject::setPosition(float x, float y)
{
	sprite->setPosition(x, y);
	num_text->setPosition(glm::vec2(x,y) + glm::vec2(8, 4));
}

void GameObject::setPosition(glm::vec2 pos)
{
	setPosition(pos.x,pos.y);
}

void GameObject::setName(string n)
{
	name = n;
}

string GameObject::getName()
{
	return name;
}

void GameObject::setAccumulate(bool b)
{
	accumulate = b;

}

bool GameObject::canAccumulate()
{
	return accumulate;
}

int GameObject::getNumObj()
{
	return num_obj;
}

void GameObject::incrementNum()
{
	if (accumulate && num_obj < 64) num_obj++;
	if (num_obj > 0) num_text->setText(std::to_string(num_obj));

}

void GameObject::decrementNum()
{
	if (accumulate && num_obj > 0) num_obj--;
	if (num_obj > 0) num_text->setText(std::to_string(num_obj));
	else num_text->setText("");
}

ShaderProgram* GameObject::program = nullptr;

bool operator==(GameObject & lhs, GameObject & rhs)
{
	bool same_name = lhs.getName() == rhs.getName();
	return same_name;
}