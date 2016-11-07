/*
 * Screen.h
 *
 *  Created on: 23 Aug 2016
 *      Author: user
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include <iostream>
#include <SDL.h>
#include <string.h>
namespace Steves {

class Screen {
public:
	//Set Screen Parameters
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;
	Screen();
	bool init();
	int processEvents();
	void closeScreen();
	void update();
	void setPixel(int x, int y, Uint32 Colour);
	void clear(bool collisions);
	void boxBlur();


private:

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer1;
	Uint32 *m_buffer2;

};

}

#endif /* SCREEN_H_ */
