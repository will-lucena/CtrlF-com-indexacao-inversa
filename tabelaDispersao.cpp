#include "libs/tabelaDispersao.h"
#include "libs/funcoesBasicas.h"

/**
 * Funcao para criar uma instancia da struct ondeExiste
 * @return existe -> um ponteiro da struct tpExiste com valores default
 */
ondeExiste criarOndeExiste()
{
	ondeExiste existe = new tpExiste;

	if(existe == NULL)
	{
		return NULL;
	}

	existe->arquivos = new std::string[50];
	existe->linhas = new std::string[50];

	for(int index = 0; index < 50; index++)
	{
		existe->arquivos[index] = "";
		existe->linhas[index] = "";	
	}
	return existe;
}

/**
 * Funcao para criar uma instacia da struct TabelaDispersao
 * @param tamanho -> inteiro correspondente ao tamanho inicial da tabela
 * @return tabela -> um ponteiro da struct tpDispersao com valores default
 */
TabelaDispersao criarTabela(int tamanho)
{
	TabelaDispersao tabela = new tpDispersao;	
	if(tabela == NULL)
	{
		return NULL;
	}

	tabela->tamanho = tamanho;	
	tabela->qtdArquivos = 0;
	tabela->qtdPalavras = 0;
	tabela->chave = new std::string[tabela->tamanho];
	tabela->item = new ondeExiste[tabela->tamanho];

	for(int index = 0; index < tabela->tamanho; index++)
	{
		tabela->chave[index] = "";
		tabela->item[index] = criarOndeExiste();
	}
	
	return tabela;
}

/**
 * Funcao que expande a tabela de dispersao
 * @param tabela -> tabela atual que contem os itens/chaves que será redimensionada
 * @return chama a funcao de redimensionar com o novo tamanho como parametro
 */
TabelaDispersao expandirTabela(TabelaDispersao tabela)
{    		
    return redimensionarTabela(tabela, (tabela->tamanho * 3) + 1);    
}

/**
 * Funcao que reduz a tabela de dispersao
 * @param tabela -> tabela atual que contem os itens/chaves que será redimensionada
 * @return chama a funcao de redimensionar com o novo tamanho como parametro
 */
TabelaDispersao reduzirTabela(TabelaDispersao tabela)
{    
 	return redimensionarTabela(tabela, (int)(tabela->tamanho/ 3) + 1);    
}

/**
 * Funcao para redimensinoar a tabela, gera uma nova com o tamanho redimensionado e os itens/chaves realocados
 * @param tabela -> tabela atual que contem os itens/chaves e será redimensionada
 * @param tamanho -> inteiro correspondente ao novo tamanho da tabela
 * @return novaTabela -> tabela redimensionada com os itens realocados
 */

TabelaDispersao clonarTabela(TabelaDispersao tabela)
{
	TabelaDispersao novaTabela = new tpDispersao;
    novaTabela = criarTabela(tabela->tamanho);    

    for (int index = 0; index < tabela->tamanho; index++)
    {
    	if(tabela->chave[index] != "" && tabela->chave[index] != REMOVIDO)
    	{
    		for(int indexAux = 0; indexAux < 50; indexAux++)
    		{    			
    			if(tabela->item[index]->arquivos[indexAux] != "" && tabela->item[index]->arquivos[indexAux] != REMOVIDO)
    			{    				    						        	
		        	inserirNaTabela(novaTabela, tabela->item[index]->arquivos[indexAux], tabela->chave[index], tabela->item[index]->linhas[indexAux]);		        	
		        }
	        }
    	}
    }
    return novaTabela;
}

