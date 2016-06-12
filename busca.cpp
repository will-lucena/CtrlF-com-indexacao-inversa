#include "libs/busca.h"
#include "libs/funcoesBasicas.h"

/**
 * Funcao para buscar uma linha do arquivo
 * @param nomeArquivo -> string que informa o caminho do arquivo a ser lido
 * @param linha -> int que informa a linha a ser buscada
 * @return conteudoLinha -> A linha do arquivo correspondente ao inteiro passado como paramentro
 */
std::string pegarLinha(std::string nomeArquivo, int linha)
{	
	int linhaAtual = 0;
	std::string conteudoLinha = "";
	std::ifstream buffer(nomeArquivo);

    if (buffer.is_open())
    {
    	while(linhaAtual < linha)
    	{
    		getline(buffer, conteudoLinha);
    		linhaAtual++;
    	}
    	return conteudoLinha;
    	buffer.close();
    }
}

/**
 * Funcao para contar quantas palavras existem na linha
 * @param linha -> string correspondente a uma linha do arquivo
 * @return qtdPalavras -> a quantidade de palavras que existem naquela linha, que o mesmo da quantidade de espacos + 1
 */

int contarPalavrasNaLinha(std::string linha)
{
	int qtdPalavras = 0;

	for(int index = 0; index < linha.length(); index++)
	{
		if(linha[index] == ' ')
		{
			qtdPalavras++;
		}
	}
	return qtdPalavras;
}

/**
 * Funcao para mostrar as linhas resultantes da busca no terminal
 * @param *infos -> ponteiro (vetor) de ondeExiste (struct) que contem quais linhas e quais arquivos serao exibidos
 * @param qtdPalavras -> inteiro que informa quantas palavras foram passadas pelo terminal para busca
 * @return void
 */

void showLinha(ondeExiste* infos, int qtdPalavras)
{	
	std::string arquivo = "";
	std::string linha;
	int index = 0;	

	while(index < qtdPalavras)
	{
		if(qtdPalavras < 0)
		{
			break;
		}
		for(int indexArquivo = 0; indexArquivo < 50; indexArquivo++)
		{
			if(infos[index]->arquivos[indexArquivo] != "" && infos[index]->arquivos[indexArquivo] != REMOVIDO)
			{
				std::cout << ">> Foram encontradas " << contarPalavrasNaLinha(infos[index]->linhas[indexArquivo])
					<< " linhas no arquivo \"" << infos[index]->arquivos[indexArquivo] << "\":" << std::endl;

				for(int indexLinha = 0; indexLinha < infos[index]->linhas[indexArquivo].length(); indexLinha++)
				{
					if(infos[index]->linhas[indexArquivo][indexLinha] != ' ')
					{
						linha+=infos[index]->linhas[indexArquivo][indexLinha];
					}
					else
					{													
						std::cout << "   - linha " << linha << ": \"" << 
							pegarLinha(infos[index]->arquivos[indexArquivo], stoi(linha)) << "\"" << std::endl;
						linha = "";
					}
				}
				linha = "";
			}
		}
		index++;	   				
	}
}

/**
 * @override para função bAND
 */
void showLinha(ondeExiste *infos, int qtdInfos, int qtdArquivos)
{		
	if(qtdInfos != 1)
	{
		ondeExiste *novaInfos = new ondeExiste[qtdInfos - 1];
		for(int index = 0; index < qtdInfos - 1; index++)
		{
			novaInfos[index] = criarOndeExiste();
		}

		int arquivoExiste, posicaoArquivo;	
		int *linhas;
		int novaposicaoInf = 0;	
		
		for(int index = 0; index < qtdInfos - 1; index++)
		{
			posicaoArquivo = 0;

			for(int indexArquivo = 0; indexArquivo < qtdArquivos; indexArquivo++)
			{
				arquivoExiste = verificarArquivo(infos[index]->arquivos[indexArquivo], infos[index + 1]->arquivos, qtdArquivos);			
				
				if(arquivoExiste >= 0)
				{																						
					linhas = verificarArquivo(infos[index]->linhas[indexArquivo], infos[index + 1]->linhas[arquivoExiste], linhas);				
					
					for(int indexLinha = 0; indexLinha < sizeof(linhas) / 4; indexLinha++)
					{
						if(linhas[indexLinha] > 0)
						{							
							novaInfos[novaposicaoInf]->linhas[posicaoArquivo] += std::to_string(linhas[indexLinha]) + " ";
						}
					}	
					novaInfos[novaposicaoInf]->arquivos[posicaoArquivo] = infos[index]->arquivos[indexArquivo];		
					posicaoArquivo++;
				}
			}									
			novaposicaoInf++;
		}			
		if(novaposicaoInf >= 1)
		{				
			showLinha(novaInfos,novaposicaoInf,posicaoArquivo);	
		}
		else
		{
			showLinha(infos,qtdInfos);
		}
	}
	else
	{		
		showLinha(infos,qtdInfos);
	}	
}

