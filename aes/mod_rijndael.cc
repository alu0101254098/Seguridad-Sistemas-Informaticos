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
typedef vector<vector<Byte>> estado;
typedef vector<Byte> columna;

const Byte AES_byte  = Byte(string("00011011"));

const int nIter = 10;

// Pasa la cadena de binario a cadena hexadecimal
string BinHexACadena(string cadena){
  string resultado, x;
  int Ncaracter = cadena.size()/4;
  for (int i = 0; i < Ncaracter; i++){
    string caracter = cadena.substr(i*4, i*4 + 4);
    bitset<4> aux = bitset<4>(caracter);
    std::stringstream stream;
    stream << std::hex << aux.to_ulong();
    std::string result( stream.str() );
    resultado += result;
  }
  return resultado;
}

// De cadena hexadecimal al cadena binario
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

const estado emult = {
  {Byte(string("00000010")), Byte(string("00000011")), Byte(string("00000001")), Byte(string("00000001"))},
  {Byte(string("00000001")), Byte(string("00000010")), Byte(string("00000011")), Byte(string("00000001"))},
  {Byte(string("00000001")), Byte(string("00000001")), Byte(string("00000010")), Byte(string("00000011"))},
  {Byte(string("00000011")), Byte(string("00000001")), Byte(string("00000001")), Byte(string("00000010"))}
};

  // Matriz para la operación inversa
const estado invMat = {
  {Byte(string("00001110")), Byte(string("00001011")), Byte(string("00001101")), Byte(string("00001001"))},
  {Byte(string("00001001")), Byte(string("00001110")), Byte(string("00001011")), Byte(string("00001101"))},
  {Byte(string("00001101")), Byte(string("00001001")), Byte(string("00001110")), Byte(string("00001011"))},
  {Byte(string("00001011")), Byte(string("00001101")), Byte(string("00001001")), Byte(string("00001110"))}
};

const int sbox[256] =   {
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

const int InvSBox[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};

estado getSBox (){

  estado out;
  out.resize(16);
  for (int i = 0; i < 16; i++)
    out[i].resize(16);

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      out[i][j] = sbox[i*16 + j];
    }
  }

  return out;
}

estado getInvSBox (){

  estado out;
  out.resize(16);
  for (int i = 0; i < 16; i++)
    out[i].resize(16);

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      out[i][j] = InvSBox[i*16 + j];
    }
  }

  return out;
}

void showEstado(estado e) {
  cout << "―――――――――――" << endl;
  
  for (int j = 0; j < 4; j++) {
      for (int i = 0; i < 4; i++) {
      cout << BinHexACadena(e[i][j].to_string()) << " ";
    }
    cout << endl;
  }
  cout << "―――――――――――" << endl;
}

void showCol(columna e) {
  cout << "――" << endl;
  for (int i = 0; i < 4; i++) {   
    cout << BinHexACadena(e[i].to_string()) << endl;
  }
  cout << "――" << endl;
}

Byte mult(Byte b1, int pos, Byte Const) {
  for (int i = 0; i < pos; i++) {
    if (b1[7]){
      b1 <<= 1;
      b1 ^= Const;
    } else {
      b1 <<= 1;
    }
  }
  return b1;
}

Byte tracemult(Byte b1, int pos, Byte Const) {
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

// obtiene el primer numero hexadecimal de un numero
int get1Hex(Byte b) {
  return Byte(b.to_string().substr(0, 4)).to_ulong();
}

// obtiene el segundo numero hexadecimal de un numero
int get2Hex(Byte b) {
  return Byte(b.to_string().substr(4)).to_ulong();
}

// Primera operacion, realiza una exclusive-OR a cada elemento de
// los dos estados entrantes y devuelve el estado resultado
estado addRoundKey(estado e1, estado e2) {

  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out[i][j] = e1[i][j] ^ e2[i][j];
    }
  }

  return out;
}

// Suma dos columnas
columna addColumns(columna e1, columna e2) {
  columna out;
  out.resize(4);
  for (int i = 0; i < 4; i++) {
    // cout << e1[i].to_string() << " ^ " << e2[i].to_string() << " = " << (e1[i] ^ e2[i]).to_string() << endl;
    out[i] = e1[i] ^ e2[i];
  }
  return out;
}

// Segunda iter Byte Sub

estado SubBytes(estado e) {
  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out[i][j] =  getSBox()[get1Hex(e[i][j])][get2Hex(e[i][j])];
    }
  }
  return out;
}

estado InvSubBytes(estado e) {
  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out[i][j] = getInvSBox()[get1Hex(e[i][j])][get2Hex(e[i][j])];
    }
  }
  return out;
}

