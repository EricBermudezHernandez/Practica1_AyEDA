#include "big_int.hpp"

int main() {
  BigInt<8> numero_binario{275};
  numero_binario.print();
  return 0;
}