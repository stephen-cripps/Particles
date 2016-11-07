/*
 * Particle.cpp
 *
 *  Created on: 4 Sep 2016
 *      Author: user
 */

#include "Particle.h"
#include <stdlib.h>
#include "Screen.h"
#include <math.h>

namespace Steves {

Particle::Particle() :
	m_x(0), m_y(0) { //initialises to center of screen

	speedScaler = 0.0000;
	m_speed = speedScaler * ((double) rand() / RAND_MAX);
	direction = 2 * M_PI * ((double) rand() / RAND_MAX); //initialise speed and direction for each particle

}

void Particle::update(double interval, bool collisions) {

	m_x += m_speed * cos(direction) * interval;
	m_y += m_speed * sin(direction) * interval; //update position based on speed and direction. Multiplying by interval between game loop iterations makes it run as same speed on all systems

	if (collisions) {//collisions with wall
		if (m_x >= 1 || m_x <= -1) {
			direction = M_PI - direction;
			if (direction <= 0) {
				direction += 2 * M_PI;
			}
		} else if (m_y <= -((double) Screen::SCREEN_HEIGHT
				/ Screen::SCREEN_WIDTH) || m_y
				>= ((double) Screen::SCREEN_HEIGHT / Screen::SCREEN_WIDTH)) {
			direction = 2 * M_PI - direction;
		}
	}

}

Uint32 Particle::setColour() {//sets colour based on speeeeeeeeeeed No idea how this works really.. copypasta, but uses SLH with hue based on speed then converts to RGB

	int S = 1;
	double L = 0.5; //from black to white (lightness)
	double H = 0.5 - (m_speed / (speedScaler * 2)); //goes from 0.5->0 (I think this is from cyan to red)(HUE)
	double var_2 = 0;

	if (L < 0.5)
		var_2 = L * (1 + S);
	else
		var_2 = (L + S) - (S * L);

	double var_1 = 2 * L - var_2;

	unsigned char R = (unsigned char) 255 * Hue_2_RGB(var_1, var_2,
			H + ((double) 1 / 3)); //this double wasnt copied and that fucked me
	unsigned char G = (unsigned char) 255 * Hue_2_RGB(var_1, var_2, H);
	unsigned char B = (unsigned char) 255 * Hue_2_RGB(var_1, var_2,
			H - ((double) 1 / 3));

	Uint32 colour = 0;

	colour += R;
	colour <<= 8;
	colour += G;
	colour <<= 8;
	colour += B;
	colour <<= 8;
	colour += 0xff;

	return colour;
}

double Particle::Hue_2_RGB(double v1, double v2, double vH) //Function Hue_2_RGB
{
	if (vH < 0)
		vH += 1;
	if (vH > 1)
		vH -= 1;
	if ((6 * vH) < 1)
		return (v1 + (v2 - v1) * 6 * vH);
	if ((2 * vH) < 1)
		return (v2);
	if ((3 * vH) < 2)
		return (v1 + (v2 - v1) * ((2 / 3) - vH) * 6);
	return (v1);
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

}
