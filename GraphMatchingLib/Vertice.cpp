#include "Vertice.h"

Vertice::Vertice(const std::string& etiqueta, int enumeracion) 
	: _etiqueta(etiqueta), _enumeracion(enumeracion), _grado(0)
{
}


Vertice::~Vertice(void)
{
}

const std::string& Vertice::GetEtiqueta() const
{
	return _etiqueta;
}

int Vertice::GetEnumeracion() const
{
	return _enumeracion;
}

int Vertice::GetGrado() const
{
	return _grado;
}

void Vertice::SetGrado(int grado)
{
	_grado = grado;
}

std::ostream& operator <<(std::ostream& salida, const Vertice& v)
{
	//El formato de salida que se le dar� es del tipo:
	//Etiqueta\tEnumeraci�n\tGrado
	salida<<v._etiqueta<<"\t"<<v._enumeracion<<"\t"<<v._grado;
	return salida;
}

bool Vertice::operator <(const Vertice& v) const
{
	return _etiqueta < v._etiqueta;
}