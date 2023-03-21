#include <iostream>
#include <math.h>
#include <vector>
#include <cassert>
#include <bitset>

using namespace std;

typedef bitset<8> Byte;
typedef vector<vector<Byte>> estado;
typedef vector<estado> CadenaBloques;

// Devuelve el numero de bytes que le faltan para completar
// un estado
int ExponenciacionRapida(int a, int b, int m) {
  int x = 1;
  int y = a % m;
  int i = 1;
  cout << "----------------------------------------" << endl;
  while (b > 0 && y > 1) {
    if (b%2 == 1) {
      // Mostrar la traza en la ejecucion
      x = (x * y) % m;
      b--;
      cout << "Iteracion " << i << ": " << "x = " << x << " y = " << y << " b = " << b << endl;
      i++;
    } else {
      // Mostrar la traza en la ejecucion
      y = (y * y) % m;
      b /= 2;
      cout << "Iteracion " << i << ": " << "x = " << x << " y = " << y << " b = " << b << endl;
      i++;
    }
  }
  cout << "----------------------------------------" << endl;
  return x;
}

void DiffieHellman(int p, int alpha, int xa, int xb, int m) {
  cout << "―-―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――" << endl;
  cout << "Entrada: p = " << p << " a = " << alpha << " k = " << xa << " x = " << xb << " m = " << m << endl;
  // Ambos calculan su clave publica y se la intercambian
  int yA = ExponenciacionRapida(alpha, xa, p);
  int yB = ExponenciacionRapida(alpha, xb, p);

  // Cada uno con la clave del otro, genera la clave secreta
  int KA = ExponenciacionRapida(yB, xa, p);
  int KB = ExponenciacionRapida(yA, xb, p);

  cout << "Salida : yA = " << yA << " | yB = " << yB << " | K = " << KA << endl;
  cout << "―-―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――" << endl;
}

int main (void){

  bool quit = false;
  int opt;

  while(!quit){

    cout << "---------------――---" << endl;
    cout << "Elija una opción: " << endl;
    cout << "1) Diffie-Hellman" << endl;
    cout << "2) Banco de Pruebas" << endl;
    cout << "0) Salir" << endl;
    cout << "--------------------" << endl;
    
    cin >> opt;

    switch (opt){
      case 1:{
        int p = 43, alpha = 23, xa = 25, xb = 33, m = 34;
        DiffieHellman(p, alpha, xa, xb, m);
        break;
      }
      case 2:{
        DiffieHellman(13, 4, 5, 2, 8);
        DiffieHellman(43, 23, 25, 33, 18);
        DiffieHellman(113, 43, 54, 71, 28);
        DiffieHellman(31, 2, 771, 342, 28);
        break;
      }
      case 0:
        quit = true;
        break;          
      default:
        cout << "Opcion incorrecta" << endl;
        break;
    }
  }
  //cambiar el nombre a una carpeta en bash
  //mv -v "old name" "new name"

  return 0;
}