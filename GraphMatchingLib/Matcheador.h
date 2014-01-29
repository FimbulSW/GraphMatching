#pragma once

#include <memory>
#include <deque>

class Arco;
class Grafo;

struct Patron
{
	int Offset;
	bool Expandible;
	std::deque<std::shared_ptr<Arco> > ArcosGrafoMuestra;
	std::deque<std::shared_ptr<Arco> > ArcosGrafoBusqueda;
	void AgregarArcos(std::shared_ptr<Arco>&, std::shared_ptr<Arco>&);
};

//Clase Matcheador. 
// Se encarga de buscar todos los posibles patrones de un grafo de muestra sobre un grafo de búsqueda.
// Complejidad NP			
class Matcheador
{
private:
	Grafo& _busqueda;
	Grafo& _muestra;

	std::deque<std::shared_ptr<Patron> > _patrones;

	// Muestra si el arco de muestra y de búsqueda son candidatos para entrar al patrón.
	bool EsCandidato(std::shared_ptr<Patron>&, const std::shared_ptr<Arco>&, const std::shared_ptr<Arco>&);
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

public:
	// Crea una instancia de matcheador.
	// El primer parámetro es el grafo de muestra, del cual se generarán sus formas canóncas.
	// El segundo parámetro es el grafo de búsqueda, en el cual se encontrarán los patrones.
	Matcheador(Grafo&, Grafo&);

	// Método que se encarga de encontrar los patrones del grafo de muestra con respecto al de búsqueda.
	// Complejidad NP.
	void MatcheaGrafos();

	~Matcheador();
};

