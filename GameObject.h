#pragma once

#include <iostream>
#include <string>
#include "TileMap.h"
#include "Text.h"
#include "SoundController.h"

using namespace std;

class Player;

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void action(Player *player, glm::vec2 mouse_pos, TileMap *map);

	void render();

	void setSprite(Sprite* spr);
	Sprite* getSprite();

	void setPosition(float x, float y);
	void setPosition(glm::vec2 pos);

	void setName(string n);
	string getName();

	void setAccumulate(bool b);
	bool canAccumulate();
	int getNumObj();
	void incrementNum();
	void decrementNum();
	void decrementNum(int n);

	static ShaderProgram *program;

	friend bool operator== (GameObject & lhs, GameObject & rhs);
	friend bool operator== (const GameObject &lhs, const GameObject &rhs);
private:
	string name;
	Sprite* sprite;
	bool accumulate;
	int num_obj;
	Text* num_text;

};
