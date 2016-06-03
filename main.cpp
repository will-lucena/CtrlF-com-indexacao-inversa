#include <getopt.h>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "base.h"
#include "tabelaDispersao.h"


using namespace std;

int main(int argc, char * argv[])
{
    string terminal[argc-1];
    int j = 1;
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
    if (terminal[0] == "-i")
    {
        cout << "passou" << endl;
        TabelaDispersao tabela = new tpDispersao;
        int argumento = 1;
        while(argumento < argc-1)
        {
            cout << "passou1" << endl; 
            tabela = preProcessamento(tabela,terminal[argumento], lista);
            cout << "passou" << endl;
            geraLog(tabela);
            cout << "passou" << endl;
            showTabela(tabela);
            cout << "passou" << endl;
            argumento++;
        }
    }




    /*
    Lista lista = carregarBase("base.txt");
    while (getopt_long_only(argc, argv, "", opcoes, &index) != -1)
    {
        if (liFlag || laFlag || ltFlag)
        {
            if (liFlag)
            {
                listarInsercao("base.txt");
            }
            else if (laFlag)
            {
                listarAlfabetica("base.txt");
            }
            else
            {
                listarTamanho("base.txt");
            }
        }
        else if (inserirFlag)
        {
            string arg = string(optarg);
            stringstream ss(arg);
            string item;
            int numeroDeVirgulas = std::count(arg.begin(), arg.end(), ',');
            string arquivos[numeroDeVirgulas + 1];

            int index = 0;
            while (getline(ss, item, ',')) 
            {
                arquivos[index] = item;
                index++;
            }

            inserir(lista, arquivos, index);
            exit(1);
        }
        else if (removerFlag)
        {
            string arg = string(optarg);
            stringstream ss(arg);
            string item;
            int numeroDeVirgulas = std::count(arg.begin(), arg.end(), ',');
            string arquivos[numeroDeVirgulas + 1];

            int index = 0;
            while (getline(ss, item, ','))
            {
                arquivos[index] = item;
                index++;
            }

            remover(lista, arquivos, index);
            exit(1);
        }
        else if (bANDFlag)
        {
            if (pAFlag)
            {
                if (tTFlag)
                {
                    
                }
                else
                {
                    
                }
            }
            else if (pCFlag)
            {
                if (tTFlag)
                {
                    
                }
                else
                {

                }
            }
            else
            {
                if (tTFlag)
                {
                    
                }
                else
                {
                    
                }
            }
        }
        else if (bORFlag)
        {
            if (pAFlag)
            {
                if (tTFlag)
                {
                    
                }
                else
                {
                    
                }
            }
            else if (pCFlag)
            {
                if (tTFlag)
                {
                    
                }
                else
                {
                    
                }
            }
            else
            {
                if (tTFlag)
                {
                    
                }
                else
                {
                    
                }
            }
        }
    }
    //*/
    return 0;
}
