#include <stdio.h>
#include <SDL2/SDL.h>

int main (int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO)==0){
        printf("Error: %s/n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "HOLA MUNDO", //TITULO DE LA VENTANA
        SDL_WINDOWPOS_CENTERED, //posicion de la ventana en x
        SDL_WINDOWPOS_CENTERED, //posicion de la ventana en y
        800, //ancho de la ventana
        600, //alto de la entana
        0
    );

    if (window== NULL){
        printf("Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_RaiseWindow(window); //pone en frente a la ventana

    SDL_Delay(40000);

    SDL_DestroyWindow(window);

    SDL_Quit(); //destruye todo lo que init crea

}