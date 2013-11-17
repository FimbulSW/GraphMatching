#include "Arco.h"
#include "Vertice.h"


Arco::Arco(const std::shared_ptr<Vertice>& v1, const std::shared_ptr<Vertice>& v2, const std::string& etiqueta)
	: _origen(nullptr), _destino(nullptr), _etiqueta(etiqueta)
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

bool Arco::operator<(const Arco& otroArco) const 
{
	//TODO: Comparar los arcos en base a los siguientes puntos:
	//1) Grado de adyacencia de forma ascendente
	//2) Frecuencia de aparición de forma descendente
	//3) Orden lexicográfico.
	//4) Enumración de vértices.

	//Primero comparamos la adyacencia
	//Si la adyacencia del otro arco es menor que la nuestra entonces somos menores.
	
	if(otroArco.GetGrado() < GetGrado()) return true;
	return false;
}