void limparTabela(TabelaDispersao tabela)
{
	for (int index = 0; index < tabela->tamanho; index++)
	{
		tabela->item[index] = criarOndeExiste();
		tabela->chave[index] =  "";
	}
	tabela->qtdArquivos = 0;
	tabela->qtdPalavras = 0;
}
/* //	VERSAO NOVA
TabelaDispersao redimensionarTabela(TabelaDispersao tabela, int tamanho)
{		
    TabelaDispersao clone = clonarTabela(tabela);
    limparTabela(tabela);
    tabela = criarTabela(tamanho); 

    for (int index = 0; index < clone->tamanho; index++)
    {
    	if(clone->chave[index] != "" && clone->chave[index] != REMOVIDO)
    	{
    		for(int indexAux = 0; indexAux < 50; indexAux++)
    		{    			
    			if(clone->item[index]->arquivos[indexAux] != "" && clone->item[index]->arquivos[indexAux] != REMOVIDO)
    			{    				    						        	
		        	inserirNaTabela(tabela, clone->item[index]->arquivos[indexAux], clone->chave[index], clone->item[index]->linhas[indexAux]);		        	
		        }
	        }
    	}
    }     

    tabela->qtdPalavras = clone->qtdPalavras;
    tabela->qtdArquivos = clone->qtdArquivos;    

    return tabela;
}
/**/
//*  VERSAO ANTIGA
TabelaDispersao redimensionarTabela(TabelaDispersao tabela, int tamanho)
{		
    TabelaDispersao novaTabela = new tpDispersao;
    novaTabela = criarTabela(tamanho);    

    for (int index = 0; index < tabela->tamanho; index++)
    {
    	if(tabela->chave[index] != "" && tabela->chave[index] != REMOVIDO)
    	{
    		for(int indexAux = 0; indexAux < 50; indexAux++)
    		{    			
    			if(tabela->item[index]->arquivos[indexAux] != "" && tabela->item[index]->arquivos[indexAux] != REMOVIDO)
    			{    				    						        	
		        	inserirNaTabela(novaTabela, tabela->item[index]->arquivos[indexAux], tabela->chave[index], tabela->item[index]->linhas[indexAux]);		        	
		        }
	        }
    	}
    }     

    novaTabela->qtdPalavras = tabela->qtdPalavras;
    novaTabela->qtdArquivos = tabela->qtdArquivos;    

    return novaTabela;
}
/**/
/**
 * Funcao para inserir uma nova palavra na tabela de dispersao
 * @param tabela -> tabela de dispersao onde será adicionada a palavra passada como paramentro
 * @param arquivo -> caminho de onde está salvo o arquivo que contem a palavra
 * @param chave -> palavra a ser adicionada na tabela de dispersao
 * @param linha -> linha do arquivo onde está a palavra
 * @return tabela -> retorna a tabela passada como paramentro, porém atualizada com a nova palavra
 */
TabelaDispersao inserirNaTabela(TabelaDispersao tabela, std::string arquivo, std::string chave, std::string linha)
{		
	int hash = Hash(preHash(chave), tabela->tamanho);	

	for(int index = 0; index < tabela->tamanho; index++)
	{					
		if(tabela->chave[hash] == "" || tabela->chave[hash] == REMOVIDO)
		{							
			tabela->chave[hash] = chave;			
			tabela->item[hash]->arquivos[0] = arquivo;
			tabela->item[hash]->linhas[0] = " " + linha + " ";
			tabela->qtdPalavras++;		

			if((float) tabela->qtdPalavras > (float) tabela->tamanho * 0.80)
			{    					  								
				tabela = expandirTabela(tabela);    					
			} 
			return tabela;
		}				
		else if(tabela->chave[hash] == chave)
		{			
			for(int indexArquivo = 0; indexArquivo < tabela->qtdArquivos + 1; indexArquivo++)
			{				
				if(tabela->item[hash]->arquivos[indexArquivo] == arquivo)
				{				
					if((long) tabela->item[hash]->linhas[indexArquivo].find(" " + linha + " ") == -1)
					{																	
						tabela->item[hash]->linhas[indexArquivo] += (linha + " ");																								
					}
					return tabela;
				}				
			}

			tabela->item[hash]->arquivos[tabela->qtdArquivos] = arquivo;
			tabela->item[hash]->linhas[tabela->qtdArquivos] += (linha + " ");
			return tabela;				
		}
		else
		{								
			hash = (hash + 1) % tabela->tamanho;
		}					
	}	
	return tabela;
}

