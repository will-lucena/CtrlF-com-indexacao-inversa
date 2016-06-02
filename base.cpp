#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "base.h"

/**
 * Funcao para mostrar a lista
 * 
 * @param lista -> lista que ser� mostrada 
 *  
 * @return void
 *
 */
void show(Lista lista)
{
    std::cout << ">>> Exibicao da lista iniciada <<<" << std::endl;
    for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
    {
        std::cout << p->conteudo->caminho << std::endl;
    }
    std::cout << ">>> Exibicao finalizada <<<" << std::endl;
}

/**
 * Funcao para percorrer uma string que contem dois termos divididos por um '\t', separa os dois termos e os armazena em seu respectivo campo do struct
 *
 * @param linha -> a string a ser "quebrada"
 * @param arquivo -> o arquivo que receber� os termos contidos na linha
 *
 * @return void
 */
void percorrerLinha(std::string linha, Arquivo arquivo)
{
    std::string buffer = "";
    bool divisor = false;
    for (int i = 0; i < linha.length(); i++)
    {
        if (!divisor && linha[i] != '\t')
        {
            buffer = buffer + linha[i];
        }
        if (linha[i] == '\t')
        {
            arquivo->caminho = buffer;
            divisor = true;
            buffer = "";
        }
        if (divisor && linha[i] != '\n')
        {
            buffer = buffer + linha[i];
        }
        if (i == linha.length()-1)
        {
            arquivo->quantidadeDePalavras = std::stoi(buffer);
        }
    }
}

/**
 * Funcao para ler a base de dados armazenada em um .txt e armazena-la em uma lista
 * 
 * @param log -> caminho do arquivo .txt onde est� a base
 *
 * @return lista -> retorna uma lista onde cada n� corresponde a uma linha do arquivo base
 *
 */
Lista carregarBase(const char* log)
{
    std::cout << ">>> Carregando base <<<" << std::endl;
    Lista lista = criarLista();
    //*
    std::string line = "";
    std::ifstream abrir;
    abrir.open(log);
    if (abrir.is_open())
    {
        while (!abrir.eof())
        {
            getline(abrir, line);
            {
                if (line != "")
                {
                    Arquivo arquivo = criarArquivo();
                    arquivo->caminho = line;
                    percorrerLinha(line, arquivo);
                    inserirNaLista(lista, arquivo);
                }  
            }  
        }
    }
    abrir.close();
    /**/
    std::cout << ">>> Base carregada <<<" << std::endl;
    return lista;
}

/**
 * Funcao para copiar uma lista, inserindo elemento a elemento da lista base na lista clonada
 *
 * @param lista -> a lista que se deseja fazer uma c�pia
 *
 * @return lista -> uma lista nova que contem os mesmos elementos da antiga
 *
 */
Lista clonarLista(Lista lista)
{
    std::cout << ">>> Clonando lista <<<" << std::endl;
    Lista clonada = criarLista();
    for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
    {
        inserirNaLista(clonada, p->conteudo);
    }
    std::cout << ">>> Clonagem finalizada <<<" << std::endl;
    return clonada;
}


/**
 * Funcao para inserir um (ou mais) arquivos vindos do terminal na lista
 *
 * @param lista -> lista onde ser� adicionado/atualizado os arquivos passados pelo terminal
 * @param caminhos -> vetor de string contendo o/os arquivos que devem ser adicionados a lista
 * @param quantidadeDeArquivos -> inteiro que informa quantos arquivos ser�o inseridos
 * 
 * @return void
 *
 */
void inserir(Lista lista, std::string* caminhos, int quantidadeDeArquivos)
{
    std::cout << ">>> Inserindo novo arquivo na base <<<" << std::endl;
    int indice = 0;
    bool atualizado = false;
    while (indice < quantidadeDeArquivos)
    {
        Arquivo arquivo = criarArquivo();
        arquivo->caminho = caminhos[indice];
        for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
        {
            if (arquivo->caminho == p->conteudo->caminho)
            {
                atualizado = removerDaLista(lista, arquivo);
            }
        }
        inserirNaLista(lista, arquivo);
        indice++;
    }

    if (atualizado)
    {
        std::cout << "Arquivos foram atualizados" << std::endl;
    }

    std::ofstream novo;
    novo.open("base.txt");
    if (novo.is_open())
    {
        for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
        {
            novo << p->conteudo->caminho << '\t' << p->conteudo->quantidadeDePalavras << std::endl;
        }
        novo.close();
    }
    std::cout << ">>> Insercao finalizada <<<" << std::endl;
}

