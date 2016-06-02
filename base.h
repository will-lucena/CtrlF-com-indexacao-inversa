#ifndef BASE_H
#define BASE_H

#include <string>

#include "lista.h"

void show(Lista);

Lista carregarBase(const char*);

Lista clonarLista(Lista);

void inserir(Lista, std::string*, int);

void remover(Lista, std::string*, int);

void listarInsercao(const char*);

void listarTamanho(const char*);

void listarAlfabetica(const char*);

void percorrerLinha(std::string, Arquivo);

void selectionSortInt(Lista);

void selectionSortString(Lista);

#endif // BASE_H
