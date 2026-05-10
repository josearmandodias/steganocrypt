#include <stdio.h>
#include <stdlib.h>
#include "traitement.h"

sImagePGM* convertir_gris(const sImagePPM* img)
{
    sImagePGM* imgpgm = malloc(sizeof(sImagePGM));
    imgpgm->largeur = img->largeur;
    imgpgm->hauteur = img->hauteur;
    imgpgm->max = img->max;

    imgpgm->pixels = malloc(imgpgm->hauteur * sizeof(sPixelGris*));
    if (!imgpgm->pixels) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    for (int i = 0; i < imgpgm->hauteur; i++) 
    {
        imgpgm->pixels[i] = malloc(imgpgm->largeur * sizeof(sPixelGris));
    }

    for (int i = 0; i < imgpgm->hauteur; i++)
    {
        for (int j = 0; j < imgpgm->largeur; j++)
        {
            sPixelGris* p = &imgpgm->pixels[i][j];
            p->valeur = (img->pixels[i][j].r + img->pixels[i][j].g + img->pixels[i][j].b) / 3;
        }
    }
    return imgpgm;
}

sImagePGM* seuiller(const sImagePGM* img, int seuil)
{
    sImagePGM* imgpgm = malloc(sizeof(sImagePGM));
    imgpgm->largeur = img->largeur;
    imgpgm->hauteur = img->hauteur;
    imgpgm->max = img->max;

    imgpgm->pixels = malloc(imgpgm->hauteur * sizeof(sPixelGris*));
    if (!imgpgm->pixels) 
    {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    for (int i = 0; i < imgpgm->hauteur; i++) 
    {
        imgpgm->pixels[i] = malloc(imgpgm->largeur * sizeof(sPixelGris));
    }

    for (int i = 0; i < imgpgm->hauteur; i++)
    {
        for (int j = 0; j < imgpgm->largeur; j++)
        {
            imgpgm->pixels[i][j].valeur = (img->pixels[i][j].valeur > seuil) ? 255 : 0;
        }
    }

    return imgpgm;
}