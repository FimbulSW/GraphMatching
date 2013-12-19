#pragma once

#include <string>

//Clase que maneja las etiquetas.
//No puede instanciarse, la única manera de utilizarla es a través de la clase DespachadorEtiqueta
class Etiqueta
{
private:
	//Constructor básico usado para generar la etiqueta.
	Etiqueta(const std::string&);
public:
	//Se declara como clase amiga a DespachadorEtiquetas, así será la única clase capaz de instanciar a Etiqueta.
	friend class DespachadorEtiquetas;

	//Constructor copia y operador de asignación fueron quitados del API, para manejar una única instancia.
	Etiqueta(const Etiqueta&) = delete;
	Etiqueta& operator=(const Etiqueta&) = delete;

	std::string _etiqueta;
	~Etiqueta(void);
};
