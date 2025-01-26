#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "Headers/initArray.h"
#include "Headers/printScreen.h"

using namespace std;

int direction = 2;                              // Down, Right, Up, Left

vector<vector<char>> updateScreen (vector<vector<char>> screen, vector<vector<int>> snake, vector<int> food);
vector<vector<int>> calcSnake (vector<vector<int>> prevSnake, int direction, bool removeTail);
bool validateChoice(char choice, int direction);
bool foodEaten (vector<vector<int>> snake, vector<int> food);
vector<int> spawnFood(vector<vector<int>> snake);
bool checkSnakeCollision (vector<vector<int>> snake);

vector<vector<char>> screen = initArray();
int screenHeight = screen.size();                   // Global screen size variables
int screenWidth = screen[0].size();                 

int main() {
    srand(time(0));
    initscr();
    noecho();
    cbreak();
    timeout(0);  // Make getch non-blocking
    curs_set(0);
    
    vector<vector<int>> snake = {{screenHeight/2, screenWidth/2+4}, {screenHeight/2, screenWidth/2+3}, {screenHeight/2, screenWidth/2+2}, {screenHeight/2, screenWidth/2+1}, {screenHeight/2, screenWidth/2}};
    
    int ch;
    int speed = 100000;
    bool sFood = true;
    bool removeTail = true;
    vector<int> food;

    while (true) {
        
        
        ch = getch();

        if (ch!= ERR && validateChoice(ch, direction)) {
        switch (ch) {
            case 'w':
                direction = 3;
                break;
            case 'a':
                direction = 4;
                break;
            case 's':
                direction = 1;
                break;
            case 'd':
                direction = 2;
                break;
            }
        }

        if (sFood) food = spawnFood(snake);
        sFood = false;
        if (foodEaten(snake, food)) {
            sFood = true;
            removeTail = false;
            speed*=0.99;
        }
        
        snake = calcSnake(snake, direction, removeTail);
        removeTail = true;
        screen = updateScreen(screen, snake, food);
        clear();
        printScreen(screen);
        refresh();
        usleep(100000);
    }
    endwin();
    return 0;

}


bool foodEaten (vector<vector<int>> snake, vector<int> food) {
    for (vector<int> pos : snake) {
        if (pos == food) return true;
    }
    return false;
}


bool validateChoice(char choice, int direction) {
    int temp;
    switch (choice) {
            case 'w':
                temp = 3;
                break;
            case 'a':
                temp = 4;
                break;
            case 's':
                temp = 1;
                break;
            case 'd':
                temp = 2;
                break;
        }
        return (abs(temp-direction)!=2);                // Checks if the input is valid
}


vector<int> spawnFood (vector<vector<int>> snake) {
    bool valid = false;
    vector<int> food;
    while (!valid) {
        food = {rand() % screenHeight, rand() % screenWidth};
        valid = true;
        for (vector<int> snakeCord : snake) {
            if (snakeCord == food) {
                valid = false;
                break;
            }
        }
    }
    return food;
}


vector<vector<char>> updateScreen (vector<vector<char>> screen, vector<vector<int>> snake, vector<int> food) {
    screen = initArray();
    for (vector<int> pos : snake) {
        screen[pos[0]][pos[1]] = '#';
    }
    screen[food[0]][food[1]] = '8';
    return screen;
}


vector<vector<int>> calcSnake (vector<vector<int>> snake, int direction, bool removeTail) {
    if (removeTail) 
        snake.pop_back();                               // Removing the last element (the tail)
    vector<int> head = snake[0];
    vector<int> newPos;
    switch (direction) {
        case 1: 
            newPos = {head[0]+1, head[1]};
            break;
        case 2: 
            newPos = {head[0], head[1]+1};
            break;
        case 3: 
            newPos = {head[0]-1, head[1]};
            break;
        case 4: 
            newPos = {head[0], head[1]-1};
            break;
    }
    snake.insert(snake.begin(), newPos);
    return snake;
}