// Bradford Bush
// CSC_690C
// C Programming assignment #2
// 7/26/2024

/* Snake.c is a simple, console-based, snake game in which the player uses 'w' 's' 'a' and 'd' for directionality.
   The player controls the snake that moves within a fixed grid with the goal of eating random fruits that increases
   the score by 10 every time a fruit is eaten. The game will run in a continuous loop until the player decides
   to end the program manually or if the snake collides with its tail.
   To end the game prematurely you use 'x'.
*/

// imports
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// global variables used to track game state
int width = 25, height = 25; // dimensions of the game area
int gameover, score; // gameover flag and score
int x, y, fruitX, fruitY; // coordinates of the snake's head and the fruit
int tailX[100], tailY[100]; // arrays to store the positions of the snake's tail
int tailLength; // length of the snake's tail
int dir; // variable to store direction (0=stop, 1=left, 2=right, 3=up, 4=down)

// function to setup initial game state
void setup() {
    gameover = 0; // game is not over
    dir = 0; // initial direction is stop
    score = 0; // initial score is zero
    x = width / 2; // initial position of the snake's head (x coordinate)
    y = height / 2; // initial position of the snake's head (y coordinate)
    fruitX = rand() % width; // random x coordinate for the fruit
    fruitY = rand() % height; // random y coordinate for the fruit
    tailLength = 0; // initial tail length is zero
}

// function that draws the game area using a bounding box
void draw() {
    system("cls"); // clears the console

    // draws top border
    for (int i = 0; i < width + 2; i++) 
        printf("#");
    printf("\n");

    // draws game area with snake and fruit
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) // draws left border
                printf("#");
            if (i == y && j == x) // draws snakes head
                printf("O");
            else if (i == fruitY && j == fruitX) // draws fruit (the 'F' char) 
                printf("F");
            else {
                int print = 0;
                // draws snakes tail
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = 1;
                    }
                }
                if (!print)
                    printf(" ");
            }
            if (j == width - 1) // draws right border
                printf("#");
        }
        printf("\n");
    }

    // draws the bottom border
    for (int i = 0; i < width + 2; i++) 
        printf("#");
    printf("\n");

    // displays current score
    printf("score: %d\n", score);
}

// function to get user input
void input() {
    // checks to see if a key is pressed
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': // moves left
                dir = 1;
                break;
            case 'd': // moves right
                dir = 2;
                break;
            case 'w': // moves up
                dir = 3;
                break;
            case 's': // moves down
                dir = 4;
                break;
            case 'x': // ends game
                gameover = 1;
                break;
        }
    }
}

// function to implement the game logic
void logic() {
    int prevX = tailX[0]; // previous x coordinate of the head
    int prevY = tailY[0]; // previous y coordinate of the head
    int prev2X, prev2Y; // variables to store the previous position
    tailX[0] = x; // sets head position as first element in the tail array
    tailY[0] = y;
    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // updates head position based on direction
    switch (dir) {
        case 1: // left
            x--;
            break;
        case 2: // right
            x++;
            break;
        case 3: // up
            y--;
            break;
        case 4: // down
            y++;
            break;
        default:
            break;
    }

    // checks to see if the snakes head hits the fruit ('F')
    if (x == fruitX && y == fruitY) {
        score += 1; // increments score by 1 each time fruit is eaten
        fruitX = rand() % width; // generates new x coordinate for fruit
        fruitY = rand() % height; // generates new y coordinate for fruit
        tailLength++; // increases the tail length
    }

    // checks to see if the snake hits the border
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // checks to see if/when the snake hits itself
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;
    }
}

int main() {
    setup(); // initializes game
    while (!gameover) {
        draw(); // draws game area
        input(); // gets user input
        logic(); // updates game logic
        Sleep(100); // delay to control the speed of the snake
    }
    return 0;
}
