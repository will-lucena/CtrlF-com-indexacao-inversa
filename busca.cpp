#include "busca.h"

ondeExiste encontrarPalavras(TabelaDispersao tabela, string* palavras, int quantidadeDePalavras)
{
	ondeExiste listaDePalavras = new Tpexiste;
	int palavrasValidas = 0;
	for (int i = 0; i < quantidadeDePalavras; i++)
	{
		int hash = Hash(preHash(palavras[i]), tabela->tamanhoTabela);

		while(tabela->chave[hash] != "")
		{
			if (tabela->chave[hash] == palavras[i])
			{
				listaDePalavras = tabela->item[hash];
				palavrasValidas++;
				break;
			}
			else
			{
				hash++;
			}
		}
	}
	return listaDePalavras;
}

void bAND(TabelaDispersao tabela, string* palavras, int quantidadeDePalavras)
{
	ondeExiste listaDePalavras = encontrarPalavras(tabela, palavras, quantidadeDePalavras);
	cout << listaDePalavras->arquivos << '\t' <<  listaDePalavras->linhas << endl;
}


