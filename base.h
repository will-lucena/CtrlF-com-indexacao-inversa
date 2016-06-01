#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include <string>

#include "lista.h"

void show(Lista);

Lista carregarBase(const char*);

Lista clonarLista(Lista);

void inserir(Lista, std::string*, int);

void listarInsercao(char*);

#endif // BASE_H_INCLUDED
