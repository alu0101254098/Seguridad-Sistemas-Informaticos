#include <iostream>
#include <map>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h> 
#include <string.h>
#include <iomanip>
#include <utility>

using namespace std;

typedef bitset<8> Byte;
const Byte AES_byte  = Byte(string("00011011"));
const Byte SNOW_byte = Byte(string("10101001"));

string HexToBin(string cadena) {
  string resultado;
  for (int i = 0; i < cadena.size(); i++){
    switch (cadena[i]){
      case 'a':
        resultado += bitset<4>(10).to_string();
        break;
      case 'b':
        resultado += bitset<4>(11).to_string();
        break;
      case 'c':
        resultado += bitset<4>(12).to_string();
        break;
      case 'd':
        resultado += bitset<4>(13).to_string();
        break;
      case 'e':
        resultado += bitset<4>(14).to_string();
        break;
      case 'f':
        resultado += bitset<4>(15).to_string();
        break;
      default:
        resultado += bitset<4>(cadena[i]).to_string();
    }
  }
  return resultado;
}

Byte mult(Byte b1, int pos, Byte Const) {
  cout << "――――――――――――――――――――――――――――――" << endl;
  cout << "STEP " << 0 << endl;
  cout << setw(10) << b1.to_string() << endl;
  for (int i = 0; i < pos; i++) {
  cout << "STEP " << i + 1 << endl;
    if (b1[7]){
      b1 <<= 1;
      cout << setw(4) << b1.to_string() << " + " << Const.to_string() << " = ";
      b1 ^= Const;
      cout << b1.to_string() << endl;
    } else {
      b1 <<= 1;
      cout << setw(10) << b1.to_string() << endl;
    }
  }
  cout << "――――――――――――――――――――――――――――――" << endl;
  return b1;
}

Byte full_mult(Byte b1, Byte b2, Byte Const){
  
  Byte result = Byte(string("00000000"));
  for (int i = 0; i < 8; i++) 
    if (b2[i]) 

      result ^= mult(b1, i, Const);

  return result;
}


int main (void){

  bool quit = false;
  int opt;

  while(!quit){

    cout << "--------------------" << endl;
    cout << "Elija una opción: " << endl;
    cout << "1) AES" << endl;
    cout << "2) SNOW" << endl;
    cout << "0) Salir" << endl;
    cout << "--------------------" << endl;
    cin >> opt;
    string b1, b2;

    switch (opt){
      case 1:{
        cout << "b1" << endl;
        cin >> b1;
        cout << "b2" << endl;
        cin >> b2;
        cout << full_mult(Byte(HexToBin(b1)), Byte(HexToBin(b2)), AES_byte) << endl;
        break;
      }
      case 2:{
        cout << "b1" << endl;
        cin >> b1;
        cout << "b2" << endl;
        cin >> b2;
        cout << full_mult(Byte(HexToBin(b1)), (Byte(HexToBin(b2))), SNOW_byte) << endl;
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