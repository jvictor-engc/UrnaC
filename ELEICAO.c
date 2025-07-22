#include "ELEICAO.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iniciar_structs_elc(struct ELEICAO **q){
    for(int i = 0 ; i < 5 ; i++){
        q[i]->alow = 0;
    }
}
/*
 *  recebe um ponteiro para ponteiro p, que foi criada dentro da função campo_ELEICAO.
*/

void introduzir_elc() {
    printf("-------------------------------------------------------------------------------------------");
    printf("\n\nO que deseja fazer?\n\n");
    printf("[1]Adicionar Eleicao\n");
    printf("[2]Mostrar Eleicao\n");
    printf("[3]Excluir Eleicao\n");
    printf("[4]Alterar Eleicao\n");
    printf("[5]Pesquisar Eleicao\n");
    printf("[6]Salvar e Voltar\n\n");
}
/*
 *  Introdução utilizada na função campo_uf.
 */

int achar_livre_elc(struct ELEICAO **q){
    for (int i = 0; i < 5; i++){
        if((q[i]->alow) == 0) return i;
    }
    return -1;
}
/*
 * Recebe o mesmo ponteiro pra ponteiro p. A função entra nas structs que foram trazidas para a ram e definem alow como 0.
 * Alow é uma flag que diz se a struct está sendo usada.
 * Futuramente alterar para nova função que mostra apenas as structs que foram alteradas dentro da ram para, na hora de gravar
 * no disco, não desperdiçar tempo. IDEIA: 0-vazio 1-preenchido 2-alterado na ram.
 */

int find_for_struct(struct ELEICAO **q,int year, int code) {
    for (int i = 0; i < 5; i++) {
        if ((q[i]->ano == year)&&(q[i]->codigo_uf == code)&&(q[i]->alow != 0)) {
            return i;
        }
    }
    return -1;
}

void adicionar_elc(struct ELEICAO **q){
    int livre = achar_livre(q);
    if(livre == -1) {
        printf("Lista Cheia\n");
        return;
    }
    printf("Digite as informacoes.\n");


    printf("Ano*:");
    fflush(stdin);
    scanf("%d", &(q[livre]->ano));

    printf("Codigo da UF*:");
    fflush(stdin);
    scanf("%d", &(q[livre]->codigo_uf));

    int indice = find_for_struct(q, (q[livre]->ano), q[livre]->codigo_uf);

    if (indice != -1) {
        printf("\nO conjunto ANO e Codigo da UF ja existem\n");
        return;
    }

    printf("Descricao*:");
    fflush(stdin);
    fgets(q[livre]->descricao, sizeof(q[livre]->descricao), stdin);

    for (int i = 0 ; q[livre]->descricao[i] != '\0' ; i++) {
        if (q[livre]->descricao[i] == '\n') q[livre]->descricao[i] = '\0';
    }

    q[livre]->alow = 2;

}

void mostrar_elc(struct ELEICAO **q) {
    int flag = 0;
    printf("-------------------------------------------------------------------------------------------");
    for (int i = 0; i < 5; i++){
        if((q[i]->alow) != 0){
            printf("\nAno: %d\n", (q[i]->ano));
            printf("Codigo UF: %d\n", q[i]->codigo_uf);
            printf("Descricao: %s\n", q[i]->descricao);
            printf("\n");
            flag++;
        }
    }
    if(flag == 0) printf("\n\nNao ha ELEICOES cadastradas\n\n");
}



void excluir_elc(struct ELEICAO **q) {

    while (1) {
        int year;
        int code;
        int indice;
        int escolha;

        printf("Quem voce quer excluir?\n\n");
        printf("Digite o Ano:");
        scanf("%d", &year);

        printf("Digite o Codigo UF:");
        scanf("%d", &code);

        indice = find_for_struct(q, year, code);
        if (indice == -1) {
            printf("\nSem essa eleicao.\n");
            continue;
        }
        printf("Ano: %d\n", (q[indice]->ano));
        printf("Codigo UF: %d\n", (q[indice]->codigo_uf));
        printf("Descricao: %s\n", (q[indice]->descricao));

        printf("\nApagar?\n");
        printf("[1]Sim\n");
        printf("[2]Nao\n");

        scanf("%d", &escolha);
        if (escolha == 1) q[indice]->alow = 0;

        return;
    }

}

void campo_ELEICAO() {
    struct ELEICAO *p[5];
    for(int i = 0 ; i < 5 ; i++){
        p[i] = malloc(sizeof(struct ELEICAO));
    }//crio um vetor de ponteiro para struct UF e aloco um espaço struc UF para cada ponteiro

    iniciar_structs_elc(p);

    FILE *E = fopen("elc", "rb+");
    if(E == NULL) E = fopen("elc", "wb+");
    if(E == NULL) printf("erro ao abrir arquivo");// abro o arquivo de nome elc

    fseek(E, 0, SEEK_SET);
    for (int i = 0; i < 5; i++){
        fread(p[i], sizeof(struct ELEICAO), 1, E);
    }// lê para a memória alocada o tamanho de uma struct UF uma vez do arquivo U

    /////////////////////////////////////////////////////////////////////////////////////


    while(1) {

        introduzir_elc();

        int escolha;
        scanf("%d", &escolha);

        switch(escolha){
            case 1: adicionar_elc(p);
                break;

            case 2: mostrar_elc(p);
                break;

            case 3: excluir_elc(p);
                break;

            case 4: //alterar(p);
                break;

            case 5: //pesquisar(p);
                break;
            case 6:
                fseek(E, 0, SEEK_SET);
                for (int i = 0; i < 5; i++){
                    if (p[i]->alow == 2) {
                        p[i]->alow = 1;//quando salvo, deixa de ser tratado como alterado
                        fseek(E, i * sizeof(struct ELEICAO), SEEK_SET);
                        fwrite(p[i], sizeof(struct ELEICAO), 1, E);
                    }
                }
                for(int i = 0 ; i < 5 ; i++) free(p[i]);
                fclose(E);
                return;

            default: printf("\nOpcao invalida\n");

        }

    }
}