/**
 * Funcao para encontrar os arquivos na tabela hash e armazenas suas informações em um ponteiro (vetor) de ondeExiste (struct)
 * @param tabela -> tabela hash usada para indexação que contem as palavras dos arquivos
 * @param palavra -> ponteiro (vetor) de strings com as palavras a serem buscadas na tabela hash
 * @param qtdPalavras -> inteiro que informa quantas palavras foram pssadas pelo terminal para a busca
 * @return infos -> ponteiro (vetor) de ondeExiste (struct) contendo todas as informações necessarias para se exibir as palavras buscadas
 */

ondeExiste* carregarPalavras(TabelaDispersao tabela, std::string* palavra, int qtdPalavras)
{	
	ondeExiste* infos = new ondeExiste[qtdPalavras];	
	int hash;
	for(int index = 0; index < qtdPalavras; index++)
	{
		infos[index] = criarOndeExiste();
		hash = Hash(preHash(palavra[index]), tabela->tamanho);

		for(int indexAux = 0; indexAux < tabela->qtdArquivos; indexAux++)
		{
			if(tabela->chave[hash] == "")
			{
				break;
			}
			else if (tabela->chave[hash].find(palavra[index]) != -1)
			{
				infos[index]->arquivos = tabela->item[hash]->arquivos;
				infos[index]->linhas = tabela->item[hash]->linhas;				
			}
			else
			{
				hash = (hash+1) % tabela->tamanho;
			}
		}		
	}
	return infos;	
}

/**
 * Funcao da entrada -bOR que recebe n palavras e mostra no terminal todas as ocorrencias dessas palavras na tabela hash
 * @param palavra -> ponteiro (vetor) de strings que contem as palavras buscadas
 * @param qtdPalavras -> inteiro que informa quantas palavras serão buscadas
 * @param tabela -> tabela hash usada para indexacao que contem as palavras dos arquivos
 * @return void
 */

void bOR(std::string* palavra, int qtdPalavras, TabelaDispersao tabela)
{
	showLinha(carregarPalavras(tabela, palavra, qtdPalavras), qtdPalavras);
}

/**
 * Funcao da entrada -bAND que recebe n palavras e mostra no terminal as ocorrencias em comum (mesma linha do mesmo arquivo) da tabela hash
 * @param palavra -> ponteiro (vetor) de strings que contem as palavras buscadas
 * @param qtdPalavras -> inteiro que informa quantas palavras serão buscadas
 * @param tabela -> tabela hash usada para indexacao que contem as palavras dos arquivos
 * @return void
 */
void bAND(std::string* palavra, int qtdPalavras, TabelaDispersao tabela)
{	
	ondeExiste *infos = new ondeExiste[qtdPalavras];

	infos = carregarPalavras(tabela, palavra, qtdPalavras);

	showLinha(infos, qtdPalavras, tabela->qtdArquivos);
}

//verifica os arquivos e retornam a posição dos arquivos que correspondem
int verificarArquivo(std::string arquivo, std::string* ListaArquivo, int qtdArquivos)
{
	if(arquivo == "")
	{
		return -1;
	}
	for(int index = 0; index < qtdArquivos; index++)
	{		
		if(ListaArquivo[index] != "")
		{		
			if(ListaArquivo[index].find(arquivo) != -1)
			{
				return index;
			}
		}
	}
	return -1;
}


//Verifica a linha
int* verificarArquivo(std::string linhaArquivo1, std::string linhaArquivo2, int* linhasEquivalentes)
{	
	if(linhaArquivo1 == "" || linhaArquivo2 == "")
	{
		return NULL;
	}

	std::string menor, maior;
	
	std::string conversao = "";
	int qtdLinhas = 0;

	if(linhaArquivo1.length() < linhaArquivo2.length())
	{
		menor = linhaArquivo1;
		maior = linhaArquivo2;
	}
	else
	{
		menor = linhaArquivo2;
		maior = linhaArquivo1;
	}

	int linhas[contarPalavrasNaLinha(menor)];	
	
	for(int index = 0; index < menor.length(); index++)
	{
		if(menor[index]!=' ')
		{
			conversao = conversao + menor[index];			
		}
		else
		{					
			linhas[qtdLinhas] = stoi(conversao);			
			qtdLinhas++;
			conversao = "";
		}
	}		
	
	linhasEquivalentes = new int[qtdLinhas];
	
	for(int index = 0; index < qtdLinhas + 1; index++)
	{
		linhasEquivalentes[index] = -1;
	}	
	
	qtdLinhas = 0;		
	
	for(int index = 0; index < contarPalavrasNaLinha(menor); index++)
	{					
		if( (long) maior.find(std::to_string(linhas[index])) != -1)
		{			
			linhasEquivalentes[qtdLinhas] = linhas[index];			
			qtdLinhas++;
		}
	}
	return linhasEquivalentes;
}