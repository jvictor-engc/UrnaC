#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VOTO.h"

void introduzir_v() {
    printf("[1]Adicionar Votos\n");
    printf("[2]Mostrar Votos de uma eleicao\n");// ordenar por candidato
    printf("[3]Mostrar quantidade de Votos por ano\n");//e ordenar por UF
    printf("[4]Salvar e Voltar\n");
}

int achar_livre_v(struct VOTO **q){
    for (int i = 0; i < MAX_V; i++){
        if((q[i]->alow) == 0) return i;
    }
    return -1;
}

int verifica_cod_uf_(int code) {
    struct uf {
        int a;
        int b;
        char c[20];
        char d[3];
    };
    struct uf *p = malloc(sizeof(struct uf));

    FILE *U = fopen("ufs", "rb+");
    if(U == NULL) U = fopen("ufs", "wb+");
    if(U == NULL) printf("erro ao abrir arquivo");// abro o arquivo de nome ufs

    int flag = 0;
    for (int i = 0 ; 1 ; i++) {
        fseek(U, i * sizeof(struct uf), SEEK_SET);
        int count = fread(p, sizeof(struct uf), 1, U);

        if (count == 0) {
            free(p);
            fclose(U);
            return 0;
        }

        if (p->b == code) {
            flag = 1;
            break;
        }
    }
    free(p);
    fclose(U);

    return flag;
}

void adicionar_v(struct VOTO **q) {
    int livre = achar_livre_v(q);
    if(livre == -1) {
        printf("Lista Cheia\n");
        return;
    }
    printf("Digite as informacoes.\n");

    while (1) {
        printf("Insira o Ano do voto: ");
        int year;
        scanf("%d", &year);

    }

    while (1) {
        printf("Codigo da UF*:");
        fflush(stdin);
        scanf("%d", &(q[livre]->codigo_uf));

        if ( !verifica_cod_uf_(q[livre]->codigo_uf) ) {
            printf("Codigo da UF nao existe\n");
            return;
        }
        break;

    }
}///parei aqui

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

    fseek(V, 0, SEEK_SET);
    for (int i = 0; i < MAX_V; i++) {
        fread(p[i], sizeof(struct VOTO), 1, V);
    }

    ///////////////////////////////////////////////////////////////////////////////////////

    while(1) {
        introduzir();

        int escolha;
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                fseek(V, 0, SEEK_SET);
                for (int i = 0; i < MAX_V; i++){
                    if (p[i]->alow == 2) {
                        p[i]->alow = 1;//quando salvo, deixa de ser tratado como alterado
                        fseek(V, i * sizeof(struct VOTO), SEEK_SET);
                        fwrite(p[i], sizeof(struct VOTO), 1, V);
                    }
                }
                for(int i = 0 ; i < MAX_V ; i++) free(p[i]);
                fclose(U);
                return;

            default: printf("\nOpcao invalida\n");
        }

    }
}




