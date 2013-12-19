#pragma once

#include <string>

//Clase que maneja las etiquetas.
//No puede instanciarse, la �nica manera de utilizarla es a trav�s de la clase DespachadorEtiqueta
class Etiqueta
{
private:
	//Constructor b�sico usado para generar la etiqueta.
	Etiqueta(const std::string&);
	//Constructor copia y operador de asignaci�n fueron quitados del API, para manejar una �nica instancia.
	Etiqueta(const Etiqueta&);
	Etiqueta& operator=(const Etiqueta&);
public:
	friend class DespachadorEtiquetas;
	std::string _etiqueta;
	~Etiqueta(void);
};
