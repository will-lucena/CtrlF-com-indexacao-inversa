#ifndef TABELADISPERSAO_H_INCLUDED
#define TABELADISPERSAO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

#include "lista.h"
#include "base.h"

struct Tpexiste
{
	std::string* arquivos;
	std::string* linhas;
};
typedef Tpexiste* ondeExiste;

struct tpDispersao
{
	int qtdArquivos;
	int qtdPalavras;	
	int tamanhoTabela;
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
bool inserirTabela(TabelaDispersao,std::string,std::string,std::string);
TabelaDispersao RedimensionarTabela(TabelaDispersao,int);
TabelaDispersao ReduzirTabela(TabelaDispersao);
TabelaDispersao ExpandirTabela(TabelaDispersao);
void geraLog(TabelaDispersao);
TabelaDispersao carregarLog();


#endif //TABELADISPERSAO_H_INCLUDED