columna SubBytesColumn(columna e) {
  columna out;
  out.resize(4);

  for (int i = 0; i < 4; i++) {
    out[i] =  getSBox()[get1Hex(e[i])][get2Hex(e[i])];
  }
  return out;
}

// shift Rows

estado shiftRows(estado e) {
  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k < 4; k++) {
        out[i][k] = e[i][(k+i)%4];
      }
    }
  }
  return out;
}

estado InvShiftRows(estado e) {
  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k < 4; k++) {
        out[i][(k+i)%4] = e[i][k];
      }
    }
  }
  return out;
}

columna RotWord(columna e) {
  columna out;
  out.resize(4);
  for (int i = 0; i < 4; i++) {
    out[i] = e[(i + 1)%4];
  }
  return out;
}

// Ha de llamarse 4 veces, una por cada columna
estado mixColums (estado e) {
  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      Byte b = Byte(string("00000000"));
      for (int k = 0; k < 4; k++) {
        b ^= full_mult(e[k][i], emult[j][k], AES_byte);
      }
      out[j][i] = b;
    }
  }

  return out;
}

estado InvMixColumns(estado e) {
  // Realizamos la operación inversa para cada columna de la matriz
  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      Byte b = Byte(string("00000000"));
      for (int k = 0; k < 4; k++) {
        b ^= full_mult(e[k][i], invMat[j][k], AES_byte);
      }
      out[j][i] = b;
    }
  }

  return out;
}

void assignCol(estado& e, columna n, int pos) {
    e[0][pos] = n[0];    // Copia la columna de 
    e[1][pos] = n[1];    // posicion pos en e
    e[2][pos] = n[2];
    e[3][pos] = n[3];
}

columna getCol(estado& e, int pos) {
  columna c;
  c.resize(4);
  c[0] = e[0][pos];    // Copia la columna de 
  c[1] = e[1][pos];    // posicion pos en e
  c[2] = e[2][pos];
  c[3] = e[3][pos];
  return c;
}

vector<estado> expanseKey(estado c) {

  vector<columna> rc = {{Byte(string("00000001")), Byte(string("00000000")), Byte(string("00000000")), Byte(string("00000000"))},
                        {Byte(string("00000010")), Byte(string("00000000")), Byte(string("00000000")), Byte(string("00000000"))},
                        {Byte(string("00000100")), Byte(string("00000000")), Byte(string("00000000")), Byte(string("00000000"))},
                        {Byte(string("00001000")), Byte(string("00000000")), Byte(string("00000000")), Byte(string("00000000"))},
                        {Byte(string("00010000")), Byte(string("00000000")), Byte(string("00000000")), Byte(string("00000000"))},
                        {Byte(string("00100000")), Byte(string("00000000")), Byte(string("00000000")), Byte(string("00000000"))},
                        {Byte(string("01000000")), Byte(string("00000000")), Byte(string("00000000")), Byte(string("00000000"))},
                        {Byte(string("10000000")), Byte(string("00000000")), Byte(string("00000000")), Byte(string("00000000"))},
                        {Byte(string("00011011")), Byte(string("00000000")), Byte(string("00000000")), Byte(string("00000000"))},
                        {Byte(string("00110110")), Byte(string("00000000")), Byte(string("00000000")), Byte(string("00000000"))}};
  

  vector<estado> out;
  out.push_back(c);

  for (int i = 1; i <= nIter; i++){
    estado nuevo;
    nuevo.resize(4);
    for (int i = 0; i < 4; i++)
      nuevo[i].resize(4);
    columna first = { out[i-1][0][3],    // Copia la ultima columna de 
                      out[i-1][1][3],    // la iteracion iteracion
                      out[i-1][2][3],
                      out[i-1][3][3]};

    first = RotWord(first);
    first = SubBytesColumn(first);

    first = addColumns(first, getCol(out[i-1], 0));  // Sumamos la primera col de la iter anterior, 
    first = addColumns(first, rc[i - 1]);    // con la que habiamos generado mas el rc correspondiente

    assignCol(nuevo, first, 0); // Asignamos first como la primera col de nuevo
    for (int j = 1; j < 4; j++){
      columna c1 = getCol(out[i - 1], j);
      columna c2 = getCol(nuevo, j - 1);
      assignCol(nuevo, addColumns(c1, c2), j);
    }
    out.push_back(nuevo);
  }
  return out;
}

void showIter(estado e, estado c, int i) {
    cout << "――――――――――――――――――――――――――――――――――――――――" << endl;
    cout << "R" << i << endl;
    cout << "SubClave" << endl;
    showEstado(c);
    cout << "Bloque" << endl;
    showEstado(e);
    cout << "――――――――――――――――――――――――――――――――――――――――" << endl;
}

