#include "funcao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    Lista *lista = malloc(sizeof(Lista));
    int opcao;
    
    do{
        opcao = menu();

        if(opcao == 1){
            Tarefa *nova = cria_tarefa();
            inserir_tarefa(lista, nova);
        }else if(opcao == 2){
            remover_tarefa(lista);
        }else if(opcao == 3){
            consultar_tarefa(lista);
        }else if(opcao == 4){
            mostra_tarefas(lista);
        }else if (opcao == 5){
            ler_arquivos(lista);
        }else if (opcao == 6){
            gravar_arquivos(lista);
        }else if (opcao == 7){
            ordenar_tarefas_por_prioridade
    }while (opcao != 8);
        
}

int inserir_tarefa(Lista *lista, Tarefa *tarefa){
    if(lista->qtde == 100){
        return 0;
    }
    lista->vetor[lista->qtde] = tarefa;
    lista->qtde++;
    return 1;
}

Tarefa *cria_tarefa(){
    Tarefa *nova = malloc(sizeof(Tarefa));
    printf("Digite o nome da tarefa: ");
    scanf("%s", nova->nome);
    printf("Digite a prioridade da tarefa: ");
    scanf("%d", &nova->prioridade);
    printf("Digite a duração da tarefa: ");
    scanf("%d", &nova->duracao);
    return nova;
}

void mostra_tarefas(Lista *lista){
    for(int i = 0; i < lista->qtde; i++){
        printf("--------------------------\n");
        printf("Nome: \t\t%s\n", lista->vetor[i]->nome);
        printf("Prioridade: \t%d\n", lista->vetor[i]->prioridade);
        printf("Duração: \t%d\n", lista->vetor[i]->duracao);
        printf("--------------------------\n");
    }
}

int menu(){
    int opcao;
    
    printf("--------------------------\n");
    printf("1 - inserir tarefa\n");
    printf("2 - remover tarefa\n");
    printf("3 - consultar tarefa\n");
    printf("4 - mostrar tarefas\n");
    printf("5 - ler arquivo\n");
    printf("6 - gravar arquivo\n");
    printf("7 - sair\n");
    printf("--------------------------\n");
    printf("Digite sua opção: ");
    scanf("%d", &opcao);

    return opcao;
}

void remover_tarefa(Lista *lista){
    char tarefa[20];
    int i;
    printf("--------------------------\n");
    printf("Digite o nome da tarefa a ser removida: ");
    scanf("%s", tarefa);
    for(i = 0; i < lista->qtde; i++){
        if(strcmp(lista->vetor[i]->nome, tarefa) == 0){
            break;
        }
    }

    if(i == lista->qtde){
        printf("--------------------------\n");
        printf("Tarefa não encontrada\n");
        printf("--------------------------\n");
        return;
    }

    free(lista->vetor[i]);

    for(int j = i; j < lista->qtde - 1; j++){
        lista->vetor[j] = lista->vetor[j + 1];
    }
    lista->qtde--;

    printf("\nTarefa removida com sucesso\n");
    printf("--------------------------\n");

}

void consultar_tarefa(Lista *lista){
    char tarefa[20];
    int i;
    printf("--------------------------\n");
    printf("Digite o nome da tarefa a ser consultada: ");
    scanf("%s", tarefa);
    for(i = 0; i < lista->qtde; i++){
        if(strcmp(lista->vetor[i]->nome, tarefa) == 0){
            printf("--------------------------\n");
            printf("Nome: \t\t%s\n", lista->vetor[i]->nome);
            printf("Prioridade: \t%d\n", lista->vetor[i]->prioridade);
            printf("Duração: \t%d\n", lista->vetor[i]->duracao);
            printf("--------------------------\n");
            break;
        }
    }

    if(i == lista->qtde){
        printf("--------------------------\n");
        printf("Tarefa não encontrada\n");
        printf("--------------------------\n");
        return;
    }

}

void ler_arquivos(Lista *lista) {
    FILE *file = fopen("tarefas.txt", "r"); 
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    while (!feof(file)) {
        Tarefa *nova = malloc(sizeof(Tarefa));
        if (fscanf(file, "%s %d %d", nova->nome, &nova->prioridade, &nova->duracao) == 3) {
            lista->vetor[lista->qtde] = nova;
            lista->qtde++;
        } else {
            free(nova);
            break;
        }
    }

    fclose(file); 
    printf("Tarefas carregadas com sucesso!\n");
}

void gravar_arquivos(Lista *lista) {
    FILE *file = fopen("tarefas.txt", "w"); 

    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    for (int i = 0; i < lista->qtde; i++) {
        fprintf(file, "%s %d %d\n", lista->vetor[i]->nome, lista->vetor[i]->prioridade, lista->vetor[i]->duracao);
    }

    fclose(file); 
    printf("Tarefas salvas com sucesso!\n");
}

void ordenar_tarefas_por_prioridade(Lista *lista) {
    for (int i = 0; i < lista->qtde - 1; i++) {
        for (int j = i + 1; j < lista->qtde; j++) {
            if (lista->vetor[i]->prioridade < lista->vetor[j]->prioridade) {
                Tarefa *temp = lista->vetor[i];
                lista->vetor[i] = lista->vetor[j];
                lista->vetor[j] = temp;
            }
        }
    }
}
