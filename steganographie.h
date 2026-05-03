#ifndef STEGANOGRAPHIE_H
#define STEGANOGRAPHIE_H

#include "image.h"

int get_bit(int valeur, int k);  
unsigned char set_lsb(unsigned char composante, int bit);
void encoder_bit(sImagePPM* img, int n, int bit);
int decoder_bit(const sImagePPM* img, int n);
int cacher_message(sImagePPM* img, const char* message);
char* extraire_message(const sImagePPM* img);

#endif