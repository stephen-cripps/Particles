//============================================================================
// Name        : ParticleExplosion.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL.h>
#include <string.h>
#include "screen.h"
#include<math.h>
#include<STDLib.h>
#include<time.h>
#include "swarm.h"

using namespace Steves;

int main(int argc, char* argv[]) {

	srand(time(NULL));//Seeds the random funcion
	//initialise screen
	Screen screen;
	if (!screen.init()) {
		std::cout << "screen initialisation failed" << std::endl;
	}

	Swarm swarm;

	bool blurring = false;
	bool collisions = true;

	//Game Loop
	while (true) {



		double elapsed = SDL_GetTicks();

		if (!blurring) {
			screen.clear(collisions); //turn off for blur
		}
		swarm.update(elapsed, collisions); //updates particle positions

		const Particle * const pParticles = swarm.getParticles();

		for (int i = 0; i < Swarm::N_PARTICLES; i++) {

			Particle particle = pParticles[i]; //initiates a particle and finds its coord from pparticle
			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = (particle.m_y * Screen::SCREEN_WIDTH / 2)
					+ (Screen::SCREEN_HEIGHT / 2); //(Sets x and y axis of explosion to be the same to avoid oval shape)(centers vertically)


			Uint32 colour = particle.setColour(); //returns RGB colour value based on speed


			screen.setPixel(x, y, colour);

		}
		if(blurring){
		screen.boxBlur();
		}
		screen.update();



		if (screen.processEvents() == 1) {//Checks if x has been clicked
			break;
		}
		else if (screen.processEvents() == 2) {// Checks if mouse has been clicked on screen
			blurring = !blurring;
		}
		else if (screen.processEvents() == 3){
			collisions = !collisions;
		}

	}

	std::cout << "end of program" << std::endl;
	return 0;
}
