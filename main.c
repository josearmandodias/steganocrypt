#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"
#include "image.h"
#include "steganographie.h"
#include "traitement.h"

char g_source[256] = "";
char g_sortie[256] = "";
char g_message[256] = "";
int g_cle[10];
int g_taille_cle = 0;
sImagePPM* g_img = NULL;

void menu_principal(void) 
{
    int choix;
    while (1) {
        printf("\n=== StéganoCrypt ===");
        printf(" | fichier: %s", strlen(g_source)>0 ? g_source : "(aucun)");
        printf(" | message: %s\n", strlen(g_message)>0 ? g_message : "(aucun)");
        printf("1. Cryptographie\n");
        printf("2. Images\n");
        printf("3. Stéganographie\n");
        printf("4. Traitement et compression\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        if (choix == 1)
        {
            menu_cryptographie();
        } 
        else if (choix == 2) 
        {
            menu_images();
        }
        else if (choix == 3) 
        {
            menu_steganographie();
        }
        else if (choix == 4) 
        {
            menu_traitement();
        }
        else if (choix == 0) 
        {
            printf("Au revoir !\n"); 
            return;
        }
        else 
        {
            printf("Choix invalide.\n");
        }
    }
}

int main(){
    menu_principal();
    return 0;
}
