#pragma once

#include"Particle.h"
namespace venk {

	class Swarm{
	public:
		const static int NPARTICLE = 5000;
	private:
		Particle * m_pParticle;
		int lastTime;

	public:
		Swarm();
		virtual ~Swarm();
		void update(int elapse);
		const Particle *const getParticle() { return m_pParticle; };
	};

}


