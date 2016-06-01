#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>

struct tpArquivo
{
	std::string caminho;
	int quantidadeDePalavras;
};
typedef tpArquivo* Arquivo;

struct tpNo
{
    Arquivo conteudo;
	struct tpNo* proximo;
	struct tpNo* anterior;
};
typedef tpNo* No;

struct tpLista
{
	No cabeca;
	No cauda;
	int tamanho;
};
typedef tpLista* Lista;

Lista criarLista();

No criarNo(Arquivo);

bool vazia(Lista);

bool inserirNaLista(Lista, Arquivo);

bool removerDaLista(Lista, Arquivo);

Arquivo criarArquivo();

#endif // LISTA_H_INCLUDED
