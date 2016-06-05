#ifndef busca_h
#define busca_h

#include <iostream>
#include <fstream>

#include "tabelaDispersao.h"

using namespace std;

void bAND(TabelaDispersao, string*, int, Lista);

void mostrarLinha(Lista, ondeExiste, TabelaDispersao);

void lerTexto(Arquivo, std::string, int);

#endif