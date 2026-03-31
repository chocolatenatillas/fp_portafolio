#include <stdio.h>
#include <stdbool.h>
int main() {
    if (true){
        printf("la condicion es verdadera\n");
    }

    if (1){
        printf("la condicion es verdadera\n");
    }

    if (!0){
        printf("la condicion es verdadera\n");
    }

    if (-2){
        printf("la condicion es verdadera\n");
    }

    if (false){
        printf("la condicion es verdadera\n");
    }

    if (0){
        printf("la condicion es verdadera\n");
    }

    if (!1){
        printf("la condicion es verdadera\n");
    }
return 0;
}