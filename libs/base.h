#ifndef Base_h
#define Base_h

#include <string>

#include "lista.h"

Lista carregarBase(const char*);

void inserirNaBase(Lista, Arquivo);

void removerDaBase(Lista, Arquivo);

void listarInsercao(Lista);

void listarTamanho(Lista);

void listarAlfabetica(Lista);

void percorrerLinha(std::string, Arquivo);

void selectionSortDecrescente(Lista);

void selectionSortCrescente(Lista);

#endif //Base_h
