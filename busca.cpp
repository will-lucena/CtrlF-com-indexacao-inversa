#include <algorithm>

#include "busca.h"
#include "lista.h"

ondeExiste encontrarPalavras(TabelaDispersao tabela, string palavra)
{
	ondeExiste infos = new Tpexiste;
	int hash = Hash(preHash(palavra), tabela->tamanhoTabela);
	while (tabela->chave[hash] != "")
	{
		if (tabela->chave[hash].find(palavra) != -1)
		{
			infos->arquivos = tabela->item[hash]->arquivos;
			infos->linhas = tabela->item[hash]->linhas;
			return infos;
		}
		else
		{
			hash = (hash+1) % tabela->tamanhoTabela;
		}
	}
	return NULL;
}

void mostrarLinha(ondeExiste palavra, int* linhas, int quantasLinhas, int arquivo)
{
	
	for (int i = 0; i < quantasLinhas; i++)
	{
		std::ifstream texto;
    	texto.open(palavra->arquivos[arquivo]);
    	if (texto.is_open())
    	{
			int linhaAtual = 0;
			std::string linha;
			while (linhaAtual < linhas[i])
			{
				getline(texto, linha);
				linhaAtual++;
			}
			cout << linha << endl;
		}
		texto.close();		
	}
}

void bAND(TabelaDispersao tabela, string* palavras, int quantidadeDePalavras)
{
	//implementar com mais de uma palavra
	//*
	int* linhasASeremExibidas;
	int cont = 0;
	for (int i = 0; i < quantidadeDePalavras; i++)
	{
		ondeExiste palavra = encontrarPalavras(tabela, palavras[i]);
		if (palavra != NULL)
		{
			for (int j = 0; j < tabela->qtdArquivos; j++)
			{
				int numeroDeVirgulas = count(palavra->linhas[j].begin(), palavra->linhas[j].end(), ',');
				linhasASeremExibidas = new int[numeroDeVirgulas-1];
				int index = 0;
				string numero = "";
				int contEncerrar = 0;
				while (cont < numeroDeVirgulas) 
				{
                	if (isdigit(palavra->linhas[j][index]))
                	{
                		if (palavra->linhas[j][index+1] != ',')
                		{
                			numero = numero + palavra->linhas[j][index];
                			contEncerrar++;
                			if (contEncerrar > 5)
                			{
                				break;
                			}
                		}
                		else
                		{
                			numero = numero + palavra->linhas[j][index];
	                		linhasASeremExibidas[cont] = stoi(numero);
	                		cont++;
	                		contEncerrar = 0;
	                		numero = "";
                		}
                	}
                	index++;
           		}
           		mostrarLinha(palavra, linhasASeremExibidas, cont, j);
			}
		}
	}
	for (int i = 0; i < cont; i++)
	{
		cout << linhasASeremExibidas[i] << endl;
	}
	/**/
	/*
	ondeExiste palavra = encontrarPalavras(tabela, palavras[0]);
	if (palavra != NULL)
	{
		int i = 0;
		while (i < tabela->qtdArquivos)
		{
			if (palavra->arquivos[i] == "")
			{
				break;
			}
			cout << palavra->arquivos[i] << '\t';
			cout << palavra->linhas[i] << endl;
			mostrarLinha(base, palavra, tabela);
			i++;
		}
	}
	else
	{
		cout << "Palavra nao encontrada" << endl;
	}
	/**/
}
