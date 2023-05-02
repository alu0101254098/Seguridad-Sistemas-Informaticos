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

  cout << "Salida : yA = " << yA << " | yB = " << yB << " | KA = " << KA << " | KB = " << KB << endl;
  cout << "―-―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――" << endl;
}