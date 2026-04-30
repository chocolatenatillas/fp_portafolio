#include <stdio.h>
int main(){
    // for(;;);
    // printf("for infinito\n");

    int i=0;
    for(;i<10;i++);
    printf("%d\n", i);

    for(;i<10;++i);
    printf("%d\n", i);

    return 0;
}