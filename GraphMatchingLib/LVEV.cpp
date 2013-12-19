#include "LVEV.h"
#include "Etiqueta.h"
#include "DespachadorEtiquetas.h"


LVEV::LVEV(const std::shared_ptr<Etiqueta>& origen, const std::shared_ptr<Etiqueta>& arco, const std::shared_ptr<Etiqueta>& destino)
	: _origen(origen), _arco(arco), _destino(destino), _frecuencia(1)
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
