#ifndef Lista_h
#define Lista_h

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

void inserirNaLista(Lista, Arquivo);

bool removerDaLista(Lista, Arquivo);

Arquivo criarArquivo();
#endif // Lista_h
