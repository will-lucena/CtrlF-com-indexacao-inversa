#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "base.h"

void show(Lista lista)
{
    std::cout << ">>> Exibicao da lista iniciada <<<" << std::endl;
    for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
    {
        std::cout << p->conteudo->caminho << std::endl;
    }
    std::cout << ">>> Exibicao finalizada <<<" << std::endl;
}

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


/*
    * Cria um novo stream de saida
    * insere no arquivo o novo todos os elementos que tinham na base antiga
    * em seguida insere os novos que foram passados pela linha de comando
    * optarg = o primeiro paramentro da linha de comando
    * optind = o indice de onde começa os outros paramentros
    * fecha o arquivo e retorna o caminho do arquivo criado
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



/*
    * Recebe um arquivo base e abre um stream de leitura com base nesse arquivo
    * enquanto o arquivo nao chegar ao final (funcao .eof()) imprime a linha atual do arquivo
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

Lista selectionSortInt(Lista lista)
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
    return lista;
}

Lista selectionSortString(Lista lista)
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
    return lista;
}