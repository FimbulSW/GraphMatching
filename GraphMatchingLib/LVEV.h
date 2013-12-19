#pragma once

#include <memory>
#include <iostream>

class Etiqueta;

class LVEV
{
private:
	//Constructor b�sico de LVEV, toma como par�metros:
	//1) Etiqueta de origen.
	//2) Etiqueta del arco.
	//3) Etiqueta de destino.
	LVEV(const std::shared_ptr<Etiqueta>&, const std::shared_ptr<Etiqueta>&, const std::shared_ptr<Etiqueta>&);

	//Constructor sencillo de LVEV
	//El orden es el mismo que el primero.
	LVEV(const std::string&, const std::string&, const std::string&);
	
	std::shared_ptr<Etiqueta> _origen;
	std::shared_ptr<Etiqueta> _destino;
	std::shared_ptr<Etiqueta> _arco;

	std::string _lvevString;

	int _frecuencia;
public:
	//Declaramos a DespachadorLVEV como clase amiga, de �sta forma ser� la �nica capaz de crear instancias de LVEV
	friend class DespachadorLVEV;

	//Quitamos de uso al constructor copia y al operador de asignaci�n.
	LVEV& operator=(const LVEV&) = delete;
	LVEV(const LVEV&) = delete;

	~LVEV(void);
	//Cambia la frecuencia de nuestro LVEV
	void SetFrecuencia(int);

	//Obtenemos la frecuencia de nuestro LVEV
	int GetFrecuencia() const;

	//Sobrecargamos el operador == sobre los LVEV para preguntar sobre las referencias origen, arco y destino.
	bool operator==(const LVEV&) const;

	//Devolvemos la forma de cadena del LVEV
	const std::string& GetLVEVString() const;
};

