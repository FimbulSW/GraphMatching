#include "Arco.h"
#include "Vertice.h"
#include "Etiqueta.h"
#include "DespachadorEtiquetas.h"
#include "LVEV.h"
#include "DespachadorLVEV.h"

Arco::Arco(const std::shared_ptr<Vertice>& v1, const std::shared_ptr<Vertice>& v2, const std::string& etiqueta)
	: _origen(nullptr), _destino(nullptr), _etiqueta(DespachadorEtiquetas::GetInstancia().GetEtiqueta(etiqueta)), _lvev(nullptr), _gradoAdyacencia(0)
{
	bool comparacion = *v1 < *v2;
	_origen = comparacion ? v1 : v2;
	_destino = comparacion ? v2 : v1;

	_vev = _origen->GetEtiqueta() + _etiqueta->_etiqueta + _destino->GetEtiqueta();
	_lvev = DespachadorLVEV::GetInstancia().GetLVEV(_origen->GetEtiqueta(), etiqueta, _destino->GetEtiqueta());

	CalcularGrado();
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
	return _gradoAdyacencia;
}

int Arco::GetFrecuencia() const
{
	return _lvev->GetFrecuencia();
}

const std::string& Arco::GetLVEVString() const
{
	return _lvev->GetLVEVString();
}

const std::shared_ptr<LVEV>& Arco::GetLVEV() const
{
	return _lvev;
}

void Arco::CalcularGrado()
{
	_gradoAdyacencia = _origen->GetEnumeracion() == _destino->GetEnumeracion() ? 
						_origen->GetGrado() - 1 :
						_origen->GetGrado() + _destino->GetGrado() - 2;
}

bool Arco::operator<(const Arco& otroArco) const 
{
	//TODO: Comparar los arcos en base a los siguientes puntos:
	//1) Grado de adyacencia de forma ascendente
	//2) Frecuencia de aparición de forma descendente
	//3) Orden lexicográfico.
	//4) Enumración de vértices.

	//Primero comparamos la adyacencia
	//Si nuestra adyacencia es menor a la del otro arco, entonces somos menores.
	if(this->GetGrado() < otroArco.GetGrado()) return true;

	//Si nuestra frecuencia es mayor a la del otro arco, entonces somos menores.
	if(this->GetFrecuencia() > otroArco.GetFrecuencia()) return true;

	//Si nuestra etiqueta es menor a la del otro arco, entonces somos menores.
	if(this->GetLVEVString() < otroArco.GetLVEVString()) return true;

	//Si la enumeracion de nuestro vértice origen es menor que la enumeración que el vértice
	//origen del otro arco, entonces somos menores.
	if(this->_origen->GetEnumeracion() < otroArco._origen->GetEnumeracion()) return true;

	//Si no entonces verificamos con los respectivos vértices destino.
	if(this->_destino->GetEnumeracion() < otroArco._destino->GetEnumeracion()) return true;

	//Si no funciona ninguna de las anteriores entonces somos mayores o iguales.
	return false;
}

bool Arco::operator==(const Arco& otroArco) const
{
	return _lvev == otroArco._lvev;
}

void Arco::CambiaEstado(EstadoArco estado)
{
	_estado = estado;
}