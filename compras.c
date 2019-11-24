#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX 40

struct no {
    char nome[MAX];
    int categoria;
    struct no *anterior;
    struct no *proximo;
};
typedef struct no no;

struct listadecompras {
    no *inicio;
    no *final;
};
typedef struct listadecompras listadecompras;

void inserir(listadecompras *lista);

void mostrar(listadecompras *lista);

void remover(listadecompras *lista);

void reiniciar(listadecompras *lista);

int main() {
    setlocale(LC_ALL, "portuguese");
    int escolha;
    listadecompras lista;
    lista.inicio = NULL;
    lista.final = NULL;

    while (1) {
        escolha = -1;
        system("cls");

        puts("[1] Inserir");
        puts("[2] Remover");
        puts("[3] Mostrar");
        puts("[4] Reiniciar");
        puts("[0] Sair\n");
        printf("Escolha: ");
        scanf("%i", &escolha);

        switch (escolha) {
            case 0:
                exit(0);
            case 1:
                system("cls");
                inserir(&lista);
                system("pause");
                break;
            case 2:
                system("cls");
                remover(&lista);
                system("pause");
                break;
            case 3:
                system("cls");

                mostrar(&lista);

                system("pause");
                break;

            case 4:
                system("cls");
                reiniciar(&lista);
                puts("Lista zerada!\n");
                system("pause");
                break;
            default:
                break;
        }
    }
}

void inserir(listadecompras *lista) {
    no *novo = (no *) malloc(sizeof(no));
    no *aux = lista->inicio;

    printf("Digite o nome: ");
    scanf("%s", &novo->nome);
    printf("Digite a categoria: ");
    scanf("%i", &novo->categoria);

    if (aux == NULL) {
        novo->anterior = NULL;
        novo->proximo = NULL;
        lista->inicio = novo;
        lista->final = novo;
        return;
    } else {
        while (aux->proximo != NULL) {
            if (aux->proximo->categoria > novo->categoria)
                break;
            aux = aux->proximo;
        }

        if (aux->proximo == NULL) {
            novo->anterior = aux;
            aux->proximo = novo;
            novo->proximo = NULL;
            lista->final = aux;
        } else {
            novo->proximo = aux->proximo;
            novo->proximo->anterior = novo;
            aux->proximo = novo;
            novo->anterior = aux;
            lista->final = novo;
        }
    }
}

void mostrar(listadecompras *lista) {
    no *aux = lista->inicio;
    int contador = 1;
    if (aux == NULL)
        puts("Lista Vazia!");
    else {
        while (aux != NULL) {
            printf("Número: %i Nome: %s Categoria: %i\n", contador, aux->nome, aux->categoria);
            aux = aux->proximo;
            contador++;
        }
    }
}

void remover(listadecompras *lista) {
    no *aux = lista->inicio;
    char nomeremover[MAX];

    printf("Digite o nome para ser removido: ");
    scanf("%s", &nomeremover);

    if (aux == NULL)
        printf("Lista vazia!");
    else {
        if (strcmp(nomeremover, aux->nome) == 0) {
            lista->inicio = aux->proximo;
            aux->proximo->anterior = NULL;
            free(aux);
            return;
        }
        while (aux->proximo != NULL) {
            if (strcmp(nomeremover, aux->nome) == 0)
                break;
            aux = aux->proximo;
        }
        if (aux->proximo == NULL) {
            aux->anterior->proximo = NULL;
            free(aux);
        } else {
            aux->anterior->proximo = aux->proximo;
            aux->proximo->anterior = aux->anterior;
            free(aux);
        }
    }
}

void reiniciar(listadecompras *lista) {
    no *aux = lista->inicio;
    if (aux == NULL)
        return;
    else {
        while (aux != NULL) {
            no *aux2 = aux;
            aux = aux->proximo;
            free(aux2);
        }
        free(aux);
        lista->inicio = NULL;
        lista->final = NULL;
    }
}