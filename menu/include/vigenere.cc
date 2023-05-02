#include <iostream>
#include <string>

const int mod = 26; //Igualamos el modulo al numero de caracteres de nuestro abecedario
const std::string alfabeto = "abcdefghijklmnopqrstuvwxyz"; //Definimos el abecedario

//Funcion para cifrar y descifrar un texto
std::string AlgoritmoVigenere(std::string texto_, std::string pClave_, bool encriptacion) {
  int texto_len = texto_.length();
  int clave_len = pClave_.length();

  if (texto_len == 0) {
    std::cerr << "No has escrito texto." << std::endl; //Comprobamos que el texto no este vacio
  }

  for (long unsigned i = 0; i < texto_.length(); i++) {
    if (alfabeto.find(texto_[i]) == std::string::npos) { //Si no se encuentra el caracter en nuestro abecedario da error
      std::cerr << "El texto original debe contener solo caracteres del alfabeto mayúsculas." << std::endl;
      return "";
    }
    if (alfabeto.find(pClave_[i % clave_len]) == std::string::npos) { //Lo mismo con la clave
      std::cerr << "La clave solo puede contener caracteres del alfabeto mayúsculas." << std::endl;
      return "";
    }
    int desplazamiento = encriptacion ? alfabeto.find(pClave_[i % clave_len]) : mod - alfabeto.find(pClave_[i % clave_len]); //Si encriptacion es true devuelve el desplazamiento como la posicion de la letra tal cual, si no la desvuelve restando al mod para descifrar
    //std::cout << "Iteracion [" << i + 1 << "]:" << alfabeto[alfabeto.find(texto_[i])] << "+" << alfabeto[desplazamiento] << "=";
    //std::cout << "Desplazamiento: " << desplazamiento << "+ " << "Posicion de la letra: " << alfabeto.find(texto_[i]) <<std::endl;
    //std::cout << "=" << (alfabeto.find(texto_[i]) + desplazamiento) % mod << std::endl;
    texto_[i] = alfabeto[(alfabeto.find(texto_[i]) + desplazamiento) % mod]; //Se suman las posiciones % mod para que este dentro de nuestro alfabeto
    //std::cout << texto_[i] << std::endl;
    
  }
  return texto_;
}