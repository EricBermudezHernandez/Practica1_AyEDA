#ifndef BIG_INT_H
#define BIG_INT_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

void PrintVector(std::vector<char> vector) {
  for (auto& digito : vector) std::cout << static_cast<char>(digito + '0');
  std::cout << std::endl;
}

template <size_t Base>
class BigInt {
 public:
  // Constructores
  BigInt(long long n = 0);
  BigInt(std::string&);
  BigInt(const char*);
  BigInt(const BigInt<Base>&);  // Constructor de copia
  // Acceso:
  int sign() const { return signo_; }   // Signo: 1 o -1
  char operator[](int posicion) const;  // Acceso al i-ésimo dígito
  // Operadores:
  BigInt<Base>& operator=(const BigInt<Base>&);
  // Inserción / Extracción
  template <size_t Bass>
  friend std::ostream& operator<<(std::ostream&, const BigInt<Bass>&);
  template <size_t Bass>
  friend std::istream& operator>>(std::istream&, BigInt<Bass>&);
  // Operadores de comparación
  template <size_t Bass>
  friend bool operator==(const BigInt<Bass>& numero1,
                         const BigInt<Bass>& numero2);
  bool operator!=(const BigInt<Base>&) const;
  template <size_t Bass>
  friend bool operator>(const BigInt<Bass>& numero1,
                        const BigInt<Bass>& numero2);
  bool operator>=(const BigInt<Base>&) const;
  template <size_t Bass>
  friend bool operator<(const BigInt<Bass>& numero1,
                        const BigInt<Bass>& numero2);
  bool operator<=(const BigInt<Base>&) const;
  // Operadores de incremento / decremento
  BigInt<Base>& operator++();    // Pre-incremento
  BigInt<Base> operator++(int);  // Post-incremento
  BigInt<Base>& operator--();    // Pre-decremento
  BigInt<Base> operator--(int);  // Post-decremento
  // Operadores aritméticos
  template <size_t Bass>
  friend BigInt<Bass> operator+(const BigInt<Bass>&, const BigInt<Bass>&);
  // ==========================================================
  // Esta implementación asume que el resultado de la resta siempre es positivo
  BigInt<Base> operator-(const BigInt<Base>& numero2) const {
    int carry = 0;
    BigInt<Base> aux_numero1{*this}, aux_numero2{numero2}, result;

    // Rellenando el número más corto con 0s
    int lengthDiff = aux_numero1.numero_.size() - aux_numero2.numero_.size();
    if (lengthDiff < 0) {  // numero2 es el menor de los dos
      for (int i = 0; i < -lengthDiff; i++) {
        aux_numero1.numero_.push_back(0);
      }
    } else if (lengthDiff > 0) {  // numero1 es el menor de los dos
      for (int i = 0; i < lengthDiff; i++) {
        aux_numero2.numero_.push_back(0);
      }
    }

    // Restando los números
    for (int i = 0; i < aux_numero1.numero_.size(); i++) {
      int difference = aux_numero1.numero_[i] - aux_numero2.numero_[i] - carry;
      if (difference < 0) {
        carry = 1;
        difference += Base;
      } else {
        carry = 0;
      }
      result.numero_.push_back(difference);
    }

    // Al final de cada operación se añade un 0 adicional al resultado de la multiplicación,
    // por lo que se elimina antes de devolver el resultado invirtiendo el número,
    // quitando el 0 y volviendo a invertir el número
    std::reverse(result.numero_.begin(), result.numero_.end());
    result.numero_.pop_back();
    std::reverse(result.numero_.begin(), result.numero_.end());

    return result;
  }

