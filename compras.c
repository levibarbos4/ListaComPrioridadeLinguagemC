#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX 40

struct no {
    char nome[MAX];
    int categoria;
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
        novo->proximo = NULL;
        lista->inicio = novo;
        lista->final = novo;
        return;
    } else if (novo->categoria < aux->categoria) {
       novo->proximo = aux;
       lista->inicio = novo;
    } else {
        if (aux->proximo == NULL) {
            if (aux->categoria > novo->categoria) {
                novo->proximo = aux;
                aux->proximo = NULL;
                lista->inicio = novo;
                return;
            }
            aux->proximo = novo;
            novo->proximo = NULL;
            lista->final = aux;
            return;
        } else {
            while (aux->proximo != NULL) {
                if (aux->proximo->categoria > novo->categoria)
                    break;
                aux = aux->proximo;
            }
            if (aux->proximo == NULL) {
                aux->proximo = novo;
                novo->proximo = NULL;
                lista->final = novo;
                return;;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
            lista->final = novo;
        }
    }
}

void mostrar(listadecompras *lista) {
    no *aux = lista->inicio;
    int escolha, categoria, contador = 1;

    puts("[1] Mostrar tudo");
    puts("[2] Mostrar por cadegoria\n\n");
    printf("Escolha: ");
    scanf("%i", &escolha);

    if (aux == NULL)
        puts("Lista Vazia!");
    else if (escolha == 1) {
        while (aux != NULL) {
            printf("Número: %i Nome: %s Categoria: %i\n", contador, aux->nome, aux->categoria);
            aux = aux->proximo;
            contador++;
        }
    } else if (escolha == 2) {
        printf("Digite a categoria: ");
        scanf("%i", &categoria);
        if (aux->categoria > categoria) {
            puts("Categoria vazia!");
            system("cls");
            return;
        }
        while (aux != NULL) {
            if (aux->categoria > categoria) break;
            else if (aux->categoria == categoria)
                printf("Número: %i Nome: %s Categoria: %i\n", contador, aux->nome, aux->categoria);
            aux = aux->proximo;
            contador++;
        }
    }
}

void remover(listadecompras *lista) {
    no *aux = lista->inicio;
    no *aux2;
    char nomeremover[MAX];

    printf("Digite o nome para ser removido: ");
    scanf("%s", &nomeremover);

    if (aux == NULL)
        printf("Lista vazia!");
    else {
        if (strcmp(nomeremover, aux->nome) == 0) {
            lista->inicio = aux->proximo;
            puts("Item a ser removido: ");
            printf("Nome: %s", aux->nome);
            printf("Categoria: %i", aux->categoria);
            free(aux);
            return;
        }
        while (aux->proximo != NULL) {
            if (strcmp(nomeremover, aux->proximo->nome) == 0)
                break;
            aux = aux->proximo;
        }
        if (aux->proximo == NULL) {
            puts("Não encontrado!");
        } else {
            aux2 = aux->proximo;
            aux->proximo = aux->proximo->proximo;
            printf("Nome: %s", aux2->nome);
            printf("Categoria: %i", aux2->categoria);
            free(aux2);
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
