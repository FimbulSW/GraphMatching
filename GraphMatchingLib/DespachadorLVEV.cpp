#include "DespachadorLVEV.h"
#include "Etiqueta.h"
#include "DespachadorEtiquetas.h"
#include "LVEV.h"

DespachadorLVEV::DespachadorLVEV()
{
}


DespachadorLVEV::~DespachadorLVEV()
{
}

std::shared_ptr<LVEV> DespachadorLVEV::GetLVEV(const std::shared_ptr<Etiqueta>& origen, const std::shared_ptr<Etiqueta>& arco, const std::shared_ptr<Etiqueta>& destino)
{
	std::string lvevString = origen->_etiqueta + arco->_etiqueta + destino->_etiqueta;
	auto busqueda = _coleccionLVEV.find(lvevString);

	if (busqueda == _coleccionLVEV.end())
	{
		_coleccionLVEV[lvevString] = std::shared_ptr<LVEV>(new LVEV(origen, arco, destino));
		return _coleccionLVEV[lvevString];
	}
	
	busqueda->second->IncrementaFrecuencia();
	return busqueda->second;
}

std::shared_ptr<LVEV> DespachadorLVEV::GetLVEV(const std::string& origen, const std::string& arco, const std::string& destino)
{
	return GetLVEV(
		DespachadorEtiquetas::GetInstancia().GetEtiqueta(origen),
		DespachadorEtiquetas::GetInstancia().GetEtiqueta(arco),
		DespachadorEtiquetas::GetInstancia().GetEtiqueta(destino)
		);
}

DespachadorLVEV& DespachadorLVEV::GetInstancia()
{
	return GetInstancia(0);
}

DespachadorLVEV& DespachadorLVEV::GetInstancia(int id)
{
	static std::map<int, std::shared_ptr<DespachadorLVEV> > _despachadores;
	auto busqueda = _despachadores.find(id);

	if (busqueda == _despachadores.end())
	{
		_despachadores[id] = std::shared_ptr<DespachadorLVEV>(new DespachadorLVEV());
	}

	return *_despachadores[id];
}

void DespachadorLVEV::Vacia()
{
	_coleccionLVEV.clear();
}