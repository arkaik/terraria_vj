#include "TextureFactory.h"

Texture * TextureFactory::getTexture(std::string name)
{
	if (M[name] == nullptr) {
		M[name] = new Texture();
		M[name]->loadFromFile(name, TEXTURE_PIXEL_FORMAT_RGBA);
		
	}
	return M[name];
}
