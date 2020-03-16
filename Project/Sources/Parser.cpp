#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <iterator>
#include <vector>
#include <fstream>
#include <iostream>

#include "../Headers/Tree.h"

using namespace std;

tree file_parser(string file_name, tree &dict, int& count)
{
	string file_path = "../Project/Files/" + file_name;
	ifstream file;
	file.open(file_path, ios::in);
	string current_word;
	vector <string> all_words;
	while (!file.eof())
	{
		char a = file.get();
		if (a >= 65 && a <= 90 || a >= 97 && a <= 122 || a >= 128 && a <= 175 || a >= 224 && a <= 243)
			current_word += tolower(a);
		else
			if (a == 32)
			{
				if (!current_word.empty())
					 all_words.push_back(current_word);
				current_word.clear();
			}
	}
	if (!current_word.empty())
		all_words.push_back(current_word);
	while (!all_words.empty())
	{
		if (dict.find(dict.root, all_words.back()) == 0)
		{
			dict.root = dict.add(dict.root, all_words.back());
			count++;
		}
		else
			dict.find(dict.root, all_words.back())->count++;
		all_words.pop_back();
	}
	return dict;
}