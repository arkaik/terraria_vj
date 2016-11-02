#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
	
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 24 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(float(tileSize) / tilesheet.width(), float(tileSize) / tilesheet.height());
	tileMap = vector<vector<Tile> >(mapSize.y, vector<Tile>(mapSize.x));
	vertices = new float[mapSize.y * mapSize.x * 24];

	map = new int[mapSize.x * mapSize.y];
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			fin.get(tile);
			if(tile == ' ')
				map[j*mapSize.x+i] = 0;
			else
				map[j*mapSize.x+i] = tile - int('0');

			tileMap[j][i] = Tile(glm::vec2(j, i), Tile::Type(map[j*mapSize.x + i]));
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();
	
	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	shaderprogram = &program;
	int tile;
	nTiles = 0;
	minCoordsMap = minCoords;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vertices = new float[int(mapSize.y) * int(mapSize.x) * 24];

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
			int vid = j * mapSize.x * 24 + i * 24;
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;
				
				int rndTile = rand() % 4;
				texCoordTile[0] = glm::vec2(float(rndTile*16) / tilesheet.width(), float((tile-1)*16) / tilesheet.height());

				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				tileMap[j][i].setTexRect(glm::vec4(texCoordTile[0], texCoordTile[1]));
				
				//First triangle 1
				vertices[vid] = posTile.x; vertices[vid+1] = posTile.y;
				vertices[vid + 2] = texCoordTile[0].x; vertices[vid + 3] = texCoordTile[0].y;
				vertices[vid + 4] = posTile.x + blockSize; vertices[vid + 5] = posTile.y;
				vertices[vid + 6] = texCoordTile[1].x; vertices[vid + 7] = texCoordTile[0].y;
				vertices[vid + 8] = posTile.x + blockSize; vertices[vid + 9] = posTile.y + blockSize;
				vertices[vid + 10] = texCoordTile[1].x; vertices[vid + 11] = texCoordTile[1].y;
				// Second triangle 1
				vertices[vid+12] = posTile.x; vertices[vid+13] = posTile.y;
				vertices[vid+14] = texCoordTile[0].x; vertices[vid+15] = texCoordTile[0].y;
				vertices[vid+16] = posTile.x + blockSize; vertices[vid+17] = posTile.y + blockSize;
				vertices[vid+18] = texCoordTile[1].x; vertices[vid+19] = texCoordTile[1].y;
				vertices[vid+20] = posTile.x; vertices[vid+21] = posTile.y + blockSize;
				vertices[vid+22] = texCoordTile[0].x; vertices[vid+23] = texCoordTile[1].y;
				
			}
			else {
				vertices[vid] = posTile.x; vertices[vid + 1] = posTile.x;
				vertices[vid + 2] = 0; vertices[vid + 3] = 0;
				vertices[vid + 4] = posTile.x; vertices[vid + 5] = posTile.x;
				vertices[vid + 6] = 0; vertices[vid + 7] = 0;
				vertices[vid + 8] = posTile.x + blockSize; vertices[vid + 9] = posTile.x;
				vertices[vid + 10] = 0; vertices[vid + 11] = 0;
				vertices[vid + 12] = posTile.x; vertices[vid + 13] = posTile.x;
				vertices[vid + 14] = 0; vertices[vid + 15] = 0;
				vertices[vid + 16] = posTile.x + blockSize; vertices[vid + 17] = posTile.x;
				vertices[vid + 18] = 0; vertices[vid + 19] = 0;
				vertices[vid + 20] = posTile.x; vertices[vid + 21] = posTile.x;
				vertices[vid + 22] = 0; vertices[vid + 23] = 0;
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * mapSize.x * mapSize.y * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

void TileMap::updateTile(int i, int j, Tile::Type t, glm::vec4 texRect)
{
	int vid = j * mapSize.x * 24 + i * 24;
	glm::vec2 posTile = glm::vec2(minCoordsMap.x + i * tileSize, minCoordsMap.y + j * tileSize);
	if (t != Tile::Void)
	{
		// Non-empty tile
		glm::vec4 tc = tileMap[j][i].getTexRect();

		int rndTile = rand() % 4;
		glm::vec2 texCoordTile0, texCoordTile1;
		texCoordTile0 = glm::vec2(float(rndTile * 16) / tilesheet.width(), float((int(t) - 1) * 16) / tilesheet.height());
		texCoordTile1 = texCoordTile0 + tileTexSize;

		//First triangle 1
		vertices[vid] = posTile.x; vertices[vid+1] = posTile.y;
		vertices[vid + 2] = texCoordTile0.x; vertices[vid + 3] = texCoordTile0.y;
		vertices[vid + 4] = posTile.x + blockSize; vertices[vid + 5] = posTile.y;
		vertices[vid + 6] = texCoordTile1.x; vertices[vid + 7] = texCoordTile0.y;
		vertices[vid + 8] = posTile.x + blockSize; vertices[vid + 9] = posTile.y + blockSize;
		vertices[vid + 10] = texCoordTile1.x; vertices[vid + 11] = texCoordTile1.y;
		// Second triangle 1
		vertices[vid+12] = posTile.x; vertices[vid+13] = posTile.y;
		vertices[vid+14] = texCoordTile0.x; vertices[vid+15] = texCoordTile0.y;
		vertices[vid+16] = posTile.x + blockSize; vertices[vid+17] = posTile.y + blockSize;
		vertices[vid+18] = texCoordTile1.x; vertices[vid+19] = texCoordTile1.y;
		vertices[vid+20] = posTile.x; vertices[vid+21] = posTile.y + blockSize;
		vertices[vid+22] = texCoordTile0.x; vertices[vid+23] = texCoordTile1.y;
		
	}
	else {
		vertices[vid] = posTile.x; vertices[vid + 1] = posTile.y;
		vertices[vid + 2] = 0; vertices[vid + 3] = 0;
		vertices[vid + 4] = posTile.x; vertices[vid + 5] = posTile.y;
		vertices[vid + 6] = 0; vertices[vid + 7] = 0;
		vertices[vid + 8] = posTile.x; vertices[vid + 9] = posTile.y;
		vertices[vid + 10] = 0; vertices[vid + 11] = 0;
		vertices[vid + 12] = posTile.x; vertices[vid + 13] = posTile.y;
		vertices[vid + 14] = 0; vertices[vid + 15] = 0;
		vertices[vid + 16] = posTile.x; vertices[vid + 17] = posTile.y;
		vertices[vid + 18] = 0; vertices[vid + 19] = 0;
		vertices[vid + 20] = posTile.x; vertices[vid + 21] = posTile.y;
		vertices[vid + 22] = 0; vertices[vid + 23] = 0;
	}

	//glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * mapSize.x * mapSize.y * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = shaderprogram->bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = shaderprogram->bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));

}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size)
{
	int x, y0, y1;
	
	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		if(int(tileMap[y][x].getType()) != 0)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size)
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		if(int(tileMap[y][x].getType()) != 0)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY)
{
	int x0, x1, y;
	
	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for(int x=x0; x<=x1; x++)
	{
		if(int(tileMap[y][x].getType()) != 0)
		{
			if(*posY - tileSize * y + size.y <= 4)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}
	
	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2 & pos, const glm::ivec2 & size, int* posY)
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = pos.y / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (int(tileMap[y][x].getType()) != 0)
		{	
			return true;
			/* TODO: mejorar la colision hacia arriba
			if (*posY - tileSize * y - size.y <= 4)
			{
				return true;
			}*/
		}
	}

	return false;
}

Tile* TileMap::getTile(float i, float j) {
	glm::ivec2 tilePos = (glm::vec2(i, j) - minCoordsMap);
	if (inbounds(tilePos)) {
		int y = tilePos.y / 16;
		int x = tilePos.x / 16;
		return &tileMap[y][x];
	}
	else {
		return nullptr;
	}
}

bool TileMap::inbounds(glm::ivec2 p) {
	glm::vec2 bounds = minCoordsMap + glm::vec2(mapSize.x*16, mapSize.y * 16);
	bool b1 = p.x > 0;
	bool b2 = p.x < bounds.x;
	bool b3 = p.y > 0;
	bool b4 = p.y < bounds.y;

	return (b1 && b2 && b3 && b4);
}





























