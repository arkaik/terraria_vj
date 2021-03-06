#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

//cambio de aumento pos de 2 a 4

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	delayMax = 20;
	bJumping = false;
	radius = 8;

	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);



	if (Game::instance().getMouseKey(0))
	{
		glm::vec2 mpos = Game::instance().getMousePosition();
		glm::vec2 ppos = sprite->getPosition();
		glm::vec2 opos = ppos - glm::vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
		glm::vec2 smpos = opos + mpos;
		if (inventory->getSelectedObject() != nullptr) {
			inventory->getSelectedObject()->action(this, smpos, map);
		}
	}

	if(Game::instance().getKey('a') || Game::instance().getKey('A'))
	{  
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)) || !map->inbounds(posPlayer))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getKey('d') || Game::instance().getKey('D'))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)) || !map->inbounds(posPlayer))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		// Podemos quitarlo si hace falta
		else if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			bJumping = false;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			if(Game::instance().getKey('w') || Game::instance().getKey('W'))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}
	whoOverlap();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::render()
{
	sprite->render();
}

void Player::setInventory(Inventory * inv)
{
	inventory = inv;
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setHealth(Health * h)
{
	heal = h;
}

void Player::decrementLife()
{
	heal->decrementLife();
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec2 Player::getPosition() {
	return sprite->getPosition();
}

glm::ivec2 Player::getPlayerPosition() {
	return posPlayer;
}

glm::vec2 Player::getMapPosition()
{
	glm::vec2 ret = (glm::ivec2(sprite->getPosition()) - tileMapDispl) / 16;
	return glm::vec2(ret.y, ret.x);
}

void Player::addToInventory(GameObject *go)
{
	inventory->addObject(go);
}

void Player::addEnemy(EnemigoBase * eb)
{
	collisionList.push_back(eb);
	delays.push_back(0);
}

std::list<EnemigoBase*> * Player::getCloseEnemies()
{
	return &collisionList;
}

bool Player::overlap(glm::vec4 bound)
{
	glm::vec2 ppos = getPosition();

	if ((ppos.x < bound.x+bound.z) && (ppos.x + 16 > bound.x) && (ppos.y < bound.y+bound.w) && (ppos.y + 32 > bound.y))
		return true;
	else return false;
}

void Player::whoOverlap() {
	int i = 0;
	list<int>::iterator it1 = delays.begin();
	for (list<EnemigoBase*>::iterator it = collisionList.begin() ; it != collisionList.end(); ++it) {
		if (overlap(glm::vec4((*it)->getPosition(), (*it)->getWidth(), (*it)->getHeight()))) {
			if (*it1 == 0) decrementLife(); 
			++*it1;
			if (*it1 == delayMax) *it1 = 0;
		}
		else *it1 = 0;
		++it1;
	}
}

int Player::getHealthPoints()
{
	return heal->getPoints();
}


