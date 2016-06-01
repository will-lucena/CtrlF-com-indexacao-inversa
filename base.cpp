#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "lista.h"

void show(Lista lista)
{
    std::cout << ">>> Exibicao da lista iniciada <<<" << std::endl;
    for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
    {
        std::cout << p->conteudo->caminho << std::endl;
    }
    std::cout << ">>> Exibicao finalizada <<<" << std::endl;
}

Lista carregarBase(const char* log)
{
    std::cout << ">>> Carregando base <<<" << std::endl;
    Lista lista = criarLista();
    //*
    std::string line = "";
    std::ifstream abrir;
    Arquivo arquivo = criarArquivo();
    abrir.open(log);
    if (abrir.is_open())
    {
        while (!abrir.eof())
        {
            getline(abrir, line);
            {
                if (line != "")
                {
                    std::cout << line << std::endl;
                    arquivo->caminho = line;
                    std::cout << arquivo->caminho << std::endl;
                    inserirFim(lista, arquivo);
                }  
            }  
        }
    }
    abrir.close();
    show(lista);
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
        inserirFim(clonada, p->conteudo);
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
    std::cout << ">>> Inserido novo arquivo na base <<<" << std::endl;
    int indice = 0;
    show(lista);
    while (indice < quantidadeDeArquivos)
    {
        Arquivo arquivo = criarArquivo();
        arquivo->caminho = caminhos[indice];
        for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
        {
            if (arquivo->caminho == p->conteudo->caminho)
            {
                removerDaLista(lista, arquivo);
            }
        }
        inserirFim(lista, arquivo);
        indice++;
    }

    std::ofstream novo;
    novo.open("base2.txt");
    if (novo.is_open())
    {
        for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
        {
            novo << p->conteudo->caminho << '\t' << p->conteudo->quantidadeDePalavras << std::endl;
        }
        novo.close();
    }
}

/*
    * Recebe um arquivo base e abre um stream de leitura com base nesse arquivo
    * enquanto o arquivo nao chegar ao final (funcao .eof()) imprime a linha atual do arquivo
 */

void listarInsercao(char* log)
{
    std::cout << ">>> Exibindo base por ordem de insercao <<<" << std::endl;
    Lista lista = carregarBase(log);
    for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
    {
        std::cout << p->conteudo->caminho << '\t' << p->conteudo->quantidadeDePalavras << std::endl;
    }
    std::cout << ">>> Exibicao finalizada <<<" << std::endl;
}
