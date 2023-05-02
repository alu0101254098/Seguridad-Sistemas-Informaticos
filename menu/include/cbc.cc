#include "rijndael.cc"
using namespace std;

typedef vector<estado> CadenaBloques;

estado cadenaToEstado(string clave){

  if (clave.size() < 32) {
    for (int i = clave.size(); i <= 32; i++)
      clave += "0";
  }

  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);
  int count = 0;
  
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      out[i][j] = Byte(HexToBin1(clave.substr(count, 2)));
      count += 2;
    }
  }
  return out;
}

string estadoToCadena(estado e){
  string out;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out += BinHexACadena(e[j][i].to_string());
    }
  }
  return out;
}

// Devuelve el numero de bytes que le faltan para completar
// un estado
int emptyString(string s) {
  if (s.size() < 32) {
    return 32 - s.size();
  }
  int c = 0;
  for (long unsigned int i = 0; i < s.size(); i++) {
    if (s[i] == '-') {
      c++;
    }
  }
  return c;
}

CadenaBloques CBC(CadenaBloques plaintext, estado clave, estado IV) {

  CadenaBloques CipherTexts;
  CipherTexts.resize(plaintext.size());

  CipherTexts[0] = Rijndael(addRoundKey(plaintext[0], IV), clave);

  for (long unsigned int i = 1; i < plaintext.size(); i++) {

    CipherTexts[i] = Rijndael(addRoundKey(plaintext[i], CipherTexts[i - 1]), clave);

  }
  return CipherTexts;
}

CadenaBloques stealingCBC(CadenaBloques plaintext, estado clave, estado IV, int lastBytesLeft = 0) {

  CadenaBloques CipherTexts;
  CipherTexts.resize(plaintext.size());

  CipherTexts[0] = Rijndael(addRoundKey(plaintext[0], IV), clave);
  for (long unsigned int i = 1; i < plaintext.size() - 1; i++) {
    CipherTexts[i] = Rijndael(addRoundKey(plaintext[i], CipherTexts[i - 1]), clave);
  }

  // Las dos ultimas iteraciones las hacemos a mano
  int i = 1;
  estado lastState = Rijndael(addRoundKey(CipherTexts[i - 1], plaintext[i]), clave);
  string prevStateData = estadoToCadena(CipherTexts[i - 1]);

  // Intercambio de valores
  CipherTexts[i - 1] = lastState;     // Este encadenamiento de funciones, es para convertir un estado dado por filas a uno dado por columnas
  CipherTexts[i] = cadenaToEstado(prevStateData.erase(32 - lastBytesLeft));

  return CipherTexts;
}

void showCBCSecuence(CadenaBloques s) {
  for (long unsigned int i = 0; i < s.size(); i++) {
    cout << "Bloque " << i + 1 << " de texto cifrado" << endl;
    showEstado(s[i]);
    cout << estadoToCadena(s[i]) << endl;
  }
}