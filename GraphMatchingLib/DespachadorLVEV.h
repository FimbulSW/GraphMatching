#pragma once

#include <memory>
#include <map>

class LVEV;
class Etiqueta;

class DespachadorLVEV
{
private:
	std::map<std::string, std::shared_ptr<LVEV> > _coleccionLVEV;
	DespachadorLVEV();
public:
	DespachadorLVEV(const DespachadorLVEV&) = delete;
	DespachadorLVEV& operator=(const DespachadorLVEV&) = delete;
	~DespachadorLVEV();

	//Devuelve una referencia a un LVEV que cumpla con el origen, arco y destino.
	//De no existir entonces lo crea, de otra manera regresa la instancia actual.
	std::shared_ptr<LVEV> GetLVEV(const std::shared_ptr<Etiqueta>&, const std::shared_ptr<Etiqueta>&, const std::shared_ptr<Etiqueta>&);
	//Devuelve una referencia a un LVEV que cumpla con el origen, arco y destino.
	//De no existir entonces lo crea, de otra manera regresa la instancia actual.
	std::shared_ptr<LVEV> GetLVEV(const std::string&, const std::string&, const std::string&);

	//Limpia todas las referencias hacia los LVEV almacenados
	//¡¡ADVERTENCIA!!
	//Sólo es utilizado para asuntos de pruebas, no usar nunca en resolución del algoritmo.
	void Vacia();

	//Nos regresa la instancia del despachador con ID 0, dado que él se encagargará de que sólo puedan existir una instancia por cada LVEV diferente
	//lo declaramos como static.
	static DespachadorLVEV& GetInstancia();

	//Nos regresa la instancia del despachador con el ID especificado, dado que él se encargará de que sólo puedan existir una instancia por cada LVEV diferente
	//lo declaramos como static.
	static DespachadorLVEV& GetInstancia(int);
};

