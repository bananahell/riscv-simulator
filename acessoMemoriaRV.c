/**
 * Trabalho 1 - Organização e Arquitetura de Computadores
 * UnB - 2020/2
 * @author Pedro Nogueira - 14/0065032
 *
 * Este trabalho consiste na simulação das instruções de acesso à memória do
 * RISCV RV32I em linguagem C.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// A memória é simulada como um arranjo de inteiros de 32 bits.
// Ou seja, a memória é um arranjo de 4KWords, ou 16KBytes.
#define MEM_SIZE 4096
int32_t mem[MEM_SIZE];

typedef bool uint1_t;  // somente usado para ints de 1 bit só

#define BYTE1AND 0x000000FF  // 00000000 00000000 00000000 11111111
#define BYTE2AND 0x0000FF00  // 00000000 00000000 11111111 00000000
#define BYTE3AND 0x00FF0000  // 00000000 11111111 00000000 00000000
#define BYTE4AND 0xFF000000  // 11111111 00000000 00000000 00000000

#define BYTE1OR 0xFFFFFF00  // 11111111 11111111 11111111 00000000
#define BYTE2OR 0xFFFF00FF  // 11111111 11111111 00000000 11111111
#define BYTE3OR 0xFF00FFFF  // 11111111 00000000 11111111 11111111
#define BYTE4OR 0x00FFFFFF  // 00000000 11111111 11111111 11111111

#define ALLONE 0xFFFFFFFF  // 11111111 11111111 11111111 11111111

/**
 * Lê um inteiro alinhado - endereços múltiplos de 4.
 * A função calcula o endereço de memória somando os parâmetros:
 * Endereço palavra = address + kte
 * A função deve checar se o endereço é um múltiplo de 4 (%4 == 0).
 * Se não for, deve escrever uma mensagem de erro e retornar zero.
 * Se o endereço estiver correto, a função deve:
 * • Dividi-lo por 4 para obter o índice do vetor memória
 * • Retornar o o valor lido da memória
 */
int32_t lw(uint32_t address, int32_t kte) {
  if ((address + kte) % 4 != 0) {
    printf("Error reading the address in lw - address not multiple of 4!\n");
    return 0;
  }
  return mem[(address + kte) / 4];
}

/**
 * Lê um byte do vetor memória e retorna-o, estendendo o sinal para 32 bits.
 * Lembrando que as palavras da memória tem 4 bytes cada, para acessar um byte
 * dentro da palavra pode-se:
 * • Ler a palavra que contém o byte e, por operações de mascaramento, extrair
 * byte endereçado, ou
 * • Criar um ponteiro para byte e fazer um type cast (coerção de tipo) do
 * endereço do vetor memória (int *) para byte (char *).
 */
int32_t lb(uint32_t address, int32_t kte) {
  uint1_t signal;
  int32_t word = mem[(address + kte) / 4];
  uint32_t byte = (address + kte) % 4;
  int32_t result;
  switch (byte) {
    case 0:
      result = (word & BYTE1AND);
      break;
    case 1:
      result = (word & BYTE2AND) >> 8;
      break;
    case 2:
      result = (word & BYTE3AND) >> 16;
      break;
    case 3:
      result = (word & BYTE4AND) >> 24;
      break;
  }
  signal = result >> 3;
  return signal ? (result | BYTE1OR) : result;
}

/**
 * Lê um byte do vetor memória e retorna-o como um número positivo, ou seja,
 * todos os bits superiores devem ser zerados.
 */
int32_t lbu(uint32_t address, int32_t kte) {
  int32_t word = mem[(address + kte) / 4];
  uint32_t byte = (address + kte) % 4;
  int32_t result;
  switch (byte) {
    case 0:
      result = (word & BYTE1AND);
      break;
    case 1:
      result = (word & BYTE2AND) >> 8;
      break;
    case 2:
      result = (word & BYTE3AND) >> 16;
      break;
    case 3:
      result = (word & BYTE4AND) >> 24;
      break;
  }
  return result;
}

/**
 * Escreve um inteiro alinhado na memória - endereços múltiplos de 4. O cálculo
 * do endereço é realizado da mesma forma que na operação lw().
 */
void sw(uint32_t address, int32_t kte, int32_t dado) {
  if ((address + kte) % 4 != 0) {
    printf("Error saving the word in sw - address not multiple of 4!\n");
    return;
  }
  mem[(address + kte) / 4] = dado;
}

/**
 * Escreve um byte na memória. Caso utilize operações de mascaramento, a palavra
 * que contém o byte deve ser lida da memória, o byte deve ser posicionado
 * corretamente através de deslocamentos e a escrita ocorre utilizando máscaras.
 * Alternativamente pode-se utilizar a coerção para (char *) e escrever
 * diretamente na posição usando o endereço calculado como índice.
 */
void sb(uint32_t address, int32_t kte, int8_t dado) {
  int32_t word = mem[(address + kte) / 4];
  int32_t dado32bit = dado;
  dado32bit = dado32bit & BYTE1AND;
  int32_t byteMask = dado32bit << (kte * 8);
  int32_t result;
  switch (kte) {
    case 0:
      result = (word & BYTE1OR) | byteMask;
      break;
    case 1:
      result = (word & BYTE2OR) | byteMask;
      break;
    case 2:
      result = (word & BYTE3OR) | byteMask;
      break;
    case 3:
      result = (word & BYTE4OR) | byteMask;
      break;
  }
  mem[(address + kte) / 4] = result;
}
/*
int main() {
  sb(0, 0, 0x04);
  sb(0, 1, 0x03);
  sb(0, 2, 0x02);
  sb(0, 3, 0x01);

  sb(4, 0, 0xFF);
  sb(4, 2, 0xFD);
  sb(4, 3, 0xFC);

  sw(12, 0, 0xFF);
  sw(16, 0, 0xFFFF);
  sw(20, 0, 0xFFFFFFFF);
  sw(24, 0, 0x80000000);

  printf("mem[0] = %08x\n", mem[0]);
  printf("mem[1] = %08x\n", mem[1]);
  printf("mem[2] = %08x\n", mem[2]);
  printf("mem[3] = %08x\n", mem[3]);
  printf("mem[4] = %08x\n", mem[4]);
  printf("mem[5] = %08x\n", mem[5]);
  printf("mem[6] = %08x\n", mem[6]);

  printf("lb(4,0) = %08x\n", lb(4, 0));
  printf("lb(4,1) = %08x\n", lb(4, 1));
  printf("lb(4,2) = %08x\n", lb(4, 2));
  printf("lb(4,3) = %08x\n", lb(4, 3));
  printf("lbu(4,0) = %08x\n", lbu(4, 0));
  printf("lbu(4,1) = %08x\n", lbu(4, 1));
  printf("lbu(4,2) = %08x\n", lbu(4, 2));
  printf("lbu(4,3) = %08x\n", lbu(4, 3));
  printf("lw(12,0) = %08x\n", lw(12, 0));
  printf("lw(16,0) = %08x\n", lw(16, 0));
  printf("lw(20,0) = %08x\n", lw(20, 0));

  return 0;
}
*/