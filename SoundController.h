#pragma once

#include <irrKlang.h>
#include <iostream>
#include <string>

class SoundController
{
public:

	static SoundController &instance()
	{
		static SoundController G;

		return G;
	}

	SoundController();
	~SoundController();
	void playSound(std::string s);
	void playMusic(std::string s);

private:
	irrklang::ISoundEngine* engine;
};