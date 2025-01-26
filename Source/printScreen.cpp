#include <iostream>
#include <vector>
#include <ncurses.h>
#include "../Headers/printScreen.h"

using namespace std;

void printScreen (vector<vector<char>> v) {
    for(int i=0;i<v.size();i++){                        // Prints it out line by line
		for(int j=0;j<v[i].size();j++)
			addch(v[i][j]);						// This HAS to be addch b/c we are in an ncurses terminal
	}											// Dont need the extra space b/c the terminal automatically adds a newline (i think idrk tbh)
}