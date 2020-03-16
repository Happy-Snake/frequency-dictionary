#include <SDL.h>
#include <SDL_TTF.h>
#include <iostream>
#include<cctype>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include "../Headers/Tree.h"

using namespace std;

unsigned char tree::height(node* p)				//высота узла
{
	if (p)
		return p->height;
	else
		return 0;
}

int tree::height_diff(node* p)					//разница высот узлов
{
	return height(p->right) - height(p->left);
}

void tree::set_height(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	if (hl > hr)
		p->height = hl + 1;
	else
		p->height = hr + 1;
}

node* tree::right_rotation(node* p)
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	set_height(p);
	set_height(q);
	return q;
}

node* tree::left_rotation(node* q)
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	set_height(q);
	set_height(p);
	return p;
}

node* tree::balance(node* p)
{
	set_height(p);
	if (height_diff(p) == 2)
	{
		if (height_diff(p->right) == -1)
			p->right = right_rotation(p->right);
		return left_rotation(p);
	}
	if (height_diff(p) == -2)
	{
		if (height_diff(p->left) == 1)
			p->left = left_rotation(p->left);
		return right_rotation(p);
	}
	return p;
}

node* tree::add(node* p, string input_word)				// вставка ключа k в дерево с корнем p
{
	if (!p) return new node(input_word);
	if (input_word.compare(p->word) < 0)
		p->left = add(p->left, input_word);
	else
		p->right = add(p->right, input_word);
	return balance(p);
}

node* tree::find(node* p, string input_word) 
{
	if (!p) return 0; 
	if (!input_word.compare(p->word))
		return p;
	if (input_word.compare(p->word) < 0)
		return find(p->left, input_word);
	else
		return find(p->right, input_word);
}

int y = 0;

int tree::print(node* p, SDL_Surface* text, SDL_Rect Rect, TTF_Font* font, SDL_Surface* WindSurface, SDL_Color color, SDL_Window* window, int beg, int end, int count, int key)
{
	if (p)
		if (p->count != 0)
		{
			count = print(p->left, text, Rect, font, WindSurface, color, window, beg, end, count, key);

			if (count >= beg && count <= end)
			{
				if (beg + key == count)
					text = TTF_RenderUTF8_Solid(font, (" * " + p->word + " - " + to_string((p->count))).c_str(), color);
				else 
					text = TTF_RenderUTF8_Solid(font, ("   " + p->word + " - " + to_string((p->count))).c_str(), color);
				Rect = { 30,40 + y,50,50 };
				y += 25;
				SDL_BlitSurface(text, NULL, WindSurface, &Rect);
				SDL_UpdateWindowSurface(window);
			}
			count++;
			count = print(p->right, text, Rect, font, WindSurface, color, window, beg, end, count, key);
		}
	return count;
}

void tree::find_word(node* p, int pos, int& count, string& str)
{
	if (p)
		if (p->count != 0)
		{
			find_word(p->left, pos, count, str);

			if (count == pos)
				str = p->word;
			count++;

			find_word(p->right, pos, count, str);
		}
	return;
}