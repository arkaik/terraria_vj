#pragma once

class BasicScene
{
public:
	//BaseScene();
	//~BaseScene();

	virtual void init() = 0;
	virtual void update(int deltatime) = 0;
	virtual void render() = 0;
	virtual BasicScene* changeState() = 0;

};