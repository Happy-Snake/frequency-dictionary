#include <SDL.h>
#include <SDL_TTF.h>
#include <string>
#include <iostream>
#include "../Headers/Tree.h"

extern int y;

void Control_keys_dict(int& key, SDL_Event &e, SDL_Surface* WindSurface, SDL_Surface* text, SDL_Color color, TTF_Font* font, int& beg, int& end, int number_of_words)
{
	int code = e.key.keysym.scancode;
	if (code == 81 && (end != number_of_words - 1 || key != 22))
	{
		SDL_FillRect(WindSurface, NULL, 0x000000);
		text = TTF_RenderUTF8_Solid(font, "Select word: ", color);
		key++;
		if (key == 23)
		{
			beg++;
			end++;
			key = 22;
		}
		y = 0;
	}
	if (code == 82 && (beg != 0 || key != 0))
	{
		SDL_FillRect(WindSurface, NULL, 0x000000);
		text = TTF_RenderUTF8_Solid(font, "Select word: ", color);
		key--;
		if (key == -1)
		{
			beg--;
			end--;
			key = 0;
		}
		y = 0;
	}
}

std::string print_dict(tree &dict, int number_of_words)
{
	SDL_Window* window = NULL;
	SDL_Surface* WindSurface = NULL;
	SDL_Surface* text = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	window = SDL_CreateWindow("Dictionary", 800, 50, 300, 615, SDL_WINDOW_SHOWN);

	WindSurface = SDL_GetWindowSurface(window);
	TTF_Font* font = TTF_OpenFont("../Project/Files/font.ttf", 20);


	bool loop = true;
	SDL_Event e;
	SDL_Color color{ 255,255,255 };

	SDL_StartTextInput();

	int key = 0;
	int code = 0;
	int current = 0;
	int beg = 0;
	int end = 22;

	do
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				loop = false;
			if (e.type == SDL_KEYDOWN)
				Control_keys_dict(key, e, WindSurface, text, color, font, beg, end, number_of_words);
		}
		y = 0;
		text = TTF_RenderUTF8_Solid(font, "Select word: ", color);
		SDL_Rect Rect = { 20,10,50,50 };
		SDL_BlitSurface(text, NULL, WindSurface, &Rect);
		SDL_UpdateWindowSurface(window);
		key = (key + end - beg + 1) % (end - beg + 1);
		
		dict.print(dict.root, text, Rect, font, WindSurface, color, window, beg, end, 0, key);
	} while (loop && e.key.keysym.scancode != 40);

	int cur = 0;
	std::string str;

	dict.find_word(dict.root, beg + key, cur, str);

	SDL_DestroyWindow(window);
	SDL_FreeSurface(WindSurface);
	SDL_FreeSurface(text);
	WindSurface = text = NULL;
	window = NULL;
	return str;
}