#include <iostream>
#include <fstream>
#include <sstream>

#include "libs/base.h"

/**
 * Funcao para percorrer uma string que contem dois termos divididos por um '\t', separa os dois termos e os armazena em seu respectivo campo do struct
 * @param linha -> a string a ser "quebrada"
 * @param arquivo -> o arquivo que receberá os termos contidos na linha
 * @return void
 */
void percorrerLinha(std::string linha, Arquivo arquivo)
{
    std::string buffer = "";
    bool divisor = false;
    for (int index = 0; index < linha.length(); index++)
    {
        if (!divisor && linha[index] != '\t')
        {
            buffer = buffer + linha[index];
        }
        else if (linha[index] == '\t')
        {
            arquivo->caminho = buffer;
            divisor = true;
            buffer = "";
        }
        else if (divisor && linha[index] != '\n')
        {
            buffer = buffer + linha[index];
        }
        else if (index == linha.length()-1)
        {
            arquivo->quantidadeDePalavras = std::stoi(buffer);
        }
    }
}

/**
 * Funcao para ler a base de dados armazenada em um .txt e armazena-la em uma lista
 * @param base -> caminho do arquivo .txt onde está a base
 * @return lista -> retorna uma lista onde cada nó corresponde a uma linha do arquivo base
 */
Lista carregarBase(const char* base)
{
    Lista lista = criarLista();
    //*
    std::string linha = "";
    std::ifstream abrir;
    abrir.open(base);
    if (abrir.is_open())
    {
        while (!abrir.eof())
        {
            getline(abrir, linha);
            {
                if (linha != "")
                {
                    Arquivo arquivo = criarArquivo();
                    arquivo->caminho = linha;
                    percorrerLinha(linha, arquivo);
                    inserirNaLista(lista, arquivo);
                }  
            }  
        }
    }
    abrir.close();
    /**/
    return lista;
}

/**
 * Funcao para inserir um (ou mais) arquivos vindos do terminal na lista
 * @param lista -> lista onde será adicionado/atualizado os arquivos passados pelo terminal
 * @param caminhos -> vetor de string contendo o/os arquivos que devem ser adicionados a lista
 * @param quantidadeDeArquivos -> inteiro que informa quantos arquivos serão inseridos
 * @return void
 */
