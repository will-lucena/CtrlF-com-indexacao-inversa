# Ctrl+F com indexação inversa

Projeto das disciplinas de Estrutura de Dados Básica I (EDB) e Linguagem de Programação I (LP) que teve como proposta fazer uma aplicação com dois modos distintos implementados em C++...

Modo 1: Gerenciamento de base
  Criar uma base de dados pre-processada com o uso de indexação (foi adotado a indexação inversa) onde ao inserir um arquivo novo a aplicação deveria salvar todas as palavras do mesmo para agilizar buscas. 
  O modo de gerenciamento insere (um ou mais arquivos passados via terminal), remove (um ou mais arquivos passados via terminal) e lista todos os arquivos da base por ordem de inserção do arquivo, por ordem alfabética dos nomes dos arquivos e pela quantidade de palavras de cada arquivo.
  
Modo 2: Busca de palavras
  Realizar uma busca com parametros pre-definidos (bAND, bOR, tT, tF, pC, pI, pA) e uma ou mais palavras, cada um dos paramentros realiza uma operação diferente, são elas:
  
  bAND -> Realiza interceções das palavras informadas em linhas de um mesmo arquivo, mostrando somente as linhas em que aparecem ambas palavras
  
  bOR -> Realiza uma união de todas as palavras informadas, mostrando todas as ocorrências de cada uma das palavras em cada linha de cada arquivo
  
  tT -> Opção que ativa a exibição do tempo da busca
  
  tF -> Opção que desativa a exibição do tempo da busca (default)
  
  pI -> Mostra o resultado da função bAND ou bOR por ordem de inserção dos arquivos (default)
  
  pA -> Mostra o resultado da função bAND ou bOR por ordem alfabética dos arquivos
  
  pC -> Mostra o resultado da função bAND ou bOR em ordem decrescente da quantidade de ocorrencias das palavras
  
Foram usados estruras e conceitos de ponteiros, listas duplamente encadeadas, tabela de dispersão, structs, algoritmos de busca, algoritmos de ordenação, leitura e escrita em arquivos (.txt) alocação dinamica de memoria e sobrecarga de funções

Projeto desenvolvido por Will Lucena e Welligton Miguel
