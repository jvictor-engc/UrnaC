#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VOTO.h"

void iniciar_structs_v(struct VOTO **q) {
    for(int i = 0 ; i < MAX_V ; i++) {
        q[i]->alow = 0;
    }
}

void campo_VOTO() {
    struct VOTO *p[MAX_V];
    for(int i = 0 ; i < MAX_V ; i++) {
        p[i] = malloc(sizeof(struct VOTO));
    }

    iniciar_structs_v(p);

    FILE *V = fopen("votos", "rb+");
    if(V == NULL) V = fopen("votos", "wb+");
    if(V == NULL) printf("erro ao abrir arquivo");
}




