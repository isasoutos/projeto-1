#include "funcao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    Lista *lista = malloc(sizeof(Lista));
    int opcao;

    do {
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
        }
    } while (opcao != 7);

    free(lista);
    return 0;
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

int menu() {
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

void editar_tarefa(Lista *lista) {
    if (lista->qtde == 0) {
        printf("Nenhuma tarefa cadastrada para editar.\n");
        return;
    }

    char nome_tarefa[20];
    printf("Digite o nome da tarefa que deseja editar: ");
    scanf("%s", nome_tarefa);

    for (int i = 0; i < lista->qtde; i++) {
        if (strcmp(lista->vetor[i]->nome, nome_tarefa) == 0) {
            printf("Tarefa encontrada!\n");
            printf("Digite o novo nome (ou pressione ENTER para manter o atual): ");
            scanf("%s", lista->vetor[i]->nome);

            printf("Digite a nova prioridade (ou -1 para manter a atual): ");
            int nova_prioridade;
            scanf("%d", &nova_prioridade);
            if (nova_prioridade != -1) {
                lista->vetor[i]->prioridade = nova_prioridade;
            }

            printf("Digite a nova duração (ou -1 para manter a atual): ");
            int nova_duracao;
            scanf("%d", &nova_duracao);
            if (nova_duracao != -1) {
                lista->vetor[i]->duracao = nova_duracao;
            }

            printf("Tarefa atualizada com sucesso!\n");
            return;
        }
    }

    printf("Tarefa não encontrada!\n");
}