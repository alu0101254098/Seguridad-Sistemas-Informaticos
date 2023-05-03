#include "include/vigenere.cc"
#include "include/chacha20.cc"
#include "include/cagenerator.cc"
#include "include/aesnow.cc"
#include "include/cbc.cc"
#include "include/diffie-hellman.cc"
#include "include/rsa.cc"
#include "include/eliptica.cc"


int main(void){
  int opcion;
  std::cout << "Introduzca su eleccion: " << std::endl;
  std::cout << "1) Cifrado Vigenere " << std::endl;
  std::cout << "2) Cifrado Chacha20 " << std::endl;
  std::cout << "3) Generador CA " << std::endl;
  std::cout << "4) Multiplicacion AES/SNOW " << std::endl;
  std::cout << "5) Cifrado AES " << std::endl;
  std::cout << "6) Modo CBC AES " << std::endl;
  std::cout << "7) Diffie-Hellman " << std::endl;
  std::cout << "8) RSA " << std::endl;
  std::cout << "9) Curva Eliptica " << std::endl;
  std::cout << "10) Firma RSA " << std::endl;
  std::cout << "0) Salir del Menú " << std::endl;
  std::cin >> opcion;

    if (opcion == 1){
      std::string texto, pClave_;
      std::cout << "Ingresa el texto original: " << std::endl;
      std::cin >> texto;
      std::cout << "Ingresa la palabra clave: " << std::endl;
      std::cin >> pClave_;
      std::cout << "Texto cifrado: " << AlgoritmoVigenere(texto, pClave_, true) << std::endl;
      std::cout << "Texto original: " << AlgoritmoVigenere( AlgoritmoVigenere(texto, pClave_, true), pClave_, false) << std::endl;
    }
    else if (opcion == 2){   
      std::string resultado;
      UIT32 c1, c2, c3, c4, k1, k2, k3, k4, k5, k6, k7, k8, cu, n1, n2, n3;

      c1 = hexToUint32direct("61707865");
      c2 = hexToUint32direct("3320646e");
      c3 = hexToUint32direct("79622d32");
      c4 = hexToUint32direct("6b206574");

      k1 = hexToUint32("00010203");
      k2 = hexToUint32("04050607");
      k3 = hexToUint32("08090a0b");
      k4 = hexToUint32("0c0d0e0f");
      k5 = hexToUint32("10111213");
      k6 = hexToUint32("14151617");
      k7 = hexToUint32("18191a1b");
      k8 = hexToUint32("1c1d1e1f");
      //contador
      cu = hexToUint32("01000000");
      //nonce
      n1 = hexToUint32("00000000");
      n2 = hexToUint32("0000004a");
      n3 = hexToUint32("00000000");

      UIT32 key[16] = {c1, c2, c3, c4, k1, k2, k3, k4, k5, k6, k7, k8, cu, n1, n2, n3};
      UIT32 b_it[16];
      UIT32 out[16];

      MostrarMatriz(key);

      ChaCha20(out, b_it, key );

      MostrarMatriz(b_it);
      MostrarMatriz(out);
    }
    else if(opcion == 3){
      bool t; int s1, l = 14;
      cout << "Trace? (0 | 1) > "; cin >> t; cout << endl;
      cout << "sat1? > "; cin >> s1; cout << endl;
      cout << "Secuencia C/A PRN1 = " << caGenerator(s1, l, t) << endl;
    }
    else if(opcion == 4){
      string b1, b2;
      cout << "b1" << endl;
      cin >> b1;
      cout << "b2" << endl;
      cin >> b2;
      cout << full_mult(Byte(HexToBin(b1)), Byte(HexToBin(b2)), AES_byte) << endl;
      cout << full_mult(Byte(HexToBin(b1)), Byte(HexToBin(b2)), SNOW_byte) << endl;
    }
    else if(opcion == 5){
      string Clave, Origen;
      cout << "Introduzca la clave: " << endl;
      cin >> Clave;
      cout << "Introduzca el texto original: " << endl;
      cin >> Origen;
      estado clave  = claveToEstado(Clave);
      showEstado(clave);
      estado origen = claveToEstado(Origen);
      cout << "Bloque final:" << endl;
      showEstado(Rijndael(origen, clave));
    }
    else if(opcion == 6){
      estado key  = cadenaToEstado("9dc2c84a37850c11699818605f47958c");
      estado b1  = cadenaToEstado("2e586692e647f5028ec6fa47a55a2aab");
      estado b2  = cadenaToEstado("00000000000000000000000000000000");
      string ib2cad = "000000000000000000000000000000";
      estado ib2 = cadenaToEstado(ib2cad);
      estado iv  = cadenaToEstado("256953b2feab2a04ae0180d8335bbed6");
      CadenaBloques cb = {b1, ib2};
      showCBCSecuence(CBC(cb, key, iv));
      showCBCSecuence(stealingCBC(cb, key, iv, emptyString(ib2cad)));
    }
    else if(opcion == 7){
      int p, alpha, xa, xb, m;
      cout << "Introduzca el valor de p: " << endl;
      cin >> p;
      cout << "Introduzca el valor de alpha: " << endl;
      cin >> alpha;
      cout << "Introduzca el valor de xa: " << endl;
      cin >> xa;
      cout << "Introduzca el valor de xb: " << endl;
      cin >> xb;
      cout << "Introduzca el valor de m: " << endl;
      cin >> m;
      cout << "Clave compartida: " << endl;
      DiffieHellman(p, alpha, xa, xb, m);
    }
    else if(opcion == 8){
      string mensaje;
      long p, q, d;
      cout << "Mensaje > ";
      cin >> mensaje;
      cout << "P > ";
      cin >> p;
      cout << "q > ";
      cin >> q;
      cout << "d > ";
      cin >> d;
      RSA encoder(mensaje, p, q, d);
      encoder.printData();
    }
    else if(opcion == 9){
      std::cout << "Bienvenido al algorimo" << std::endl;
      Eliptica* ptr_Eliptica = new Eliptica();
      ptr_Eliptica->algoritmo();
      delete ptr_Eliptica;
    }
    else if(opcion == 10){
      RSA encoder(11, 7, 39);
      encoder.printDataSign();
    }
    else if(opcion == 0){
      std::cout << "Saliendo..." << std::endl;
      return 0;
    }
    else{
      std::cout << "Opción inválida" << std::endl;
    }
  
  return 0;
}