void inserirNaBase(Lista lista, Arquivo arquivo)
{
    bool atualizado = false;
    for (No index = lista->cabeca->proximo; index != lista->cauda; index = index->proximo)
    {
        if (arquivo->caminho == index->conteudo->caminho)
        {
            removerDaLista(lista, arquivo);
            atualizado = true;
            std::cout << "\t>> Arquivo """ << arquivo->caminho << """ ja estava na base de buscas." << std::endl;
            std::cout << "\tSeu registro foi atualizado." << std::endl;
        }
    }

    inserirNaLista(lista, arquivo);
    if (!atualizado)
    {
        std::cout << "\t>> Arquivo """ << arquivo->caminho << """ inserido na base de buscas." << std::endl;
    } 

    std::ofstream base;
    base.open("arquivos_gerados/base.txt");
    if (base.is_open())
    {
        for (No index = lista->cabeca->proximo; index != lista->cauda; index = index->proximo)
        {
            base << index->conteudo->caminho << '\t' << index->conteudo->quantidadeDePalavras << std::endl;
        }
        base.close();
    }
}

/**
 * Funcao para remover um (ou mais) arquivos vindos do terminal na lista
 * @param lista -> lista onde será removido os arquivos passados pelo terminal
 * @param caminhos -> vetor de string contendo o/os arquivos que devem ser removidos a lista
 * @param quantidadeDeArquivos -> inteiro que informa quantos arquivos serão removidos
 * @return void
 */
void removerDaBase(Lista lista, Arquivo arquivo)
{
    bool removido = false;
    for (No index = lista->cabeca->proximo; index != lista->cauda; index = index->proximo)
    {
        if (arquivo->caminho == index->conteudo->caminho)
        {
            removido = removerDaLista(lista, arquivo);
            std::cout << "\t>> Arquivo " << arquivo->caminho << " removido da base de buscas." << std::endl;
        }
    }

    if (!removido)
    {
        std::cout << "\t>> Arquivo " << arquivo->caminho << " nao estava na base de buscas." << std::endl;
        exit(-1);
    }

    std::ofstream base;
    base.open("arquivos_gerados/base.txt");
    if (base.is_open())
    {
        for (No index = lista->cabeca->proximo; index != lista->cauda; index = index->proximo)
        {
            base << index->conteudo->caminho << '\t' << index->conteudo->quantidadeDePalavras << std::endl;
        }
        base.close();
    }
}

void removerDaBase(Lista lista, std::string arquivo)
{
    bool removido = false;
    for (No index = lista->cabeca->proximo; index != lista->cauda; index = index->proximo)
    {
        if (arquivo == index->conteudo->caminho)
        {
            Arquivo arquivo = new tpArquivo;
            arquivo->caminho = index->conteudo->caminho;
            arquivo->quantidadeDePalavras = index->conteudo->quantidadeDePalavras;
            removido = removerDaLista(lista, arquivo);
            std::cout << "\t>> Arquivo " << arquivo->caminho << " removido da base de buscas." << std::endl;
        }
    }

    if (!removido)
    {
        std::cout << "\t>> Arquivo " << arquivo << " nao estava na base de buscas." << std::endl;
        exit(-1);
    }

    std::ofstream base;
    base.open("arquivos_gerados/base.txt");
    if (base.is_open())
    {
        for (No index = lista->cabeca->proximo; index != lista->cauda; index = index->proximo)
        {
            base << index->conteudo->caminho << '\t' << index->conteudo->quantidadeDePalavras << std::endl;
        }
        base.close();
    }
}

/**
 * Funcao para mostrar a lista pela ordem de inserção
 * @param log -> caminho do arquivo .txt que deverá ser mostrado
 * @return void
 */
void listarInsercao(Lista lista)
{
    std::cout << "\t>> Arquivos contidos na base de buscas" << std::endl;
    for (No index = lista->cabeca->proximo; index != lista->cauda; index = index->proximo)
    {
        std::cout << "\t\t- " << index->conteudo->caminho << std::endl;
    }
}

/**
 * Funcao para mostrar a lista em ordem decrescente com relação a quantidade de palavras de cada arquivo
 * @param log -> caminho do arquivo .txt que deverá ser mostrado
 * @return void
 */
void listarTamanho(Lista lista)
{
    std::cout << "\t>> Arquivos contidos na base de buscas" << std::endl;
    selectionSortDecrescente(lista);
    for (No index = lista->cabeca->proximo; index != lista->cauda; index = index->proximo)
    {
        std::cout << "\t\t- " << index->conteudo->caminho << std::endl;
    }
}

/**
 * Funcao para mostrar a lista em ordem alfabética
 * @param log -> caminho do arquivo .txt que deverá ser mostrado
 * @return void
 */
void listarAlfabetica(Lista lista)
{
    std::cout << "\t>> Arquivos contidos na base de buscas" << std::endl;
    selectionSortCrescente(lista);
    for (No index = lista->cabeca->proximo; index != lista->cauda; index = index->proximo)
    {
        std::cout << "\t\t- " << index->conteudo->caminho << std::endl;
    }
}

/**
 * Funcao auxiliar que ordena a lista em ordem decrescente
 * @param lista -> lista a ser ordenada
 * @return void
 */
void selectionSortDecrescente(Lista lista)
{
    for (No busca = lista->cabeca->proximo; busca != lista->cauda; busca = busca->proximo)
    {
        No maior = busca;
        for (No aux = busca->proximo; aux != lista->cauda; aux = aux->proximo)
        {
            if (aux->conteudo->quantidadeDePalavras > maior->conteudo->quantidadeDePalavras)
            {
                maior = aux;
            }
        }
        if (maior != busca)
        {
            int palavrasTmp = maior->conteudo->quantidadeDePalavras;
            std::string nomeTmp = maior->conteudo->caminho;

            maior->conteudo->quantidadeDePalavras = busca->conteudo->quantidadeDePalavras;
            maior->conteudo->caminho = busca->conteudo->caminho;

            busca->conteudo->quantidadeDePalavras = palavrasTmp;
            busca->conteudo->caminho = nomeTmp;
        }
    }
}

/**
 * Funcao auxiliar que ordena a lista em ordem alfabetica
 * @param lista -> lista a ser ordenada
 * @return void
 */
void selectionSortCrescente(Lista lista)
{
    for (No busca = lista->cabeca->proximo; busca != lista->cauda; busca = busca->proximo)
    {
        No menor = busca;
        for (No aux = busca->proximo; aux != lista->cauda; aux = aux->proximo)
        {
            if (aux->conteudo->caminho < menor->conteudo->caminho)
            {
                menor = aux;
            }
        }
        if (menor != busca)
        {
            int palavrasTmp = menor->conteudo->quantidadeDePalavras;
            std::string nomeTmp = menor->conteudo->caminho;

            menor->conteudo->quantidadeDePalavras = busca->conteudo->quantidadeDePalavras;
            menor->conteudo->caminho = busca->conteudo->caminho;

            busca->conteudo->quantidadeDePalavras = palavrasTmp;
            busca->conteudo->caminho = nomeTmp;
        }
    }
}