/**
 * Funcao para verificar se o arquivo já foi adicionado na tabela de dispersao
 * @param tabela -> tabela onde será procurado o arquivo passado como paramentro
 * @param arquivo -> caminho onde está salvo o arquivo que se deseja verificar
 * @return true -> se o arquivo já estiver na tabela || false -> se o arquivo não estiver na tabela
 */
bool arquivoJaExiste(TabelaDispersao tabela, std::string arquivo)
{
	for(int index = 0; index < tabela->tamanho; index++)
	{
		if(tabela->chave[index] != "" && tabela->chave[index] != REMOVIDO)
		{
			for(int indexArquivo = 0; indexArquivo < tabela->qtdArquivos; indexArquivo++)
			{			
				if(tabela->item[index]->arquivos[indexArquivo].find(arquivo) != -1)
				{					
					return true;
				}
			}
		}
	}	
	return false;
}

/**
 * Funcao para remover um arquivo da tabela de dispersao
 * @param tabela -> tabela de onde será removida todas as palavras do arquivo passado como parametro
 * @param arquivo -> caminho do arquivo que será removido da tabela
 * @param lista -> lista que serve como buffer da base de dados
 * @return true -> se conseguir remover todas as palavras do arquivo da tabela || false -> se o arquivo for invalido
 */
TabelaDispersao removerDaTabela(TabelaDispersao tabela, std::string arquivo, Lista lista)
{				
	int arquivosQueTinhamAPalavra;
	bool foiRemovido = false;	
	if(arquivoJaExiste(tabela,arquivo))
	{		
		for(int index = 0; index < tabela->tamanho; index++)
		{
			arquivosQueTinhamAPalavra = 0;
			if(tabela->chave[index] != "" && tabela->chave[index] != REMOVIDO)
			{			
				for(int indexArquivo = 0; indexArquivo < tabela->qtdArquivos; indexArquivo++)
				{	
					if(tabela->item[index]->arquivos[indexArquivo] != "" && tabela->item[index]->arquivos[indexArquivo] != REMOVIDO)
					{				
						arquivosQueTinhamAPalavra++;											
						if((long) tabela->item[index]->arquivos[indexArquivo].find(arquivo) != -1)
						{							
							tabela->item[index]->arquivos[indexArquivo] = REMOVIDO;
							tabela->item[index]->linhas[indexArquivo] = REMOVIDO;								
							tabela->qtdPalavras--;		
						}			
					}		
				}					
				if(arquivosQueTinhamAPalavra == tabela->qtdArquivos)
				{
					tabela->chave[index] = REMOVIDO;						
				}				
			}											
		}										
		if(tabela->qtdPalavras < tabela->tamanho * 0.10)
		{								
			tabela = reduzirTabela(tabela);									
		}					
		tabela->qtdArquivos--;
		removerDaBase(lista, arquivo);								
		return tabela;				
	}
	else
	{
		std::cout << "\t>> Arquivo " << arquivo << " nao estava na base de buscas." << std::endl;
		return NULL;
	}	
}

/**
 * Funcao que realiza o pre-processamento do arquivo, armazenando todas as palavras na tabela de dispersao
 * @param tabela -> tabela onde será inserida as novas palavras
 * @param nomeArquivo -> caminho do arquivo a ser inserido na tabela
 * @param lista -> lista que serve como buffer da base de dados
 * @return tabela -> retorna a tabela passada como paramentro, porém atualizada com todas as novas palavras contidas no arquivo
 */
