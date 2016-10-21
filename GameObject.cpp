#include "GameObject.h"

#include "Player.h"

GameObject::GameObject() {
	accumulate = false;
	num_obj = 0;
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
}

void GameObject::setSprite(Sprite * spr)
{
	sprite = spr;
	sprite->setOrigin(16, 16);
	sprite->setFixToCamera(true);
}

void GameObject::setPosition(float x, float y)
{
	sprite->setPosition(x, y);
}

void GameObject::setPosition(glm::vec2 pos)
{
	sprite->setPosition(pos);
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
}

void GameObject::decrementNum()
{
	if (accumulate && num_obj > 0) num_obj--;
}

ShaderProgram* GameObject::program = nullptr;

bool operator==(GameObject & lhs, GameObject & rhs)
{
	bool same_name = lhs.getName() == rhs.getName();
	return same_name;
}