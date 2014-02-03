#pragma once

#include <memory>
#include <deque>
#include <iostream>

class Arco;
class Grafo;

struct Patron
{
	// Bandera para saber si el patrón puede seguirse expandiendo o no.
	bool Expandible;

	// Lista de arcos del grafo de muestra.
	std::deque<std::shared_ptr<Arco> > ArcosGrafoMuestra;

	// Lista de arcos del grafo de búsqueda
	std::deque<std::shared_ptr<Arco> > ArcosGrafoBusqueda;

	// Agrega un arco de muestra y de búsqueda al patrón.
	void AgregarArcos(std::shared_ptr<Arco>&, std::shared_ptr<Arco>&);

	// Constructor por default, pone el valor de Expandible a true.
	Patron();

	// Constructor copia, crea un patrón idéntico.
	Patron(Patron&);
};

//Clase Matcheador. 
// Se encarga de buscar todos los posibles patrones de un grafo de muestra sobre un grafo de búsqueda.
// Complejidad NP			
class Matcheador
{
protected:
	Grafo& _busqueda;
	Grafo& _muestra;
	std::ostream* salida;

	int _cuentaPatrones;
	bool _hacerLog;

	std::deque<std::shared_ptr<Patron> > _patrones;


	// Muestra si el arco de muestra y de búsqueda son candidatos para entrar al patrón.
	bool EsCandidato(std::shared_ptr<Patron>&, const std::shared_ptr<Arco>&, const std::shared_ptr<Arco>&);

	// Regresa la colección de arcos que son candidatos para un patrón en específico.
	std::deque<std::shared_ptr<Arco> > FiltraCandidatos(std::shared_ptr<Patron>&, std::shared_ptr<Arco>&, const std::deque<std::shared_ptr<Arco> >&);

	// Marca como expandible al patrón si algún arco del grafo de muestra concuerca con un elemento
	// del patrón.
	void MarcaExpansionPatron(std::shared_ptr<Patron>&);

	//Marca la expansión de todos los patrones que se encuentren en el matcheador hasta ahora.
	void MarcaExpansiones();

	// Se busca todos aquellos arcos que se encuentran en el grafo de búsqueda y si alguno concuerda
	// con la raiz entonces se crea un nuevo patrón.
	void ObtenerRaices(std::shared_ptr<Arco>&);

	// Método para encontrar arcos en el grafo de búsqueda con respecto al grafo de muéstra.
	void ExpandirPatrones();

	// Método para expandir un patrón en específico.
	// Devuelve una colección de arcos del grafo de búsqueda, para poder quitarlos
	void ExpandirPatron(std::shared_ptr<Patron>&);

	// Si llegamos a tener más de un sólo arco que pueda ser candidato entonces tendremos que crear clones del patrón
	// y a cada uno de ellos se les asignará un arco diferente.
	void CreaClones(std::shared_ptr<Patron>&, std::shared_ptr<Arco>&, std::deque<std::shared_ptr<Arco> >&);

	void AgregarPatron(std::shared_ptr<Patron>&);

public:
	// Crea una instancia de matcheador.
	// El primer parámetro es el grafo de muestra, del cual se generarán sus formas canóncas.
	// El segundo parámetro es el grafo de búsqueda, en el cual se encontrarán los patrones.
	Matcheador(Grafo&, Grafo&, bool = false);

	// Método que se encarga de encontrar los patrones del grafo de muestra con respecto al de búsqueda.
	// Complejidad NP.
	// Retorna el número de iteraciones que tomó matchear los grafos.
	int MatcheaGrafos();

	void CambiaFlujo(std::ostream*);

	// Obtiene todos los patrones que tengan un soporte igual o mayor al del parámetro.
	std::deque<std::shared_ptr<Patron> > GetPatrones(int);

	virtual ~Matcheador();
};

