#include <iostream>
#include "Screen.h" // also includes SDL.h
#include "Swarm.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {

	srand(time(NULL));

	ParticleEmulation::Screen screen = ParticleEmulation::Screen();

	if (screen.init() == false) {
		std::cout << "Error Initializing" << std::endl;
	}

	ParticleEmulation::Swarm swarm = ParticleEmulation::Swarm();

	unsigned char red, green, blue;
	int elapsed;
	// Game Loop
	while (true) {
		// update and draw particles
		elapsed = SDL_GetTicks();
		red = (1 + sin(elapsed * 0.0001)) * (255 / 2);
		green = (1 + sin(elapsed * 0.0002)) * (255 / 2);
		blue = (1 + sin(elapsed * 0.0003)) * (255 / 2);

		swarm.update(elapsed);

		// double const before and after pointer means it do not allow to chnage the pointer address and the value it holds respectively.
		const ParticleEmulation::Particle* const particles = swarm.getParticles();

		for (int i = 0; i < ParticleEmulation::Swarm::NPARTICLES; i++) {
			ParticleEmulation::Particle particle = particles[i];

			// mapping the x,y coordinate of particle to screen.
			// (x=0 +1) * width/2 : +1 because center of screen is width/2]
			int x = (particle.x + 1) * ParticleEmulation::Screen::SCREEN_WIDTH/2; 

			// (y=0 * width/2)+height/2 : +height/2 because to align particle into center of the screen and make chape circle.
			// doing this will change the bound of y axis.
			int y = particle.y * ParticleEmulation::Screen::SCREEN_WIDTH/2 + ParticleEmulation::Screen::SCREEN_HEIGHT / 2;
			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();

		screen.update();
		if (screen.processEvents()) {
			break;
		}
	}

	screen.close();
}