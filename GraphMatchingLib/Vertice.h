#pragma once

#include <string>
#include <iostream>

//Clase que determina el comportamiento de un v�rtice.
//Es el componente b�sico del grafo.
class Vertice
{
public:
	//Constructor que otorga la etiqueta y enumeraci�n del v�rtice.
	//Por default el grado del v�rtice ser� 0.
	Vertice(const std::string&, int);
	~Vertice(void);

	//Obtenemos una referencia hacia la etiqueta
	const std::string& GetEtiqueta() const;
	//Obtenemos su enumeraci�n.
	int GetEnumeracion() const;
	//Obtenemos su grado.
	int GetGrado() const;
	//Modificamos el grado de adyacencia.
	void SetGrado(int);
	//Modificamos el operador '<' para poder hacer comparaciones.
	//�sto servir� luego para poder ordenar los arcos.
	bool operator < (const Vertice&) const;
	//Modificamos el operador '<<' para los objetos de tipo ostream
	//De esta forma podemos mandar la informaci�n a cualquier tipo de flujo de salida.
	friend std::ostream& operator<<(std::ostream&, const Vertice&);

private:
	std::string _etiqueta;
	int _enumeracion;
	int _grado;
};

