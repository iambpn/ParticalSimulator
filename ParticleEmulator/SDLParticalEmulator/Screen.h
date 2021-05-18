#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"
namespace ParticleEmulation {
	class Screen {
	public:
		static const int SCREEN_WIDTH = 800;
		static const int SCREEN_HEIGHT = 600;
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		Uint32* pixelBuffer;
		Uint32* blurBuffer;

	public:
		Screen();
		bool init();
		bool processEvents();
		void setPixel(int w, int h, Uint8 red, Uint8 green, Uint8 blue);
		void update();
		void fillScreenWith(Uint8 color = 0);
		void boxBlur();
		void close();
	};
}