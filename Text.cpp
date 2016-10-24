#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Text.h"

#define ATLAS_FONT_SIZE 64
using namespace std;

bool Text::bLibInit = false;
FT_Library Text::library;

Text::Text()
{
}

Text::~Text()
{
	destroy();
}

bool Text::init(const char *filename, ShaderProgram * sp)
{
	program = sp;
	FT_Error error;

	if (!bLibInit)
	{
		error = FT_Init_FreeType(&Text::library);
		if (error)
			return false;
		bLibInit = true;
	}
	error = FT_New_Face(Text::library, filename, 0, &face);
	if (error)
		return false;
	FT_Set_Pixel_Sizes(face, ATLAS_FONT_SIZE, ATLAS_FONT_SIZE);

	if (!extractCharSizes(&maxCharWidth, &maxCharHeight))
		return false;
	fontSize = maxCharHeight;
	textureSize = 512;
	if (floor(float(textureSize) / maxCharWidth) * floor(float(textureSize) / maxCharHeight) < (128 - 32))
		textureSize = 1024;
	if (floor(float(textureSize) / maxCharWidth) * floor(float(textureSize) / maxCharHeight) < (128 - 32))
		return false;
	createTextureAtlas();

	//glm::vec2 geom[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
	//glm::vec2 texCoords[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f) };

	scaleFactor = 1;
	pos = glm::vec2(0.0);
	quad = std::vector<Sprite*>();

	return true;
}

void Text::setText(string s)
{
	text_str = s;

	glm::vec2 minTexCoord, sizeTexCoord;
	glm::vec2 apos = pos;

	quad = std::vector<Sprite*>(text_str.size());
	for (int i = 0; i < int(text_str.size()); i++)
	{
		CharMetrics cm = chars[text_str[i] - 32];
		minTexCoord = glm::vec2(float(cm.tx), float(cm.ty));
		sizeTexCoord = glm::vec2(float(cm.sx), float(cm.sy));
		quad[i] = Sprite::createSprite(textureAtlas, glm::vec4(minTexCoord, sizeTexCoord), program);
		quad[i]->setPosition(glm::vec2(apos.x + scaleFactor * cm.bl, (apos.y - scaleFactor * cm.bt)+maxCharHeight*scaleFactor));
		quad[i]->setScale(glm::vec2(scaleFactor));
		quad[i]->setFixToCamera(true);
		quad[i]->setCText(true);
		quad[i]->setColor(glm::vec4(0.f,0.f,0.f,1.f));
		apos.x += scaleFactor * cm.ax;
	}
}

void Text::setPosition(glm::vec2 p)
{
	pos = p;
	glm::vec2 apos = pos;
	for (int i = 0; i < int(quad.size()); i++) {
		CharMetrics cm = chars[text_str[i] - 32];
		quad[i]->setPosition(glm::vec2(apos.x + scaleFactor * cm.bl, (apos.y - scaleFactor * cm.bt) + maxCharHeight*scaleFactor));
		apos.x += scaleFactor * cm.ax;
	}
}

void Text::setSize(int sz)
{
	scaleFactor = float(sz) / fontSize;
	glm::vec2 apos = pos;
	for (int i = 0; i < int(quad.size()); i++) {
		CharMetrics cm = chars[text_str[i] - 32];
		quad[i]->setScale(glm::vec2(scaleFactor));
		quad[i]->setPosition(glm::vec2(apos.x + scaleFactor * cm.bl, (apos.y - scaleFactor * cm.bt) + maxCharHeight*scaleFactor));
		apos.x += scaleFactor * cm.ax;
	}
}

void Text::destroy()
{
	FT_Done_Face(face);
}

/*ShaderProgram &Text::getProgram()
{
	return *program;
}*/

int Text::getSize() const
{
	return fontSize;
}


void Text::render()
{
	for (unsigned int i = 0; i<int(quad.size()); i++)
	{
		//glm::vec2 po = glm::vec2(pos.x + scaleFactor * chars[str[i] - 32].bl, pos.y - scaleFactor * chars[str[i] - 32].bt);
		//quad[i]->setPosition(glm::vec2(pos.x + scaleFactor * chars[str[i] - 32].bl, pos.y - scaleFactor * chars[str[i] - 32].bt));
		//quad[i]->setScale(scaleFactor * glm::vec2(chars[str[i] - 32].sx, chars[str[i] - 32].sy));
		
		quad[i]->render();
		
		//pos.x += scaleFactor * chars[str[i] - 32].ax;
	}

}

bool Text::extractCharSizes(int *maxCharWidth, int *maxCharHeight)
{
	unsigned char c;

	*maxCharWidth = 0;
	*maxCharHeight = 0;
	for (c = 32; c<128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			return false;
		*maxCharWidth = glm::max(*maxCharWidth, (int)face->glyph->bitmap.width);
		*maxCharHeight = glm::max(*maxCharHeight, (int)face->glyph->bitmap.rows);
	}

	return true;
}

void Text::createTextureAtlas()
{
	int x = 0, y = 0;
	textureAtlas = new Texture();
	textureAtlas->createEmptyTexture(textureSize, textureSize);
	for (unsigned char c = 32; c<128; c++)
	{
		FT_Load_Char(face, c, FT_LOAD_RENDER);
		chars[c - 32].tx = x;
		chars[c - 32].ty = y;
		chars[c - 32].sx = face->glyph->bitmap.width;
		chars[c - 32].sy = face->glyph->bitmap.rows;
		chars[c - 32].ax = face->glyph->advance.x >> 6;
		chars[c - 32].ay = face->glyph->advance.y >> 6;
		chars[c - 32].bl = face->glyph->bitmap_left;
		chars[c - 32].bt = face->glyph->bitmap_top;
		textureAtlas->loadSubtextureFromGlyphBuffer(face->glyph->bitmap.buffer, x, y, face->glyph->bitmap.width, face->glyph->bitmap.rows);
		x += maxCharWidth;
		if ((x + maxCharWidth) >= textureSize)
		{
			x = 0;
			y += maxCharHeight;
		}
	}
	textureAtlas->generateMipmap();
	textureAtlas->setWrapS(GL_CLAMP_TO_EDGE);
	textureAtlas->setWrapT(GL_CLAMP_TO_EDGE);
}

ShaderProgram* Text::sprogram = nullptr;