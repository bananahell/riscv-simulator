/*
 *  main.cpp
 *  RISCV
 *
 *  Created by Ricardo Jacobi on 26/01/11.
 *  Copyright 2011 Universidade de Brasilia. All rights reserved.
 *
 */

#include <iomanip>
#include <iostream>
#include <map>

using namespace std;

#include "riscv.cpp"

int main() {
  load_mem("code.bin", 0);
  load_mem("data.bin", 0x2000);
  run();

  return 0;
}
