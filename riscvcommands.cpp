#include "acessoMemoriaRV.c"
#include "globals.h"

/**
 * Função ADD do tipo R. Adiciona os dois valores de registradores e guarda em
 * um terceiro.
 * @param input1 Primeiro endereço de registrador a ser somado.
 * @param input2 Segundo endereço de registrador a ser somado.
 * @param output Endereço de registrador que recebe o resultado.
 * @return A soma feita.
 */
int32_t rADD(int output, int input1, int input2) {
  int32_t result = breg[input1] + breg[input2];
  breg[output] = result;
  return result;
}

/**
 * Função ADD do tipo I. Adiciona os dois valores de registradores e guarda em
 * um terceiro.
 * @param input1 Primeiro endereço de registrador a ser somado.
 * @param immediate Imediato com o número a ser somado.
 * @param output Endereço de registrador que recebe o resultado.
 * @return A soma feita.
 */
int32_t iADDI(int output, int input1, int32_t immediate) {
  int32_t result = breg[input1] + immediate;
  breg[output] = result;
  return result;
}

/**
 * Função AND do tipo R. Faz um and bit a bit.
 * @param output Endereço de registrador que recebe o resultado.
 * @param input1 Primeiro endereço de registrador a ser comparado.
 * @param input2 Segundo endereço de registrador a ser comparado.
 * @return A comparação feita.
 */
int32_t rAND(int output, int input1, int input2) {
  int32_t result = breg[input1] & breg[input2];
  breg[output] = result;
  return result;
}

/**
 * Função AND do tipo I. Faz um and bit a bit.
 * @param output Endereço de registrador que recebe o resultado.
 * @param input1 Primeiro endereço de registrador a ser comparado.
 * @param immediate Imediato com o número a ser comparado.
 * @return A comparação feita.
 */
int32_t iANDI(int output, int input1, int32_t immediate) {
  int32_t result = breg[input1] & immediate;
  breg[output] = result;
  return result;
}

/**
 * Função AUIPC do tipo U. Soma PC com o imediato.
 * @param output Endereço de registrador que recebe o resultado.
 * @param immediate Imediato usado pra somar com o endereço de PC.
 * @return O endereço somado.
 */
uint32_t uAUIPC(int output, uint32_t immediate) {
  uint32_t result = pc + (immediate << 12);
  breg[output] = result;
  return result;
}

/**
 * Função BEQ do tipo SB. Pula para endereço se os registradores a serem
 * comparados são iguais.
 * @param input1 Primeiro endereço de registrador a ser comparado.
 * @param input2 Segundo endereço de registrador a ser comparado.
 * @param label Comando para o qual o endereço será redirecionado.
 */
void sbBEQ(int input1, int input2, int label) {
  if (breg[input1] == breg[input2]) {
    pc += label;
    has_jumped = true;
  }
}

/**
 * Função BNE do tipo SB. Pula para endereço se os registradores a serem
 * comparados são diferentes.
 * @param input1 Primeiro endereço de registrador a ser comparado.
 * @param input2 Segundo endereço de registrador a ser comparado.
 * @param label Comando para o qual o endereço será redirecionado.
 */
void sbBNE(int input1, int input2, int label) {
  if (breg[input1] != breg[input2]) {
    pc += label;
    has_jumped = true;
  }
}

/**
 * Função BGE do tipo SB. Pula para endereço se o primeiro registrador é maior
 * ou igual ao segundo.
 * @param input1 Primeiro endereço de registrador a ser comparado.
 * @param input2 Segundo endereço de registrador a ser comparado.
 * @param label Comando para o qual o endereço será redirecionado.
 */
void sbBGE(int input1, int input2, int label) {
  if (breg[input1] >= breg[input2]) {
    pc += label;
    has_jumped = true;
  }
}

/**
 * Função BGEU do tipo SB. Pula para endereço se os registradores a serem
 * comparados são diferentes. Os valores são unsigned.
 * @param input1 Primeiro endereço de registrador a ser comparado (unsigned).
 * @param input2 Segundo endereço de registrador a ser comparado (unsigned).
 * @param label Comando para o qual o endereço será redirecionado.
 */
void sbBGEU(int input1, int input2, int label) {
  if ((unsigned)breg[input1] >= (unsigned)breg[input2]) {
    pc += label;
    has_jumped = true;
  }
}

/**
 * Função BLT do tipo SB. Pula para endereço se o primeiro registrador é menor
 * que o segundo.
 * @param input1 Primeiro endereço de registrador a ser comparado.
 * @param input2 Segundo endereço de registrador a ser comparado.
 * @param label Comando para o qual o endereço será redirecionado.
 */
