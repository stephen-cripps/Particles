/*
 * Screen.cpp
 *
 *  Created on: 23 Aug 2016
 *      Author: user
 */

#include "Screen.h"
namespace Steves {

Screen::Screen() :
	m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL),
			m_buffer2(NULL) {

}
;

bool Screen::init() {

	//Check, initialisation
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	//Create SDL window.
	m_window = SDL_CreateWindow("Particle Explosion", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

	//Create renderer and texture
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (m_renderer == NULL) {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	if (m_texture == NULL) {
		SDL_DestroyTexture(m_texture);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	//Create buffer array, allocating space for each pixel
	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	//set initial buffer value
	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	return true;

}

void Screen::setPixel(int x, int y, Uint32 colour) {

	if (x <= 0 || x >= SCREEN_WIDTH || y <= 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	m_buffer1[(y * SCREEN_WIDTH) + x] = colour;
}

void Screen::update() {
	//update texture, clear and update renderer
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, sizeof(Uint32) * SCREEN_WIDTH);
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

int Screen::processEvents() {
	SDL_Event event;
	int eventValue;

	//Check for events and execute
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			eventValue = 1;
		}

		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {

				int x = event.button.x;
				int y = event.button.y;

				if (x >= SCREEN_WIDTH - 100 && x <= SCREEN_WIDTH - 50 && y
						>= 50 && y <= 100) {
					eventValue = 2;
				}else if(x >= SCREEN_WIDTH - 100 && x <= SCREEN_WIDTH - 50 && y
						>= 150 && y <= 200){
					eventValue = 3;
				}

			}
		}
	}

	return eventValue;
}

void Screen::boxBlur() {

	// Swap the buffers, so pixel current state is saved in m_buffer2 and we are drawing to m_buffer1.
	Uint32 *temp = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = temp;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {

			/*
			 * 0 0 0
			 * 0 1 0
			 * 0 0 0
			 */

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {
					int currentX = x + col;
					int currentY = y + row;

					if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY
							>= 0 && currentY < SCREEN_HEIGHT) {
						Uint32 colour = m_buffer2[currentY * SCREEN_WIDTH
								+ currentX];// finds position of current pixel in buffer array
						Uint8 red = colour >> 24; //Shifts colour value by 3 bits (8*3) and takes last 2 digits (as uint8) therefore extracting red value from colour
						Uint8 green = colour >> 16;
						Uint8 blue = colour >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;

					}
				}

			}
			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			Uint32 colour = 0;

			colour += red;
			colour <<= 8;
			colour += green;
			colour <<= 8;
			colour += blue;
			colour <<= 8;
			colour += 0xff;

			setPixel(x, y, colour); // sets pixel with average rgb colours


		}
	}
	for (int y = 50; y <= 100; y++) {//Sets blur button to on (green)
		for (int x = SCREEN_WIDTH - 100; x <= SCREEN_WIDTH - 50; x++) {

			Uint32 colour = (Uint32) 0x00ff00ff;
			setPixel(x, y, colour);
		}
	}
}

void Screen::clear(bool collisions) {
	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); // sets all pixels to black

	for (int y = 50; y <= 100; y++) {//Sets blur button to on (green)
		for (int x = SCREEN_WIDTH - 100; x <= SCREEN_WIDTH - 50; x++) {

			Uint32 colour = (Uint32) 0xff0000ff;
			setPixel(x, y, colour);
		}
	}
	if (collisions) {
		for (int y = 150; y <= 200; y++) {//Sets blur button to on (green)
			for (int x = SCREEN_WIDTH - 100; x <= SCREEN_WIDTH - 50; x++) {

				Uint32 colour = (Uint32) 0x00ff00ff;
				setPixel(x, y, colour);
			}
		}

	} else {
		for (int y = 150; y <= 200; y++) {//Sets blur button to on (green)
			for (int x = SCREEN_WIDTH - 100; x <= SCREEN_WIDTH - 50; x++) {

				Uint32 colour = (Uint32) 0xff0000ff;
				setPixel(x, y, colour);
			}
		}

	}
}

void Screen::closeScreen() {
	delete[] &m_buffer1;
	delete[] &m_buffer2;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();

}

}
