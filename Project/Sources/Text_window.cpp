#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <SDL_TTF.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "../Headers/Tree.h"
#include "../Headers/Dict.h"

using namespace std;

class word
{
public:
	string str;
	bool is_searched;
	word(string w, bool s = 0)
	{
		str = w;
		is_searched = s;
	}
};

void break_text(string file_name, vector <vector <word>> &strings, string chosen = " ")
{
	ifstream file;
	string file_path = "../Project/Files/" + file_name;
	file.open(file_path, ios::in);

	strings.clear();
	vector <word> cur_string;
	string buff;
	while (file.eof() == false)
	{
		int j;
		for (int i = buff.size(); i < 80 && file.eof() == false; i++)
		{
			char a;
			file.get(a);
			if (a == 10)
			{
				word cur_word(buff);
				if (buff == chosen + " " || buff == chosen + "." || buff == chosen + ",")
					cur_word.is_searched = true;
				cur_string.push_back(cur_word);
				strings.push_back(cur_string);
				cur_string.clear();
				buff.clear();
				break;
			}
			buff += a;
			if (a == 32)
			{
				word cur_word(buff);
				if (buff == chosen + " " || buff == chosen + "." || buff == chosen + ",")
					cur_word.is_searched = true;
				cur_string.push_back(cur_word);
				buff.clear();
			}
		}
		if (!buff.empty() && file.eof() == true)
		{
			buff[buff.size() - 1] = '\0';
			word cur_word(buff);
			if (buff == chosen + " " || buff == chosen + "." || buff == chosen + "," || buff == chosen + '\0')
				cur_word.is_searched = true;
			cur_string.push_back(cur_word);
		}
		strings.push_back(cur_string);
		cur_string.clear();
	}
}

void Print_Text(string file_name, tree &dict, int number_of_words)
{
	vector <vector <word>> strings;

	break_text(file_name, strings);

	SDL_Window* window = NULL;
	SDL_Surface* WindSurface = NULL;
	SDL_Surface* text = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	window = SDL_CreateWindow(file_name.c_str(), 50, 50, 750, 615, SDL_WINDOW_SHOWN);

	WindSurface = SDL_GetWindowSurface(window);
	TTF_Font* headline_font = TTF_OpenFont("../Project/Files/font.ttf", 35);
	TTF_Font* font = TTF_OpenFont("../Project/Files/font.ttf", 20);


	bool loop = true;
	SDL_Event e;
	SDL_Color color{ 255,255,255 };
	SDL_Color color_for_chosen_word{ 197, 15, 31 };


	SDL_StartTextInput();

	int curr_y = 0;
	int curr_x = 0;
	do
	{

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				loop = false;
			if (e.type == SDL_KEYDOWN)
				if (e.key.keysym.scancode == 40)
				{
					string cur_str;
					cur_str = print_dict(dict, number_of_words);
					break_text(file_name, strings, cur_str);
					SDL_FillRect(WindSurface, NULL, 0x000000);
					SDL_UpdateWindowSurface(window);
				}
			if (e.type == SDL_MOUSEWHEEL)
			{
				if (e.wheel.y > 0 && curr_y > 0)
				{
					SDL_FillRect(WindSurface, NULL, 0x000000);
					SDL_UpdateWindowSurface(window);
					curr_y--;
				}
				if (e.wheel.y < 0 && curr_y < strings.size())
				{
					SDL_FillRect(WindSurface, NULL, 0x000000);
					SDL_UpdateWindowSurface(window);
					curr_y++;
				}
			}
		text = TTF_RenderUTF8_Solid(headline_font, file_name.c_str(), color);
		SDL_Rect Rect = { 20,10,50,50 };
		SDL_BlitSurface(text, NULL, WindSurface, &Rect);
		SDL_UpdateWindowSurface(window);
		int y = 15;
		int x = 20;
		for (int i = 0; i < 22 && i < strings.size() - curr_y; i++)
		{
			for (int j = 0; j < strings[curr_y + i].size(); j++)
			{
				if (strings[curr_y + i][j].is_searched == true)
					text = TTF_RenderUTF8_Solid(font, strings[curr_y + i][j].str.c_str(), color_for_chosen_word);
				else
					text = TTF_RenderUTF8_Solid(font, strings[curr_y + i][j].str.c_str(), color);
				Rect = { x,40 + y,50,50 };
				if(text != nullptr)
					x += text->w;
				SDL_BlitSurface(text, NULL, WindSurface, &Rect);
				SDL_UpdateWindowSurface(window);
			}
			y += 25;
			x = 20;
		}
		
		}
	} while (loop);

	SDL_DestroyWindow(window);
	SDL_FreeSurface(WindSurface);
	SDL_FreeSurface(text);
	WindSurface = text = NULL;
	window = NULL;
	SDL_Quit();
	return;
}