void sbBLT(int input1, int input2, int label) {
  if (breg[input1] < breg[input2]) {
    pc += label;
    has_jumped = true;
  }
}

/**
 * Função BLTU do tipo SB. Pula para endereço se o primeiro registrador é menor
 * que o segundo. Os valores são unsigned.
 * @param input1 Primeiro endereço de registrador a ser comparado (unsigned).
 * @param input2 Segundo endereço de registrador a ser comparado (unsigned).
 * @param label Comando para o qual o endereço será redirecionado.
 */
void sbBLTU(int input1, int input2, int label) {
  if ((unsigned)breg[input1] < (unsigned)breg[input2]) {
    pc += label;
    has_jumped = true;
  }
}

/**
 * Função JAL do tipo UJ. Pula para o endereço especificado e guarda o PC de
 * agora.
 * @param link Onde é guardado o endereço antigo do PC.
 * @param target Endereço de instrução novo para o qual se quer pular.
 */
void ujJAL(int link, int target) {
  breg[link] = pc + 4;
  pc += target;
  has_jumped = true;
}

/**
 * Função JALR do tipo UJ. Pula para o endereço especificado no registrador mais
 * o imediato e guarda o PC de agora.
 * @param link Onde é guardado o endereço antigo do PC.
 * @param target Registrador com o endereço de instrução novo para o qual se
 * quer pular.
 * @param immediate Offset do endereço para o qual se quer pular.
 */
void ujJALR(int link, int target, int immediate) {
  breg[link] = pc + 4;
  pc = breg[target] + immediate;
  has_jumped = true;
}

/**
 * Função LB do tipo I. Carrega um byte de um endereço. Já foi feita em
 * acessoMemoriaRV.c, então só vou chamar de lá.
 * @param output Endereço de registrador que recebe o resultado.
 * @param address Endereço em bit do byte procurado.
 * @param kte Offset do endereço.
 * @return O byte encontrado.
 */
int32_t iLB(int output, uint32_t address, int32_t kte) {
  int32_t byte = lb(breg[address], kte);
  breg[output] = byte;
  return byte;
}

/**
 * Função OR do tipo R. Faz um or bit a bit.
 * @param input1 Primeiro endereço de registrador a ser comparado.
 * @param input2 Segundo endereço de registrador a ser comparado.
 * @param output Endereço de registrador que recebe o resultado.
 * @return A comparação feita.
 */
int32_t rOR(int output, int input1, int input2) {
  int32_t result = breg[input1] | breg[input2];
  breg[output] = result;
  return result;
}

/**
 * Função LBU do tipo I. Carrega um byte unsigned de um endereço. Já foi feita
 * em acessoMemoriaRV.c, então só vou chamar de lá.
 * @param output Endereço de registrador que recebe o resultado.
 * @param address Endereço em bit do byte procurado.
 * @param kte Offset do endereço.
 * @return O byte encontrado.
 */
int32_t iLBU(int output, uint32_t address, int32_t kte) {
  int32_t byte = lbu(breg[address], kte);
  breg[output] = byte;
  return byte;
}

/**
 * Função LW do tipo I. Carrega uma palavra de um endereço. Já foi feita em
 * acessoMemoriaRV.c, então só vou chamar de lá.
 * @param output Endereço de registrador que recebe o resultado.
 * @param address Endereço em bit da palavra procurada.
 * @param kte Offset do endereço.
 * @return A palavra encontrada.
 */
int32_t iLW(int output, uint32_t address, int32_t kte) {
  int32_t word = lw(breg[address], kte);
  breg[output] = word;
  return word;
}

/**
 * Função LUI do tipo U. Carrega um número imediato seguido de 12 0's.
 * @param output Endereço de registrador que recebe o resultado.
 * @param immediate Número a ser shiftado.
 * @result Número shiftado.
 */
int32_t uLUI(int output, int immediate) {
  int32_t result = immediate << 12;
  breg[output] = result;
  return result;
}

/**
 * Pseudo função NOP. Não faz operação alguma.
 */
void pseudoNOP() { iADDI(0, 0, 0); }

/**
 * Função SLTU do tipo R. Se o primeiro argumento é menor que o segundo, seta
 * para 1, senão para 0. Todos unsigned.
 * @param output Endereço de registrador que recebe o resultado.
 * @param input1 Primerio endereço de registrador a ser comparado.
 * @param input2 Segundo endereço de registrador a ser comparado.
 * @result 1 se o primeiro registrador é menor que o segundo, senão 0.
 */
int32_t rSLTU(int output, int input1, int input2) {
  uint reg1 = breg[input1];
  uint reg2 = breg[input2];
  int32_t result = reg1 < reg2 ? 1 : 0;
  breg[output] = result;
  return result;
}

