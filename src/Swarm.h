/*
 * Swarm.h
 *
 *  Created on: 4 Sep 2016
 *      Author: user
 */

#ifndef SWARM_H_
#define SWARM_H_
#include "Particle.h"

namespace Steves {

class Swarm {

public:
	const static int N_PARTICLES = 5000;

	double interval;
	double prevElapsed;
private:
	Particle *m_pParticles;

public:
	Swarm();
	virtual ~Swarm();

	const Particle * const getParticles(){ return m_pParticles; }; //a constant pointer to a particle that is constant

	void update(double elapsed,  bool collisions);
};

}

#endif /* SWARM_H_ */
