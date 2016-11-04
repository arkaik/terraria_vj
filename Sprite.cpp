#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"
#include <iostream>


Sprite *Sprite::createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program)
{
	Sprite *quad = new Sprite(quadSize, sizeInSpritesheet, spritesheet, program);

	return quad;
}

Sprite *Sprite::createSprite(Texture *tex, const glm::vec4 rect, ShaderProgram *program)
{
	Sprite *quad = new Sprite(tex, rect, program);

	return quad;
}

Sprite *Sprite::createSprite(std::string ntex, const glm::vec4 rect, ShaderProgram *program)
{
	Texture* texptr = TextureFactory::instance().getTexture(ntex);
	Sprite *quad = new Sprite(texptr, rect, program);

	return quad;
}

Sprite * Sprite::createSprite(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram * program)
{
	Sprite *quad = new Sprite(geom, texCoords, program);

	return quad;
}

Sprite::Sprite(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram * program)
{
	float vertices[16] = { geom[0].x, geom[0].y, texCoords[0].x, texCoords[0].y,
		geom[1].x, geom[0].y, texCoords[1].x, texCoords[0].y,
		geom[1].x, geom[1].y, texCoords[1].x, texCoords[1].y,
		geom[0].x, geom[1].y, texCoords[0].x, texCoords[1].y };

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	//setPosition(glm::vec2(0.f));
	setOrigin(glm::vec2(0.f));
	//fixedToCamera = 0;
}

Sprite::Sprite() :
	texture(NULL),
	texRect(),
	fixedToCamera(0),
	ctext(0),
	color(glm::vec4(1.0, 1.0, 1.0, 1.0))
{
}

Sprite::Sprite(Texture *tex, const glm::vec4 rect, ShaderProgram *program)
{
	setTextureRect(rect);
	int wtex = tex->width();
	int htex = tex->height();
	glm::vec4 texCoord = glm::vec4(rect.x / wtex, rect.y / htex, (rect.x+rect.z) / wtex, (rect.y+rect.w) / htex);
	float vertices[16] = { 0.f, 0.f, texCoord.x, texCoord.y,
		0.f, rect.w, texCoord.x, texCoord.w,
		rect.z, 0.f, texCoord.z, texCoord.y,
		rect.z, rect.w, texCoord.z, texCoord.w };

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	texture = tex;
	shaderProgram = program;
	currentAnimation = -1;
	setPosition(glm::vec2(0.f));
	setOrigin(glm::vec2(0.f));
	fixedToCamera = 0;
	color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	ctext = 0;
}


Sprite::Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program)
{
	vertices[0] = 0.f; vertices[1] = 0.f;	vertices[2] = 0.f; vertices[3] = 0.f;
	vertices[4] = 0.f; vertices[5] = quadSize.y;	vertices[6] = 0.f; vertices[7] = sizeInSpritesheet.y;
	vertices[8] = quadSize.x; vertices[9] = 0.f; vertices[10] = sizeInSpritesheet.x; vertices[11] = 0.f;
	vertices[12] = quadSize.x; vertices[13] = quadSize.y;	vertices[14] = sizeInSpritesheet.x; vertices[15] = sizeInSpritesheet.y;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
	texture = spritesheet;
	shaderProgram = program;
	currentAnimation = -1;
	setPosition(glm::vec2(0.f));
	fixedToCamera = 0;
	color = glm::vec4(1.0,1.0,1.0,1.0);
	ctext = 0;
}

void Sprite::update(int deltaTime)
{
	if(currentAnimation >= 0)
	{
		timeAnimation += deltaTime;
		while(timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
		{
			timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
			currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
		}
		texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
	}
}

void Sprite::render()
{
	//shaderProgram->use();
	shaderProgram->setUniformMatrix4f("modelview", getTransform());
	shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);
	shaderProgram->setUniform1i("fixedToCamera", fixedToCamera);
	shaderProgram->setUniform1i("ctext", ctext);
	shaderProgram->setUniform4f("color", color.r, color.g, color.b, color.a);
	glm::vec4 npos = getTransform() * glm::vec4(getPosition(), 0.f, 1.f);
	glEnable(GL_TEXTURE_2D);
	texture->use();
	//glFlush();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisable(GL_TEXTURE_2D);
	shaderProgram->default();
	//glBindVertexArray(0);
}

void Sprite::free()
{
	glDeleteBuffers(1, &vbo);
}

void Sprite::setNumberAnimations(int nAnimations)
{
	animations.clear();
	animations.resize(nAnimations);
}

void Sprite::setAnimationSpeed(int animId, int keyframesPerSec)
{
	if(animId < int(animations.size()))
		animations[animId].millisecsPerKeyframe = 1000.f / keyframesPerSec;
}

void Sprite::addKeyframe(int animId, const glm::vec2 &displacement)
{
	if(animId < int(animations.size()))
		animations[animId].keyframeDispl.push_back(displacement);
}

void Sprite::changeAnimation(int animId)
{
	if(animId < int(animations.size()))
	{
		currentAnimation = animId;
		currentKeyframe = 0;
		timeAnimation = 0.f;
		texCoordDispl = animations[animId].keyframeDispl[0];
	}
}

int Sprite::animation() const
{
	return currentAnimation;
}

void Sprite::setTexture(const Texture & tex)
{
	texture = &tex;
}

void Sprite::setTextureRect(const glm::vec4 & rectangle)
{
	if (rectangle != texRect) {
		texRect = rectangle;
		updatePositions();
		updateTexCoords();
	}
}

void Sprite::setFixToCamera(bool ftc) {
	if (ftc) fixedToCamera = 1;
	else fixedToCamera = 0;
}

void Sprite::setCText(bool ct)
{
	if (ct) ctext = 1;
	else ctext = 0;
}

glm::vec4 Sprite::getLocalBounds() const
{
	float width = std::abs(texRect.z);
	float height = std::abs(texRect.w);
	return glm::vec4(0.f, 0.f, width, height);
}

void Sprite::setColor(glm::vec4 c)
{
	color = c;
}


void Sprite::updatePositions()
{
	glm::vec4 bounds = getLocalBounds();

	vertices[0] = 0;
	vertices[1] = 0;
	vertices[4] = 0;
	vertices[5] = bounds.w;
	vertices[8] = bounds.z;
	vertices[9] = 0;
	vertices[12] = bounds.z;
	vertices[13] = bounds.w;
}

void Sprite::updateTexCoords()
{
	float left = static_cast<float>(texRect.x);
	float right = left + texRect.z;
	float top = static_cast<float>(texRect.y);
	float bottom = top + texRect.w;

	vertices[2] = left;
	vertices[3] = top;
	vertices[6] = left;
	vertices[7] = bottom;
	vertices[10] = right;
	vertices[11] = top;
	vertices[14] = right;
	vertices[15] = bottom;
}




