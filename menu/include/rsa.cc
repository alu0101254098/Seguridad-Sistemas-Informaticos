#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>

typedef long long Dlong;

const int nPrimos = 50;

using namespace std;

Dlong mod2(Dlong x, Dlong mod2) {
  if (x < 0) {
    while (x < 0) {
      x += mod2;
    }
  } else {
    x %= mod2;
  }
  return x;
}

class RSA {
  private:
    Dlong _p, _q, _d, _fi, _n, _e, potencia;
    vector<Dlong> primerosPrimos = {2, 3, 5, 7, 11, 13, 17, 19};
	  string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    vector<Dlong> mensaje_codificado;
    vector<Dlong> mensaje_cifrado;
    string texto_origin;

  public:

    Dlong ExponenciacionRapida(Dlong a, Dlong b, Dlong m);
    Dlong EuclideExtendido(Dlong a, Dlong b);
    bool lehmanPeralta(Dlong p);
    vector<Dlong> codificarMensaje(string mensaje);
    string decodificarMensaje(Dlong mensaje);
    Dlong blockCypher(string block, Dlong blockSize);
    string blockDecypher(Dlong tmp, Dlong blockSize);
    void printData();
    void printDataSign();

    RSA(string mensaje, Dlong p, Dlong q, Dlong d);
    RSA(Dlong mensaje, Dlong ea, Dlong na);
    ~RSA(){}

    void execute();
};

RSA::RSA(string mensaje, Dlong p, Dlong q, Dlong d){
  // Comprobamos que sean primos
  assert(lehmanPeralta(p) && lehmanPeralta(q));

  // Calculamos fi, n y e 
  _fi = (p - 1) * (q - 1);
  _n = p * q;
  _d = d;
  _e = mod2(EuclideExtendido(d, _fi), _fi); // Inverso mod2 fi
  // Codificamos y encriptamos el mensaje
  codificarMensaje(mensaje);
}

RSA::RSA(Dlong mensaje, Dlong ea, Dlong na){

  potencia = ExponenciacionRapida(mensaje, ea, na);

}

void RSA::printData() {
  cout << "------------------------------------------------" << endl;
  cout << "Fi = " << _fi << endl; 
  cout << "N  = " << _n << endl;
  cout << "d  = " << _d << endl;
  cout << "e  = " << _e << endl;
  cout << "Mensaje codificado : " << "< ";
  for (long unsigned int i = 0; i < mensaje_codificado.size(); i++)
    cout << mensaje_codificado[i] << " ";
  cout << ">" << endl;
  cout << "Mensaje cifrado    : " << "< ";
  for (long unsigned int i = 0; i < mensaje_cifrado.size(); i++)
    cout << mensaje_cifrado[i] << " ";
  cout << ">" << endl;
  cout << "------------------------------------------------" << endl;
}

void RSA::printDataSign(){
  cout << "------------------------------------------------" << endl;
  cout << "Calculamos la potencia: " << potencia << endl;
  cout << "Decodificamos obteniendo el mensaje original: " << "<";
  cout << decodificarMensaje({potencia});
  cout << ">" << endl;
  cout << "------------------------------------------------" << endl;
}

vector<Dlong> RSA::codificarMensaje(string mensaje) {
  Dlong blockSize = (Dlong)std::log(_n) / (Dlong)std::log(alfabeto.size());
  cout << "Tamaño del bloque: " << blockSize << " | Genera " << mensaje.size() / blockSize << " bloques" << endl;

  // Rellenamos con X el tam no sea multiplo del tamaño de bloque
  if ((mensaje.size() % blockSize) == 0) {
    for (long unsigned int i = 0; i < mensaje.size() % blockSize; i++)
      mensaje.push_back('X');
  }

  vector<Dlong> out;

  Dlong temp;
  for (long unsigned int i = 0; i < mensaje.size(); i += blockSize)  {
    string block = mensaje.substr(i, blockSize);
    temp = blockCypher(block, blockSize);
    out.push_back(temp);
    // Aprovechamos que tenemos los valores de cada bloque para cifrarlos directamente
    mensaje_cifrado.push_back(ExponenciacionRapida(temp, _e, _n));
  }

  mensaje_codificado = out; // guardamos los datos en el atributo
  return out;
}
//Decofificaciom de RSA
string RSA::decodificarMensaje(Dlong mensaje){
  Dlong blockSize = (Dlong)std::log(_n) / (Dlong)std::log(alfabeto.size());
  string out = "";
  Dlong temp;
  temp = mensaje;
  out = blockDecypher(temp, blockSize);
  texto_origin = out;
  return out;
}

Dlong RSA::blockCypher(string block, Dlong blockSize) {
  Dlong out = 0;
  for (Dlong i = 0; i < blockSize; i++)
    out += ((block[i] == ' ')? alfabeto.find('X') : alfabeto.find(block[i])) * ExponenciacionRapida(alfabeto.size(), blockSize - (i + 1), _n);
  return out;
}

string RSA::blockDecypher(Dlong tmp, Dlong blockSize){
  string out = "";
  Dlong temp;
  for (Dlong i = 0; i < 1; i++) {
    temp = tmp % ExponenciacionRapida(alfabeto.size(), blockSize - (i + 1), _n);
    out += alfabeto[temp];
    tmp -= temp;
  }
  return out;
}

// Devuelve el numero de bytes que le faltan para completar
// un estado
Dlong RSA::ExponenciacionRapida(Dlong a, Dlong b, Dlong m) {
  Dlong x = 1;
  Dlong y = a % m;
  while (b > 0 && y > 1) {
    if (b%2 == 1) {
      x = (x * y) % m;
      b--;
    } else {
      y = (y * y) % m;
      b /= 2;
    }
  }
  return x;
}

Dlong RSA::EuclideExtendido(Dlong a, Dlong b) {

  Dlong x = 1, y = 0;
  Dlong xLast = 0, yLast = 1;
  Dlong q, r, m, n;
  while (a != 0) {
      q = b / a;
      r = b % a;
      m = xLast - q * x;
      n = yLast - q * y;
      xLast = x, yLast = y;
      x = m, y = n;
      b = a, a = r;
  }
  return xLast;
}

bool RSA::lehmanPeralta(Dlong p) {
	for (long unsigned int i = 0; i < primerosPrimos.size(); i++)
		if ((p % primerosPrimos[i] == 0) && (p != primerosPrimos[i]))
			return false;

	//Enteros aleatorios entre 2 y p-1
	std::vector<Dlong> randPrimes;

	for (Dlong i = 0; i < nPrimos; i++)
		randPrimes.push_back(2 + rand() %((p - 1) - 2));

	// Ai^((p-1)/2) % p. Todos deben dar 1, desde que 1 falle, no lo es.
	bool compuesto = true;
	for (long unsigned int i = 0; i < randPrimes.size(); i++)
		if (ExponenciacionRapida(randPrimes[i], (p - 1) / 2, p) != 1) {
			compuesto = false;
			break;
		}

	if (compuesto)
		return false;

	// Si existe un i tal que Ai^((p-1)/2) % p != -1, es compuesto.
	Dlong temp = 0;
	for (long unsigned int i = 0; i < randPrimes.size(); i++) {
		temp = ExponenciacionRapida(randPrimes[i], (p - 1) / 2, p);
		if (temp != 1)
			temp -= p;

		if ((temp != -1) && (temp != 1))
			return false;
	}

	return true;
}