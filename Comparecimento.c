#include "Comparecimento.h"
#include "PESSOA.h"

#include <stdio.h>
#include <stdlib.h>


void cadastrar_comparecimento(struct PESSOA *p[]) {
    char titulo[25]; int indice = 0;
    printf("Digite o TITULO do eleitor que quer cadastrar que votou");
    fflush(stdin);
    gets(titulo);
    indice = search_titulo(titulo, p);
    if (indice == -1) {
        printf("Titulo nao encontrado!\n");
        return;
    }
    if (p[indice]->comparecimento == 1 ) {
        printf("Comparecimento ja registrado!\n");
        return;
    }
    p[indice]->comparecimento = 1;
    printf("Comparecimento Registrado!\n");
}

void campo_comparecimento() {
    FILE *arquivo = fopen("pessoas","rb+");
    if (arquivo == NULL) {
        printf("ainda nao foram registradas pessoas!\n");
        return;
    }
    struct PESSOA *pessoa[MAX];
    for (int i = 0; i < MAX; i++) {
        pessoa[i] = malloc(sizeof(struct PESSOA));
        pessoa[i]->comparecimento = 0;
        pessoa[i]->allow = 0;
    }
    for (int i = 0; i < MAX; i++) {
        fread(pessoa[i], sizeof(struct PESSOA), 1, arquivo);
    }
    int choice, flag = 0;
    do {
        printf("Escolha sua opcao:\n");
        printf("[1]para cadastrar comparecimento\n");
        printf("[2]para verificar comparecimento\n");
        printf("[3]para remover comparecimento\n");
        printf("[4]para SAIR e SALVAR\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                cadastrar_comparecimento(pessoa);
                break;
            case 2:
                //verificar_comparecimento(p);
                break;
            case 3:
                //remover_comparecimento(p);
                break;
            case 4:
                flag = 1;
                break;
            default:
                printf("opcao invalida\n");
                break;
        }
    }while (!flag);
    fseek(arquivo, 0, SEEK_SET);
    for (int i = 0; i < MAX; i++) {
        fwrite(pessoa[i], sizeof(struct PESSOA), 1, arquivo);
    }
    fclose(arquivo);
}
