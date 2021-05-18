#pragma once
namespace ParticleEmulation {
	class Particle
	{
	public:
		double x;
		double y;
		double speed;
		double direction;
	public:
		Particle();
		void update(int interval);
		void init();
	};
}
