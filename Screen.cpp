#include<iostream>
#include "Screen.h"

 namespace venk {

	Screen::Screen():main_window(NULL), rendererWindow(NULL), texture(NULL), buffer1(NULL), buffer2(NULL) {

	}
	
	bool Screen::init() {

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "SDL Init failed. " << SDL_GetError() << std::endl;
			return false;
		}

		main_window = SDL_CreateWindow("Interactive Fire Explosion", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_CENTERED, window_Width, window_Height, SDL_WINDOW_SHOWN);
		if (main_window == NULL)
		{
			SDL_Quit();
			return false;
		}

		rendererWindow = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (rendererWindow == NULL)
		{
			std::cout << "Could not create renderer." << std::endl;
			SDL_DestroyWindow(main_window);
			SDL_Quit();
			return false;
		}

		texture = SDL_CreateTexture(rendererWindow, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, window_Width, window_Height);
		if (texture == NULL)
		{
			std::cout << "Could not create texture." << std::endl;
			SDL_DestroyRenderer(rendererWindow);
			SDL_DestroyWindow(main_window);
			SDL_Quit();
			return false;
		}
		buffer1 = new Uint32[window_Width*window_Height];
		buffer2 = new Uint32[window_Width*window_Height];

		memset(buffer1, 0, window_Width* window_Height * sizeof(Uint32));
		memset(buffer2, 0, window_Width* window_Height * sizeof(Uint32));

		return true;
	}

	void Screen::boxBlur() {
		Uint32 *temp = buffer1;
		buffer1 = buffer2;
		buffer2 = temp;

		for (size_t y = 0; y < window_Height; y++)
		{
			for (size_t x = 0; x < window_Width; x++) {

				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;

				for (int row = -1; row <= 1; row++)
				{
					for (int col = -1; col <= 1; col++)
					{
						int currentX = x + col;
						int currentY = y + row;

						if (currentX>=0 && currentX < window_Width && currentY >= 0 && currentY < window_Height)
						{
							Uint32 color = buffer2[currentY * window_Width + currentX];

							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redTotal += red;
							greenTotal += green;
							blueTotal += blue;

						}
					}
				}

				Uint8 red = redTotal/9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;

				setPixel(x, y, red, green,blue);

			}
		}
	}

	/*void Screen::clear() {
		memset(m_buffer1, 0, S_Width* S_Height * sizeof(Uint32));
		memset(m_buffer2, 0, S_Width* S_Height * sizeof(Uint32));

	}*/


	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
		
		if (x < 0 || x >= window_Width || y < 0 || y >= window_Height) {
			return;
		}

		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		buffer1[(y * window_Width) + x] = color;
	}
	void Screen::update() {

		SDL_UpdateTexture(texture, NULL, buffer1, window_Width * sizeof(Uint32));
		SDL_RenderClear(rendererWindow);
		SDL_RenderCopy(rendererWindow, texture, NULL, NULL);
		SDL_RenderPresent(rendererWindow);
	}
	bool Screen::processEvent() {

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) {
				return false;
			}
		}
		return true;
	}
	void Screen::close() {
		delete[] buffer1;
		delete[] buffer2;
		SDL_DestroyRenderer(rendererWindow);
		SDL_DestroyTexture(texture);
		SDL_DestroyWindow(main_window);
		SDL_Quit();
	}

}
