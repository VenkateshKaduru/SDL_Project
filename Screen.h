#pragma once

#include<SDL.h>
namespace venk {

	class Screen
	{
	public: 
		const static int window_Width = 800;
		const static int window_Height = 600;
	private:
		SDL_Window *main_window;
		SDL_Renderer *rendererWindow;
		SDL_Texture *texture;
		Uint32 *buffer1;
		Uint32 *buffer2;

	public:
		Screen();
		bool init();
		void update();
		void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		bool processEvent();
		void close();
		//void clear();
		void boxBlur();
	};

}


