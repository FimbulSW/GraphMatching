#pragma once

#include <string>

//Clase que maneja las etiquetas.
//No puede instanciarse, la única manera de utilizarla es a través de la clase DespachadorEtiqueta
class Etiqueta
{
private:
	//Constructor básico usado para generar la etiqueta.
	Etiqueta(const std::string&);
	//Constructor copia y operador de asignación fueron quitados del API, para manejar una única instancia.
	Etiqueta(const Etiqueta&);
	Etiqueta& operator=(const Etiqueta&);
public:
	friend class DespachadorEtiquetas;
	std::string _etiqueta;
	~Etiqueta(void);
};
