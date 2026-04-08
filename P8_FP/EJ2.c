#include <stdio.h>
int main(){
    int a, b, c, x, y;
    printf ("Escriba dos numeros para sumar\n");
    scanf("%d %d", &a, &b);
    while (a!=0 && b!=0){
        x=a+b;
        printf("El resultado de la suma de %d y %d es %d\n", a, b, x);
        printf("Si desea sumar otro numero, escribalo, en caso contrario escriba 0\n");
        scanf("%d", c);
        y=x+c;
        printf("El resultado de la suma de %d y %d es %d\n", x, c, y);
    }
    printf("no fue posible reaizar la suma\n");
    return 0;
}