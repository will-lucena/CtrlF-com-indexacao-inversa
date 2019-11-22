#ifndef Base_h
#define Base_h

#include "structs.h"
#include "lista.h"

Lista carregarBase(const char*);

void inserirNaBase(Lista, Arquivo);

void removerDaBase(Lista, Arquivo);

void removerDaBase(Lista, std::string);

void listarInsercao(Lista);

void listarTamanho(Lista);

void listarAlfabetica(Lista);

void percorrerLinha(std::string, Arquivo);

void selectionSortDecrescente(Lista);

void selectionSortCrescente(Lista);

std::string toLowerCase(std::string);

#endif
