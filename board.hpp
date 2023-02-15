#ifndef BOARD_H
#define BOARD_H

#include "big_int.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

template <size_t Base>
class Board {
 public:
  // Constructor
  Board(std::string fichero);
  // Método que empieza a leer todas las líneas del fichero, omitiendo la primera
  void Start();
  // Método que realiza las operaciones en notación polaca inversa(RPN)
  void Procesar();
  // Método que añade una variable al atributo privado
  void Insertar(std::string etiqueta, BigInt<Base> valor_numerico);

 private:
  std::map<std::string, BigInt<Base>&> variables_;
  std::ifstream fichero_;
};

template <size_t Base>
Board<Base>::Board(std::string fichero) {
  fichero_.open(fichero.c_str(), std::ios::in);
}

template <size_t Base>
void Board<Base>::Start() {
  std::string linea;
  // Leemos todas las líneas del fichero
  while (!fichero_.eof()) {
    std::getline(fichero_, linea);
  }
  // Generamos el fichero salida:
  std::ofstream fichero_salida;
  fichero_salida.open("fichero_salida.txt", std::ios::out);
}

template <size_t Base>
void Board<Base>::Procesar() {
  // Aquí iría el RPN para hacer las operaciones
}

template <size_t Base>
void Board<Base>::Insertar(std::string etiqueta, BigInt<Base> valor_numerico) {
  variables_.insert(std::make_pair(etiqueta, valor_numerico));
}

#endif