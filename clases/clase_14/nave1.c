#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 30
#define HEIGHT 15

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

int naveX, naveY;

char direction = 'd';

bool game_over = false;

void moveNave(int *x, int *y, char dir){

    switch(dir){

        case 'w':
        case 'W':
            (*y)--;
            break;

        case 's':
        case 'S':
            (*y)++;
            break;

        case 'a':
        case 'A':
            (*x)--;
            break;

        case 'd':
        case 'D':
            (*x)++;
            break;
    }
}

void clearScreen(){

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

}

#ifdef _WIN32

char readInput(){

    if(_kbhit())
        return _getch();

    return direction;
}

#else

struct termios oldt;

void enableRawMode(){

    struct termios newt;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int flags = fcntl(STDIN_FILENO, F_GETFL, O_NONBLOCK);

    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void disableRawMode(){

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

char readInput(){

    int ch;

    ch = getchar();

    if(ch != EOF)
        return ch;

    return 0;
}

#endif

void setup(){

    naveX = WIDTH / 2;
    naveY = HEIGHT - 4;
}

void draw(){

    clearScreen();

    for(int i = 0; i < HEIGHT; i++){

        for(int j = 0; j < WIDTH; j++){

            // Bordes
            if(j == 0 || i == 0 || i == HEIGHT - 1 || j == WIDTH - 1){

                printf(YELLOW "▒");
            }

            // Parte superior de la nave
            else if(i == naveY && j == naveX){

                printf(BLUE "#");
            }

            // Parte inferior izquierda y derecha
            else if(i == naveY + 1 &&
                   (j == naveX - 1 || j == naveX + 1)){

                printf(BLUE "#");
            }

            // Espacios vacíos
            else{

                printf(RESET " ");
            }
        }

        printf("\n");
    }
}

void logic(){

    // Colisión con paredes
    if(naveX <= 1 || naveX >= WIDTH - 2 ||
       naveY <= 1 || naveY >= HEIGHT - 3){

        game_over = true;
    }
}

int main(){

    char newDirection;

    setup();

#ifndef _WIN32
    enableRawMode();
#endif

    while(!game_over){

        draw();

        newDirection = readInput();

        // Arriba
        if((newDirection == 'W' || newDirection == 'w') &&
           direction != 's' && direction != 'S'){

            direction = newDirection;
        }

        // Abajo
        else if((newDirection == 'S' || newDirection == 's') &&
                direction != 'w' && direction != 'W'){

            direction = newDirection;
        }

        // Izquierda
        else if((newDirection == 'A' || newDirection == 'a') &&
                direction != 'd' && direction != 'D'){

            direction = newDirection;
        }

        // Derecha
        else if((newDirection == 'D' || newDirection == 'd') &&
                direction != 'a' && direction != 'A'){

            direction = newDirection;
        }

        moveNave(&naveX, &naveY, direction);

        logic();

#ifdef _WIN32
        Sleep(150);
#else
        usleep(150000);
#endif
    }

#ifndef _WIN32
    disableRawMode();
#endif

    printf("\nGame Over\n");

    return 0;
}