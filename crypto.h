//
// Created by jjjose on 4/27/26.
//

#ifndef CRYPTO_H
#define CRYPTO_H

char* chiffrer_transposition(const char* message, const int* cle, int taille_cle);
char* dechiffrer_transposition(const char* message, const int* cle, int taille_cle);

#endif
