#pragma once
#include <SDL.h>
#include <SDL_TTF.h> 

struct node					//узлы дерева
{
	int count;
	std::string word;
	unsigned char height;
	node* left;
	node* right;
	node(std::string input_word, int k = 1)
	{
		word = input_word;
		count = k;
		left = right = 0;
		height = 1;
	}
};

struct tree				// дерево с корневым узлом root
{
public:
	node* root;
	node* add(node* p, std::string input_word);
	node* find(node* p, std::string input_word);
	int print(node* p, SDL_Surface* text, SDL_Rect Rect, TTF_Font* font, SDL_Surface* WindSurface, SDL_Color color, SDL_Window* window, int beg, int end, int count, int key);
	void find_word(node* p, int pos, int &count, std::string& str);
	tree(node* p)
	{
		root = p;
	}
private:
	void set_height(node* p);
	node* balance(node* p);
	unsigned char height(node* p);
	int height_diff(node* p);
	node* right_rotation(node* p);
	node* left_rotation(node* q);
};