#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformable {
public:
	Transformable();

	void setPosition(float x, float y);
	void setPosition(glm::vec2 pos);
	void setRotation(float angle);
	void setScale(float fx, float fy);
	void setScale(glm::vec2 scal);
	void setOrigin(float ox, float oy);
	void setOrigin(glm::vec2 or);

	glm::vec2 getPosition();
	glm::vec2 getScale();

	glm::mat4 getTransform();

private:
	glm::vec2 position;
	glm::vec2 origin;
	glm::vec2 scale;
	float rotation;
	glm::mat4 transformMatrix;
	bool needUpdate;

};