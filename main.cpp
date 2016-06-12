#include <algorithm>
#include <chrono>

#include "libs/base.h"
#include "libs/tabelaDispersao.h"
#include "libs/busca.h"

using namespace std::chrono;

int main(int argc, char * argv[])
{
    std::string terminal[argc-1];
    int j = 1;
    long double duracao;


    for(int i = 0; i < argc-1; i++)
    {
        terminal[i] = argv[j];
        j++;
    } 
    
    Lista lista = carregarBase("arquivos_gerados/base.txt");
    TabelaDispersao tabela = carregarLog("arquivos_gerados/Log.txt");
    
    if (terminal[0] == "-i")
    {
        int argumento = 1;
        while(argumento < argc-1)
        { 
            tabela = preProcessamento(tabela,terminal[argumento], lista);
            argumento++;
        }
        geraLog(tabela);
    }
    else if (terminal[0] == "-r")
    {
        int argumento = 1;
        while(argumento < argc-1)
        { 
            tabela = removerDaTabela(tabela,terminal[argumento], lista);
            argumento++;
        }
        geraLog(tabela);
    }
    else if (terminal[0] == "-li")
    {
        listarInsercao(lista);
    }

    else if (terminal[0] == "-la")
    {
        listarAlfabetica(lista);
    }

    else if (terminal[0] == "-lt")
    {
        listarTamanho(lista);
    }
    else if (terminal[0] == "-bAND")
    {
        if (terminal[1] == "-pI")
        {
            if (terminal[2] == "-tT")
            {
                int argumento = 3, palavra = 0;
                std::string palavras[argc-3];
                while (argumento < argc-1)
                {
                    palavras[palavra] = terminal[argumento];
                    palavra++;
                    argumento++;
                }

                high_resolution_clock::time_point t1 = high_resolution_clock::now();
                bAND(palavras, palavra, tabela);
                high_resolution_clock::time_point t2 = high_resolution_clock::now();

                duracao = duration<long double, std::micro>(t2 - t1).count();
                std::cout << duracao << std::endl;
            }
            else
            {
                int argumento = 2, palavra = 0;
                std::string palavras[argc-2];
                while (argumento < argc-1)
                {
                    palavras[palavra] = terminal[argumento];
                    palavra++;
                    argumento++;
                }
                bAND(palavras, palavra, tabela);
            }
                
        }
        else if (terminal[1] != "-pA" && terminal[1] != "-pC")
        {
            if (terminal[1] == "-tT")
            {
                int argumento = 2, palavra = 0;
                std::string palavras[argc-2];
                while (argumento < argc-1)
                {
                    palavras[palavra] = terminal[argumento];
                    palavra++;
                    argumento++;
                }

                high_resolution_clock::time_point t1 = high_resolution_clock::now();
                bAND(palavras, palavra, tabela);
                high_resolution_clock::time_point t2 = high_resolution_clock::now();

                duracao = duration<long double, std::micro>(t2 - t1).count();
                std::cout << duracao << std::endl;
            }
            else
            {
               int argumento = 1, palavra = 0;
                std::string palavras[argc-2];
                while (argumento < argc-1)
                {
                    palavras[palavra] = terminal[argumento];
                    palavra++;
                    argumento++;
                }
                bAND(palavras, palavra, tabela);
            }
        }
        else
        {
            std::cout << "Metodo de listagem " << terminal[1] << " nao foi implementado" << std::endl;
        }
    }

    else if (terminal[0] == "-bOR")
    {
        if (terminal[1] == "-pI")
        {
            if (terminal[2] == "-tT")
            {
                int argumento = 3, palavra = 0;
                std::string palavras[argc-3];
                while (argumento < argc-1)
                {
                    palavras[palavra] = terminal[argumento];
                    palavra++;
                    argumento++;
                }

                high_resolution_clock::time_point t1 = high_resolution_clock::now();
                bOR(palavras, palavra, tabela);
                high_resolution_clock::time_point t2 = high_resolution_clock::now();

                duracao = duration<long double, std::micro>(t2 - t1).count();
                std::cout << duracao << std::endl;
            }
            else
            {
                int argumento = 2, palavra = 0;
                std::string palavras[argc-2];
                while (argumento < argc-1)
                {
                    palavras[palavra] = terminal[argumento];
                    palavra++;
                    argumento++;
                }
                bOR(palavras, palavra, tabela);
            }
                
        }
        else if (terminal[1] != "-pA" && terminal[1] != "-pC")
        {
            if (terminal[1] == "-tT")
            {
                int argumento = 2, palavra = 0;
                std::string palavras[argc-2];
                while (argumento < argc-1)
                {
                    palavras[palavra] = terminal[argumento];
                    palavra++;
                    argumento++;
                }

                high_resolution_clock::time_point t1 = high_resolution_clock::now();
                bOR(palavras, palavra, tabela);
                high_resolution_clock::time_point t2 = high_resolution_clock::now();

                duracao = duration<long double, std::micro>(t2 - t1).count();
                std::cout << duracao << std::endl;
            }
            else
            {
                int argumento = 1, palavra = 0;
                std::string palavras[argc-2];
                while (argumento < argc-1)
                {
                    palavras[palavra] = terminal[argumento];
                    palavra++;
                    argumento++;
                }
                bOR(palavras, palavra, tabela);
            }
        }
        else
        {
            std::cout << "Metodo de listagem " << terminal[1] << " nao foi implementado" << std::endl;
        }
    }

    return 0;
}
