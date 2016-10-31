#include "SoundController.h"

SoundController::SoundController()
{
	engine = irrklang::createIrrKlangDevice();
	if (!engine)
	{
		printf("Could not startup engine\n");
		return; // error starting up the engine
	}

}

SoundController::~SoundController()
{
	engine->drop();
}

void SoundController::playSound(std::string s) {
	engine->play2D(s.c_str(), false);
}

void SoundController::playMusic(std::string s) {
	engine->play2D(s.c_str(), true);
}