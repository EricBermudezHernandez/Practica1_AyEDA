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

bool EsOperador(std::string operador) {
  if (operador == "+") {
    return true;
  } else if (operador == "-") {
    return true;
  } else if (operador == "*") {
    return true;
  } else if (operador == "/") {
    return true;
  } else if (operador == "%") {
    return true;
  } else if (operador == "^") {
    return true;
  } else if (operador == "++") {
    return true;
  } else if (operador == "--") {
    return true;
  }
  return false;
}

template <size_t Base>
class Board {
 public:
  // Constructor
  Board(const std::string& fichero);
  // Método que empieza a leer todas las líneas del fichero, omitiendo la primera
  void Start();
  // Método que realiza las operaciones en notación polaca inversa(RPN)
  BigInt<Base> Procesar(const std::string& expresion_notacion_polaca);
  // Método que añade una variable al atributo privado
  void Insertar(const std::string& etiqueta, BigInt<Base>& valor_numerico);
  // Método que sirve para evaluar las operaciones a la hora de usar la notación polaca inversa
  BigInt<Base> Evaluar(BigInt<Base>& operando1, BigInt<Base>& operando2, const std::string& operador);
 private:
  std::map<const std::string, BigInt<Base>&> variables_;
  std::ifstream fichero_;
};

template <size_t Base>
Board<Base>::Board(const std::string& fichero) {
  fichero_.open(fichero.c_str(), std::ios::in);
}

// Método que empieza a leer todas las líneas del fichero, omitiendo la primera
template <size_t Base>
void Board<Base>::Start() {
  std::string linea, etiqueta,simbolo_igual, valor_numerico_big_int;
  // Leemos todas las líneas del fichero
  while (!fichero_.eof()) {
    std::getline(fichero_, linea);
    if (EsOperador(std::to_string(linea[linea.size() - 1]))) { // Los operandos en la notación polaca inversa se guardan al final de la línea, por lo que comprobamos si esto es verdad para saber si hay una operación o no
      std::istringstream aux{linea}; // Hacemos un stringstream para poder tener la etiqueta del resultado
      std::string etiqueta; // Este string será la etiqueta del resultado de la operación entre dos operandos
      aux >> etiqueta; // En la primera línea se hallará el identificador de la variable resultado de la operación
      BigInt<Base> resultado_notacion_polaca{Procesar(linea)};
      Insertar(etiqueta, resultado_notacion_polaca);
    } else {
      std::istringstream aux_linea{linea}; // Declaramos un stringstream para poder coger fácilmente la primera palabra de el fichero
      aux_linea >> etiqueta;
      aux_linea >> simbolo_igual; // Esto es el "=" ej.-> N1 = 3456, nos lo quitamos para llegar a lo siguiente que es el valor de el BigInt
      aux_linea >> valor_numerico_big_int; // Este sería el valor númerico del BigInt que va después del igual
      BigInt<Base> valor{valor_numerico_big_int};
      Insertar(etiqueta, valor);
    }
  }
  // Generamos el fichero salida iterarando en el Board para guardar los valores
  std::ofstream fichero_salida;
  fichero_salida.open("fichero_salida.txt", std::ios::out);
  auto it = variables_.begin();
  while (it != variables_.end()) {
    fichero_salida <<it->first <<" = "<<it->second << '\n';
    it++;
  }
}

template <size_t Base> 
BigInt<Base> Board<Base>::Evaluar(BigInt<Base>& operando1, BigInt<Base>& operando2,const std::string& operador) {
  std::string prueba;
  if (operador == "+") {
    return operando1 + operando2;
  } else if (operador == "-") {
    return operando1 - operando2;
  } else if (operador == "*") {
    return operando1 * operando2;
  } else if (operador == "/") {
    return operando1 / operando2;
  } else if (operador == "%") {
    return operando1 % operando2;
  } else if (operador == "^") {
    return pow(operando1, operando2);
  } else if (operador == "++") {
    return operando1++;
  } else if (operador == "--") {
    return operando1--;
  }
  return BigInt<Base>{};
}

template <size_t Base>
BigInt<Base> Board<Base>::Procesar(const std::string& expresion_notacion_polaca) {
  // Aquí iría el RPN para hacer las operaciones
  std::stack<BigInt<Base>> pila;
  std::istringstream aux{expresion_notacion_polaca};
  std::string operandos;
  while (aux >> operandos) {
    // Buscamos las variables del board por su etiqueta, si existe, lo metemos por su valor en la pila
    if (!EsOperador(operandos)) {
      if (variables_.find(operandos) != variables_.end()) {
        pila.push(variables_[operandos]); 
      }
    } else {
      BigInt<Base> operando1, operando2, resultado;
      if (!pila.empty()) {
        operando1 = pila.top();
        pila.pop();
      }
      if (!pila.empty()) {
        operando2 = pila.top();
        pila.pop();
      }
      size_t encontrado = operandos.find("++");
      if (encontrado != std::string::npos) {
        resultado = Evaluar(operando1, operando2, std::to_string(operandos[encontrado]));
        pila.push(resultado);
      }
      size_t encontrado2 = operandos.find("--");
      if (encontrado2 != std::string::npos) {
        resultado = Evaluar(operando1, operando2, std::to_string(operandos[encontrado]));
        pila.push(resultado);
      } else {
        resultado = Evaluar(operando1, operando2, operandos);
        pila.push(resultado);
      }
    }
  }
  return pila.top();
}

template <size_t Base>
void Board<Base>::Insertar(const std::string& etiqueta, BigInt<Base>& valor_numerico) {
  std::map<const std::string, BigInt<Base>&> aux;
  aux.insert(std::make_pair(etiqueta, valor_numerico));
  //variables_.insert(std::make_pair(etiqueta, valor_numerico));
}

#endif
