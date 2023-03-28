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

void DiffieHellman(int p, int alpha, int Xa, int Xb, int Xc, int m) {
  cout << "―-―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――" << endl;
  cout << "Entrada: p = " << p << " a = " << alpha << " k = " << Xa << " x = " << Xb << " m = " << m << endl;
  // Ambos calculan su clave publica y se la intercambian
    int Y_a, Y_b, Y_c;
    Y_a = ExponenciacionRapida(alpha, Xa, p);
    Y_b = ExponenciacionRapida(alpha, Xb, p);
    Y_c = ExponenciacionRapida(alpha, Xc, p);

    int Ka, Kb, Kc;
    Ka = ExponenciacionRapida(Y_c, Xa, p);
    Kb = ExponenciacionRapida(Y_a, Xb, p);
    Kc = ExponenciacionRapida(Y_b, Xc, p);

    int c_a, c_b, c_c;
    c_a = Ka;
    c_b = Kb;
    c_c = Kc;

    Ka = ExponenciacionRapida(c_c, Xa, p);
    Kb = ExponenciacionRapida(c_a, Xb, p);
    Kc = ExponenciacionRapida(c_b, Xc, p);


  cout << "Salida : yA = " << Y_a << " | yB = " << Y_b << "| yC" << " | K = " << Ka << endl;

  if (Ka == Kb && Ka == Kc)
    cout << "La clave es correcta" << endl;
  else
    cout << "La clave es incorrecta" << endl;
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
        int p = 43, alpha = 23, xa = 25, xb = 33, xc=21, m = 34;
        DiffieHellman(p, alpha, xa, xb, xc, m);
        break;
      }
      case 2:{
        DiffieHellman(13, 4, 5, 2, 21, 8);
        DiffieHellman(43, 23, 25, 33, 21, 18);
        DiffieHellman(113, 43, 54, 71, 21, 28);
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

  return 0;
}