#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

bool gameOver;
const int width = 40;
const int height = 20;
int x, y, starX, starY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    starX = rand() % width;
    starY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        std::cout << "\033[1;36m#\033[0m";  // niebieski
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                std::cout << "\033[1;36m#\033[0m";  // niebieski
            if (i == y && j == x)
                std::cout << "\033[1;32mO\033[0m";  // zielony
            else if (i == starY && j == starX)
                std::cout << "\033[1;31m*\033[0m";  // czerwony
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "\033[1;32mo\033[0m";  // zielony
                        print = true;
                    }
                }
                if (!print)
                    std::cout << " ";
            }

            if (j == width - 1)
                std::cout << "\033[1;36m#\033[0m";  // niebieski
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 2; i++)
        std::cout << "\033[1;36m#\033[0m";  // niebieski
    std::cout << std::endl;
    std::cout << "Score:" << score << std::endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Algorithm() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    x = (x + width) % width;  // Zapobiega wyjściu poza lewą lub prawą krawędź planszy
    y = (y + height) % height; // Zapobiega wyjściu poza górną lub dolną krawędź planszy

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == starX && y == starY) {
        score += 10;
        starX = rand() % width;
        starY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Algorithm();
        Sleep(50);
    }

    std::cout << "Game Over! Press any key to exit..." << std::endl;
    _getch();

    return 0;
}
