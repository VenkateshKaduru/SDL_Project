#include<iostream>
#include<SDL.h>
#include<cstring>
#include<stdlib.h>
#include<time.h>
#include"Screen.h"
#include"Swarm.h"


using namespace venk;

int main(int argc, char *argv[]) {

	//srand(time(NULL));

	Screen screen;
	if (screen.init() == false)
	{
		std::cout << "SDL failed to initialise."<<SDL_GetError() << std::endl;
	}

	Swarm swarm;
	while (true)
	{
		int elapse = SDL_GetTicks();
		swarm.update(elapse);

		unsigned char red = (unsigned char)((1 + sin(elapse*0.0004)) * 128);
		unsigned char green = (unsigned char)((1 + sin(elapse*0.0005)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapse*0.0006)) * 128);

		const Particle *const pParticles = swarm.getParticle();
		for (size_t i = 0; i < Swarm::NPARTICLE; i++)
		{
			Particle partcle = pParticles[i];

			int x = (partcle.m_x + 1)* Screen::window_Width / 2;
			//int y = (partcle.m_y + 1)* Screen::S_Width * Screen::S_Height/ 2;
			int y = partcle.m_y * Screen::window_Width / 2 + Screen::window_Height/2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();
		//update
		
		/*for (size_t y = 0; y < Screen::S_Height; y++)
		{
			for (size_t x = 0; x < Screen::S_Width; x++) {
				screen.setPixel(x, y, red, green, blue);
			}
		}*/
		
		screen.update();

		if (screen.processEvent()==false)
		{
			break;
		}	

	}
	screen.close();
	
	return EXIT_SUCCESS;
}