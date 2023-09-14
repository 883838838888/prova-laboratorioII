#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>

// Estrutura de dados para um contato
typedef struct {
    char nome[50];
    char email[50];
    char telefone[15];
} Contato;

// Tamanho m�ximo da lista de contatos
#define MAX_CONTATOS 100
#define _CTYPE_H

// Tabela hash para armazenar os contatos
Contato tabela[MAX_CONTATOS];

// Fun��o de mapeamento: multiplica��o
int hash(char* chave) {
    unsigned int h = 0;
    int i;
    for (i = 0; chave[i] != '\0'; i++) {
        h = h * 31 + chave[i];
    }
    return h % MAX_CONTATOS;
}

// Fun��o para tratar colis�o: endere�amento direto
int hash_colisao(int indice) {
    return (indice + 1) % MAX_CONTATOS;
}

// Fun��o para validar um nome de contato
bool validarNome(char* nome) {
    int i;
    for (i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i])) {
            return false;
        }
    }
    return true;
}

// Fun��o para validar um e-mail de contato
bool validarEmail(char* email) {
    int i, atCount = 0, dotCount = 0;
    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            atCount++;
        }
        if (email[i] == '.') {
            dotCount++;
        }
    }
    return atCount == 1 && dotCount >= 1;
}

// Fun��o para validar um telefone de contato
bool validarTelefone(char* telefone) {
    int i, digitCount = 0, dashCount = 0;
    for (i = 0; telefone[i] != '\0'; i++) {
        if (isdigit(telefone[i])) {
            digitCount++;
        }
        if (telefone[i] == '-') {
            dashCount++;
        }
    }
    return digitCount >= 8 && digitCount <= 12 && dashCount <= 1;
}

// Fun��o para adicionar um novo contato
void adicionarContato() {
    Contato novoContato;
    printf("Digite o nome: ");
    scanf("%s", novoContato.nome);
    if (!validarNome(novoContato.nome)) {
        printf("Nome inv�lido.\n");
        return;
    }

    printf("Digite o e-mail: ");
    scanf("%s", novoContato.email);
    if (!validarEmail(novoContato.email)) {
        printf("E-mail inv�lido.\n");
        return;
    }

    printf("Digite o telefone: ");
    scanf("%s", novoContato.telefone);
    if (!validarTelefone(novoContato.telefone)) {
        printf("Telefone inv�lido.\n");
        return;
    }

    // Calcular o �ndice de hash para o novo contato
    int indice = hash(novoContato.nome);

    // Verificar se o �ndice est� livre
    if (strlen(tabela[indice].nome) == 0) {
        tabela[indice] = novoContato;
        printf("Contato adicionado com sucesso!\n");
    } else {
        // Verificar se o contato j� existe
        int indice_colisao = hash_colisao(indice);
        while (strlen(tabela[indice_colisao].nome) > 0) {
            indice_colisao = hash_colisao(indice_colisao);
        }
        tabela[indice_colisao] = novoContato;
        printf("Contato adicionado com sucesso!\n");
    }
}
// Fun��o para listar contatos
void listarContatos() {
    int i;

    // Imprimir o cabe�alho da lista
    printf("Lista de contatos:\n");
    printf("Nome | E-mail | Telefone\n");

    // Imprimir cada contato
    for (i = 0; i < MAX_CONTATOS; i++) {
        if (strlen(tabela[i].nome) > 0) {
            printf("%s | %s | %s\n", tabela[i].nome, tabela[i].email, tabela[i].telefone);
        }
    }
}
// Fun��o para buscar um contato
void buscarContato() {
    char nome[50];
    int indice;

    // Pedir o nome do contato a ser buscado
    printf("Digite o nome do contato a ser buscado: ");
    scanf("%s", nome);

    // Calcular o �ndice de hash para o nome
    indice = hash(nome);

    // Verificar se o contato existe
    if (strlen(tabela[indice].nome) > 0) {
        // O contato foi encontrado
        printf("Contato encontrado:\n");
        printf("Nome: %s\n", tabela[indice].nome);
        printf("E-mail: %s\n", tabela[indice].email);
        printf("Telefone: %s\n", tabela[indice].telefone);
    } else {
        // O contato n�o foi encontrado
        printf("Contato n�o encontrado.\n");
    }
}
// Fun��o para exportar contatos
void exportarContatos() {
    // Abrir o arquivo para escrita
    FILE* arquivo = fopen("contatos.csv", "w");

    // Verificar se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        return;
    }

    // Imprimir o cabe�alho do arquivo CSV
    fprintf(arquivo, "nome,email,telefone\n");

    // Imprimir cada contato
    int i;
    for ( i = 0; i < MAX_CONTATOS; i++) {
        if (strlen(tabela[i].nome) > 0) {
            fprintf(arquivo, "%s,%s,%s\n", tabela[i].nome, tabela[i].email, tabela[i].telefone);
        }
    }

    // Fechar o arquivo
    fclose(arquivo);

    // Imprimir mensagem de sucesso
    printf("Contatos exportados com sucesso.\n");
}
// Fun��o para exibir o menu
int main() {
    int opcao;
    setlocale(LC_ALL, "Portuguese");

    // Loop principal do menu
    while (1) {
        printf(" MENU:\n");
        printf("1. Adicionar contato\n");
        printf("2. Listar contatos\n");
        printf("3. Buscar contato\n");
        printf("4. Exportar contatos\n");
        printf("5. Sair\n");
        printf("Digite a opcao desejada: \n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                listarContatos();
                break;
            case 3:
                buscarContato();
                break;
            case 4:
                exportarContatos();
                break;
            case 5:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opcaoo invalida. Tente novamente.\n");
        }

        printf("\n");
    }
}

