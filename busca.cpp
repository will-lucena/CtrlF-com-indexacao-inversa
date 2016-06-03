#include "busca.h"

ondeExiste encontrarPalavras(TabelaDispersao tabela, string* palavras, int quantidadeDePalavras)
{
	ondeExiste listaDePalavras = new Tpexiste;
	int palavrasValidas = 0;
	for (int i = 0; i < quantidadeDePalavras; i++)
	{
		int hash = Hash(preHash(palavras[i]), tabela->tamanhoTabela);
		if (tabela->chave[hash] == palavras[i])
		{
			listaDePalavras->arquivos = tabela->item[hash]->arquivos;
			listaDePalavras->linhas = tabela->item[hash]->linhas;
			palavrasValidas++;
			break;
		}
		else
		{
			while (tabela->chave[hash] != "")
			{
				
				if (tabela->chave[hash].find(palavras[i]) != -1)
				{
					listaDePalavras->arquivos = tabela->item[hash]->arquivos;
					listaDePalavras->linhas = tabela->item[hash]->linhas;
					palavrasValidas++;
					break;
				}
				else
				{
					hash = (hash+1) % tabela->tamanhoTabela;
				}
			}
		}
	}
	return listaDePalavras;
}

void bAND(TabelaDispersao tabela, string* palavras, int quantidadeDePalavras)
{
	ondeExiste listaDePalavras = encontrarPalavras(tabela, palavras, quantidadeDePalavras);
	int i = 0;
	while (i < tabela->qtdArquivos)
	{
		cout << listaDePalavras->arquivos[i] << '\t';
		cout << listaDePalavras->linhas[i] << endl;
		i++;
	}
}


