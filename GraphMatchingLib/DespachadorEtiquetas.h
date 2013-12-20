#pragma once

#include <map>
#include <string>
#include <algorithm>
#include <memory>

#include "Etiqueta.h"

//Clase que se encarga de entregar etiquetas que ya han sido creadas.
//De no haber sido creada entonces se crea y la entrega.
//Se maneja de manera estática, porque así las referencias existirán hasta que el programa termine.
class DespachadorEtiquetas
{
private:
	//Constructor privado, sólo la funcion GetInstancia puede crear un objeto de ésta clase.
	DespachadorEtiquetas(void);
	//Se manejan las etiqutas atravez de un map para verificar si dicha etiqueta ya ha sido creada.
	std::map<std::string, std::shared_ptr<Etiqueta> > _coleccionEtiquetas;
public:
	//Deshabilitamos el constructor copia y el operador de asignación.
	DespachadorEtiquetas(const DespachadorEtiquetas&) = delete;
	DespachadorEtiquetas& operator=(const DespachadorEtiquetas&) = delete;

	//Destructor
	~DespachadorEtiquetas(void);
	//Método que nos regresa una etiqueta en base a un string
	//Si dicha etiqueta existe entonces regresa su referencia, de otra manera la crea en el map y regresa la referencia.
	const std::shared_ptr<Etiqueta>& GetEtiqueta(const std::string&);

	//Método para el manejo de Singleton, crea una instancia estática que es la que guardará todas las referencias.
	static DespachadorEtiquetas& GetInstancia();
};
