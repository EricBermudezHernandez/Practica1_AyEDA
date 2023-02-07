#ifndef BIG_INT_H
#define BIG_INT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <size_t Base>
class BigInt {
 public:
  // Constructores
  BigInt(long n = 0);
  BigInt(std::string&);
  BigInt(const char* );
  BigInt(const BigInt<Base>&); // Constructor de copia
  /*
  // Operadores:
  BigInt<Base>& operator=(const BigInt<Base>&);
  // Inserción / Extracción
  friend std::ostream& operator<<(std::ostream&, const BigInt<Base>&);
  friend std::istream& operator>>(std::istream&, BigInt<Base>&);
  // Operadores de comparación
  friend bool operator==(const BigInt<Base>&, const BigInt<Base> &);
  bool operator!=(const BigInt<Base>&) const;
  friend bool operator>(const BigInt<Base>&, const BigInt<Base> &);
  bool operator>=(const BigInt<Base> &) const;
  friend bool operator<(const BigInt<Base>&, const BigInt<Base>&);
  bool operator<=(const BigInt<Base>&) const;
  // Operadores de incremento / decremento
  BigInt<Base>& operator++(); // Pre-incremento
  BigInt<Base> operator++(int); // Post-incremento
  BigInt<Base>& operator--(); // Pre-decremento
  BigInt<Base> operator--(int); // Post-decremento
  // Operadores aritméticos
  friend BigInt<Base> operator+(const BigInt<Base>&, const BigInt<Base>&);
  BigInt<Base> operator-(const BigInt<Base> &) const;
  BigInt<Base> operator-() const;
  BigInt<Base> operator*(const BigInt<Base>&) const;
  friend BigInt<Base> operator/(const BigInt<Base>&, const BigInt<Base>&);
  BigInt<Base> operator%(const BigInt<Base>&) const;
  // Potencia ab
  friend BigInt<Base> pow(const BigInt<Base>&, const BigInt<Base>&);
  */
  // PRINT BORRAAAAAAAAAARRRRR
  void print() {
    for (auto& digito : numero_) {
      std::cout << digito;
    }
    std::cout << std::endl;
  }
 private:
  std::vector<char> numero_;
};

#endif