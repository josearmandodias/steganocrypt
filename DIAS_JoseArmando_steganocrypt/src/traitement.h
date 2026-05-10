#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include "image.h"

sImagePGM* convertir_gris(const sImagePPM* img);
sImagePGM* seuiller(const sImagePGM* img, int seuil);

#endif