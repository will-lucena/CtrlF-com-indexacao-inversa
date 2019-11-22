#ifndef TabelaDispersao_h
#define TabelaDispersao_h

#include <fstream>

#include "structs.h"
#include "lista.h"

#define REMOVIDO "??????"
#define TAMANHO_INICIAL 800

int preHash(std::string);

int Hash(int,int);

void showTabela(TabelaDispersao);

ondeExiste criarOndeExiste();

TabelaDispersao criarTabela(int);

TabelaDispersao preProcessamento(TabelaDispersao, std::string, Lista);

TabelaDispersao inserirNaTabela(TabelaDispersao, std::string, std::string, std::string);

TabelaDispersao redimensionarTabela(TabelaDispersao, int);

TabelaDispersao reduzirTabela(TabelaDispersao);

TabelaDispersao expandirTabela(TabelaDispersao);

void geraLog(TabelaDispersao);

TabelaDispersao carregarLog(const char*);

TabelaDispersao removerDaTabela(TabelaDispersao, std::string, Lista);

bool verificaArquivo(TabelaDispersao, std::string);

void limparTabela(TabelaDispersao tabela);

TabelaDispersao clonarTabela(TabelaDispersao tabela);

#endif 