#ifndef IMAGE_H
#define IMAGE_H

typedef struct 
{ 
    unsigned char r, g, b; 
} sPixel;

typedef struct 
{ 
    int largeur, hauteur, max; sPixel** pixels; 
} sImagePPM;

typedef struct {
    unsigned char valeur;
} sPixelGris;

typedef struct {
    int largeur, hauteur, max;
    sPixelGris** pixels;
} sImagePGM;

sImagePPM* charger_ppm(const char* chemin);        
int        sauvegarder_ppm(const sImagePPM*, const char*);   
void       liberer_ppm(sImagePPM* img);

#endif