#include "libs/lista.h"

/**
 * Funcao para instanciar uma lista e inicializar seus componentes basicos
 * @return lista -> retorna a lista criada
 */
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

/**
 * Funcao para instanciar um no com um conteudo passado como parametro e inicializar seus ponteiros
 * @param arquivo -> arquivo que será usado como conteudo do no
 * @return lista -> retorna a lista criada
 */
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

/**
 * Funcao para instanciar um arquivo e inicializar seus componentes basicos
 * @return arquivo -> retorna o arquivo criado
 */
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

/**
 * Funcao para inserir um arquivo na lista
 * @param lista -> lista onde será inserido o arquivo
 * @param arquivo -> arquivo a ser inserido na lista
 * @return true se o arquivo tiver sido inserido
 */
void inserirNaLista(Lista lista, Arquivo arquivo)
{
	No novo = criarNo(arquivo);

	novo->proximo = lista->cauda;
	novo->anterior = lista->cauda->anterior;

	lista->cauda->anterior->proximo = novo;
	lista->cauda->anterior = novo;
	lista->tamanho++;
}

/**
 * Funcao para remover um arquivo na lista
 * @param lista -> lista onde será removido o arquivo
 * @param arquivo -> arquivo a ser removido na lista
 * @return true se o arquivo tiver sido removido, false caso a lista seja vazia ou o arquivo nulo
 */
bool removerDaLista(Lista lista, Arquivo arquivo)
{
    if (lista->tamanho == 0 || arquivo == NULL)
    {
        return false;
    }

    No index = lista->cabeca->proximo;
    while(index->conteudo->caminho != arquivo->caminho && index != lista->cauda)
    {
        index = index->proximo;
    }
    
    index->anterior->proximo = index->proximo;
    index->proximo->anterior = index->anterior;
    free(index);
    return true;
}