  // ==========================================================
  BigInt<Base> operator-() const;
  // ==========================================================
  BigInt<Base> operator*(const BigInt<Base>& numero2) const {
    BigInt<Base> aux{*this},result{"0"};
    for (int i = 0; i < aux.numero_.size(); i++) {
      int carry = 0;
      BigInt<Base> aux_result;
      for (int j = 0; j < numero2.numero_.size() || carry > 0; j++) {
        int mul =
            aux.numero_[i] * (j < numero2.numero_.size() ? numero2.numero_[j] : 0) +
            carry;
        aux_result.numero_.push_back(mul % Base);
        carry = mul / Base;
      }
      for (int j = 0; j < i; j++) {
        aux_result.numero_.insert(aux_result.numero_.begin(), 0);
      }
      result = result + aux_result;
    }
    // Al final de cada operación se añade un 0 adicional al resultado de la multiplicación,
    // por lo que se elimina antes de devolver el resultado invirtiendo el número,
    // quitando el 0 y volviendo a invertir el número
    std::reverse(result.numero_.begin(), result.numero_.end());
    result.numero_.pop_back();
    std::reverse(result.numero_.begin(), result.numero_.end());
    return result;
  }
  // ==========================================================
  template <size_t Bass>
  friend BigInt<Bass> operator/(const BigInt<Bass>& numero1, const BigInt<Bass>& numero2);
  BigInt<Base> operator%(const BigInt<Base>&) const;
  // Potencia ab
  template <size_t Bass>
  friend BigInt<Bass> pow(const BigInt<Bass>&, const BigInt<Bass>&);
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
  // Comprobamos si existe el carácter '-' para ver si el número es negativo o
  // no
  size_t signo_encontrado{numero_string.find('-')};
  if (signo_encontrado ==
      std::string::npos) {  // npos es una constante de string que dice si lo ha
                            // encontrado o no
    signo_ = 1;
  } else {
    signo_ = -1;
  }
  for (int i{numero_string.size() - 1}; i >= 0; --i) {
    if (isalpha(numero_string[i])) {  // Comprobamos si el dígito es un caracter
                                      // para después comprobar si es un
                                      // caracter hexadecimal para hacer la
                                      // conversión y meterlo en el vector
      if (numero_string[i] == 'A' || numero_string[i] == 'B' ||
          numero_string[i] == 'C' || numero_string[i] == 'D' ||
          numero_string[i] == 'E' || numero_string[i] == 'F') {
        switch (numero_string[i]) {  // En caso de que sea una de las letras que
                                     // queremos, comprobamos cual es y metemos
                                     // su correspondiente valor en hexdecimal
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
      } else {  // En caso de no ser ninguna de las letras hexadecimales, el
                // usuario nos habrá metido una incorrecta por lo que indicamos
                // el error
        std::cerr << "Letra incorrecta" << std::endl;
        exit(1);
      }
    } else {  // Si no es ninguna letra, es que es un número, por lo que lo
              // metemos directamente
      numero_.emplace_back(
          numero_string[i] -
          '0');  // Le restamos '0' para convertirlo en un entero
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
    if (isalpha(*numero)) {  // Comprobamos si el dígito es un caracter para
                             // después comprobar si es un caracter hexadecimal
                             // para hacer la conversión y meterlo en el vector
      if (*numero == 'A' || *numero == 'B' || *numero == 'C' ||
          *numero == 'D' || *numero == 'E' || *numero == 'F') {
        switch (*numero++) {  // En caso de que sea una de las letras que
                              // queremos, comprobamos cual es y metemos su
                              // correspondiente valor en hexdecimal
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
    } else {  // Si no es ninguna letra, es que es un número, por lo que lo
              // metemos directamente
      vector_aux.emplace_back(
          (*numero++) - '0');  // Le restamos '0' para convertirlo en un entero
    }
  }
  std::reverse(vector_aux.begin(),
               vector_aux.end());  // Invertimos el vector para que se guarde
                                   // alrevés en el vector de chars del objeto
  numero_ = vector_aux;
}

template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& segundo_numero) {
  numero_ = segundo_numero.numero_;
}

// ========================= SOBRECARGA DE OPERADOR [] =========================

template <size_t Base>
char BigInt<Base>::operator[](int posicion) const {
  // Usamos la "fórmula" [(numero_.size() - 1) - posicion] para acceder a el
  // número que queremos, esto lo hacemos así ya que el vector de chars del
  // BigInt está dado la vuelta
  if (numero_[(numero_.size() - 1) - posicion] >= 10) {  // Si el número es mayor o igual que 10 es que es una letra en
                                                        // hexadecimal así que la convertimos a un número
    return ( static_cast<char>('A' + numero_[(numero_.size() - 1) - posicion] - 10));
  }  // Si es menor que 10 es que es un número, por lo que lo convertimos a un
     // char o lo sacamos por pantalla
  return (static_cast<char>(numero_[(numero_.size() - 1) - posicion] + '0'));
}

// ========================= SOBRECARGA DE OPERADORES DE INSERCIÓN/EXTRACCIÓN
// =========================

template <size_t Base>
std::ostream& operator<<(std::ostream& os, const BigInt<Base>& numero) {
  for (int i{numero.numero_.size() - 1}; i >= 0; --i) {
    if (numero.numero_[i] >= 10) {  // Si el número es mayor o igual que 10 es que es una letra en
                                    // hexadecimal así que la convertimos a un número
      os << (static_cast<char>('A' + numero.numero_[i] - 10));
    } else {  // Si es menor que 10 es que es un número, por lo que lo
              // convertimos a un char o lo sacamos por pantalla
      os << (static_cast<char>(numero.numero_[i] + '0'));
    }
  }
  return os;
}

template <size_t Base>
std::istream& operator>>(std::istream& is, BigInt<Base>& big_int) {
  std::string aux_numero;
  is >> aux_numero;  // Guardamos el número en un string
  BigInt<Base> aux{
      aux_numero};  // Creamos un BigInt auxiliar para que el vector de chars de
                    // el número que queremos introducirle el valor sea cambiado
                    // por el que queramos
  big_int.numero_.clear();  // Borramos el contenido del BigInt para
                            // introducirle el nuevo valor
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
bool operator>(const BigInt<Base>& numero1, const BigInt<Base>& numero2) {
  std::vector<char> aux_vector_numero1{numero1.numero_}, aux_vector_numero2{numero2.numero_};
  long unsigned int i{aux_vector_numero1.size() - 1}, j{aux_vector_numero2.size() - 1}, size_maximo{};
  // Eliminamos los posibles 0s a la izquierda que puedan haber, para poder comparar por el tamaño de los vectores
    while(static_cast<char>(aux_vector_numero1[i] + '0') == '0') {
        aux_vector_numero1.pop_back();
        i--;
    }
    while(static_cast<char>(aux_vector_numero2[j] + '0')  == '0') {
        aux_vector_numero1.pop_back();
        j--;
    }
    if (aux_vector_numero1.size() > aux_vector_numero2.size()) {
        return true;
    } else if (aux_vector_numero2.size() > aux_vector_numero1.size()){
        return false;
    }
    // Si hemos llegado a este punto, es que tienen el mismo tamaño, tenemos invertir los vectores por que están alrevés por el propio constructor de BigInt para después compararlos
    std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
    std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
    return aux_vector_numero1 > aux_vector_numero2;
}

template <size_t Bass>
bool operator<(const BigInt<Bass>& numero1, const BigInt<Bass>& numero2) {
  std::vector<char> aux_vector_numero1{numero1.numero_}, aux_vector_numero2{numero2.numero_};
  long unsigned int i{aux_vector_numero1.size() - 1}, j{aux_vector_numero2.size() - 1}, size_maximo{};
  // Eliminamos los posibles 0s a la izquierda que puedan haber, para poder comparar por el tamaño de los vectores
    while(static_cast<char>(aux_vector_numero1[i] + '0') == '0') {
        aux_vector_numero1.pop_back();
        i--;
    }
    while(static_cast<char>(aux_vector_numero2[j] + '0')  == '0') {
        aux_vector_numero1.pop_back();
        j--;
    }
    if (aux_vector_numero1.size() < aux_vector_numero2.size()) {
        return true;
    } else if (aux_vector_numero2.size() < aux_vector_numero1.size()){
        return false;
    }
    // Si hemos llegado a este punto, es que tienen el mismo tamaño, tenemos invertir los vectores por que están alrevés por el propio constructor de BigInt para después compararlos
    std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
    std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
    return aux_vector_numero1 < aux_vector_numero2;
}

template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& numero2) const {
  return numero_ != numero2.numero_;
}

template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base>& numero2) const {
  std::vector<char> aux_vector_numero1{numero_}, aux_vector_numero2{numero2.numero_};
  long unsigned i{aux_vector_numero1.size() - 1}, j{aux_vector_numero2.size() - 1}, size_maximo{};
  // Eliminamos los posibles 0s a la izquierda que puedan haber, para poder comparar por el tamaño de los vectores
    while(static_cast<char>(aux_vector_numero1[i] + '0') == '0') {
        aux_vector_numero1.pop_back();
        i--;
    }
    while(static_cast<char>(aux_vector_numero2[j] + '0')  == '0') {
        aux_vector_numero1.pop_back();
        j--;
    }
    if (aux_vector_numero1.size() > aux_vector_numero2.size()) {
        return true;
    } else if (aux_vector_numero2.size() > aux_vector_numero1.size()){
        return false;
    }
    // Si hemos llegado a este punto, es que tienen el mismo tamaño, tenemos invertir los vectores por que están alrevés por el propio constructor de BigInt para después compararlos
    std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
    std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
    return aux_vector_numero1 >= aux_vector_numero2;
}

template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base>& numero2) const {
  std::vector<char> aux_vector_numero1{numero_}, aux_vector_numero2{numero2.numero_};
  long unsigned i{aux_vector_numero1.size() - 1}, j{aux_vector_numero2.size() - 1}, size_maximo{};
  // Eliminamos los posibles 0s a la izquierda que puedan haber, para poder comparar por el tamaño de los vectores
    while(static_cast<char>(aux_vector_numero1[i] + '0') == '0') {
        aux_vector_numero1.pop_back();
        i--;
    }
    while(static_cast<char>(aux_vector_numero2[j] + '0')  == '0') {
        aux_vector_numero1.pop_back();
        j--;
    }
    if (aux_vector_numero1.size() < aux_vector_numero2.size()) {
        return true;
    } else if (aux_vector_numero2.size() < aux_vector_numero1.size()){
        return false;
    }
    // Si hemos llegado a este punto, es que tienen el mismo tamaño, tenemos invertir los vectores por que están alrevés por el propio constructor de BigInt para después compararlos
    std::reverse(aux_vector_numero1.begin(), aux_vector_numero1.end());
    std::reverse(aux_vector_numero2.begin(), aux_vector_numero2.end());
    return aux_vector_numero1 <= aux_vector_numero2;
}

// ========================= OPERADORES ARITMÉTICOS =========================

template <size_t Base>
BigInt<Base> operator+(const BigInt<Base>& numero1,
                       const BigInt<Base>& numero2) {
  int carry = 0;
  BigInt<Base> aux_numero1{numero1}, aux_numero2{numero2},
      result;  // resultado como BigInt

  // Rellenando el número más corto con 0s
  int lengthDiff = aux_numero1.numero_.size() - aux_numero2.numero_.size();
  if (lengthDiff < 0) {  // a es el menor de los dos
    for (int i = 0; i < -lengthDiff; i++) {
      aux_numero1.numero_.push_back(0);
    }
  } else if (lengthDiff > 0) {  // b es el menor de los dos
    for (int i = 0; i < lengthDiff; i++) {
      aux_numero2.numero_.push_back(0);
    }
  }

  // Sumando los números
  for (int i = 0; i < aux_numero1.numero_.size(); i++) {
    int sum = aux_numero1.numero_[i] + aux_numero2.numero_[i] + carry;
    result.numero_.push_back(sum % Base);
    carry = sum / Base;
  }

  // Añadiendo el carry si es que hay
  if (carry > 0) {
    result.numero_.push_back(carry);
  }

  // Al final de cada operación se añade un 0 adicional al resultado de la suma,
  // por lo que se elimina antes de devolver el resultado invirtiendo el número,
  // quitando el 0 y volviendo a invertir el número
  std::reverse(result.numero_.begin(), result.numero_.end());
  result.numero_.pop_back();
  std::reverse(result.numero_.begin(), result.numero_.end());
  return result;
}

// MAL
template <size_t Base> 
BigInt<Base> operator/(const BigInt<Base>& numero1, const BigInt<Base>& numero2) {
  // Si se cumplen las siguientes dos condiciones, el divisor, que en este caso es "numero2", es 0. Una división por 0 no es posible, por lo que lo indicamos y salimos del programa
  if (numero2.numero_.size() == 1 && numero2.numero_[0] == 0) {
    std::cout << "No es posible realizar una división por 0" << std::endl;
    exit(1);
  }

  // Verificar si el dividendo(numero1) es menor que el divisor(numero2), si esto es así, el cociente de la división dará 0, por lo que retornamos un BigInt con valor 0.
  if (numero1 < numero2) {
    return BigInt<Base>{};
  }

  // realizar la división
  BigInt<Base> dividendo, divisor, resultado, cifra;
  for (int i{0}; i < numero1.numero_.size(); ++i) {
    BigInt<Base> aux{numero1.numero_[i]};
    dividendo = (dividendo * BigInt<Base>{Base}) + aux;
    cifra = BigInt<Base>{};
    while (dividendo >= numero2) {
      dividendo = dividendo - numero2;
      cifra++;
    }
    resultado = (resultado * BigInt<Base>{Base}) + cifra;
  }

  while (resultado.numero_.size() > 1 && resultado.numero_.back() == 0) {
    resultado.numero_.pop_back();
  }

  return resultado;
}

/*
template <size_t Base>
BigInt<Base> operator%(const BigInt<Base>& numero1) {
  // Si se cumplen las siguientes dos condiciones, el divisor, que en este caso es "numero2", es 0. Una división por 0 no es posible, por lo que lo indicamos y salimos del programa
  if (numero2.numero_.size() == 1 && numero2.numero_[0] == 0) {
    std::cout << "No es posible realizar una división por 0" << std::endl;
    exit(1);
  }

  // Verificar si el dividendo (numero1) es menor que el divisor (numero2), si esto es así, el módulo de la división será el mismo que el dividendo.
  if (numero1 < numero2) {
    return numero1;
  }

  // Realizar la operación de módulo
  BigInt<Base> num1{numero1}, num2{numero2}, dividendo, divisor, resultado, cifra;
  for (int i{0}; i < num1.numero_.size(); ++i) {
    BigInt<Base> aux{num1.numero_[i]};
    dividendo = (dividendo * BigInt<Base>{Base}) + aux;
    cifra = BigInt<Base>{"0"};
    while (dividendo >= num2) {
      dividendo = dividendo - num2;
      cifra++;
    }
  }
  return dividendo;
}
*/
// Potencia
template <size_t Base>
BigInt<Base> pow(const BigInt<Base>&, const BigInt<Base>&) {}

// ========================= OPERADORES DE INCREMENTO / DECREMENTO

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator++() {  // Pre-incremento
  // BigInt auxiliar inicializado a '1' para poder hacer el incremento con la
  // sobrecarga del operador '+'
  BigInt<Base> aux{1};
  *this = *this + aux;
  return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator++(int) {  // Post-incremento
  // primero hacemos el incremento del objeto que está invocando el método y
  // después devolvemos una copia del mismo objeto antes de ser incrementado.
  // Esto se hace así para que el operador de post-incremento no sume antes de
  // utilizar el número
  BigInt<Base> aux{1}, result{*this};
  *this = *this + aux;
  return result;
}

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator--() {  // Pre-decremento
  // Como no se puede restar un BigInt con una constante, Inicializamos un BigInt con valor 1 para poder restar aprovechando la sobrecarga del operador
  BigInt<Base> restando{1};
  *this = *this - restando;
  return *this;
}  

template <size_t Base>
BigInt<Base> BigInt<Base>::operator--(int) {  // Post-decremento
  BigInt<Base> aux{*this},restando{1};
  *this = *this - restando;
  return aux;
}  

#endif
