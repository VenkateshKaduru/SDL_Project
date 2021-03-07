#include "Swarm.h"

namespace venk {

	Swarm::Swarm(): lastTime(0) {
		m_pParticle = new Particle[NPARTICLE];
	}

	Swarm::~Swarm() {
		delete[]m_pParticle;
	}

	void Swarm::update(int elapse) {

		int interval = elapse - lastTime;
		for (size_t i = 0; i < Swarm::NPARTICLE; i++)
		{
			m_pParticle[i].update(interval);
		}
		lastTime = elapse;
	}
}