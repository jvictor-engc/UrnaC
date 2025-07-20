#ifndef MAX
#define MAX 27
#endif

//generico
void iniciar_structs();
void abrir_criar_arq();


//UF
int achar_livre();
void adicionar();
struct UF{
    int alow;
    int codigo;
    char descricao[20];
    char sigla[3];
};
void campo_UF();
void mostrar();