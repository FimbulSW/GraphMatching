#include "DespachadorEtiquetas.h"


DespachadorEtiquetas::DespachadorEtiquetas(void)
{
}


DespachadorEtiquetas::~DespachadorEtiquetas(void)
{
}

const std::shared_ptr<Etiqueta>& DespachadorEtiquetas::GetEtiqueta(const std::string& etiqueta)
{
	auto busqueda = _coleccionEtiquetas.find(etiqueta);
	if(busqueda == _coleccionEtiquetas.end())
	{
		_coleccionEtiquetas[etiqueta] = std::shared_ptr<Etiqueta>(new Etiqueta(etiqueta));
		busqueda = _coleccionEtiquetas.find(etiqueta);
	}
	return busqueda->second;
}

DespachadorEtiquetas& DespachadorEtiquetas::GetInstancia()
{
	static std::shared_ptr<DespachadorEtiquetas> instancia(new DespachadorEtiquetas());
	return *instancia;
}