#pragma once


#include <vector>
#include <glm/glm.hpp>
#include "TextureFactory.h"
#include "ShaderProgram.h"
#include "AnimKeyframes.h"
#include "Transformable.h"


// This class is derived from code seen earlier in TexturedQuad but it is also
// able to manage animations stored as a spritesheet. 


class Sprite : public Transformable
{

public:
	// Textured quads can only be created inside an OpenGL context
	static Sprite *createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);
	static Sprite *createSprite(Texture *tex, const glm::vec4 rect, ShaderProgram *program);
	static Sprite *createSprite(std::string ntex, const glm::vec4 rect, ShaderProgram *program);
	static Sprite *createSprite(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram *program);
	Sprite(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram *program);
	Sprite(Texture *texture, const glm::vec4 rect, ShaderProgram *program);
	Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);
	Sprite();
	void update(int deltaTime);
	void render();
	void free();

	void setNumberAnimations(int nAnimations);
	void setAnimationSpeed(int animId, int keyframesPerSec);
	void addKeyframe(int animId, const glm::vec2 &frame);
	void changeAnimation(int animId);
	int animation() const;

	void setTexture(const Texture &tex);
	void setTextureRect(const glm::vec4 &rectangle);
	const Texture* getTexture() const;
	const glm::vec4& getTextureRect() const;

	void setFixToCamera(bool ftc);
	void setCText(bool ct);
	glm::vec4 getLocalBounds() const;
	void setColor(glm::vec4 c);
private:
	void updatePositions();
	void updateTexCoords();

private:
	const Texture *texture;
	ShaderProgram *shaderProgram;
	glm::vec4 texRect;
	float vertices[16];

	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int currentAnimation, currentKeyframe;
	float timeAnimation;
	glm::vec2 texCoordDispl;
	vector<AnimKeyframes> animations;
	
	int ctext;
	int fixedToCamera;
	
	glm::vec4 color;
};



