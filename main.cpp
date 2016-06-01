#include <getopt.h>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "base.h"
#include "tabelaDispersao.h"


using namespace std;

int main(int argc, char * argv[])
{
	//TabelaDispersao tabela = new tpDispersao;	
	//tabela = preProcessamento(tabela,"arquivo.txt");
	//tabela = preProcessamento(tabela,"arquivo2.txt");	
	//geraLog(tabela);
	//showTabela(tabela);
	//*	
    bool inserirFlag = false;
    bool removerFlag = false;
    bool liFlag = false;
    bool laFlag = false;
    bool ltFlag = false;
    bool bANDFlag = false;
    bool bORFlag = false;
    bool pAFlag = false;
    bool pCFlag = false;
    bool pIFlag = true;
    bool tTFlag = false;
    bool tFFlag = true;

    const struct option opcoes[] = {
        {"i", required_argument, (int*)&inserirFlag, true},
        {"r", required_argument, (int*)&removerFlag, true},
        {"li", no_argument, (int*)&liFlag, true},
        {"la", no_argument, (int*)&laFlag, true},
        {"lt", no_argument, (int*)&ltFlag, true},
        {"bAND", required_argument, (int*)&bANDFlag, true},
        {"bOR", required_argument, (int*)&bORFlag, true},
        {"pA", required_argument, (int*)&pAFlag, true},
        {"pC", required_argument, (int*)&pCFlag, true},
        {"pI", required_argument, (int*)&pIFlag, true},
        {"tT", no_argument, (int*)&tTFlag, true},
        {"tF", no_argument, (int*)&tFFlag, true},
        {NULL, 0, 0, 0}
    };

    int index = 0;

    Lista lista = carregarBase("base.txt");
    while (getopt_long_only(argc, argv, "", opcoes, &index) != -1)
    {
        if (liFlag || laFlag || ltFlag)
        {
            if (liFlag)
            {

            }
            else if (laFlag)
            {

            }
            else
            {

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
            while (getline(ss, item, ',')) {
                arquivos[index] = item;
                index++;
            }

            inserir(lista, arquivos, index);
        }
        else if (removerFlag)
        {

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
