#pragma once

#include <map>
#include <string>
#include <algorithm>
#include <memory>

#include "Etiqueta.h"

//Clase que se encarga de entregar etiquetas que ya han sido creadas.
//De no haber sido creada entonces se crea y la entrega.
//Se maneja de manera est�tica, porque as� las referencias existir�n hasta que el programa termine.
class DespachadorEtiquetas
{
private:
	//Constructor privado, s�lo la funcion GetInstancia puede crear un objeto de �sta clase.
	DespachadorEtiquetas(void);
	//Se manejan las etiqutas atravez de un map para verificar si dicha etiqueta ya ha sido creada.
	std::map<std::string, std::shared_ptr<Etiqueta> > _coleccionEtiquetas;
public:
	//Deshabilitamos el constructor copia y el operador de asignaci�n.
	DespachadorEtiquetas(const DespachadorEtiquetas&) = delete;
	DespachadorEtiquetas& operator=(const DespachadorEtiquetas&) = delete;

	//Destructor
	~DespachadorEtiquetas(void);
	//M�todo que nos regresa una etiqueta en base a un string
	//Si dicha etiqueta existe entonces regresa su referencia, de otra manera la crea en el map y regresa la referencia.
	const std::shared_ptr<Etiqueta>& GetEtiqueta(const std::string&);

	//M�todo para el manejo de Singleton, crea una instancia est�tica que es la que guardar� todas las referencias.
	static DespachadorEtiquetas& GetInstancia();
};
