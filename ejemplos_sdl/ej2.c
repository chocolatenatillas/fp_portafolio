#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

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

    bool running= true;
    SDL_Event event; //detecta acciones que hace el usuario, los eventos

    SDL_RaiseWindow(window); //pone en frente a la ventana

    while(running){
        while (SDL_PollEvent(&event));{ //detecta los eventos, & porque debe recibir la direccion, el &nos da la direccion de memoria
        if(event.type== SDL_QUIT){
            running= false;
        } else if(event.type == SDL_KEYDOWN){
            if(event.key.keysym. sym == SDLK_x)
            running= false;

        }
    }
    }

    //SDL_Delay(40000);

    SDL_DestroyWindow(window);

    SDL_Quit(); //destruye todo lo que init crea

}