/**
 * Função ORI do tipo I. Faz um or bit a bit com o imediato.
 * @param output Endereço de registrador que recebe o resultado.
 * @param input1 Primerio endereço de registrador a ser comparado.
 * @param immediate Segundo número a ser comparado.
 * @result Resultado da comparação.
 */
int32_t iORI(int output, int input1, int immediate) {
  int32_t result = breg[input1] | immediate;
  breg[output] = result;
  return result;
}

/**
 * Função SB do tipo S. Salva um byte em um endereço. Já foi feita em
 * acessoMemoriaRV.c, então só vou chamar de lá.
 * @param address Endereço em bit do byte procurado.
 * @param kte Offset do endereço.
 * @param dado Byte a ser salvo na memória.
 */
void sSB(uint32_t address, int32_t dado, int32_t kte) {
  int8_t byte = breg[dado] & BYTE1AND;
  sb(breg[address], kte, byte);
}

/**
 * Função SLLI do tipo I. Shifta o número no registrador pra esquerda conforme
 * o imediato
 * @param output Endereço de registrador que recebe o resultado.
 * @param input1 Registrador com o número a ser shiftado.
 * @param immediate Número de vezes a ser shiftado.
 * @result O número shiftado.
 */
int32_t iSLLI(int output, int input1, int immediate) {
  int32_t result = breg[input1] << immediate;
  breg[output] = result;
  return result;
}

/**
 * Função SLT do tipo R. Se o primeiro argumento é menor que o segundo, seta
 * para 1, senão para 0.
 * @param output Endereço de registrador que recebe o resultado.
 * @param input1 Primerio endereço de registrador a ser comparado.
 * @param input2 Segundo endereço de registrador a ser comparado.
 * @result 1 se o primeiro registrador é menor que o segundo, senão 0.
 */
int32_t rSLT(int output, int input1, int input2) {
  int32_t result = breg[input1] < breg[input2] ? 1 : 0;
  breg[output] = result;
  return result;
}

/**
 * Função SRAI do tipo I. Faz um shift aritmético para a direita na quantidade
 * de bits especificado.
 * @param output Endereço de registrador que recebe o resultado.
 * @param input1 Registrador do número a ser shiftado.
 * @param immediate Quantidade de bits a ser shiftado.
 * @result Número shiftado.
 */
int32_t iSRAI(int output, int input1, int immediate) {
  int32_t result = breg[input1] >> immediate;
  breg[output] = result;
  return result;
}

/**
 * Função SRLI do tipo I. Faz um shift lógico para a direita na quantidade de
 * bits especificado.
 * @param output Endereço de registrador que recebe o resultado.
 * @param input1 Registrador do número a ser shiftado.
 * @param immediate Quantidade de bits a ser shiftado.
 * @result Número shiftado.
 */
int32_t iSRLI(int output, int input1, int immediate) {
  uint32_t reg1 = breg[input1];
  int32_t result = reg1 >> immediate;
  breg[output] = result;
  return result;
}

/**
 * Função SUB do tipo R. Subtrai os dois valores de registradores e guarda em um
 * terceiro.
 * @param input1 Primeiro endereço de registrador a ser subtraído.
 * @param input2 Segundo endereço de registrador a ser subtraído.
 * @param output Endereço de registrador que recebe o resultado.
 * @return A subtração feita.
 */
int32_t rSUB(int output, int input1, int input2) {
  int32_t result = breg[input1] - breg[input2];
  breg[output] = result;
  return result;
}

/**
 * Função SW do tipo S. Salva uma palavra em um endereço. Já foi feita em
 * acessoMemoriaRV.c, então só vou chamar de lá.
 * @param address Endereço em bit da palavra procurada.
 * @param kte Offset do endereço.
 * @param dado Palavra a ser salva na memória.
 */
void sSW(uint32_t address, int32_t dado, int32_t kte) {
  sw(address, kte, dado);
}

/**
 * Função XOR do tipo R. Faz um xor bit a bit.
 * @param input1 Primeiro endereço de registrador a ser comparado.
 * @param input2 Segundo endereço de registrador a ser comparado.
 * @param output Endereço de registrador que recebe o resultado.
 * @return A comparação feita.
 */
int32_t rXOR(int output, int input1, int input2) {
  int32_t result = breg[input1] ^ breg[input2];
  breg[output] = result;
  return result;
}

/**
 * Função ecall. Vê o comando em A7 e executa conforme.
 * @return Se a função chamar exit retorna true.
 */
bool sysECALL() {
  int value = breg[A7];
  switch (value) {
    case 1:
      printf("%d", breg[A0]);
      break;
    case 4:
      printf("%d", mem[breg[A0] >> 2]);
      break;
    case 10:
      return true;
    default:
      break;
  }
  return false;
}
