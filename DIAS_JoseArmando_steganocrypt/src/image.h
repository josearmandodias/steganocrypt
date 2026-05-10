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
sImagePPM* rotation_90(const sImagePPM* img);
sImagePPM* symetrie_h(const sImagePPM* img);
sImagePPM* symetrie_v(const sImagePPM* img);
sImagePPM* redimensionner(const sImagePPM* img, int nouv_largeur, int nouv_hauteur);
int        sauvegarder_ppm(const sImagePPM*, const char*);   
void       liberer_ppm(sImagePPM* img);
void       liberer_pgm(sImagePGM* img);

#endif