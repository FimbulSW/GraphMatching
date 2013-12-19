#pragma once

#include <map>
#include <string>
#include <algorithm>
#include <memory>

#include "Etiqueta.h"

class DespachadorEtiquetas
{
private:
	DespachadorEtiquetas(void);
	std::map<std::string, std::shared_ptr<Etiqueta> > _coleccionEtiquetas;
	DespachadorEtiquetas(const DespachadorEtiquetas&);
	DespachadorEtiquetas& operator=(const DespachadorEtiquetas&);
public:
	~DespachadorEtiquetas(void);
	const std::shared_ptr<Etiqueta>& GetEtiqueta(const std::string&);
	static DespachadorEtiquetas& GetInstancia();
};
