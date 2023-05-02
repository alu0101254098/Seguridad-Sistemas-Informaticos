#include <iostream>
#include <bits/stdc++.h> 

using namespace std;

const int ROUNDS = 20;
typedef uint32_t UIT32;

//Convierte la cadena de binario a cadena hexadecimal
string BinToHexString(string cadena){
  string resultado, x;
  int Ncaracter = cadena.size()/4;
  for (int i = 0; i < Ncaracter; i++){
    string caracter = cadena.substr(i*4, i*4 + 4);
    bitset<4> aux = bitset<4>(caracter);
    stringstream stream;
    stream << hex << aux.to_ulong();
    string result( stream.str() );
    resultado += result;
  }
  return resultado;
}

//Convierte la cadena de entrada a little endian
string StringToLittle(string r) {
  string s;
  for (int i = r.size() - 1; i >= 1; i -= 2){
    s += r.substr(i-1, 1) + r.substr(i, 1);
  }
  return s;
}

//Convierte la UIT32 en little endian a uint32_t
UIT32 hexToUint32(string cadena){ 
  return UIT32(stoul(StringToLittle(cadena), nullptr, 16));
}

//Convierte la cadena a uint32_t
UIT32 hexToUint32direct(string cadena){ 
  return UIT32(stoul((cadena), nullptr, 16));
}
//Convierte uint32_t a cadena
string u32ToString(UIT32 pal){
  bitset<32> x(pal);
  return BinToHexString(x.to_string());
}

//Desplazamiento lateral de la UIT32 a b bits
UIT32 RDTL(UIT32 a, UIT32 b){
  return (((a) << (b)) | ((a) >> (32 - b)));
}

//Quarte Round 4 palabras de entrada
void QR(UIT32 &a, UIT32 &b, UIT32 &c, UIT32 &d){
  a += b;
  d ^= a;
  d = RDTL(d, 16);

  c += d;
  b ^= c;
  b = RDTL(b, 12);

  a += b;
  d ^= a;
  d = RDTL(d, 8);

  c += d;
  b ^= c;
  b = RDTL(b, 7);
}

void ChaCha20(UIT32 out[16], UIT32 b_it[16], UIT32 in[16]){
  UIT32 x[16];
  for (int i = 0; i < 16; ++i)
    x[i] = in[i];

  for (int i = 0; i < ROUNDS; i += 2){

    QR(x[0], x[4], x[ 8], x[12]);
    QR(x[1], x[5], x[ 9], x[13]);
    QR(x[2], x[6], x[10], x[14]);
    QR(x[3], x[7], x[11], x[15]);

    QR(x[0], x[5], x[10], x[15]);
    QR(x[1], x[6], x[11], x[12]);
    QR(x[2], x[7], x[ 8], x[13]);
    QR(x[3], x[4], x[ 9], x[14]);
  }

  for (int i = 0; i < 16; ++i){
    b_it[i] = x[i];
    out[i] = x[i] + in[i];
  }
}

//Muestra la matriz
void MostrarMatriz(UIT32 x[16]){
  cout << endl <<  "------------------------------------" << endl;
  for (int i = 0; i < 16; ++i){
    if(i % 4 == 0){
      cout << endl;
    }
    cout << u32ToString(x[i]) << " ";
  }
  cout  << endl << "------------------------------------" << endl;
}