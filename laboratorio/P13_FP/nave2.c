#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define WIDTH 55
#define HEIGHT 24

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
#define RESET   "\033[0m"

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

typedef struct { float x, y; float dx, dy; bool active; } Entity;

Entity ship, bullet, enemy, enemyBullet, star, asteroid;
int score = 0;
bool paused = false;
bool game_over = false;

#ifndef _WIN32
void enableRawMode() {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    fcntl(STDIN_FILENO, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}
#endif

char getInput() {
#ifdef _WIN32
    if (_kbhit()) return _getch();
#else
    char ch; if (read(STDIN_FILENO, &ch, 1) > 0) return ch;
#endif
    return 0;
}

void setup() {
    srand(time(NULL));
    ship = (Entity){WIDTH / 2.0f, (float)HEIGHT - 3, 0, 0, true};
    enemy = (Entity){WIDTH / 2.0f, 2, 0.5f, 0, true};
    asteroid = (Entity){(float)(rand() % WIDTH), 1, 0.2f, 0.4f, true};
    star.active = false; bullet.active = false; enemyBullet.active = false;
}

void draw() {
    printf("\033[H"); 
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == (int)ship.y && j == (int)ship.x) printf(GREEN "▲" RESET);
            else if (i == (int)ship.y + 1 && j >= (int)ship.x - 1 && j <= (int)ship.x + 1) printf(GREEN "█" RESET);
            else if (bullet.active && i == (int)bullet.y && j == (int)bullet.x) printf(CYAN "o" RESET);
            else if (enemyBullet.active && i == (int)enemyBullet.y && j == (int)enemyBullet.x) printf(RED "v" RESET);
            else if (enemy.active && i == (int)enemy.y && j == (int)enemy.x) printf(RED "👾" RESET);
            else if (star.active && i == (int)star.y && j == (int)star.x) printf(YELLOW "★" RESET);
            else if (asteroid.active && i == (int)asteroid.y && j == (int)asteroid.x) printf(WHITE "O" RESET);
            else printf(" ");
        }
        printf("\n");
    }
    if (paused) printf(YELLOW "  [ PAUSA ] - Pulsa 'P' para seguir    " RESET "\n");
    else printf(WHITE " Score: %05d | P: Pausa | ¡Nave y balas rebotan!" RESET "\n", score);
}

int main() {
    setup();
#ifndef _WIN32
    enableRawMode();
#endif
    printf("\033[?25l");
    system("cls || clear");
    int frame = 0;
    while (!game_over) {
        char key = getInput();
        if (key == 'p' || key == 'P') paused = !paused;
        if (key == 'x' || key == 'X') break;
        if (!paused) {
            if (key == 'a' || key == 'A') ship.dx = -1.0f;
            if (key == 'd' || key == 'D') ship.dx = 1.0f;
            if ((key == 'k' || key == 'K' || key == ' ') && !bullet.active) 
                bullet = (Entity){ship.x, ship.y - 1, 0.5f, -1.3f, true};

            ship.x += ship.dx;
            if (ship.x <= 1 || ship.x >= WIDTH - 2) { ship.dx *= -1; ship.x += ship.dx; }

            if (bullet.active) {
                bullet.x += bullet.dx; bullet.y += bullet.dy;
                if (bullet.x <= 0 || bullet.x >= WIDTH - 1) bullet.dx *= -1;
                if (bullet.y <= 0) bullet.dy *= -1;
                if (bullet.y >= HEIGHT) bullet.active = false;
                if (enemy.active && (int)bullet.y == (int)enemy.y && (int)bullet.x == (int)enemy.x) {
                    score += 100; enemy.active = false; bullet.active = false;
                }
            }
            if (enemy.active) {
                enemy.y += 0.05f;
                enemy.x = (WIDTH / 2.0f) + (sinf(frame * 0.07f) * (WIDTH / 2.5f));
                if (!enemyBullet.active && rand() % 45 == 0) enemyBullet = (Entity){enemy.x, enemy.y + 1, 0, 0.8f, true};
                if (enemy.y >= ship.y + 1) enemy.active = false;
            } else if (frame % 150 == 0) { enemy.active = true; enemy.y = 1; }

            if (enemyBullet.active) {
                enemyBullet.y += 0.8f;
                if (enemyBullet.y >= HEIGHT) enemyBullet.active = false;
                if (enemyBullet.active && (int)enemyBullet.y == (int)ship.y && abs((int)enemyBullet.x - (int)ship.x) <= 1) game_over = true;
            }
            if (asteroid.active) {
                asteroid.x += asteroid.dx; asteroid.y += asteroid.dy;
                if (asteroid.x <= 0 || asteroid.x >= WIDTH - 1) asteroid.dx *= -1;
                if (asteroid.y >= ship.y + 1) asteroid.active = false;
            } else if (rand() % 70 == 0) asteroid = (Entity){(float)(rand() % WIDTH), 0, (float)((rand()%10-5)*0.1), 0.4f, true};

            if (star.active) {
                star.y += 0.3f;
                if (star.y >= HEIGHT) star.active = false;
                if ((int)star.y == (int)ship.y && abs((int)star.x - (int)ship.x) <= 1) { score += 500; star.active = false; }
            } else if (rand() % 300 == 0) star = (Entity){(float)(rand() % WIDTH), 0, 0, 0.3f, true};
            frame++;
        }
        draw();
        #ifdef _WIN32
            Sleep(30); 
        #else
            usleep(30000); 
        #endif
    }
    printf("\033[?25h" RED "\n  GAME OVER - Score: %d\n" RESET, score);
    return 0;
}