#pragma once

#include <string>

//Clase que maneja las etiquetas.
//No puede instanciarse, la �nica manera de utilizarla es a trav�s de la clase DespachadorEtiqueta
class Etiqueta
{
private:
	//Constructor b�sico usado para generar la etiqueta.
	Etiqueta(const std::string&);
public:
	//Se declara como clase amiga a DespachadorEtiquetas, as� ser� la �nica clase capaz de instanciar a Etiqueta.
	friend class DespachadorEtiquetas;

	//Constructor copia y operador de asignaci�n fueron quitados del API, para manejar una �nica instancia.
	Etiqueta(const Etiqueta&) = delete;
	Etiqueta& operator=(const Etiqueta&) = delete;

	std::string _etiqueta;
	~Etiqueta(void);
};
