#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX 40

struct no {  // estrutura de cada item
    char nome[MAX];
    int categoria;
    struct no *proximo;
};
typedef struct no no;

struct listadecompras { // estrutura da lita de compras
    no *inicio;
    no *final;
};
typedef struct listadecompras listadecompras;

// cabe�alhos das fun��es

void inserir(listadecompras *lista);

void mostrar(listadecompras *lista);

void remover(listadecompras *lista);

void reiniciar(listadecompras *lista);

int main() {
    setlocale(LC_ALL, "portuguese"); // seta local como portugu�s, desativar se for usar no linux
    int escolha;  // guarda a escolha do menu

    // inicia a lista
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
                inserir(&lista); // chama a fun��o de inserir
                system("pause");
                puts("");
                break;
            case 2:
                system("cls");
                remover(&lista); // chamma a fun��o para remover
                system("pause");
                puts("");
                break;
            case 3:
                system("cls");
                mostrar(&lista); // chama a fun��o mostrar
                puts("");
                system("pause");
                break;

            case 4:
                system("cls");
                reiniciar(&lista); // zera a lista
                puts("Lista zerada!\n");
                puts("");
                system("pause");
                break;
            default:
                break;
        }
    }
}

void inserir(listadecompras *lista) {
    no *novo = (no *) malloc(sizeof(no));  // aloca um novo n�
    no *aux = lista->inicio;  // cria uma auxiliar apontando para o primeiro da lista

    // recebe os dados para o novo n�
    printf("Digite o nome: ");
    scanf("%s", &novo->nome);
    puts("[1] Mercearia");
    puts("[2] Higiene e limpeza");
    puts("[3] Horti-fruti");
    puts("[4] Refrigerados\n");

    printf("Digite a categoria: ");
    scanf("%i", &novo->categoria);

    if (aux == NULL) {  // insere caso a lista esteja vazia
        novo->proximo = NULL;
        lista->inicio = novo;
        lista->final = novo;
        return;
    } else if (novo->categoria < aux->categoria) { // insere no come�o caso a categoria seja a de maior prioridade
        novo->proximo = aux;
        lista->inicio = novo;
    } else {
        if (aux->proximo == NULL) {
            if (aux->categoria > novo->categoria) { // inser��o pro prioridade
                novo->proximo = aux;
                aux->proximo = NULL;
                lista->inicio = novo;
                return;
            }
            aux->proximo = novo; // inser��o no fim da lista
            novo->proximo = NULL;
            lista->final = aux;
            return;
        } else { // percorre a lista para achar o fim da categoria
            while (aux->proximo != NULL) {
                if (aux->proximo->categoria > novo->categoria)
                    break;
                aux = aux->proximo;
            }
            if (aux->proximo == NULL) { // insere no fim
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
    no *aux = lista->inicio; // no aux recebe o come�o
    int escolha, categoria, contador = 1;

    puts("[1] Mostrar tudo");
    puts("[2] Mostrar por cadegoria\n\n");
    printf("Escolha: ");
    scanf("%i", &escolha);

    if (aux == NULL) // verifica se a lista est� vazia
        puts("Lista Vazia!");
    else if (escolha == 1) { // mostra todos os elementos
        while (aux != NULL) {
            printf("N�mero: %i \t Nome: %s \t Categoria: %i\n", contador, aux->nome, aux->categoria);
            aux = aux->proximo;
            contador++;
        }
    } else if (escolha == 2) { //mostra elementos por categoria
        printf("Digite a categoria: ");
        scanf("%i", &categoria);
        if (aux->categoria > categoria) { // verifica se a categoria existe
            puts("Categoria vazia!");
            system("cls");
            return;
        }
        while (aux != NULL) { // percorre a lista printando apenas a categoria desejada
            if (aux->categoria > categoria) break;
            else if (aux->categoria == categoria)
                printf("N�mero: %i \t Nome: %s \t Categoria: %i\n", contador, aux->nome, aux->categoria);
            aux = aux->proximo;
            contador++;
        }
    }
}

void remover(listadecompras *lista) {
    no *aux = lista->inicio;  // dois auxiliares no inicio
    no *aux2;
    char nomeremover[MAX];

    printf("Digite o nome para ser removido: ");
    scanf("%s", &nomeremover);  // recebe o nome do elemento a ser removido

    if (aux == NULL)  // verifica se est� vazia a lista
        printf("Lista vazia!");
    else {
        if (strcmp(nomeremover, aux->nome) == 0) {  // remove o primeiro elemento caso seja
            lista->inicio = aux->proximo;
            puts("Item a ser removido: ");
            printf("Nome: %s\n", aux->nome);
            printf("Categoria: %i\n", aux->categoria);
            free(aux);
            return;
        }
        while (aux->proximo != NULL) {  // percorre at� achar o elemento desejado
            if (strcmp(nomeremover, aux->proximo->nome) == 0)
                break;
            aux = aux->proximo;
        }
        if (aux->proximo == NULL) {  // retorna caso n encontre
            puts("N�o encontrado!");
        } else {  // remove o elemento desejado
            aux2 = aux->proximo;
            aux->proximo = aux->proximo->proximo;
            printf("Nome: %s\n", aux2->nome);
            printf("Categoria: %i\n", aux2->categoria);
            free(aux2);
        }
    }
}

void reiniciar(listadecompras *lista) {
    no *aux = lista->inicio;
    if (aux == NULL)  // retorna se a lista estiver vazia
        return;
    else {
        while (aux != NULL) {  // percorre deletando a lista at� achar o �ltimo elemento
            no *aux2 = aux;
            aux = aux->proximo;
            free(aux2);
        }
        free(aux); // deleta o �ltimo elemento
        lista->inicio = NULL;  // lista � reiniciada
        lista->final = NULL;
    }
}

// aten��o, a lista tem prioridade por categoria
// a menor categoria sempre ter� prioridade
// n�o estando limitada as 4 categorias
// final da lista n�o � necess�rio
// se for compilar lembre-se de alterar a condifica��o do arquivo para windows 1252