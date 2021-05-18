#include "Particle.h"
#include <stdlib.h>
#include <SDL_stdinc.h>
#include <math.h>

ParticleEmulation::Particle::Particle() :
	x(0), y(0)
{
	this->init();
}

void ParticleEmulation::Particle::init() {
	this->x = 0;
	this->y = 0;
	this->direction = (2 * M_PI * rand()) / RAND_MAX;
	this->speed = (0.04 * rand()) / RAND_MAX;
	this->speed *= this->speed; // tweaking particles
}

void ParticleEmulation::Particle::update(int interval)
{
	this->direction += interval * 0.0003;
	double xspeed = this->speed * cos(this->direction);
	double yspeed = this->speed * sin(this->direction);

	this->x += xspeed * interval;
	this->y += yspeed * interval;

	// bouncing particle
	/* particle is bonced by checking its x,y position.
	* edge x,y position is calculated by using the aspect ratio.
	* eg. screen size = w 800 x h 600 then aspect ratio = 4:3
	* therefore,  1 screen is divided into 4 parts into width and 3 parts into height
	* since we have mapped the height or y axix to width in SDLParticalEmulator, we nee to use aspect ratio of width.
	* 1part of width = 1/4 = 0.25
	* yaxix  = 3*0.25 = 0.75;
	*/

	if (this->x <= -1.0 || this->x >= 1.0) {
		//this->x = -this->x; // for bouncing
		this->init(); // re initializing the particle out of screen to center
	}
	if (this->y <= -0.75 || this->y >= 0.75) {
		//this->y = -this->y; // for bouncing
		this->init();
	}

	// randomly re intialising
	if (rand() < RAND_MAX / 100) {
		this->init();
	}
}
