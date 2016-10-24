#pragma once

#include <ft2build.h>
#include <freetype/freetype.h>
#include FT_FREETYPE_H
#include "ShaderProgram.h"
#include "Sprite.h"
#include <string>
#include <vector>

#define NUM_CHARACTERS (128 - 32)

using namespace std;

struct CharMetrics
{
	int tx, ty; 		// Pos x, y inside texture in pixels
	int sx, sy; 		// Size of char in pixels
	int ax, ay; 		// Advance for each character in a string sequence
	int bl, bt; 		// Bitmap left and top adjusting
};

class Text
{
public:
	Text();
	~Text();

	bool init(const char *filename, ShaderProgram * sp);
	void destroy();

	//ShaderProgram &getProgram();
	int getSize() const;
	//void render(char c, const glm::vec2 &pixel, int size, const glm::vec4 &color);
	void render();

	void setText(string s);
	void setPosition(glm::vec2 p);
	void setSize(int sz);

	static ShaderProgram *sprogram;

private:
	//void initShaders();
	bool extractCharSizes(int *maxCharWidth, int *maxCharHeight);
	void createTextureAtlas();

private:
	int fontSize, textureSize, maxCharWidth, maxCharHeight;
	FT_Face face;
	CharMetrics chars[NUM_CHARACTERS];
	Texture* textureAtlas;
	ShaderProgram* program;
	std::vector<Sprite*> quad;
	string text_str;

	static bool bLibInit;
	static FT_Library library;

	glm::vec2 pos;
	float scaleFactor;

};

