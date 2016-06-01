#include "lista.h"

using namespace std;

Lista criarLista()
{
	Lista lista = new tpLista;
    if( lista == NULL )
    {
        return NULL;
    }

    Arquivo arquivo = new tpArquivo;
    arquivo->caminho = "";
    arquivo->quantidadeDePalavras = 0;
    lista->cabeca = criarNo(arquivo);
    if( lista->cabeca == NULL )
    {
        return NULL;
    }

    lista->cauda = criarNo(arquivo);
    if( lista->cauda == NULL )
    {
        return NULL;
    }

    lista->cabeca->proximo  = lista->cauda;
    lista->cabeca->anterior = NULL;
    lista->cauda->proximo  = NULL;
    lista->cauda->anterior = lista->cabeca;

    lista->tamanho = 0;
    return lista;
}

No criarNo(Arquivo arquivo)
{
    No no = new tpNo;
    if(no == NULL)
    {
        return NULL;
    }

    no->proximo = NULL;
    no->anterior = NULL;

    no->conteudo = arquivo;

    return no;
}

Arquivo criarArquivo()
{
    Arquivo arquivo = new tpArquivo;
    if (arquivo == NULL)
    {
        return NULL;
    }

    arquivo->caminho = "";
    arquivo->quantidadeDePalavras = 0;

    return arquivo;
}

bool vazia(Lista lista)
{
	if (lista->tamanho == 0)
    {
		return true;
    }
	else
    {
		return false;
    }
}

bool inserirFim(Lista lista, Arquivo arquivo)
{
	No novo = criarNo(arquivo);

	novo->proximo = lista->cauda;
	novo->anterior = lista->cauda->anterior;

	lista->cauda->anterior->proximo = novo;
	lista->cauda->anterior = novo;
	lista->tamanho++;

	return true;
}

bool removerDaLista(Lista lista, Arquivo arquivo)
{
    if (lista->tamanho == 0)
    {
        return false;
    }

    No busca = lista->cabeca->proximo;
    while(busca->conteudo->caminho != arquivo->caminho && busca->conteudo->quantidadeDePalavras != arquivo->quantidadeDePalavras
        && busca != lista->cauda)
    {
        busca = busca->proximo;
    }
    while (busca != lista->cauda->anterior)
    {
        busca->conteudo->caminho = busca->proximo->conteudo->caminho;
        busca->conteudo->quantidadeDePalavras = busca->proximo->conteudo->quantidadeDePalavras;
        busca = busca->proximo;
    }
    busca->anterior->proximo = busca->proximo;
    busca->proximo->anterior = busca->anterior;
    free(busca);
    return true;
}
