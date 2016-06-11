#ifndef TabelaDispersao_h
#define TabelaDispersao_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

#include "lista.h"
#include "base.h"

#define REMOVIDO "??????"
#define TAMANHO_INICIAL 800

struct tpExiste
{
	std::string* arquivos;
	std::string* linhas;
};
typedef tpExiste* ondeExiste;

struct tpDispersao
{
	int qtdArquivos;
	int qtdPalavras;	
	int tamanho;
	ondeExiste *item;
	std::string *chave;
	
};
typedef tpDispersao* TabelaDispersao;

int preHash(std::string);
int Hash(int,int);
void showTabela(TabelaDispersao);
ondeExiste criarOndeExiste();
TabelaDispersao criarTabela(int);
TabelaDispersao preProcessamento(TabelaDispersao, std::string, Lista);
TabelaDispersao inserirNaTabela(TabelaDispersao,std::string,std::string,std::string);
TabelaDispersao redimensionarTabela(TabelaDispersao,int);
TabelaDispersao reduzirTabela(TabelaDispersao);
TabelaDispersao expandirTabela(TabelaDispersao);
void geraLog(TabelaDispersao);
TabelaDispersao carregarLog(const char*);
bool removerDaTabela(TabelaDispersao, std::string, Lista);
bool verificaArquivo(TabelaDispersao, std::string);
void limparTabela(TabelaDispersao tabela);
TabelaDispersao clonarTabela(TabelaDispersao tabela);

#endif //TabelaDispersao_h