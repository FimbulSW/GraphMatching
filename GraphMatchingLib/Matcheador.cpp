#include "Matcheador.h"
#include "Grafo.h"
#include "Arco.h"


Matcheador::Matcheador(Grafo& Muestra, Grafo& Busqueda) : _muestra(Muestra), _busqueda(Busqueda)
{
}

Matcheador::~Matcheador()
{
}

bool Matcheador::EsCandidato(std::shared_ptr<Patron>& patron, 
							 const std::shared_ptr<Arco>& arcoMuestra, const std::shared_ptr<Arco>& arcoBusqueda)
{
	//Exploramos todos los arcos en nuestro patr�n.
	for (int i = 0, l = patron->ArcosGrafoMuestra.size(); i < l; i++)
	{
		//Si el arco de muestra o el de b�squeda ya se encuentran en el patr�n, entonces no son candidatos para entrar.
		if (arcoMuestra == patron->ArcosGrafoMuestra[i] || arcoBusqueda == patron->ArcosGrafoBusqueda[i]) return false;

		//Obtenemos si el arco de muestra y b�squeda son adyacentes o no con la posici�n actual de los arcos del patr�n.
		bool esMuestraAdyacente = _muestra.EsAdyacente(arcoMuestra, patron->ArcosGrafoMuestra[i]);
		bool esBusquedaAdyacente = _busqueda.EsAdyacente(arcoBusqueda, patron->ArcosGrafoBusqueda[i]);

		// Si es adyacente en uno tiene que serlo para el otro y viceversa, por lo que si sus valores son
		// distintos entonces no pueden ser candidatos.
		if (esMuestraAdyacente != esBusquedaAdyacente) return false;
	}
	//Si termina la iteraci�n quiere decir que ha pasado los filtros, por lo que s� es un candidato.
	return true;
}

void Matcheador::MarcaExpansionPatron(std::shared_ptr<Patron>& patron)
{
	// Obtenemos los arcos de la forma can�nica actual de nuestro grafo de muestra.
	auto arcosMuestra = _muestra.GetArcos();
	// Los exploramos todos.
	for (auto arcoMuestra : arcosMuestra)
	{
		// Exploramos todos los arcos de muestra que se encuentran dentro de nuestro patr�n
		for (auto arcoPatron : patron->ArcosGrafoMuestra)
		{
			// Si el arco de muestra es igual al arco del patr�n, entonces es expandible.
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
			// Creamos el nuevo patr�n, agregando la raiz y el arco de b�squeda como su primeros arcos.
			auto nuevoPatron = std::make_shared<Patron>();
			nuevoPatron->AgregarArcos(raiz, arcoBusqueda);
			// Dado que �ste arco ya ha sido matcheado con alg�n arco del grafo de b�squeda
			// lo pondremos como matcheado.
			arcoBusqueda->SetEstado(EstadoArco::MATCHEADO);
			// Por �ltimo agregamos el nuevo patr�n a nuestra colecci�n.
			_patrones.push_back(nuevoPatron);
		}
	}
}