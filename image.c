#include <stdio.h>
#include <stdlib.h>
#include "image.h"

typedef struct 
{ 
    unsigned char r, g, b; 
} sPixel;

typedef struct 
{ 
    int largeur, hauteur, max; sPixel** pixels; 
} sImagePPM;

sImagePPM* charger_ppm(const char* chemin)
{
    char buff[16];
    sImagePPM *img;
    FILE *fp;
    fp = fopen(chemin, "rb");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", chemin);
        exit(1);
    }

    //read image format
    if (!fgets(buff, sizeof(buff), fp)) {
        perror(chemin);
        exit(1);
    }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    img = (sImagePPM *)malloc(sizeof(sImagePPM));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    return img;
}


int        sauvegarder_ppm(const sImagePPM*, const char*);   
void       liberer_ppm(sImagePPM* img);