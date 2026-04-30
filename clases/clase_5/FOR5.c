#include <stdio.h>

int main() {
    int n, i, j, k;
    printf("Digite um número: ");
    scanf("%d", &n);

    for (i = n; i >= 1; i--) {
        
        for (j = 1; j <= i; j++) {
            printf("%d ", j);
        }

        for (k = 0; k <=2* (n-i); k++) {
            printf("  "); 
        }

        for (j = i; j >= 1; j--) {
            printf("%d ", j);
        }

        printf("\n");
    }

    return 0;
}