#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
    FILE *file;
} IMAGEN;

char elegir_caracter(int intensidad) {
    char *paleta = "@#S%?*+;:,. "; 
    int indice = intensidad * 11 / 256;
    return paleta[indice];
}

IMAGEN abrir_imagen(const char *ruta) {
    IMAGEN img = {0, 0, NULL};
    img.file = fopen(ruta, "rb");

    if (img.file) {
        fseek(img.file, 18, SEEK_SET);
        fread(&img.width, 4, 1, img.file);
        fread(&img.height, 4, 1, img.file);
        fseek(img.file, 54, SEEK_SET);
    } else {
        printf("Error: No se pudo abrir el archivo %s\n", ruta);
    }
    return img;
}

void imprimir_ascii(IMAGEN img) {
    if (!img.file) return;

    int MAX_X = 100;
    int MAX_Y = 100;

    int saltox = img.width / MAX_X;
    if (saltox < 1) saltox = 1;

    int saltoy1 = img.height / MAX_Y;
    if (saltoy1 < 1) saltoy1 = 1;
    int saltoy2 = saltoy1 * 2; 

    for (int y = img.height - 1; y >= 0; y -= saltoy2) {
        long offset = 54 + (y * img.width * 3);
        fseek(img.file, offset, SEEK_SET);

        for (int x = 0; x < img.width; x += saltox) {
            unsigned char bgr[3];
            fread(bgr, 1, 3, img.file);

            int gris = (bgr[0] + bgr[1] + bgr[2]) / 3;
            printf("%c", elegir_caracter(gris));

            if (saltox > 1) {
                fseek(img.file, (saltox - 1) * 3, SEEK_CUR);
            }
        }
        printf("\n");
    }
}

int main() {
    char nombre_archivo[100];
    printf("Escribe el nombre de la imagen (ej: test.bmp): ");
    scanf("%s", nombre_archivo);

    IMAGEN mi_foto = abrir_imagen(nombre_archivo);

    if (mi_foto.file != NULL) {
        imprimir_ascii(mi_foto);
        fclose(mi_foto.file);
    }

    printf("\nPresiona Enter para salir...");
    getchar();
    getchar();
    return 0;
}