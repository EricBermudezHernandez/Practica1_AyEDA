#include "big_int.hpp"

// Implementación constructores
template <size_t Base>
BigInt<Base>::BigInt(long n) {
	long resto{0};
	std::vector<char> aux;
	while (n >= Base) {
		resto = n % Base;
		n /= Base;
		aux.emplace_back(static_cast<char> (resto));
	}
	aux.emplace_back(static_cast<char>(n));
	std::reverse(aux.begin(), aux.end());
	numero_ = aux;
}

template <size_t Base>
BigInt<Base>::BigInt(std::string& numero_string) {
	long aux_numero_string{std::stol(numero_string)},resto{0};
	std::vector<char> aux;
	while (aux_numero_string >= Base) {
		resto = aux_numero_string % Base;
		aux_numero_string /= Base;
		aux.emplace_back(static_cast<char> (resto));
	}
	aux.emplace_back(static_cast<char>(aux_numero_string));
	std::reverse(aux.begin(), aux.end());
	numero_ = aux;
}

template <size_t Base>
BigInt<Base>::BigInt(const char* numero) {
	long aux_numero{std::atol(numero)},resto{0};
	std::vector<char> aux;
	while (aux_numero >= Base) {
		resto = aux_numero % Base;
		aux_numero /= Base;
		aux.emplace_back(static_cast<char> (resto));
	}
	aux.emplace_back(static_cast<char> (aux_numero));
	std::reverse(aux.begin(), aux.end());
	numero_ = aux;
}

template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& big_int) {
	numero_  = big_int.numero_;
}

