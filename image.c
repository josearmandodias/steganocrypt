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
    if (!fp) 
    {
        fprintf(stderr, "Unable to open file '%s'\n", chemin);
        exit(1);
    }

    //read image format
    if (!fgets(buff, sizeof(buff), fp)) 
    {
        perror(chemin);
        exit(1);
    }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6')
    {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    img = (sImagePPM *)malloc(sizeof(sImagePPM));
    if (!img) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    fscanf(fp, "%d\n", &img->largeur);
    fscanf(fp, "%d\n", &img->hauteur);
    fscanf(fp, "%d\n", &img->max);

    img->pixels = malloc(img->hauteur * sizeof(sPixel*));
    if (!img->pixels) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }
    
    for (int i = 0; i < img->hauteur; i++) 
    {
        img->pixels[i] = malloc(img->largeur * sizeof(sPixel));
    }

    for (int i = 0; i < img->hauteur; i++) 
    {
        for (int j = 0; j < img->largeur; j++) 
        {
            fread(&img->pixels[i][j], sizeof(sPixel), 1, fp);
        }
    }

    fclose(fp);
    return img;  
}

int sauvegarder_ppm(const sImagePPM* img, const char* chemin)
{
    FILE *fp = fopen(chemin, "wb");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", chemin);
        return -1;
    }

    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", img->largeur, img->hauteur);
    fprintf(fp, "%d\n", img->max);

    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            fwrite(&img->pixels[i][j], sizeof(sPixel), 1, fp);
        }
    }
    fclose(fp);
    return 0;
}

void liberer_ppm(sImagePPM* img)
{
    for (int i = 0; i < img->hauteur; i++) 
    {
        free(img->pixels[i]);
    }
    free(img->pixels);
    free(img);
}

sImagePPM* rotation_90(const sImagePPM* img)
{
    sImagePPM* copieimg = malloc(sizeof(sImagePPM));
    if (!copieimg) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    copieimg->largeur = img->hauteur;  // dimensions inversées
    copieimg->hauteur = img->largeur;
    copieimg->max = img->max;

    copieimg->pixels = malloc(copieimg->hauteur * sizeof(sPixel*));
    if (!copieimg->pixels) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }
    for (int i = 0; i < copieimg->hauteur; i++) 
    {
        copieimg->pixels[i] = malloc(copieimg->largeur * sizeof(sPixel));
    }

    for (int i = 0; i < img->hauteur; i++)
    {
        for (int j = 0; j < img->largeur; j++)
        {
            copieimg->pixels[j][copieimg->largeur-1-i] = img->pixels[i][j];
        }
    }

    return copieimg;
}

sImagePPM* symetrie_h(const sImagePPM* img)
{
    sImagePPM* copieimg = malloc(sizeof(sImagePPM));
    if (!copieimg) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    copieimg->largeur = img->largeur;
    copieimg->hauteur = img->hauteur;
    copieimg->max = img->max;

    copieimg->pixels = malloc(copieimg->hauteur * sizeof(sPixel*));
    if (!copieimg->pixels) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    for (int i = 0; i < copieimg->hauteur; i++) 
    {
        copieimg->pixels[i] = malloc(copieimg->largeur * sizeof(sPixel));
    }

    for (int i = 0; i < img->hauteur; i++)
    {
        for (int j = 0; j < img->largeur; j++)
        {
            copieimg->pixels[i][j] = img->pixels[i][copieimg->largeur-1-j];
        }
    }

    return copieimg;
} // axe vertical


sImagePPM* symetrie_v(const sImagePPM* img)
{
    sImagePPM* copieimg = malloc(sizeof(sImagePPM));
    if (!copieimg) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    copieimg->largeur = img->largeur;
    copieimg->hauteur = img->hauteur;
    copieimg->max = img->max;

    copieimg->pixels = malloc(copieimg->hauteur * sizeof(sPixel*));
    if (!copieimg->pixels) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    for (int i = 0; i < copieimg->hauteur; i++) 
    {
        copieimg->pixels[i] = malloc(copieimg->largeur * sizeof(sPixel));
    }

    for (int i = 0; i < img->hauteur; i++)
    {
        for (int j = 0; j < img->largeur; j++)
        {
            copieimg->pixels[i][j] = img->pixels[copieimg->hauteur-1-i][j];
        }
    }

    return copieimg;
} // axe horizontal

sImagePPM* redimensionner(const sImagePPM* img, int nouv_largeur, int nouv_hauteur)
{
    sImagePPM* copieimg = malloc(sizeof(sImagePPM));
    if (!copieimg) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    copieimg->largeur = nouv_largeur;
    copieimg->hauteur = nouv_hauteur;
    copieimg->max = img->max;

    copieimg->pixels = malloc(copieimg->hauteur * sizeof(sPixel*));\
    if (!copieimg->pixels) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }
    
    for (int i = 0; i < copieimg->hauteur; i++) 
    {
        copieimg->pixels[i] = malloc(copieimg->largeur * sizeof(sPixel));
    }

    for (int i = 0; i < copieimg->hauteur; i++)
    {
        for (int j = 0; j < copieimg->largeur; j++)
        {
            copieimg->pixels[i][j] = img->pixels[i * img->hauteur / copieimg->hauteur][j * img->largeur / copieimg->largeur];
        }
    }

    return copieimg;
};