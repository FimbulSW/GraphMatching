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
// Se encarga de buscar todos los posibles patrones de un grafo de muestra sobre un grafo de b�squeda.
// Complejidad NP			
class Matcheador
{
private:
	Grafo& _busqueda;
	Grafo& _muestra;

	std::deque<std::shared_ptr<Patron> > _patrones;

	// Muestra si el arco de muestra y de b�squeda son candidatos para entrar al patr�n.
	bool EsCandidato(std::shared_ptr<Patron>&, const std::shared_ptr<Arco>&, const std::shared_ptr<Arco>&);
	// Marca como expandible al patr�n si alg�n arco del grafo de muestra concuerca con un elemento
	// del patr�n.
	void MarcaExpansionPatron(std::shared_ptr<Patron>&);

	//Marca la expansi�n de todos los patrones que se encuentren en el matcheador hasta ahora.
	void MarcaExpansiones();

	// Se busca todos aquellos arcos que se encuentran en el grafo de b�squeda y si alguno concuerda
	// con la raiz entonces se crea un nuevo patr�n.
	void ObtenerRaices(std::shared_ptr<Arco>&);

	// M�todo para encontrar arcos en el grafo de b�squeda con respecto al grafo de mu�stra.
	void ExpandirPatrones();

public:
	// Crea una instancia de matcheador.
	// El primer par�metro es el grafo de muestra, del cual se generar�n sus formas can�ncas.
	// El segundo par�metro es el grafo de b�squeda, en el cual se encontrar�n los patrones.
	Matcheador(Grafo&, Grafo&);

	// M�todo que se encarga de encontrar los patrones del grafo de muestra con respecto al de b�squeda.
	// Complejidad NP.
	void MatcheaGrafos();

	~Matcheador();
};

