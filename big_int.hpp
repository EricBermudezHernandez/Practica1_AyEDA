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
  BigInt(long long n = 0);
  BigInt(std::string&);
  BigInt(const char* );
  BigInt(const BigInt<Base>&); // Constructor de copia
  // Acceso:
  int sign() const { return signo_; }  // Signo: 1 o -1
  char operator[](int posicion) const; // Acceso al i-ésimo dígito
  // Operadores:
  BigInt<Base>& operator=(const BigInt<Base>&);
  // Inserción / Extracción
  template <size_t Bass>
  friend std::ostream& operator<<(std::ostream&, const BigInt<Bass>&);
  template <size_t Bass>
  friend std::istream& operator>>(std::istream&, BigInt<Bass>&);
  // Operadores de comparación
  template <size_t Bass>
  friend bool operator==(const BigInt<Bass>& numero1, const BigInt<Bass>& numero2); 
  bool operator!=(const BigInt<Base>&) const;
  template <size_t Bass>
  friend bool operator>(const BigInt<Bass>& numero1, const BigInt<Bass> & numero2);
  bool operator>=(const BigInt<Base> &) const;
  template <size_t Bass>
  friend bool operator<(const BigInt<Bass>& numero1, const BigInt<Bass>& numero2);
  bool operator<=(const BigInt<Base>&) const;
  /*
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
    for (int i{0}; i < numero_.size(); ++i) {
      std::cout << i;
    }
    std::cout << std::endl;
  }
 private:
  int signo_;
  std::vector<char> numero_;
};

// ========================= CONSTRUCTORES =========================
template <size_t Base>
BigInt<Base>::BigInt(long long n) {
  long long resto{0};
  // Comprobamos si el número es menor que 0 para determinar el signo
  if (n >= 0) {
    signo_ = 1;
  } else {
    signo_ = -1;
  }
  while (n > 9) {
    resto = n % 10;
    n /= 10;
    numero_.emplace_back(resto);
  }
  numero_.emplace_back(n);
}

template <size_t Base>
BigInt<Base>::BigInt(std::string& numero_string) {
  // Comprobamos si existe el carácter '-' para ver si el número es negativo o no
  size_t signo_encontrado{numero_string.find('-')};
  if (signo_encontrado == std::string::npos) { // npos es una constante de string que dice si lo ha encontrado o no
    signo_ = 1;
  } else {
    signo_ = -1;
  }
  for (int i{numero_string.size() - 1}; i >= 0; --i) {
    if (isalpha(numero_string[i])) { // Comprobamos si el dígito es un caracter para después comprobar si es un caracter hexadecimal para hacer la conversión y meterlo en el vector
      if (numero_string[i] == 'A' || numero_string[i] == 'B' || numero_string[i] == 'C' || numero_string[i] == 'D' || numero_string[i] == 'E' || numero_string[i] == 'F') {
        switch (numero_string[i]) { // En caso de que sea una de las letras que queremos, comprobamos cual es y metemos su correspondiente valor en hexdecimal
          case 'A':
            numero_.emplace_back(10);
          break;
          case 'B':
            numero_.emplace_back(11);
          break;
          case 'C':
            numero_.emplace_back(12);
          break;
          case 'D':
            numero_.emplace_back(13);
          break;
          case 'E':
            numero_.emplace_back(14);
          break;
          case 'F':
            numero_.emplace_back(15);
          break;
          default:
          break;
      }
    } else { // En caso de no ser ninguna de las letras hexadecimales, el usuario nos habrá metido una incorrecta por lo que indicamos el error
      std::cerr << "Letra incorrecta" << std::endl;
      exit(1);
      }
    } else { // Si no es ninguna letra, es que es un número, por lo que lo metemos directamente
      numero_.emplace_back(numero_string[i] -'0'); // Le restamos '0' para convertirlo en un entero 
    }
  }
}

template <size_t Base>
BigInt<Base>::BigInt(const char* numero) {
  std::vector<char> vector_aux;
  long long aux{std::stoll(numero)};
  // Comprobamos si el número es menor que 0 para determinar el signo
  if (aux >= 0) {
    signo_ = 1;
  } else {
    signo_ = -1;
  }
  while (*numero != '\0') {
      if (isalpha(*numero)) { // Comprobamos si el dígito es un caracter para después comprobar si es un caracter hexadecimal para hacer la conversión y meterlo en el vector
        if (*numero == 'A' || *numero == 'B' || *numero == 'C' || *numero == 'D' || *numero == 'E' || *numero == 'F') {
          switch (*numero++) { // En caso de que sea una de las letras que queremos, comprobamos cual es y metemos su correspondiente valor en hexdecimal
            case 'A':
              vector_aux.emplace_back(10);
            break;
            case 'B':
              vector_aux.emplace_back(11);
            break;
            case 'C':
              vector_aux.emplace_back(12);
            break;
            case 'D':
              vector_aux.emplace_back(13);
            break;
            case 'E':
              vector_aux.emplace_back(14);
            break;
            case 'F':
              vector_aux.emplace_back(15);
            break;
            default:
            break;
        }
      } else {
        std::cerr << "Letra incorrecta" << std::endl;
        exit(1);
        }
      } else { // Si no es ninguna letra, es que es un número, por lo que lo metemos directamente
        vector_aux.emplace_back((*numero++) -'0'); // Le restamos '0' para convertirlo en un entero 
      }
    }
    std::reverse(vector_aux.begin(), vector_aux.end()); // Invertimos el vector para que se guarde alrevés en el vector de chars del objeto
    numero_ = vector_aux; 
}

template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& segundo_numero) {
  numero_ = segundo_numero.numero_;
}

// ========================= SOBRECARGA DE OPERADOR [] =========================

template <size_t Base>
char BigInt<Base>::operator[](int posicion) const {
  // Usamos la "fórmula" [(numero_.size() - 1) - posicion] para acceder a el número que queremos, esto lo hacemos así ya que el vector de chars del BigInt está dado la vuelta
  if (numero_[(numero_.size() - 1) - posicion] >= 10 ) { // Si el número es mayor o igual que 10 es que es una letra en hexadecimal así que la convertimos a un número
    return (static_cast<char>('A' + numero_[(numero_.size() - 1) - posicion] - 10));
  }  // Si es menor que 10 es que es un número, por lo que lo convertimos a un char o lo sacamos por pantalla
    return (static_cast<char>(numero_[(numero_.size() - 1) - posicion] + '0'));
}


// ========================= SOBRECARGA DE OPERADORES DE INSERCIÓN/EXTRACCIÓN =========================

template <size_t Base>
std::ostream& operator<<(std::ostream& os, const BigInt<Base>& numero) {
  for (int i{numero.numero_.size() - 1}; i >= 0; --i) {
    if (numero.numero_[i] >= 10) { // Si el número es mayor o igual que 10 es que es una letra en hexadecimal así que la convertimos a un número
      os << (static_cast<char>('A' + numero.numero_[i] - 10));
    } else { // Si es menor que 10 es que es un número, por lo que lo convertimos a un char o lo sacamos por pantalla
      os << (static_cast<char>(numero.numero_[i] + '0'));
    } 
  }
  return os;
}

template <size_t Base>
std::istream& operator>>(std::istream& is, BigInt<Base>& big_int) {
  std::string aux_numero;
  is >> aux_numero; // Guardamos el número en un string
  BigInt<Base> aux{aux_numero}; // Creamos un BigInt auxiliar para que el vector de chars de el número que queremos introducirle el valor sea cambiado por el que queramos
  big_int.numero_.clear(); // Borramos el contenido del BigInt para introducirle el nuevo valor
  big_int.numero_ = aux.numero_;
  return is;
}

// ========================= SOBRECARGA DE OPERADOR '=' =========================

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator=(const BigInt<Base>& segundo_numero) {
  numero_ = segundo_numero.numero_;
  return *this;
}

// ========================= SOBRECARGA DE OPERADORES DE COMPARACIÓN =========================

template <size_t Base>
bool operator==(const BigInt<Base>& numero1, const BigInt<Base>& numero2) {
  return numero1.numero_ == numero2.numero_;
}

template <size_t Base>
bool operator>(const BigInt<Base>& numero1, const BigInt<Base> & numero2) {
  std::vector<char> aux_vector_numero1{numero1.numero_}, aux_vector_numero2{numero2.numero_};
  std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
  std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
  return aux_vector_numero1 > aux_vector_numero2;
}

template <size_t Bass>
bool operator<(const BigInt<Bass>& numero1, const BigInt<Bass>& numero2) {
  std::vector<char> aux_vector_numero1{numero1.numero_}, aux_vector_numero2{numero2.numero_};
  std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
  std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
  return aux_vector_numero1 < aux_vector_numero2;
}

template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& numero2) const {
  return numero_ != numero2.numero_;
}

template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base> & numero2) const {
  std::vector<char> aux_vector_numero1{numero1.numero_}, aux_vector_numero2{numero2.numero_};
  std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
  std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
  return aux_vector_numero1 >= aux_vector_numero2;
}

template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base>& numero2) const {
  std::vector<char> aux_vector_numero1{numero1.numero_}, aux_vector_numero2{numero2.numero_};
  std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
  std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
  return aux_vector_numero1 <= aux_vector_numero2;
}

#endif
