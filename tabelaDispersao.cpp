#include "tabelaDispersao.h"

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
	tabela->chave = new string[tabela->tamanhoTabela];
	tabela->item = new ondeExiste[tabela->tamanhoTabela];
	for(int cont=0;cont<tabela->tamanhoTabela;cont++){
		tabela->chave[cont]="";
		tabela->item[cont]=criarOndeExiste();
	}
	
	return tabela;
}

bool inserirTabela(TabelaDispersao tabela,std::string arquivo,std::string chave,std::string linha){					
	int nchave= Hash(preHash(chave),tabela->tamanhoTabela);		
	for(int cont=0;cont < tabela->tamanhoTabela;cont++){					
		if(tabela->chave[nchave]==""){							
			tabela->chave[nchave]=chave;			
			tabela->item[nchave]->arquivos[0]=arquivo;
			tabela->item[nchave]->linhas[0]+=linha;			
			return true;
		}		
		else if(tabela->chave[nchave]==chave){
			for(int verifica=0;verifica<tabela->qtdArquivos;verifica++){
				if(tabela->item[nchave]->arquivos[verifica]==arquivo){
					tabela->item[nchave]->linhas[verifica]+=(" "+linha);
					return true;					
				}
			}				
			tabela->item[nchave]->arquivos[tabela->qtdArquivos]=arquivo;
			tabela->item[nchave]->linhas[tabela->qtdArquivos]+=(" "+linha);
			return true;				
		}
		else{								
			nchave=(nchave+1)%tabela->tamanhoTabela;
		}	
	}	
	return false;
}

TabelaDispersao preProcessamento(TabelaDispersao tabela, std::string nomeArquivo){
	tabela = criarTabela(10000);
    string linhas,palavra;    
    char vLinha[10];
    int cont=0,sub,valorLinha=0;
    ifstream ss(nomeArquivo);
    if (ss.is_open()){        	
    	while (!ss.eof()){
    		getline(ss, linhas);
    		linhas+=" ";
    		valorLinha++;    	    		 			    
    		for(sub=0;sub<linhas.length();sub++){  
    			if(isalpha(linhas[sub])){    				
    				palavra=palavra+linhas[sub];    				
    			}else{      				
    				cont++;  	 	    				
    				sprintf(vLinha,"%d",valorLinha);     				    				  					    	
    				inserirTabela(tabela,nomeArquivo,palavra,vLinha);    				    				    			    				 	
    				if(cont>=tabela->tamanhoTabela){        		        	
        				break;
        			}
        			palavra=""; 
    			}     			      			    			   			 			    	
    		}
        	if(ss.eof()||ss.fail()||ss.bad()){
        		break;
        	}
    	}    	    	
    	tabela->qtdArquivos++;     	
    	ss.close();    	
    }else{
    	return tabela;
    }
    return tabela;
}

void showTabela(TabelaDispersao tabela){
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

bool geraLog(TabelaDispersao tabela){
	int palavras,ondeExiste,linhas;
	ofstream ss("Log.txt");
    if (ss.is_open()){     
    	ss<<tabela->tamanhoTabela<<endl;   	
    	for(palavras=0;palavras<tabela->tamanhoTabela;palavras++){
			for(ondeExiste=0;ondeExiste<sizeof(tabela->item);ondeExiste++){			
				if(tabela->item[palavras]->arquivos[ondeExiste]!=""){				
					ss<<tabela->chave[palavras]<<" ";
					ss<<tabela->item[palavras]->arquivos[ondeExiste]<<" ";
					ss<<tabela->item[palavras]->linhas[ondeExiste]<<endl;
				}			
			}
		}
    }
    ss.close();

	return false;
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
