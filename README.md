# OAC - Processador RiscV Monociclo em C++

Trabalho de Organização e Arquitetura de Computadores  
Pedro Nogueira - 14/0065032  
UnB - 2020/2  

Projeto de um processador monociclo na arquitetura RISC-V na linguagem C++.  
O trabalho simula a arquitetura de um processador RISC-V na linguagem C++ como o programa [RARS](https://github.com/TheThirdOne/rars/releases) faz. Ele recebe um dump de dados de memória tanto de instrução quanto de memória em um arquivo externo que ele lê e roda cada instrução conforme.  

## Especificações

### Plataforma

WSL2|Ubuntu em um Windows 10  
gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)  
VSCode  

### Como rodar

O comando ```g++ -o ./main.exe -std=c++17 -Wall -Wno-overflow -pedantic -Wextra -g main.cpp``` compila o projeto todo, bastando depois rodar o executável main.exe resultante. O comando ```cppcheck . --enable=all --suppress=missingIncludeSystem``` funciona para checagem do projeto.  

### PDF

O PDF do professor está na raiz do projeto.  

### main.cpp

Código que começa o projeto, procurando na raiz os arquivos de dump.  

### globals.h

Constantes e flags utilizadas pelo projeto inteiro.  

### acessoMemoriaRV.c

Trabalho antigo contendo as funcionalidades para escrita e leitura na memória.  

### riscvcommands.cpp

Comandos possíveis do projeto, cada um com sua função correspondente.  

### riscv.cpp

Arquitetura completa do processador, unindo a ideia de cada funcionalidade na sequência lógica dos acontecimentos dentro da estrutura.  
A arquitetura é dividida em 3 pedaços de funcionamento:  

- fetch: Fase em que cada instrução é reconhecida como uma instrução e carregada para o processador de uma em uma.  
- decode: Identificação da funcionalidade requisitada pela instrução pegada no fetch.  
- execute: Execução da funcionalidade reconhecida no decode.  

### code.bin/data.bin

Arquivos de dump das instruções gerados pelo RARS. O arquivo code.bin contém as instruções (.text) enquanto o arquivo data.bin contém os dados (.data).  

### Esse README.md

Vamos sempre atualizar, se atentando ao formato markdown dele. Inclusive os espaços no final das linhas!!!  

### Estilo

Estilo Google nativo do VSCode.  
