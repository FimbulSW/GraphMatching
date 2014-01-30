#include "Matcheador.h"
#include "Grafo.h"
#include "Arco.h"

#include <set>

Patron::Patron() : Expandible(true) { }

Patron::Patron(Patron& patron) : Expandible(true)
{
	ArcosGrafoMuestra = patron.ArcosGrafoMuestra;
	ArcosGrafoBusqueda = patron.ArcosGrafoBusqueda;
}

void Patron::AgregarArcos(std::shared_ptr<Arco>& arcoMuestra, std::shared_ptr<Arco>& arcoBusqueda)
{
	ArcosGrafoMuestra.push_back(arcoMuestra);
	ArcosGrafoBusqueda.push_back(arcoBusqueda);
	arcoBusqueda->SetEstado(EstadoArco::MATCHEADO);
}


Matcheador::Matcheador(Grafo& Muestra, Grafo& Busqueda) : _muestra(Muestra), _busqueda(Busqueda)
{
}

Matcheador::~Matcheador()
{
}

bool Matcheador::EsCandidato(std::shared_ptr<Patron>& patron, 
							 const std::shared_ptr<Arco>& arcoMuestra, const std::shared_ptr<Arco>& arcoBusqueda)
{
	//Exploramos todos los arcos en nuestro patrón.
	for (int i = 0, l = patron->ArcosGrafoMuestra.size(); i < l; i++)
	{
		//Si el arco de muestra o el de búsqueda ya se encuentran en el patrón, entonces no son candidatos para entrar.
		if (arcoMuestra == patron->ArcosGrafoMuestra[i] || arcoBusqueda == patron->ArcosGrafoBusqueda[i]) return false;

		//Obtenemos si el arco de muestra y búsqueda son adyacentes o no con la posición actual de los arcos del patrón.
		bool esMuestraAdyacente = _muestra.EsAdyacente(arcoMuestra, patron->ArcosGrafoMuestra[i]);
		bool esBusquedaAdyacente = _busqueda.EsAdyacente(arcoBusqueda, patron->ArcosGrafoBusqueda[i]);

		// Si es adyacente en uno tiene que serlo para el otro y viceversa, por lo que si sus valores son
		// distintos entonces no pueden ser candidatos.
		if (esMuestraAdyacente != esBusquedaAdyacente) return false;
	}
	//Si termina la iteración quiere decir que ha pasado los filtros, por lo que sí es un candidato.
	return true;
}

std::deque<std::shared_ptr<Arco> > Matcheador::FiltraCandidatos(std::shared_ptr<Patron>& patron, std::shared_ptr<Arco>& arcoMuestra, std::deque<std::shared_ptr<Arco> >& arcosSimilares)
{
	std::deque<std::shared_ptr<Arco> > resultado;
	for (auto arco : arcosSimilares)
	{ 
		if (EsCandidato(patron, arcoMuestra, arco))
			resultado.push_back(arco);
	}
	return resultado;
}

void Matcheador::MarcaExpansionPatron(std::shared_ptr<Patron>& patron)
{
	// Obtenemos los arcos de la forma canónica actual de nuestro grafo de muestra.
	auto arcosMuestra = _muestra.GetArcos();
	// Los exploramos todos.
	for (auto arcoMuestra : arcosMuestra)
	{
		// Exploramos todos los arcos de muestra que se encuentran dentro de nuestro patrón
		for (auto arcoPatron : patron->ArcosGrafoMuestra)
		{
			// Si el arco de muestra es igual al arco del patrón, entonces es expandible.
			if (arcoMuestra == arcoPatron)
			{
				patron->Expandible = true;
				return;
			}
		}
	}
	// De otra forma entonces no lo es.
	patron->Expandible = false;
}

void Matcheador::MarcaExpansiones()
{
	// Verificamos todos los patrones que son capaces de expandirse.
	for (auto patron : _patrones)
	{
		MarcaExpansionPatron(patron);
	}
}

void Matcheador::ObtenerRaices(std::shared_ptr<Arco>& raiz)
{
	// Obtenemos todos los arcos que tengan el mismo lvev que la raiz.
	auto arcosBusqueda = _busqueda.GetArcos(raiz);

	for (auto arcoBusqueda : arcosBusqueda)
	{
		// Si no se encuentra matcheado...
		if (arcoBusqueda->GetEstado() != EstadoArco::MATCHEADO)
		{
			// Creamos el nuevo patrón, agregando la raiz y el arco de búsqueda como su primeros arcos.
			auto nuevoPatron = std::make_shared<Patron>();
			nuevoPatron->AgregarArcos(raiz, arcoBusqueda);
			
			// Por último agregamos el nuevo patrón a nuestra colección.
			_patrones.push_back(nuevoPatron);
		}
	}
}

void Matcheador::ExpandirPatrones()
{
	//TODO:
	// Agregar el comportamiento adecuado para la expansión de patrones...

	auto inicioPatrones = _patrones.begin();
	for (int i = 0; inicioPatrones + i != _patrones.end(); i++)
	{
		if (_patrones[i]->Expandible)
			ExpandirPatron(_patrones[i]);
	}
}

void Matcheador::ExpandirPatron(std::shared_ptr<Patron>& patron)
{
	auto arcosMuestra = _muestra.GetArcos();
	for (auto arcoMuestra : arcosMuestra)
	{
		auto arcosCandidatos = FiltraCandidatos(patron, arcoMuestra, _busqueda.GetArcos(arcoMuestra));
		if (arcosCandidatos.size() == 0) continue;
		if (arcosCandidatos.size() > 1)
			CreaClones(patron, arcoMuestra, arcosCandidatos);
			
		patron->AgregarArcos(arcoMuestra, arcosCandidatos[0]);
	}
}

void Matcheador::CreaClones(std::shared_ptr<Patron>& patron, std::shared_ptr<Arco>& arcoMuestra, std::deque<std::shared_ptr<Arco> >& candidatos)
{
	// Exploramos todos los arcos que son posibles candidatos al arcoMuestra, excepto el 0
	// porque es el que le corresponde al patrón original.
	for (int i = 1, tamano = candidatos.size(); i < tamano; i++)
	{
		// Se crea un patrón copia
		auto nuevoPatron = std::make_shared<Patron>(*patron);
		// Se le asignan los respectivos arcos (muestra y búsqueda)
		nuevoPatron->AgregarArcos(arcoMuestra, candidatos[i]);

		_patrones.push_back(nuevoPatron);
	}
}

void Matcheador::MatcheaGrafos()
{
	_muestra.CreaFormaCanonica();
	auto arcosMuestra = _muestra.GetArcos();
	while (_busqueda.Vacio() || arcosMuestra.size() > 0)
	{
		MarcaExpansiones();
		ObtenerRaices(arcosMuestra[0]);
		ExpandirPatrones();
		_busqueda.EliminaMatcheados();
		_muestra.CreaFormaCanonica();
		arcosMuestra = _muestra.GetArcos();
	}
}

std::deque<std::shared_ptr<Patron> > Matcheador::GetPatrones(int soporte)
{
	std::deque<std::shared_ptr<Patron> > resultado;
	for (auto patron : _patrones)
	{
		if (patron->ArcosGrafoBusqueda.size() >= soporte)
			resultado.push_back(patron);
	}
	return resultado;
}