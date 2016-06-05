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

void mostrarLinha(Lista lista, ondeExiste palavra, TabelaDispersao tabela)
{
	for (No p = lista->cabeca->proximo; p != lista->cauda; p = p->proximo)
	{
		for (int i = 0; i < tabela->qtdArquivos; i++)
		{
			if (p->conteudo->caminho == palavra->arquivos[i])
			{
				std::ifstream texto;
    			texto.open(palavra->arquivos[i]);
				int linhaAtual = 0;
				std::string linha;
				if (texto.is_open())
			    {
			    	//implementar com vetor de inteiros que indica as linhas
			        while (linhaAtual < 2)
			        {
			            getline(texto, linha);
			            linhaAtual++;
			        }
			        cout << linha << endl;
			    	texto.close();
			    }
			}
		}
		
	}
}

void bAND(TabelaDispersao tabela, string* palavras, int quantidadeDePalavras, Lista base)
{
	//implementar com mais de uma palavra
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
}
