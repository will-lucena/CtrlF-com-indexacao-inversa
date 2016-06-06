#include "libs/tabelaDispersao.h"

using namespace std;
/*
Operações relacionadas a Tabela
//*/

ondeExiste criarOndeExiste(){
	ondeExiste existe = new Tpexiste;
	if(existe==NULL){
		return NULL;
	}
	existe->arquivos = new string[50];
	existe->linhas = new string[50];	
	for(int cont=0;cont<50;cont++){
		existe->arquivos[cont]="";
		existe->linhas[cont]="";	
	}
	return existe;
}

TabelaDispersao criarTabela(int tamanho){
	TabelaDispersao tabela = new tpDispersao;	
	if(tabela==NULL){
		return NULL;
	}
	tabela->tamanhoTabela=tamanho;	
	tabela->qtdArquivos=0;
	tabela->qtdPalavras=0;
	tabela->chave = new string[tabela->tamanhoTabela];
	tabela->item = new ondeExiste[tabela->tamanhoTabela];
	for(int cont=0;cont<tabela->tamanhoTabela;cont++){
		tabela->chave[cont]="";
		tabela->item[cont]=criarOndeExiste();
	}
	
	return tabela;
}

int cont3=0;
TabelaDispersao ExpandirTabela(TabelaDispersao tabela){    		
    return RedimensionarTabela(tabela, (tabela->tamanhoTabela*2)+1);    
}

TabelaDispersao ReduzirTabela(TabelaDispersao tabela){    
 	return RedimensionarTabela(tabela, (tabela->tamanhoTabela/2)+1);    
}

TabelaDispersao RedimensionarTabela(TabelaDispersao tabela, int tamanho){		
	int arquivos;
    TabelaDispersao novaTabela = new tpDispersao;
    novaTabela = criarTabela(tamanho);    
    for (int cont = 0; cont < tabela->tamanhoTabela; cont++){
    	if(tabela->chave[cont]!=""){
    		for(arquivos=0;arquivos<50;arquivos++){
    			if(tabela->item[cont]->arquivos[arquivos]!=""){
		        	inserirTabela(novaTabela, tabela->item[cont]->arquivos[arquivos], tabela->chave[cont], tabela->item[cont]->linhas[arquivos]);		        	
		        }
	        }
    	}
    }    
    return novaTabela;

}

bool inserirTabela(TabelaDispersao tabela,std::string arquivo,std::string chave,std::string linha){						
	int nchave= Hash(preHash(chave),tabela->tamanhoTabela);			
	for(int cont=0;cont < tabela->tamanhoTabela;cont++){					
		if(tabela->chave[nchave]==""){							
			tabela->chave[nchave]=chave;			
			tabela->item[nchave]->arquivos[0]=arquivo;
			tabela->item[nchave]->linhas[0]=","+linha+",";						
			return true;
		}				
		else if(tabela->chave[nchave]==chave){
			for(int verifica=0;verifica<50;verifica++){				
				if(tabela->item[nchave]->arquivos[verifica]==arquivo){										
					if((long)tabela->item[nchave]->linhas[verifica].find(","+linha+",")==-1){												
						tabela->item[nchave]->linhas[verifica]+=(linha+",");						
						return true;																			
					}else{
						return true;
					}
				}				
			}				
			tabela->item[nchave]->arquivos[tabela->qtdArquivos]=arquivo;
			tabela->item[nchave]->linhas[tabela->qtdArquivos]+=(linha+" ");
			return true;				
		}
		else{								
			nchave=(nchave+1)%tabela->tamanhoTabela;
		}	
	}	
	return false;
}

