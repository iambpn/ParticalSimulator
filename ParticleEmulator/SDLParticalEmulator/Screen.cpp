#include "Screen.h"
#include <iostream>

namespace ParticleEmulation {
	Screen::Screen() :
		window(NULL), renderer(NULL), texture(NULL),
		pixelBuffer(NULL), blurBuffer(NULL) {}

	bool Screen::init() {
		if (SDL_Init(SDL_INIT_VIDEO) > 0) {
			return false;
		}

		this->window = SDL_CreateWindow("Particle Explosinon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (this->window == NULL) {
			SDL_Quit();
			return false;
		}

		this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);
		this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT);

		if (this->renderer == NULL) {
			return false;
		}

		if (this->texture == NULL) {
			SDL_DestroyRenderer(this->renderer);
			return false;
		}

		this->pixelBuffer = new Uint32[Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT];
		this->blurBuffer = new Uint32[Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT];
		this->fillScreenWith();

		return true;
	}

	bool Screen::processEvents() {
		SDL_Event event;

		// check for events
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return true;
			}

			SDL_Delay(20);
		}
		return false;
	}

	void Screen::setPixel(int w, int h, Uint8 red, Uint8 green, Uint8 blue)
	{
		// bound checking
		if (w < 0 || w >= ParticleEmulation::Screen::SCREEN_WIDTH ||
			h < 0 || h >= ParticleEmulation::Screen::SCREEN_HEIGHT) {
			return;
		}

		//<< is left shift operator
		Uint32 color = 0;
		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 255; //alfa

		this->pixelBuffer[(h * Screen::SCREEN_WIDTH) + w] = color;
	}

	void Screen::update()
	{
		SDL_UpdateTexture(texture, NULL, this->blurBuffer, Screen::SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	void Screen::fillScreenWith(Uint8 color)
	{
		// set 255 or FF to the pixelbuffer memory byte by byte.
		memset(this->pixelBuffer, color, Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT * sizeof(Uint32));
		memset(this->blurBuffer, color, Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT * sizeof(Uint32));
	}

	void Screen::boxBlur()
	{
		// swap buffer, so pixel is in boxbuffer and we are drawing to pixelBuffer.
		Uint32* temp = this->blurBuffer;
		this->blurBuffer = this->pixelBuffer;
		this->pixelBuffer = temp;

		for (int y = 0; y < ParticleEmulation::Screen::SCREEN_HEIGHT; y++) {
			for (int x = 0; x < ParticleEmulation::Screen::SCREEN_WIDTH; x++) {
				/*
				* 0 0 0
				* 0 1 0
				* 0 0 0
				*/
				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;
				for (int row = -1; row <= 1; row++) {
					for (int col = -1; col <= 1; col++) {
						int currentx = x + col;
						int currenty = y + row;
						if (currentx >= 0 && currentx < ParticleEmulation::Screen::SCREEN_WIDTH
							&& currenty >= 0 && currenty < ParticleEmulation::Screen::SCREEN_HEIGHT) {
							Uint32 color = this->blurBuffer[currenty * ParticleEmulation::Screen::SCREEN_WIDTH + currentx];
							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redTotal += red;
							greenTotal += green;
							blueTotal += green;
						}
					}
				}
				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;
				
				this->setPixel(x, y, red, green, blue);
			}
		}
	}

	void Screen::close() {
		delete[]  this->pixelBuffer;
		delete[]  this->blurBuffer;
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}