#ifndef Structs_h
#define Structs_h

struct tpArquivo
{
	std::string caminho;
	int quantidadeDePalavras;
};
typedef tpArquivo* Arquivo;

struct tpNo
{
    Arquivo conteudo;
	struct tpNo* proximo;
	struct tpNo* anterior;
};
typedef tpNo* No;

struct tpLista
{
	No cabeca;
	No cauda;
	int tamanho;
};
typedef tpLista* Lista;

struct tpExiste
{
	std::string* arquivos;
	std::string* linhas;
};
typedef tpExiste* ondeExiste;

struct tpDispersao
{
	int qtdArquivos;
	int qtdPalavras;	
	int tamanho;
	ondeExiste *item;
	std::string *chave;
	
};
typedef tpDispersao* TabelaDispersao;

#endif