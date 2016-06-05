#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>

#include "base.h"
#include "tabelaDispersao.h"
#include "busca.h"


using namespace std;
using namespace std::chrono;

int main(int argc, char * argv[])
{
    string terminal[argc-1];
    int j = 1;
    long double duracao;


    for(int i = 0; i < argc-1; i++)
    {
        terminal[i] = argv[j];
        j++;
    }

    for(int i = 0; i < argc-1; i++)
    {
        cout << terminal[i] << endl;
    }    

    Lista lista = carregarBase("base.txt");
    TabelaDispersao tabela = carregarLog();
    if (terminal[0] == "-i")
    {
        int argumento = 1;
        while(argumento < argc-1)
        { 
            tabela = preProcessamento(tabela,terminal[argumento], lista);
            geraLog(tabela);
            //showTabela(tabela);
            argumento++;
        }
    }
    /* Ainda nao implementada a remocao da tabela de dispersao
    else if (terminal[0] == "-r")
    {
        TabelaDispersao tabela = new tpDispersao;
        tabela = carregarLog();
        int argumento = 1;
        while(argumento < argc-1)
        { 
            tabela = preProcessamento(tabela,terminal[argumento], lista);
            geraLog(tabela);
            showTabela(tabela);
            argumento++;
        }
    }
    */
    else if (terminal[0] == "li")
    {
        listarInsercao("base.txt");
    }

    else if (terminal[0] == "la")
    {
        listarAlfabetica("base.txt");
    }

    else if (terminal[0] == "lt")
    {
        listarTamanho("base.txt");
    }

    else if (terminal[0] == "-bAND")
    {
        if (terminal[1] != "pC" && terminal[1] != "pA")
        {
            if (terminal[2] == "tT")
            {
                high_resolution_clock::time_point t1 = high_resolution_clock::now();
                //listar por ordem de inserção dos arquivos com tempo de busca
                high_resolution_clock::time_point t2 = high_resolution_clock::now();

                duracao = duration<long double, std::micro>(t2 - t1).count();
            }
            else
            {
                //listar por ordem de inserção dos arquivos sem tempo de busca
                int argumento = 1, palavra = 0;
                string palavras[argc-2];
                while (argumento < argc-1)
                {
                    palavras[palavra] = terminal[argumento];
                    palavra++;
                    argumento++;
                }
                bAND(tabela, palavras, palavra);
            }
        }
        else if (terminal[1] == "pC")
        {
            if (terminal[2] != "tT")
            {
                high_resolution_clock::time_point t1 = high_resolution_clock::now();
                //listar por ordem decrescente de vezes que aconteceram nos arquivos com tempo de busca
                high_resolution_clock::time_point t2 = high_resolution_clock::now();

                duracao = duration<long double, std::micro>(t2 - t1).count();
            }
            else
            {
                //listar por ordem decrescente de vezes que aconteceram nos arquivos com tempo de busca
            }
        }
        else if (terminal[1] == "pA")
        {
            if (terminal[2] != "tT")
            {
                high_resolution_clock::time_point t1 = high_resolution_clock::now();
                //listar por ordem alfabetica do nome do arquivo com tempo de busca
                high_resolution_clock::time_point t2 = high_resolution_clock::now();

                duracao = duration<long double, std::micro>(t2 - t1).count();
            }
            else
            {
                //listar por ordem alfabetica do nome do arquivo com tempo de busca
            }
        }
    }

    return 0;
}