TabelaDispersao preProcessamento(TabelaDispersao tabela, std::string nomeArquivo, Lista lista){
	
    string linhas,palavra;    
    char vLinha[10];
    int cont=0,sub,valorLinha=0, contadorDePalavras = 0;
	ifstream ss(nomeArquivo);
    if (ss.is_open()){        	
    	while (!ss.eof()){
    		getline(ss, linhas);
    		linhas+=" ";
    		valorLinha++;		    
    		for(sub=0;sub<linhas.length();sub++){  
    			if(!ispunct(linhas[sub])&&!isspace(linhas[sub])){    			   			
    				palavra=palavra+linhas[sub];       				
    			}else{      				
    				cont++;  	 	    				    				
    				sprintf(vLinha,"%d",valorLinha);        				    				
    				if((float)tabela->qtdPalavras>=(float)tabela->tamanhoTabela*0.80){    					  				
    					tabela = ExpandirTabela(tabela);    					
    				}           				 			    			
    				inserirTabela(tabela,nomeArquivo,palavra,vLinha);      				
    				tabela->qtdPalavras++;     			
    				contadorDePalavras++;
    				palavra="";
    			}     			      			    			   			 			    	
    		}    		    		
        	if(ss.eof()||ss.fail()||ss.bad()){
        		break;
        	}
    	}    	    	
    	tabela->qtdArquivos++;
    	Arquivo arquivo = criarArquivo();
    	arquivo->caminho = nomeArquivo;
    	arquivo->quantidadeDePalavras = contadorDePalavras;
    	inserirNaBase(lista, arquivo);     	
    	ss.close();    	  
    }else{
    	std::cout << "\t>> Arquivo """ << nomeArquivo << """ nao foi encontrado no caminho passado." << std::endl;
        exit(-1);
    	return tabela;
    }
    return tabela;
}

void showTabela(TabelaDispersao tabela){
	if(tabela==NULL){
		cout<<"Tabela NULA"<<endl;
	}
	int palavras,ondeExiste;
	for(palavras=0;palavras<tabela->tamanhoTabela;palavras++){
		for(ondeExiste=0;ondeExiste<sizeof(tabela->item);ondeExiste++){			
			if(tabela->item[palavras]->arquivos[ondeExiste]!=""){				
				cout<<"Palavra["<<palavras<<"]: "<<tabela->chave[palavras];
				cout<<" Arquivo["<<ondeExiste<<"]: "<<tabela->item[palavras]->arquivos[ondeExiste];
				cout<<" Linhas["<<tabela->item[palavras]->linhas[ondeExiste]<<"]"<<endl;
			}			
		}
	}
}

void geraLog(TabelaDispersao tabela){
	int palavras,ondeExiste;
	ofstream ss("arquivos_gerados/log.txt");
    if (ss.is_open()){ 
    	ss<<tabela->tamanhoTabela<<" "<<tabela->qtdArquivos<<endl;        	
    	for(palavras=0;palavras<tabela->tamanhoTabela;palavras++){
    		if(tabela->chave[palavras]!=""){
	    		ss<<palavras<<" "<<tabela->chave[palavras]<<" \n";
				for(ondeExiste=0;ondeExiste<tabela->qtdArquivos;ondeExiste++){							
					if(tabela->item[palavras]->arquivos[ondeExiste]!=""){									
						ss<<tabela->item[palavras]->arquivos[ondeExiste]<<" ";
					}
				}
				ss<<" \n";
				for(ondeExiste=0;ondeExiste<tabela->qtdArquivos;ondeExiste++){							
					if(tabela->item[palavras]->arquivos[ondeExiste]!=""){									
						ss<<tabela->item[palavras]->linhas[ondeExiste]<<" ";
					}
				}
				ss<<" \n";
			}
		}
    }
    ss.close();	
}
//*

TabelaDispersao carregarLog(){	
	int tamanhoT=1;
	TabelaDispersao tabela = new tpDispersao;
	int posicao=0,tamanho,nchave;	
	string conteudolinhas,palavra;
	ifstream ss("arquivos_gerados/log.txt");
    if (ss.is_open()){        	    	
    	getline(ss, conteudolinhas,' ');    	
    	tamanho = atoi(conteudolinhas.c_str());    	
    	tabela = criarTabela(tamanho);    	  			    	
    	getline(ss, conteudolinhas,'\n');    	
    	tabela->qtdArquivos=atoi(conteudolinhas.c_str());

    	while (!ss.eof()){    		      		  		    		    		    	
	    	getline(ss, conteudolinhas,' ');	    		    	
			nchave = atoi(conteudolinhas.c_str());						
			getline(ss, conteudolinhas,'\n');						
			tabela->chave[nchave]=conteudolinhas;					
			getline(ss, conteudolinhas);			
			for(int cont=0;cont<conteudolinhas.length();cont++){

				if(!isspace(conteudolinhas[cont])){
    				palavra=palavra+conteudolinhas[cont];       				    							
    			}else{
    				tabela->item[nchave]->arquivos[posicao]=palavra;
    				palavra="";    				
    				if(posicao>=tabela->qtdArquivos){
    					break;
    				}
    				posicao++;    				
    			}     			
    		}    		    	    		
    		posicao=0;

    		getline(ss, conteudolinhas);    		
    		for(int cont=0;cont<conteudolinhas.length();cont++){
				if(!isspace(conteudolinhas[cont])){
    				palavra=palavra+conteudolinhas[cont];       				
    			}else{
    				tabela->item[nchave]->linhas[posicao]=palavra;
    				palavra="";
    				if(posicao>=tabela->qtdArquivos){
    					break;
    				}
    				posicao++; 
    			} 
    		}    		
			posicao=0;								
			if(nchave>=tabela->tamanhoTabela-1){
				break;
			}
    	}   
    	ss.close(); 
    	return tabela;   	
    }else{
    	tabela = criarTabela(200);
    	return tabela;
    }
}

int preHash(string nome){
	int chave=0;
	for(int cont=0;cont<(nome.length());cont++){
		chave+=(int)nome[cont]*(cont+23);
	}
	if(chave<0){
		return chave*-1;
	}
	return chave;
}

int Hash(int chave,int tamanho){
	return chave%(tamanho);
}
