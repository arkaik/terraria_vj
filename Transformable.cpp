#include "Transformable.h"

Transformable::Transformable()
{
	position = glm::vec2(0, 0);
	origin = glm::vec2(0, 0);
	scale = glm::vec2(1, 1);
	rotation = 0;
	needUpdate = true;
}

void Transformable::setPosition(float x, float y)
{
	position = glm::vec2(x, y);
	needUpdate = true;
}

void Transformable::setPosition(glm::vec2 pos)
{
	setPosition(pos.x, pos.y);
}

void Transformable::setRotation(float angle) {
	rotation = angle;
	needUpdate = true;
}

void Transformable::setScale(float fx, float fy)
{
	scale = glm::vec2(fx, fy);
	needUpdate = true;
}

void Transformable::setScale(glm::vec2 scal)
{
	setScale(scal.x, scal.y);
}

void Transformable::setOrigin (float ox, float oy)
{
	origin = glm::vec2(ox, oy);
	needUpdate = true;
}

void Transformable::setOrigin (glm::vec2 or )
{
	setOrigin(or.x,or.y);
}

glm::vec2 Transformable::getPosition()
{
	return position;
}

glm::vec2 Transformable::getScale()
{
	return scale;
}

glm::vec2 Transformable::getOrigin()
{
	return origin;
}

glm::mat4 Transformable::getTransform()
{
	if (needUpdate) {
		transformMatrix = glm::translate(glm::mat4(1.0), glm::vec3(position.x, position.y, 0.f));
		
		//transformMatrix = glm::translate(transformMatrix, glm::vec3(origin.x, origin.y, 0.f));
		//transformMatrix = glm::rotate(transformMatrix, rotation, glm::vec3(0, 0, 0));
		transformMatrix = glm::scale(transformMatrix, glm::vec3(scale.x, scale.y, 1.f));
		transformMatrix = glm::translate(transformMatrix, glm::vec3(-origin.x, -origin.y, 0.f));
		
		needUpdate = false;
	}
	
	return transformMatrix;
}

