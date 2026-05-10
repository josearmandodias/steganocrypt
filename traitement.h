#ifndef STEGANOGRAPHIE_H
#define STEGANOGRAPHIE_H

#include "image.h"

sImagePGM* convertir_gris(const sImagePPM* img);
sImagePGM* seuiller(const sImagePGM* img, int seuil);

#endif