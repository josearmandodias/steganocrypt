#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

char* chiffrer_transposition(const char* message, const int* cle, int taille_cle){
    // n devient taille_cle par copie, pour coller à l'énoncé
    int n = taille_cle;

    // on vérifie que la clé n'est pas vide
    if (n <= 0) {
        fprintf(stderr, "Erreur : clé invalide\n");
        return NULL;
    }

    // on calcule le nombre de lignes nécessaires pour le vecteur, et si taille_message n'est pas un mutliple de n, on ajoute une ligne pour le padding
    int taille_message = (int)strlen(message);
    int nb_lignes = taille_message / n;
    if (taille_message % n != 0) {
        nb_lignes++;
    }

    // allocation mémoire de la grille
    char** grille = malloc(nb_lignes * sizeof(char*));
    for (int i = 0; i < nb_lignes; i++){
        grille[i] = malloc(n * sizeof(char));
    }

    // on remplit les lignes avec le message en ajoutant les espaces si nécessaires
    int k = 0;
    for (int i = 0; i < nb_lignes; i++){
        for (int j = 0; j < n; j++){
            if (k < taille_message){
                grille[i][j] = message[k++];
            } else {
                grille[i][j] = ' ';
            }
        }
    }

    // on copie d'abord la clé puisqu'elle sert également au déchiffrement et qu'on ne doit pas la modifier
    int* cle_copie = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        cle_copie[i] = cle[i];
    }

    // on trie la clé pour pouvoir en lire l'ordre dans lequel assembler les colonnes
    int* ordre = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int min_val = 99999;
        int min_idx = 0;
        for (int j = 0; j < n; j++) {
            if (cle_copie[j] < min_val) {
                min_val = cle_copie[j];
                min_idx = j;
            }
        }
        ordre[i] = min_idx;
        cle_copie[min_idx] = 99999; // "marquer" comme déjà utilisé
    }

    char* chiffre = malloc((taille_message + 1) * sizeof(char));
    int position =  0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < nb_lignes; j++){
            if (j * n + ordre[i] < taille_message) { // on fait en sorte de ne pas inclure les espaces du padding
                chiffre[position++] = grille[j][ordre[i]];
            }
        }
    }
    chiffre[taille_message] = '\0'; // on ajoute \0 comme c'est un pointeur

    // on libere la mémoire et on retourne le résultat
    free(cle_copie);
    free(ordre);
    for (int i = 0; i < nb_lignes; i++){
        free(grille[i]);
    };
    free(grille);
    return chiffre;
}

char* dechiffrer_transposition(const char* message, const int* cle, int taille_cle){

}

