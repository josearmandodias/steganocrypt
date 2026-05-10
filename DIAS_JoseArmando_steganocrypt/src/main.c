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
char g_chiffre[256] = "";
int g_cle[10];
int g_taille_cle = 0;
sImagePPM* g_img = NULL;

void demander_si_vide(char* var, const char* question)
{
    if (strlen(var) == 0)
    {
        printf("%s", question);
        // prendre en compte les espaces
        fgets(var, 256, stdin);
        // on enleve le \n pour eviter un retour a la ligne par un fin de chaine
        var[strcspn(var, "\n")] = '\0';
    }
}

void menu_cryptographie()
{
    // chiffrer un message
    while (1) {
        int choix;
        printf("\n--- Cryptographie ---\n");
        demander_si_vide(g_message, "Message : ");
        printf("1. Chiffrer un message\n");
        printf("2. Déchiffrer un message\n");
        printf("3. Test automatique (chiffrer puis déchiffrer)\n");
        printf("0. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();
        if (choix == 1)
        {
            if (g_taille_cle == 0) {
                printf("Taille de la clé : ");
                scanf("%d", &g_taille_cle);
                printf("Entrez la clé : ");
                for (int i = 0; i < g_taille_cle; i++) {
                    scanf("%d", &g_cle[i]);
                }
            }
            char* chiffre = chiffrer_transposition(g_message, g_cle, g_taille_cle);
            strncpy(g_chiffre, chiffre, 255);
            printf("Message chiffré : %s\n", chiffre);
            free(chiffre);
        } 
        else if (choix == 2) 
        {
            if (g_taille_cle == 0) {
                printf("Taille de la clé : ");
                scanf("%d", &g_taille_cle);
                printf("Entrez la clé : ");
                for (int i = 0; i < g_taille_cle; i++) {
                    scanf("%d", &g_cle[i]);
                }
            }
            char* dechiffre = dechiffrer_transposition(g_chiffre, g_cle, g_taille_cle);
            printf("Message déchiffré : %s\n", dechiffre);
            free(dechiffre);
        }
        else if (choix == 3) 
        {
            demander_si_vide(g_message, "Message : ");
            if (g_taille_cle == 0) {
                printf("Taille de la clé : ");
                scanf("%d", &g_taille_cle);
                printf("Entrez la clé : ");
                for (int i = 0; i < g_taille_cle; i++) {
                    scanf("%d", &g_cle[i]);
                }
            }
            char* c = chiffrer_transposition(g_message, g_cle, g_taille_cle);
            char* d = dechiffrer_transposition(c, g_cle, g_taille_cle);
            if (strcmp(g_message, d) == 0)
            {
                printf("TEST OK\n");
            }
            else
            {
                printf("TEST ERREUR : '%s' != '%s'\n", g_message, d);
            }
            free(c); 
            free(d);
        }
        else if (choix == 0) 
        {
            return;
        }
        else 
        {
            printf("Choix invalide.\n");
        }
    }
}

void menu_images()
{
    while (1) {
        int choix;
        printf("\n--- Images ---\n");
        printf("1. Charger une image PPM et afficher ses infos\n");
        printf("2. Sauvegarder l'image courante\n");
        printf("0. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();
        if (choix == 1)
        {
            demander_si_vide(g_source, "Fichier source : ");
            if (g_img != NULL)
            {
                liberer_ppm(g_img);
            }
            g_img = charger_ppm(g_source);
            printf("Image chargée : %d x %d, max = %d\n", g_img->largeur, g_img->hauteur, g_img->max);
        }
        else if (choix == 2)
        {
            if (g_img == NULL) {
                printf("Aucune image chargée.\n");
            } 
            else 
            {
                demander_si_vide(g_sortie, "Fichier de sortie : ");
                sauvegarder_ppm(g_img, g_sortie);
                printf("Image sauvegardée.\n");
            }
        }
        else if (choix == 0)
        {
            return;
        } 
        else 
        {
            printf("Choix invalide.\n");
        }
    }
}

void menu_steganographie()
{
    while (1) {
        int choix;
        printf("\n--- Stéganographie ---\n");
        printf("1. Cacher un message dans l'image courante\n");
        printf("2. Extraire le message de l'image courante\n");
        printf("3. Test automatique (cacher puis extraire)\n");
        printf("0. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();
        if (choix == 1)
        {
            if (g_img == NULL)
            { 
                printf("Aucune image chargée.\n");
            }
            else
            {
                demander_si_vide(g_message, "Message : ");
                if (cacher_message(g_img, g_message) == 0)
                    printf("Message caché avec succès.\n");
                else
                    printf("Erreur : message trop long.\n");
            }
        }
        else if (choix == 2)
        {
            if (g_img == NULL)
            { 
                printf("Aucune image chargée.\n");
            }
            else
            {
                char* extrait = extraire_message(g_img);
                if (extrait == NULL)
                    printf("Erreur : aucun message trouvé.\n");
                else {
                    printf("Message extrait : %s\n", extrait);
                    free(extrait);
                }
            }
        }
        else if (choix == 3)
        {
            if (g_img == NULL) 
            { 
                printf("Aucune image chargée.\n");
            }
            else
            {
                demander_si_vide(g_message, "Message : ");
                cacher_message(g_img, g_message);
                char* extrait = extraire_message(g_img);
                if (strcmp(g_message, extrait) == 0)
                    printf("TEST OK\n");
                else
                    printf("TEST ERREUR : '%s' != '%s'\n", g_message, extrait);
                free(extrait);
            }
        }
        else if (choix == 0)
        {
             return;
        }
        else 
        {
            printf("Choix invalide.\n");
        }
    }
}

void menu_traitement()
{
    while (1) {
        int choix;
        printf("\n--- Traitement et compression ---\n");
        printf("1. Rotation 90° (sens horaire)\n");
        printf("2. Symétrie horizontale (gauche-droite)\n");
        printf("3. Symétrie verticale (haut-bas)\n");
        printf("4. Redimensionner\n");
        printf("5. Convertir en niveaux de gris\n");
        printf("6. Seuillage\n");
        printf("0. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();
        if (choix == 1)
        {
            if (g_img == NULL) { printf("Aucune image chargée.\n"); }
            else
            {
                sImagePPM* res = rotation_90(g_img);
                liberer_ppm(g_img);
                g_img = res;
                printf("Rotation effectuée.\n");
            }
        }
        else if (choix == 2)
        {
            if (g_img == NULL) { printf("Aucune image chargée.\n"); }
            else
            {
                sImagePPM* res = symetrie_h(g_img);
                liberer_ppm(g_img);
                g_img = res;
                printf("Symétrie horizontale effectuée.\n");
            }
        }
        else if (choix == 3)
        {
            if (g_img == NULL) { printf("Aucune image chargée.\n"); }
            else
            {
                sImagePPM* res = symetrie_v(g_img);
                liberer_ppm(g_img);
                g_img = res;
                printf("Symétrie verticale effectuée.\n");
            }
        }
        else if (choix == 4)
        {
            if (g_img == NULL) { printf("Aucune image chargée.\n"); }
            else
            {
                int nw, nh;
                printf("Nouvelle largeur : ");
                scanf("%d", &nw);
                printf("Nouvelle hauteur : ");
                scanf("%d", &nh);
                sImagePPM* res = redimensionner(g_img, nw, nh);
                liberer_ppm(g_img);
                g_img = res;
                printf("Redimensionnement effectué.\n");
            }
        }
        else if (choix == 5)
        {
            if (g_img == NULL) { printf("Aucune image chargée.\n"); }
            else
            {
                sImagePGM* gris = convertir_gris(g_img);
                printf("Conversion en niveaux de gris effectuée.\n");
                liberer_pgm(gris);
            }
        }
        else if (choix == 6)
        {
            if (g_img == NULL) { printf("Aucune image chargée.\n"); }
            else
            {
                int seuil;
                printf("Seuil (0-255) : ");
                scanf("%d", &seuil);
                sImagePGM* gris = convertir_gris(g_img);
                sImagePGM* res = seuiller(gris, seuil);
                liberer_pgm(gris);
                liberer_pgm(res);
                printf("Seuillage effectué.\n");
            }
        }
        else if (choix == 0) { return; }
        else { printf("Choix invalide.\n"); }
    }
}

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
        getchar();
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
    if (g_img != NULL) liberer_ppm(g_img);
    return 0;
}
