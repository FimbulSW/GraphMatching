#pragma once

#include <memory>
#include <deque>
#include <iostream>

class Arco;
class Grafo;

struct Patron
{
	// Bandera para saber si el patr�n puede seguirse expandiendo o no.
	bool Expandible;

	// Lista de arcos del grafo de muestra.
	std::deque<std::shared_ptr<Arco> > ArcosGrafoMuestra;

	// Lista de arcos del grafo de b�squeda
	std::deque<std::shared_ptr<Arco> > ArcosGrafoBusqueda;

	// Agrega un arco de muestra y de b�squeda al patr�n.
	void AgregarArcos(std::shared_ptr<Arco>&, std::shared_ptr<Arco>&);

	// Constructor por default, pone el valor de Expandible a true.
	Patron();

	// Constructor copia, crea un patr�n id�ntico.
	Patron(Patron&);
};

//Clase Matcheador. 
// Se encarga de buscar todos los posibles patrones de un grafo de muestra sobre un grafo de b�squeda.
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


	// Muestra si el arco de muestra y de b�squeda son candidatos para entrar al patr�n.
	bool EsCandidato(std::shared_ptr<Patron>&, const std::shared_ptr<Arco>&, const std::shared_ptr<Arco>&);

	// Regresa la colecci�n de arcos que son candidatos para un patr�n en espec�fico.
	std::deque<std::shared_ptr<Arco> > FiltraCandidatos(std::shared_ptr<Patron>&, std::shared_ptr<Arco>&, const std::deque<std::shared_ptr<Arco> >&);

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

	// M�todo para expandir un patr�n en espec�fico.
	// Devuelve una colecci�n de arcos del grafo de b�squeda, para poder quitarlos
	void ExpandirPatron(std::shared_ptr<Patron>&);

	// Si llegamos a tener m�s de un s�lo arco que pueda ser candidato entonces tendremos que crear clones del patr�n
	// y a cada uno de ellos se les asignar� un arco diferente.
	void CreaClones(std::shared_ptr<Patron>&, std::shared_ptr<Arco>&, std::deque<std::shared_ptr<Arco> >&);

	void AgregarPatron(std::shared_ptr<Patron>&);

public:
	// Crea una instancia de matcheador.
	// El primer par�metro es el grafo de muestra, del cual se generar�n sus formas can�ncas.
	// El segundo par�metro es el grafo de b�squeda, en el cual se encontrar�n los patrones.
	Matcheador(Grafo&, Grafo&, bool = false);

	// M�todo que se encarga de encontrar los patrones del grafo de muestra con respecto al de b�squeda.
	// Complejidad NP.
	// Retorna el n�mero de iteraciones que tom� matchear los grafos.
	int MatcheaGrafos();

	void CambiaFlujo(std::ostream*);

	// Obtiene todos los patrones que tengan un soporte igual o mayor al del par�metro.
	std::deque<std::shared_ptr<Patron> > GetPatrones(int);

	virtual ~Matcheador();
};

