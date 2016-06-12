#ifndef Busca_h
#define Busca_h

#include <fstream>

#include "structs.h"
#include "lista.h"

#define REMOVIDO "??????"

void bOR(std::string*, int, TabelaDispersao);

void bAND(std::string*, int, TabelaDispersao);

ondeExiste* quantidadeDeEspacos(TabelaDispersao, std::string*, int);

int* verificarArquivo(std::string, std::string, int*);

int verificarArquivo(std::string, std::string*, int);

void showLinha(ondeExiste*, int, TabelaDispersao);

void showLinha(ondeExiste*, int, int);

std::string linhaArquivo(std::string, int);

#endif