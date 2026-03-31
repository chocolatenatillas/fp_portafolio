#include <stdio.h>
int main(){
    printf("hola estrellitas, la tierra les dice hola:D\n");

    float a, b, c;
    printf("Escribe los numeros que deseas sumar\n");
    scanf("%f %f", &a,&b);
    c=a+b;
    printf("El resultado de sumar %.2f y %.2f es %.2f\n", a, b, c);

    return 0;
}