/**
 * Funcao para remover um (ou mais) arquivos vindos do terminal na lista
 *
 * @param lista -> lista onde ser� removido os arquivos passados pelo terminal
 * @param caminhos -> vetor de string contendo o/os arquivos que devem ser removidos a lista
 * @param quantidadeDeArquivos -> inteiro que informa quantos arquivos ser�o removidos
 * 
 * @return void
 *
 */
void remover(Lista lista, std::string* caminhos, int quantidadeDeArquivos)
{
    std::cout << ">>> Removendo arquivo da base <<<" << std::endl;
    int indice = 0;
    bool removido = false;
    while (indice < quantidadeDeArquivos)
    {
        Arquivo arquivo = criarArquivo();
        arquivo->caminho = caminhos[indice];
        for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
        {
            if (arquivo->caminho == p->conteudo->caminho)
            {
                removido = removerDaLista(lista, arquivo);
            }
        }
        indice++;
    }

    if (!removido)
    {
        std::cout << "Arquivo nao existe na base de dados" << std::endl;
        std::cout << ">>> Remocao cancelada <<<" << std::endl;
        exit(-1);
    }

    std::ofstream novo;
    novo.open("base.txt");
    if (novo.is_open())
    {
        for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
        {
            novo << p->conteudo->caminho << '\t' << p->conteudo->quantidadeDePalavras << std::endl;
        }
        novo.close();
    }
    std::cout << ">>> Remocao finalizada <<<" << std::endl;
}

/**
 * Funcao para mostrar a lista pela ordem de inser��o
 * 
 * @param log -> caminho do arquivo .txt que dever� ser mostrado
 *
 * @return void
 *
 */
void listarInsercao(const char* log)
{
    std::cout << ">>> Exibindo base por ordem de insercao <<<" << std::endl;
    Lista lista = carregarBase(log);
    for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
    {
        std::cout << p->conteudo->caminho << '\t' << p->conteudo->quantidadeDePalavras << std::endl;
    }
    std::cout << ">>> Exibicao finalizada <<<" << std::endl;
}

/**
 * Funcao para mostrar a lista em ordem decrescente com rela��o a quantidade de palavras de cada arquivo
 * 
 * @param log -> caminho do arquivo .txt que dever� ser mostrado
 *
 * @return void
 *
 */
void listarTamanho(const char* log)
{
    std::cout << ">>> Exibindo base por ordem decrescente de quantidade de palavras <<<" << std::endl;
    Lista lista = carregarBase(log);
    lista = selectionSortInt(lista);
    for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
    {
        std::cout << p->conteudo->caminho << '\t' << p->conteudo->quantidadeDePalavras << std::endl;
    }
    std::cout << ">>> Exibicao finalizada <<<" << std::endl;
}

/**
 * Funcao para mostrar a lista em ordem alfab�tica
 * 
 * @param log -> caminho do arquivo .txt que dever� ser mostrado
 *
 * @return void
 *
 */
void listarAlfabetica(const char* log)
{
    std::cout << ">>> Exibindo base em ordem alfabetica <<<" << std::endl;
    Lista lista = carregarBase(log);
    lista = selectionSortString(lista);
    for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
    {
        std::cout << p->conteudo->caminho << '\t' << p->conteudo->quantidadeDePalavras << std::endl;
    }
    std::cout << ">>> Exibicao finalizada <<<" << std::endl;
}

/**
 * Funcao auxiliar que ordena a lista em ordem decrescente
 *
 * @param lista -> lista a ser ordenada
 *
 * @return void
 *
 */
void selectionSortInt(Lista lista)
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
 *
 * @param lista -> lista a ser ordenada
 *
 * @return void
 *
 */
void selectionSortString(Lista lista)
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