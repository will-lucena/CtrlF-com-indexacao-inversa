#ifndef TABELADISPERSAO_H_INCLUDED
#define TABELADISPERSAO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

struct Tpexiste
{
	std::string* arquivos;
	std::string* linhas;
};
typedef Tpexiste* ondeExiste;

struct tpDispersao
{
	int qtdArquivos;	
	int tamanhoTabela;
	ondeExiste *item;
	std::string *chave;
	
};
typedef tpDispersao* TabelaDispersao;

int preHash(string);
int Hash(int,int);
void showTabela(TabelaDispersao);
ondeExiste criarOndeExiste();
TabelaDispersao criarTabela(int);
TabelaDispersao preProcessamento(TabelaDispersao, std::string);
bool inserirTabela(TabelaDispersao,std::string,std::string,std::string);
bool geraLog(TabelaDispersao);


#endif //TABELADISPERSAO_H_INCLUDED