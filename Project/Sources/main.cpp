#include <iostream>

#include "../Headers/Parser.h"
#include "../Headers/Tree.h"
#include "../Headers/File_menu.h"
#include "../Headers/Text_window.h"

using namespace std;


int main(int argc, char *argv[])
{
	char a = '\0';
	node root(&a, 0);
	tree dict(&root);
	string file_name = Print_Files_Menu();
	if (file_name[0] != '\0')
	{
		string file_path = "../Project/Files/" + file_name;
		int number_of_words = 0;
		dict = file_parser(file_name, dict, number_of_words);
		Print_Text(file_name, dict, number_of_words);
	}
	return 0;
}