#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <map>

class Arco;
class Vertice;

//Clase que representa un grafo.
class Grafo
{
private:
	//Colecci�n de arcos.
	std::vector<std::shared_ptr<Arco> > _arcos;
	//Colecci�n de v�rtices.
	std::map<int, std::shared_ptr<Vertice> > _vertices;
	//M�todo para determinar las adyacencias de los v�rtices.
	void ExploraGrafo();
	//Desplazamiento desde el origen, va a ser �til para sacar las formas can�nicas derivadas.
	int _offset;
	//Dado que un grafo no puede ser le�do 2 veces necesitamos marcar una bandera.
	bool _leido;
	//Nombre del grafo.
	std::string _nombre;
	//ID del despachador de LVEV
	int _idDespachador;
public:
	//Constructor del grafo, necesitamos especificar un id del despachador de LVEV, de otra forma ser� por default 0.
	Grafo(int = 0);
	~Grafo();
	//M�todo para leer los datos del grafo a trav�s de un flujo de entrada cualquiera.
	friend std::istream& operator >>(std::istream&, Grafo&);
	//Regresa los arcos pertenecientes al grafo.
	const std::vector<std::shared_ptr<Arco> >& GetArcos() const;
	//Ordena los arcos del grafo a trav�s de las reglas de exploraci�n de primero el mejor.
	void CreaFormaCanonica();
	//Devuelve el nombre del grafo.
	const std::string& GetNombre() const;
};
