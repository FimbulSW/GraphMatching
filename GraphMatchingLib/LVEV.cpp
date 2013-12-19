#include "LVEV.h"
#include "Etiqueta.h"
#include "DespachadorEtiquetas.h"


LVEV::LVEV(const std::shared_ptr<Etiqueta>& origen, const std::shared_ptr<Etiqueta>& arco, const std::shared_ptr<Etiqueta>& destino)
: _origen(origen), _arco(arco), _destino(destino), _frecuencia(1), _lvevString(_origen->_etiqueta + _arco->_etiqueta + _destino->_etiqueta)
{
}

LVEV::LVEV(const std::string& origen, const std::string& arco, const std::string& destino)
	: LVEV(DespachadorEtiquetas::GetInstancia().GetEtiqueta(origen),
		   DespachadorEtiquetas::GetInstancia().GetEtiqueta(arco),
		   DespachadorEtiquetas::GetInstancia().GetEtiqueta(destino))
{
}

LVEV::~LVEV(void)
{
}


void LVEV::SetFrecuencia(int frecuencia)
{
	_frecuencia = frecuencia;
}

int LVEV::GetFrecuencia() const
{
	return _frecuencia;
}

bool LVEV::operator==(const LVEV& otroLVEV) const
{
	return this->_origen == otroLVEV._origen && this->_destino == otroLVEV._destino && this->_arco == otroLVEV._arco;
}

const std::string& LVEV::GetLVEVString() const
{
	return _lvevString;
}