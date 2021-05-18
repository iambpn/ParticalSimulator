#include "Swarm.h"

namespace ParticleEmulation {
	Swarm::Swarm():
		last_time(0)
	{
		this->particles = new Particle[Swarm::NPARTICLES];
	}
	Swarm::~Swarm()
	{
		delete[] this->particles;
	}

	const Particle* const Swarm::getParticles() {
		return this->particles;
	}
	void Swarm::update(int elapsed)
	{
		// takng elapsed and calculating interval to make seed constant
		int interval = elapsed - this->last_time;
		for (int i = 0; i < ParticleEmulation::Swarm::NPARTICLES; i++) {
			this->particles[i].update(interval);
		}
		this->last_time = elapsed;
	}
}
