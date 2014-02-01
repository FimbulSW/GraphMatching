#include "Arco.h"
#include "Vertice.h"
#include "Etiqueta.h"
#include "DespachadorEtiquetas.h"
#include "LVEV.h"
#include "DespachadorLVEV.h"

Arco::Arco(const std::shared_ptr<Vertice>& v1, const std::shared_ptr<Vertice>& v2, const std::string& etiqueta, int idDespachador)
	//origen, destino y lvev se inician con nullptr porque primero tenemos que determinar de forma lexicográfica quién será nuestro
	//origen y destino, en ese momento se creará el lvev del arco.
	//etiqueta la inicializamos pidiéndole al despachador de etiquetas que nos provea de las mismas.
	: _origen(nullptr), _destino(nullptr), _lvev(nullptr), _etiqueta(DespachadorEtiquetas::GetInstancia().GetEtiqueta(etiqueta)), _gradoAdyacencia(0), _estado(EstadoArco::ESPERA)
{
	//Si el primer vértice es menor que el segundo entonces el origen será igual al primer vértice y el destino igual al segundo.
	//De lo contrario la asignación será inversa.
	bool comparacion = *v1 < *v2;
	_origen = comparacion ? v1 : v2;
	_destino = comparacion ? v2 : v1;

	//Se pide al despachador de LVEV que nos genere la etiqueta adecuada. Si existe entonces nos regresará la instancia actual aumentando su frecuencia en 1,
	//de otra manera creará la etiqueta y nos la regresará con frecuencia 1
	_lvev = DespachadorLVEV::GetInstancia(idDespachador).GetLVEV(_origen->GetEtiqueta(), etiqueta, _destino->GetEtiqueta());

	//Calculamos el grado de nuestro arco.
	CalcularGrado();
}

Arco::~Arco(void)
{
}

std::ostream& operator<<(std::ostream& salida, const Arco& arco)
{
	salida << arco.GetLVEVString() << " " << *arco._origen << " " << *arco._destino;
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
	//Si el arco es un bucle entonces sólo tomamos el grado del origen y le restamos 1.
	//Si no entonces sumamos los grados del origen y del destino y le restamos 2.
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
	else if (this->GetGrado() > otroArco.GetGrado()) return false;

	//Si nuestra frecuencia es mayor a la del otro arco, entonces somos menores.
	if(this->GetFrecuencia() > otroArco.GetFrecuencia()) return true;
	else if (this->GetFrecuencia() < otroArco.GetFrecuencia()) return false;

	//Si nuestra etiqueta es menor a la del otro arco, entonces somos menores.
	if(this->GetLVEVString() < otroArco.GetLVEVString()) return true;
	else if (otroArco.GetLVEVString() < this->GetLVEVString()) return false;

	//Si la enumeracion de nuestro vértice origen es menor que la enumeración que el vértice
	//origen del otro arco, entonces somos menores.
	if(this->_origen->GetEnumeracion() < otroArco._origen->GetEnumeracion()) return true;
	else if (this->_origen->GetEnumeracion() > otroArco._origen->GetEnumeracion()) return false;

	//Si no entonces verificamos con los respectivos vértices destino.
	if(this->_destino->GetEnumeracion() < otroArco._destino->GetEnumeracion()) return true;

	//Si no funciona ninguna de las anteriores entonces somos mayores o iguales.
	return false;
}

bool Arco::operator==(const Arco& otroArco) const
{
	return *_lvev == *otroArco._lvev;
}

EstadoArco Arco::GetEstado() const
{
	return _estado;
}

void Arco::SetEstado(EstadoArco estado)
{
	_estado = estado;
}