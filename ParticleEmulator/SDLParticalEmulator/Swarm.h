#pragma once
#include "Particle.h"
namespace ParticleEmulation {
	class Swarm
	{
	public:
		static const int NPARTICLES = 5000;
	private:
		Particle* particles;
		int last_time;
	public:
		Swarm();
		~Swarm();
		const Particle* const getParticles();
		void update(int elapsed);
	};
}
