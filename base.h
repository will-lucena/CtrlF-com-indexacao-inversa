#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

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

Lista selectionSortInt(Lista);

Lista selectionSortString(Lista);

#endif // BASE_H_INCLUDED
