#include <stdio.h>
#include "UF.h"
#include "PESSOA.h"
#include "Candidato.h"

// abrir arquivo
//fazer malloc
//ler arquivo pro malloc
//f: adicionar no malloc, mostrar do malloc,
// escrever do malloc no arquivo so oque mudou


int main(){
    int escolha;
    printf("\n-----------------------------------------ELEICOES------------------------------------------\n\n");


    while(1){

        printf("[1]UF\n");
        printf("[2]ELEICAO\n");
        printf("[3]CANDIDATO\n");
        printf("[4]PESSOA\n");
        printf("[5]VOTOS\n");
        printf("[6]COMPARECIMENTO\n");
        printf("[7]Sair\n\n");
        printf("Escolha a area de informacao:");
        scanf(" %d", &escolha);


        switch (escolha) {
            case 1:
                campo_UF();
                break;
            case 3:
                campo_candidato();
                break;
			case 4:
				campo_PESSOA();
				break;
            case 7:
                return 0;
            default:
                printf("\n\nDIGITE UMA OPCAO VALIDA\n\n");
        }
    }

    return 0;
}