#include "Arco.h"
#include "Vertice.h"


Arco::Arco(const std::shared_ptr<Vertice>& v1, const std::shared_ptr<Vertice>& v2, const std::string& etiqueta)
	: _origen(nullptr), _destino(nullptr), _etiqueta(etiqueta), _gradoAdyacencia(0), _frecuencia(0)
{
	bool comparacion = *v1 < *v2;
	_origen = comparacion ? v1 : v2;
	_destino = comparacion ? v2 : v1;

	_vev = _origen->GetEtiqueta() + _etiqueta + _destino->GetEtiqueta();
}


Arco::~Arco(void)
{
}

std::ostream& operator<<(std::ostream& salida, const Arco& arco)
{
	salida<<"Arco con etiqueta: "<<arco._etiqueta<<std::endl;
	salida<<"Origen: "<<*arco._origen<<std::endl;
	salida<<"Destino: "<<*arco._destino<<std::endl;
	return salida;
}

const std::shared_ptr<Vertice>& Arco::GetOrigen()
{
	return _origen;
}

const std::shared_ptr<Vertice>& Arco::GetDestino()
{
	return _destino;
}

int Arco::GetGrado() const
{
	//TODO: aplicar un algoritmo para determinar la adyacencia del arco.
	return 0;
}

int Arco::GetFrecuencia() const
{
	return _frecuencia;
}

const std::string& Arco::GetLVEV() const
{
	return _vev;
}

bool Arco::operator<(const Arco& otroArco) const 
{
	//TODO: Comparar los arcos en base a los siguientes puntos:
	//1) Grado de adyacencia de forma ascendente
	//2) Frecuencia de aparici�n de forma descendente
	//3) Orden lexicogr�fico.
	//4) Enumraci�n de v�rtices.

	//Primero comparamos la adyacencia
	//Si nuestra adyacencia es menor a la del otro arco, entonces somos menores.
	if(this->GetGrado() < otroArco.GetGrado()) return true;

	//Si nuestra frecuencia es mayor a la del otro arco, entonces somos menores.
	if(this->GetFrecuencia() > otroArco.GetFrecuencia()) return true;

	//Si nuestra etiqueta es menor a la del otro arco, entonces somos menores.
	if(this->GetLVEV() < otroArco.GetLVEV()) return true;

	//Si la enumeracion de nuestro v�rtice origen es menor que la enumeraci�n que el v�rtice
	//origen del otro arco, entonces somos menores.
	if(this->_origen->GetEnumeracion() < otroArco._origen->GetEnumeracion()) return true;

	//Si no entonces verificamos con los respectivos v�rtices destino.
	if(this->_destino->GetEnumeracion() < otroArco._destino->GetEnumeracion()) return true;

	//Si no funciona ninguna de las anteriores entonces somos mayores o iguales.
	return false;
}