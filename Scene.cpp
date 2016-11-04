#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "EndScene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25

#include "Enemigo.h"

Scene::Scene()
{
	background = NULL;
	map = NULL;
	player = NULL;
	gui = NULL;
	enemigo = NULL;
	radioDeteccionPlayer = 0;
	gui2 = NULL;
	esq = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (gui != NULL)
		delete gui;
	if (enemigo != NULL)
		delete enemigo;
	if (gui2 != NULL)
		delete gui2;
	if (background != NULL)
		delete background;
	if (esq != NULL)
		delete enemigo;
}


void Scene::init()
{
	bend = false;
	initShaders();
	SoundController::instance().playMusic("../sounds/overworld-day.ogg");
	GameObject::program = &texProgram;
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	radioDeteccionPlayer = 30*map->getTileSize();
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	//Al crear el enemigo se le pasa su posicion
	enemigo = new Enemigo(this, glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize() - 20* map->getTileSize()));
	enemigo->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemigo->setTileMap(map);
	//esq = new Esqueletillo(player, glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize() + 20* map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	//esq->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	//esq->setTileMap(map);
	gui = new Inventory();
	gui->init(texProgram);
	player->setInventory(gui);
	gui2 = new Health();
	gui2->init(texProgram);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	background = Sprite::createSprite("images/Background_92.png", glm::vec4(0, 0, 1200, 600), &texProgram);
	background->setScale(glm::vec2(2, 2));
	background->setFixToCamera(true);
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	enemigo->update(deltaTime);
	//esq->update(deltaTime);
	gui->update(deltaTime);
	gui2->update(deltaTime);
	glm::vec2 ppos = player->getPosition();
	float nx = ppos.x - float(SCREEN_WIDTH) / 2;
	float ny = ppos.y - float(SCREEN_HEIGHT) / 2;
	projection = glm::ortho(nx, ppos.x + float(SCREEN_WIDTH) / 2, ppos.y + float(SCREEN_HEIGHT) / 2, ny);
	ftcMatrix = glm::translate(glm::mat4(1.f), glm::vec3(nx, ny, 0.f));
}

void Scene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniformMatrix4f("ftcMatrix", ftcMatrix);
	texProgram.default();
	background->render();
	map->render();
	player->render();
	enemigo->render();
	gui->render();
	gui2->render();
	
}

BasicScene* Scene::changeState()
{
	if (bend) {
		SoundController::instance().stopSounds();
		BasicScene* bs = new EndScene();
		bs->init();
		return bs;
	}

	return this;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
	GLenum error = glGetError();
	
}

glm::vec2 Scene::getPlayerPos() {
	return player->getPosition();
}

glm::ivec2 Scene::getPlayerPosition() {
	return player->getPlayerPosition();
}

Player * Scene::getPlayer()
{
	return player;
}

void Scene::theEnd()
{
	bend = true;
}



