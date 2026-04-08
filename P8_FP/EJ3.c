// El usuario ingresa números (termina con 0). Mostrar cuántos números positivos fueron ingresados,
// cuaátos negativos.
#include <stdio.h>
int main()
{
    int numero, i, j;
    printf("Ingresa los numeros (termina con 0)\n");
    while (1)
    {
        scanf("%d", &numero);
        if (numero == 0)
        {
            break;
        }
        while (numero > 0)
        {
            i++;
        }
        i = 0;
        while (numero > 0)
        {
            i++;
        }
    }

    printf("hay '%d' numeros positivos y '%d' numeros negrativos\n", i, j);
    return 0;
}