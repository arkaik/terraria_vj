#pragma once

#include <map>
#include "Texture.h"

class TextureFactory
{
public:
	TextureFactory() {};

	static TextureFactory &instance()
	{
		static TextureFactory T;

		return T;
	}
	

	Texture* getTexture(std::string name);

private:
	std::map<std::string, Texture*> M;
};

