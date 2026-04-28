#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

int main(){
    // teste avec l'exemple du projet
    int cle[] = {3, 1, 4, 2};
    char* r = chiffrer_transposition("CRYPTOGRAPHIE", cle, 4);
    printf("%s\n", r);
    free(r);
}