TabelaDispersao preProcessamento(TabelaDispersao tabela, std::string nomeArquivo, Lista lista)
{
    if (arquivoJaExiste(tabela, nomeArquivo))
    {
    	tabela = removerDaTabela(tabela, nomeArquivo, lista);
    }
    std::string linha;
    std::string palavra;        
    int linhaAtual = 0, contadorDePalavras = 0;
    std::ifstream buffer(nomeArquivo);

    if (buffer.is_open())
    {        	
    	while (!buffer.eof())
    	{
    		getline(buffer, linha);
    		linha = linha + " ";
    		linhaAtual++;
    		for(int indexLinha = 0; indexLinha < linha.length(); indexLinha++)
    		{  
    			if(!ispunct(linha[indexLinha]) && !isspace(linha[indexLinha]))
    			{
    				palavra = palavra + linha[indexLinha];       				   			
    			}
    			else
    			{         				
    				palavra = toLowerCase(palavra);		    			
    				tabela = inserirNaTabela(tabela, nomeArquivo, palavra, std::to_string(linhaAtual));
    				contadorDePalavras++;      				    				     		    				
    				palavra = "";
    			}     			      			    			   			 			    	
    		}    		    		
        	if(buffer.fail() || buffer.bad())
        	{
        		break;
        	}
    	}   

    	tabela->qtdArquivos++; 
    	Arquivo arquivo = criarArquivo();
    	arquivo->caminho = nomeArquivo;
    	arquivo->quantidadeDePalavras = contadorDePalavras;
    	inserirNaBase(lista, arquivo);	

    	buffer.close();         	   	  
    }
    else
    {
    	std::cout << "\t>> Arquivo """ << nomeArquivo << """ nao foi encontrado no caminho passado." << std::endl;
    }
    return tabela;
}

void showTabela(TabelaDispersao tabela)
{
	if(tabela != NULL)
	{
		for(int index = 0; index < tabela->tamanho; index++)
		{
			for(int indexArquivo = 0; indexArquivo < sizeof(tabela->item); indexArquivo++)
			{			
				if(tabela->item[index]->arquivos[indexArquivo] != "" && tabela->item[index]->arquivos[indexArquivo] != REMOVIDO)
				{				
					std::cout<< "Palavra[" << index << "]: " << tabela->chave[index];
					std::cout<< " Arquivo[" << indexArquivo << "]: " << tabela->item[index]->arquivos[indexArquivo];
					std::cout<< " Linhas[" << indexArquivo << "][" << tabela->item[index]->linhas[indexArquivo] << "]" << std::endl;
				}			
			}
		}
	}
}

/**
 * Funcao para criar um novo arquivo .txt com a tabela de dispersao que representa a indexacao inversa dos arquivos
 * @param tabela -> tabela a ser escrita no .txt
 * @return void
 */
void geraLog(TabelaDispersao tabela)
{
	bool isEspaco = false;

	std::ofstream buffer("arquivos_gerados/Log.txt");
    if (buffer.is_open())
    { 
    	buffer << tabela->tamanho << " " << tabela->qtdArquivos << " " << tabela->qtdPalavras - 1 << "\n";        	
    	for(int index = 0; index < tabela->tamanho; index++)
    	{
    		if(tabela->chave[index] != "" && tabela->chave[index] != REMOVIDO)
    		{
	    		buffer << index << " " << tabela->chave[index] << "\n";	    		
				for(int indexArquivo = 0; indexArquivo <= tabela->qtdArquivos; indexArquivo++)
				{							
					if(tabela->item[index]->arquivos[indexArquivo] != "" && tabela->item[index]->arquivos[indexArquivo] != REMOVIDO)
					{									
						buffer <<tabela->item[index]->arquivos[indexArquivo] << "-";
					}
				}

				buffer << "\n";				
				for(int indexArquivo = 0; indexArquivo <= tabela->qtdArquivos; indexArquivo++)
				{							
					if(tabela->item[index]->linhas[indexArquivo] != "" && tabela->item[index]->linhas[indexArquivo] != REMOVIDO)
					{	
						for(int indexLinhas = 0; indexLinhas < tabela->item[index]->linhas[indexArquivo].length(); indexLinhas++)
						{
							if(tabela->item[index]->linhas[indexArquivo] != "" && tabela->item[index]->linhas[indexArquivo] != REMOVIDO)
							{
								if(!isspace(tabela->item[index]->linhas[indexArquivo][indexLinhas]))
								{
									buffer << tabela->item[index]->linhas[indexArquivo][indexLinhas];	
									isEspaco = true;
								}
								else if(isEspaco)
								{
									buffer << " ";
									isEspaco = false;
								}
							}
						}														
						buffer << "-";
					}
				}
				buffer << "\n";
			}
		}
    }
    buffer.close();	
}

/**
 * Funcao para carregar o arquivo .txt pre-processado para a tabela de dispersao a ser usada nas funcoes
 * @param caminho -> caminho onde está salvo o arquivo log.txt que contem a indexacao da tabela
 * @return tabela -> tabela inicializada com todas as linhas do arquivo passado como parametro
 */
TabelaDispersao carregarLog(const char* caminho)
{		
	TabelaDispersao tabela = new tpDispersao;
	int indexArquivo = 0;
	int hash;	
	std::string line;
	std::string palavra;
	std::ifstream buffer(caminho);
    if (buffer.is_open())
    {        	    	
    	getline(buffer, line,' ');    	
    	tabela = criarTabela(stoi(line));

    	getline(buffer, line,' ');    	    	
    	tabela->qtdArquivos=stoi(line);

    	getline(buffer, line,'\n');      	 
    	tabela->qtdPalavras=stoi(line); 

    	if(tabela->qtdArquivos == 0)
    	{
    		tabela = criarTabela(TAMANHO_INICIAL);
    		return tabela;
    	}
    	else
    	{
	    	while (!buffer.eof())
	    	{    		      		  		    		    		    	
		    	getline(buffer, line,' ');	    		    	
				hash = atoi(line.c_str());

				getline(buffer, line);						
				tabela->chave[hash] = line;										
				
				getline(buffer, line);			
				for(int indexLetra = 0; indexLetra < line.length(); indexLetra++)
				{
					if(line[indexLetra] != '-')
					{
	    				palavra = palavra + line[indexLetra];       				    							
	    			}
	    			else
	    			{
	    				tabela->item[hash]->arquivos[indexArquivo] = palavra;
	    				palavra = "";    				
	    				if(indexArquivo >= tabela->qtdArquivos)
	    				{
	    					break;
	    				}
	    				indexArquivo++;    				
	    			}     			
	    		} 

	    		indexArquivo=0;

	    		getline(buffer, line);    		
	    		for(int indexLetra = 0; indexLetra < line.length(); indexLetra++)
	    		{
					if(line[indexLetra] != '-')
					{
	    				palavra = palavra + line[indexLetra];       				
	    			}
	    			else
	    			{
	    				tabela->item[hash]->linhas[indexArquivo] = palavra;
	    				palavra = "";
	    				if(indexArquivo >= tabela->qtdArquivos)
	    				{
	    					break;
	    				}
	    				indexArquivo++; 
	    			} 
	    		}    		
				
				indexArquivo = 0;								
				
				if(buffer.fail() || buffer.bad())
				{
	        		break;
	        	}
	    	}   

    		buffer.close();        		 	    		
    		return tabela;   	
    	}
    }
    else
    {
    	tabela = criarTabela(TAMANHO_INICIAL);
    	return tabela;
    }
}

/**
 * Funcao para calcular o preHash da chave com base em um string
 * @param nome -> palavra que será usada no calculo do preHash
 * @return chave -> inteiro resultante do calculo do prehash que será usado na função do hash
 */
int preHash(std::string nome)
{
	int chave = 0;
	for(int index = 0; index < nome.length(); index++)
	{
		chave += (int) nome[index] * (index+23);
	}
	if(chave < 0)
	{
		return chave * (-1);
	}
	return chave;
}

/**
 * Funcao para calculo do hash que será usado na tabela de dispersao como indice
 * @param chave -> inteiro gerado pelo preHash
 * @param tamanho -> tamanho da tabela de dispersao
 * @return inteiro a ser usado como indice na tabela de dispersao
 */
int Hash(int chave, int tamanho)
{
	return chave % (tamanho);
}
