#include <iostream>
#include <vector>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../Headers/initArray.h"

using namespace std;

vector<vector<char>> initArray () {
    struct winsize w;                                       // Gets the size of the terminal window 
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int rows = w.ws_row;                                    // Gets the rows & columns from the struct
    int cols = w.ws_col;
    vector<char> row(cols, ' ');                            // Poulates a 2d int vector with all 0's for now
    vector<vector<char>> v(rows, row);
    return v;
}