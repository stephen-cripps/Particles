/*
 * Particle.h
 *
 *  Created on: 4 Sep 2016
 *      Author: user
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <SDL.h>

namespace Steves {

struct Particle {

	double m_x;
	double m_y;
	double m_speed;
	double direction;
	double speedScaler;


public:
	Particle();
	virtual ~Particle();
	void update(double interval,  bool collisions);
	Uint32 setColour();
	double Hue_2_RGB( double v1,double v2,double vH );
};

}

#endif /* PARTICLE_H_ */