estado Rijndael (estado e, estado  c) {
  // Etapa inicial
  vector<estado> subc = expanseKey(c);  // Generamos las 10 subclaves
  estado out = addRoundKey(e, c);       // Primera fase AddRoundKey clave original
  showIter(out, c, 0);

  // 9 iteraciones
  for (int i = 1; i < 10; i++) {

    out = SubBytes(out);
    out = shiftRows(out);
    out = mixColums(out);
    out = addRoundKey(out, subc[i]);
    showIter(out, subc[i], i);

  }

  return out;
}

estado invRijndael (estado e, estado c) {
  // Etapa inicial
  vector<estado> subc = expanseKey(c);  // Generamos las 10 subclaves
  estado out = addRoundKey(e, subc[10]);       // Inversión de AddRoundKey clave original
  showIter(out, c, 10);

  // 9 iteraciones
  for (int i = nIter - 1; i >= 1; i--) {

    out = InvShiftRows(out); // Inversión de ShiftRows
    out = InvSubBytes(out); // Inversión de SubBytes
    out = addRoundKey(out, subc[i]); // Inversión de AddRoundKey clave de ronda
    out = InvMixColumns(out); // Inversión de MixColumns
    showIter(out, subc[i], i);

  }
  // Etapa final
  out = InvShiftRows(out); // Inversión de ShiftRows
  out = InvSubBytes(out); // Inversión de SubBytes
  out = addRoundKey(out, c); // Inversión de AddRoundKey clave original
  showIter(out, subc[10], 0);

  return out;
}


estado claveToEstado(string clave){
  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);
  int count = 0;
  
    for (int j = 0; j < 4; j++) {
      for (int i = 0; i < 4; i++) {
      out[i][j] = Byte(HexToBin(clave.substr(count, 2)));
      count += 2;
    }
  }
  return out;
}

int main (void){

  bool quit = false;
  int opt;

  while(!quit){

    cout << "--------------------" << endl;
    cout << "Elija una opción: " << endl;
    cout << "1) Rijndael" << endl;
    cout << "2) Prueba addRoundKey" << endl;
    cout << "3) Prueba subBytes" << endl;
    cout << "4) Prueba ShiftRow" << endl;
    cout << "5) Prueba MixColumns" << endl;
    cout << "6) Prueba Expansion de clave" << endl;
    cout << "7) Desencriptar Rijndael" << endl;
    cout << "0) Salir" << endl;
    cout << "--------------------" << endl;
    cin >> opt;

    switch (opt){                       //1 2 3 4 1 2 3 4 1 2 3 4 1 2 3 4 
                                        //00112233445566778899aabbccddeeff
      case 1:{                        // "000102030405060708090a0b0c0d0e0f"
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
        break;
      }
      case 2:{
        estado e1 = claveToEstado("00112233445566778899aabbccddeeff");
        estado e2 = claveToEstado("000102030405060708090a0b0c0d0e0f");
        showEstado(addRoundKey(e1, e2));
        break;
      }
      case 3:{
        estado e1 = claveToEstado("00112233445566778899aabbccddeeff");
        estado e2 = claveToEstado("000102030405060708090a0b0c0d0e0f");
        estado e3 = addRoundKey(e1, e2);
        showEstado(InvSubBytes(e3));
        break;
      }
      case 4:{
        estado e1 = claveToEstado("00112233445566778899aabbccddeeff");
        estado e2 = claveToEstado("000102030405060708090a0b0c0d0e0f");
        estado e3 = addRoundKey(e1, e2);
        estado e4 = InvSubBytes(e3);
        showEstado(InvShiftRows(e4));
        break;
      }
      case 5:{
        estado e1 = claveToEstado("00112233445566778899aabbccddeeff");
        estado e2 = claveToEstado("000102030405060708090a0b0c0d0e0f");
        estado e3 = addRoundKey(e1, e2);
        estado e4 = InvSubBytes(e3);
        estado e5 = InvShiftRows(e4);
        showEstado(InvMixColumns(e5));
        break;
      }
      case 6:{
        estado e1 = claveToEstado("000102030405060708090a0b0c0d0e0f");  // d0 c9 e1 b6 
        showEstado(e1);                                                 // 14 ee 3f 63 
        vector<estado> x = expanseKey(e1);                              // f9 25 0c 0c 
                                                                        // a8 89 c8 a6 
        for (int i = 0; i < x.size(); i++)
          showEstado(x[i]);
        break;
      }
      case 7:{
        string Clave, Origen;
        cout << "Introduzca la clave: " << endl;
        cin >> Clave;
        cout << "Introduzca el texto encriptado: " << endl;
        cin >> Origen;
        estado clave  = claveToEstado(Clave);
        showEstado(clave);
        estado origen = claveToEstado(Origen);
        cout << "Bloque final:" << endl;
        showEstado(invRijndael(origen, clave));
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
