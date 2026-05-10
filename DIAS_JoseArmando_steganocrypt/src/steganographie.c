#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "steganographie.h"
#include "image.h"

int get_bit(int valeur, int k)
{
    for(int i = 0; i <= k; i++)
    {
        valeur = valeur / 2;
    }
    return valeur % 2;
}

unsigned char set_lsb(unsigned char composante, int bit)
{
    return (composante / 2) * 2 + bit;
}

void encoder_bit(sImagePPM* img, int n, int bit)
{
    sPixel* p = &img->pixels[(n/3) / img->largeur][(n/3) % img->largeur];
    if (n % 3 == 0)
    {
        p->r = set_lsb(p->r, bit);
    } else if (n % 3 == 1)
    {
        p->g = set_lsb(p->g, bit);
    } else
    {
        p->b = set_lsb(p->b, bit);
    }
}

int decoder_bit(const sImagePPM* img, int n)
{
    sPixel* p = &img->pixels[(n/3) / img->largeur][(n/3) % img->largeur];
    if (n % 3 == 0)
    {
        return get_bit(p->r, 0);
    } else if (n % 3 == 1)
    {
        return get_bit(p->g, 0);
    } else
    {
        return get_bit(p->b, 0);
    }
}



int cacher_message(sImagePPM* img, const char* message){
    if ((32 + (int)strlen(message) * 8) > img->largeur * img->hauteur * 3)
    {
        fprintf(stderr, "Message trop long\n");
        return -1;
    }

    int lon = (int)strlen(message);
    for (int k = 0; k < 32; k++)
    {
        encoder_bit(img, k, get_bit(lon, k));
    }
    for (int c = 0; c < lon; c++)
    {
        for (int j = 0; j < 8; j++)
        {
            encoder_bit(img, 32 + c*8 + j, get_bit(message[c], j));
        }
    }
    
        
    for (int i = 0; i < strlen(message); i++)
    {
        encoder_bit(img, 8, message[i]);
    }
    return 0;
}

char* extraire_message(const sImagePPM* img)
{
    int lon = 0;
    for (int k = 0; k < 32; k++)
    {
        lon += decoder_bit(img, k) * (1 << k);
    }
    if (!(lon > 0 && (32 + lon*8) <= img->largeur * img->hauteur * 3))
    {
        return NULL;
    }
    char* msg = malloc(lon + 1);
    for (int c = 0; c < lon; c++)
    {
        msg[c] = 0;
        for (int j = 0; j < 8; j++)
        {
            msg[c] += decoder_bit(img, 32 + c*8 + j) * (1 << j);
        }
    }
    msg[lon] = '\0';
    return msg;
}