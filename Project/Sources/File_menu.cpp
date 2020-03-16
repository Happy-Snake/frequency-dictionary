#include <SDL.h>
#include <SDL_TTF.h>
#include <Windows.h>
#include <string>
#include <vector>


using namespace std;

void Get_List_Of_Files(vector<string>& list_of_files)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf = FindFirstFile("../Project/Files/*.txt", &FindFileData);
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			list_of_files.push_back(FindFileData.cFileName);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
	return;
}

void Control_keys(int& key, SDL_Event &e, SDL_Surface* WindSurface, SDL_Surface* text, SDL_Color color, TTF_Font* font)
{
	int code = e.key.keysym.scancode;
	if (code == 81)
	{
		SDL_FillRect(WindSurface, NULL, 0x000000);
		text = TTF_RenderUTF8_Solid(font, "Select file: ", color);
		key++;
	}
	if (code == 82)
	{
		SDL_FillRect(WindSurface, NULL, 0x000000);
		key--;
	}
}

string Print_Files_Menu ()
{

	SDL_Window* window = NULL;
	SDL_Surface* WindSurface = NULL;
	SDL_Surface* text = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	window = SDL_CreateWindow("File selection menu", 50, 50, 800, 600, SDL_WINDOW_SHOWN);

	WindSurface = SDL_GetWindowSurface(window);
	TTF_Font* font = TTF_OpenFont("../Project/Files/font.ttf", 20);


	bool loop = true;
	SDL_Event e;
	SDL_Color color{ 255,255,255 };

	SDL_StartTextInput();

	vector <string> files;
	Get_List_Of_Files(files);
	int key = 0;
	int code = 0;
	int current = 0;
	do
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				loop = false;
			if (e.type == SDL_KEYDOWN)
				Control_keys(key, e, WindSurface, text, color, font);
		}
		text = TTF_RenderUTF8_Solid(font, "Select file: ", color);
		SDL_Rect Rect = { 20,10,50,50 };
		SDL_BlitSurface(text, NULL, WindSurface, &Rect);
		SDL_UpdateWindowSurface(window);
		key = (key + files.size()) % files.size();
		for (int i = 0; i < files.size(); i++)
		{
			SDL_Rect tRect = { 20,40 + 30 * i,50,50 };
			if (i == key)
				text = TTF_RenderUTF8_Solid(font, ("* " + files[i]).c_str(), color);
			else 
				text = TTF_RenderUTF8_Solid(font, ("  " + files[i]).c_str(), color);
			SDL_BlitSurface(text, NULL, WindSurface, &tRect);
			SDL_UpdateWindowSurface(window);
		}
	} while (loop && e.key.keysym.scancode != 40);

	SDL_DestroyWindow(window);
	SDL_FreeSurface(WindSurface);
	SDL_FreeSurface(text);
	WindSurface = text = NULL;
	window = NULL;
	SDL_Quit();
	if (loop == false)
		return '\0';
	return files[key];
}