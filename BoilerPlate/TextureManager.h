#pragma once
#ifndef _TextureManager_
#define _TextureManager_
#include "iostream"
#include "SDL.h"
#include "map"
//Singleton Class
class TextureManager
{
public:
	bool load(std::string fileName, std::string id, SDL_Renderer* renderer);
	void draw(std::string id, int x, int y, int width, int heigth, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int heigth, int currentRow, int currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	static TextureManager* Instance();
private:
	TextureManager();
	~TextureManager();
	std::map<std::string, SDL_Texture*> m_textureMap;
	static TextureManager* m_instance;
};
#endif 