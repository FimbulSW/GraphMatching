#pragma once

#include <deque>
#include <memory>
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <queue>

class Arco;
class Vertice;

//Funcion para comparar los punteros a arcos.
using ComparadorPunterosArcos = std::function<bool(const std::shared_ptr<Arco>&, const std::shared_ptr<Arco>& )>;
//Alias para la cola de prioridad de los arcos, utilizado para obtener la forma canónica.
using ColaPriorizadaArcos = std::priority_queue< std::shared_ptr<Arco>, std::deque<std::shared_ptr<Arco> >, ComparadorPunterosArcos >;

//Clase que representa un grafo.
class Grafo
{
private:
	//Colección de arcos.
	std::deque<std::shared_ptr<Arco> > _arcos;
	//Colección de vértices.
	std::map<int, std::shared_ptr<Vertice> > _vertices;
	//Arbol de adyacencia
	std::map<std::shared_ptr<Arco>, std::deque<std::shared_ptr<Arco> > > _listaAdyacencia;
	//Método para agregar arcos a la lista de adyacencia y aumenta el grado del vértice especificado.
	void AgregaALista(const std::shared_ptr<Arco>&, const std::shared_ptr<Arco>&, const std::shared_ptr<Vertice>&);
	//Método para agregar los sucesores de un arco a una cola priorizada.
	void AgregarSucesores(ColaPriorizadaArcos&, const std::deque<std::shared_ptr<Arco> >&);
	//Dado que un grafo no puede ser leído 2 veces necesitamos marcar una bandera.
	bool _leido;
	//Nombre del grafo.
	std::string _nombre;
	//ID del despachador de LVEV
	int _idDespachador;
	//¿Se ha calculado la forma canonica?
	bool _calculadaFormaCanonica;
	//Método auxiliar para calcular la forma canónica.
	void CalculaFormaCanonica();
	//Método auxiliar para calcular la forma canónica derivada.
	void CalculaFormaCanonicaDerivada();
public:
	//Constructor del grafo, necesitamos especificar un id del despachador de LVEV, de otra forma será por default 0.
	Grafo(int = 0);
	~Grafo();
	//Método para leer los datos del grafo a través de un flujo de entrada cualquiera.
	friend std::istream& operator >>(std::istream&, Grafo&);
	//Regresa los arcos pertenecientes al grafo.
	const std::deque<std::shared_ptr<Arco> >& GetArcos() const;
	//Ordena los arcos del grafo a través de las reglas de exploración de primero el mejor.
	//La primera vez que se invoque generará la forma canónica.
	//Si se invoca n veces se creará la (n-1)-ésima forma canónica derivada.
	void CreaFormaCanonica();
	//Devuelve el nombre del grafo.
	const std::string& GetNombre() const;
	//Devuelve una colección de arcos que son adyacentes al arco pasado por parámetro.
	const std::deque<std::shared_ptr<Arco> >& GetAdyacencia(const std::shared_ptr<Arco>&) const;
	//Método para determinar las adyacencias de los arcos.
	void ExploraGrafo();
};
