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
#include <stack>
#include <map>
#include <iterator>

template <size_t Base>
class Board {
 public:
  // Constructor
  Board(const std::string& fichero);
  // Método que empieza a leer todas las líneas del fichero, omitiendo la primera
  void Start();

 private:
  std::map<std::string, BigInt<Base>> variables_;
  std::ifstream fichero_;
};

template <size_t Base>
Board<Base>::Board(const std::string& fichero) {
  fichero_.open(fichero.c_str(), std::ios::in);
}

// Método que empieza a leer todas las líneas del fichero, omitiendo la primera
template <size_t Base>
void Board<Base>::Start() {
  BigInt<Base> operando_1, operando_2, resultado;
  std::stack<BigInt<Base>> pila;
  std::ofstream archivo_salida;
  std::string linea, palabra, identificador;
  std::istringstream linea_stream;
  std::getline(fichero_, linea); // metemos la primera línea en el fichero final
  std::ofstream fichero_salida;
  fichero_salida.open("fichero_salida.txt", std::ios::out);
  fichero_salida << linea;
  while (std::getline(fichero_, linea)) {
    linea_stream.str(linea);
    linea_stream >> palabra;
    identificador = palabra;
    linea_stream >> palabra;
    while(linea_stream >> palabra) {
      if(variables_.find(palabra) != variables_.end()) {
        pila.push(variables_[palabra]);
      } else if (palabra == "+") {
        operando_2 = pila.top();
        pila.pop();
        operando_1 = pila.top();
        pila.pop();
        resultado = operando_1 + operando_2;
        pila.push(resultado);
      } else if (palabra == "-") {
        operando_2 = pila.top();
        pila.pop();
        operando_1 = pila.top();
        pila.pop();
        resultado = operando_1 - operando_2;
        pila.push(resultado);
      } else if (palabra == "*") {
        operando_2 = pila.top();
        pila.pop();
        operando_1 = pila.top();
        pila.pop();
        resultado = operando_1 * operando_2;
        pila.push(resultado);
      } else if (palabra == "/") {
        operando_2 = pila.top();
        pila.pop();
        operando_1 = pila.top();
        pila.pop();
        resultado = operando_1 / operando_2;
        pila.push(resultado);
      } else if (palabra == "%") {
        operando_2 = pila.top();
        pila.pop();
        operando_1 = pila.top();
        pila.pop();
        resultado = operando_1 % operando_2;
        pila.push(resultado);
      } else {
        BigInt<Base> numero(palabra);
        pila.push(numero);
      }
    }
    variables_.insert(std::make_pair(identificador,pila.top()));
    pila.pop();
    linea_stream.clear();
  }
  // Generamos el fichero salida iterarando en el Board para guardar los valores
  auto it = variables_.begin();
  while (it != variables_.end()) {
    fichero_salida << it->first <<" = "<<it->second << '\n';
    it++;
  }
}

#endif
