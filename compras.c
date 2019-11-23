#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct no // estrutura que define um item
{
    char nome[100];
    int categoria;
    no *proximo;
    no *anterior;

} no;

typedef struct listadecompras // estrutura que define a lista de compras
{
    no *inicio;
    no *categoria1;
    no *categoria2;
    no *categoria3;
    no *categoria4;

} listadecompras;

no *criar();
void inserir(listadecompras *lista);
void iniciar(listadecompras *lista);

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "portuguese");
    int escolha, categoria;
    char nome[100];
    listadecompras lista;
    iniciar(&lista);

    while (1)
    {
        escolha = -1;
        system("cls");

        puts("[1] Inserir");
        puts("[2] Remover");
        puts("[3] Mostrar");
        puts("[4] zerar");
        puts("[0] Sair\n");
        printf("Escolha: ");
        scanf("%i", &escolha);

        switch (escolha)
        {
        case 0:
            exit(0);
            break;
        case 1:
            system("cls");
            inserir(&lista);
            system("pause");
            break;
        case 2:
            system("cls");

            printf("Nome: ");
            scanf("%s", &nome);

            system("pause");
            break;
        case 3:
            system("cls");
            system("pause");
            break;

        case 4:
            system("cls");

            puts("Lista zerada!\n");
            system("pause");
            break;
        default:
            break;
        }
    }
    return 0;
}

no *criar()
{
    no *novo = (no *)malloc(sizeof(no));
    novo->anterior = NULL;
    novo->proximo = NULL;

    printf("Digite o nome: ");
    scanf("%s", &novo->nome);
    printf("Digite a categoria: ");
    scanf("%i", &novo->categoria);

    return novo;
}

void inserir(listadecompras *lista)
{
    no *novo = criar();
    no *aux;

    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
        return;
    }
    else if (novo->categoria == 4)
    {
        aux = lista->categoria4;
        aux->proximo = novo;
        novo->anterior = aux;
        return;
    }

    else if (novo->categoria == 1)
        aux = lista->categoria1;
    else if (novo->categoria == 2)
        aux = lista->categoria2;
    else if (novo->categoria == 3)
        aux = lista->categoria3;

    novo->proximo = aux->proximo;
    aux->proximo->anterior = novo;
    novo->anterior = aux;
}

void iniciar(listadecompras *lista)
{
    lista->categoria1 = NULL;
    lista->categoria2 = NULL;
    lista->categoria3 = NULL;
    lista->categoria4 = NULL;
    lista->inicio = NULL;
}