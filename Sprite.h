#pragma once


#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
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
	Sprite();
	Sprite(Texture *texture, const glm::vec4 rect, ShaderProgram *program);
	Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

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
	glm::vec4 getLocalBounds() const;

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
	
	int fixedToCamera;
};



