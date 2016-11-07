/*
 * Swarm.cpp
 *
 *  Created on: 4 Sep 2016
 *      Author: user
 */

#include "Swarm.h"

namespace Steves {

Swarm::Swarm(): prevElapsed(0){
	m_pParticles = new Particle[N_PARTICLES]; //new particle array of size nparticles
}

void Swarm::update(double elapsed, bool collisions) {

	interval = elapsed - prevElapsed; //gets time between loop iterations

	for (int i = 0; i < Swarm::N_PARTICLES; i++) {//calls for uptate on each indivitual particle
		m_pParticles[i].update(interval, collisions);
	}

	prevElapsed = elapsed;
}

Swarm::~Swarm() {
	delete[] m_pParticles;
}

}
