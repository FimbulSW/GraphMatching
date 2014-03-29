#include "Matcheador.h"
#include "Grafo.h"
#include "Arco.h"


Patron::Patron(int iteracion) : Expandible(true), Iteracion(iteracion) { }

Patron::Patron(Patron& patron) : Expandible(true), Iteracion(patron.Iteracion)
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


Matcheador::Matcheador(Grafo& Muestra, Grafo& Busqueda, bool loggear) : _muestra(Muestra), _busqueda(Busqueda), 
																		_hacerLog(loggear), _cuentaPatrones(0)
{
	salida = &std::cout;
}

Matcheador::~Matcheador()
{
}

bool Matcheador::EsCandidato(std::shared_ptr<Patron>& patron, 
							 const std::shared_ptr<Arco>& arcoMuestra, const std::shared_ptr<Arco>& arcoBusqueda)
{
	//Verifica si el candidato es adyacente al menos a un arco del patrón.
	bool esAdyacente = false;
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

		// Si no hay problema de consistencia y es adyacente en alguna parte del patrón entonces
		//
		if (esMuestraAdyacente == true) esAdyacente = true;
	}
	//Si termina la iteración quiere decir que ha pasado los filtros, por lo que sí es un candidato.
	return esAdyacente;
}

std::deque<std::shared_ptr<Arco> > Matcheador::FiltraCandidatos(std::shared_ptr<Patron>& patron, std::shared_ptr<Arco>& arcoMuestra, const std::deque<std::shared_ptr<Arco> >& arcosSimilares)
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

void Matcheador::ObtenerRaices(std::shared_ptr<Arco>& raiz, int iteracion)
{
	// Obtenemos todos los arcos que tengan el mismo lvev que la raiz.
	auto arcosBusqueda = _busqueda.GetArcos(raiz);
	int nuevosPatrones = 0;
	if(_hacerLog){
		*salida << "Se agregaran nuevas raices" << std::endl;
		*salida<<"---El numero actual de patrones es: "<<_cuentaPatrones<<std::endl;
	}

	for (auto arcoBusqueda : arcosBusqueda)
	{
		// Si no se encuentra matcheado...
		if (arcoBusqueda->GetEstado() != EstadoArco::MATCHEADO)
		{
			// Creamos el nuevo patrón, agregando la raiz y el arco de búsqueda como su primeros arcos.
			auto nuevoPatron = std::make_shared<Patron>(iteracion);
			nuevoPatron->AgregarArcos(raiz, arcoBusqueda);
			
			// Por último agregamos el nuevo patrón a nuestra colección.
			AgregarPatron(nuevoPatron);
			if(_hacerLog){
				nuevosPatrones++;
			}
		}
	}
	if(_hacerLog){
		*salida << "Terminada la iteracion de agregar nuevas raices" << std::endl;
		*salida<<"Se han agregado "<<nuevosPatrones<<" nuevos patrones en la busqueda de raices"<<std::endl;
	}
}

void Matcheador::ExpandirPatrones()
{
	//TODO:
	// Agregar el comportamiento adecuado para la expansión de patrones...

	for (int i = 0; i < _cuentaPatrones; i++)
	{
		if (_patrones[i]->Expandible)
		{
			if(_hacerLog){
				*salida<<"Se expandira el patron no: "<<i<<" de "<<_cuentaPatrones - 1<<std::endl;
			}
			ExpandirPatron(_patrones[i]);
		}
	}
}

void Matcheador::ExpandirPatron(std::shared_ptr<Patron>& patron)
{
	// Obtenemos la forma canónica actual.
	auto arcosMuestra = _muestra.GetArcos();
	// Iteramos sobre todos los arcos.
	for (auto arcoMuestra : arcosMuestra)
	{
		// Obtenemos todos los arcos que son posibles candidatos para matchear en el patrón actual.
		auto arcosCandidatos = FiltraCandidatos(patron, arcoMuestra, _busqueda.GetArcos(arcoMuestra));
		if(_hacerLog){
			*salida << "---Se han encontrado " << arcosCandidatos.size() << " candidatos para el arco: " << *arcoMuestra << std::endl;
		}
		// Si no hay ningún candidato entonces pasaremos al siguiente arco.
		if (arcosCandidatos.size() == 0)
		{
			continue;
		}
		// Si hay más de un sólo arco que puede ser candidato entonces tenemos que generar
		// patrones idénticos, pero cada uno matcheando a un candidato distinto.
		if (arcosCandidatos.size() > 1)
		{
			if(_hacerLog){
				*salida << "---Por lo que se crearan " << arcosCandidatos.size() - 1;
				if (arcosCandidatos.size() - 1 == 1)
					*salida << " nuevo patron." << std::endl;
				else
					*salida << " nuevos patrones." << std::endl;
			}
			CreaClones(patron, arcoMuestra, arcosCandidatos);
		}
		// Llegados a este punto sólo matcheamos los arcos correspondientes.
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

		if(_hacerLog){
			*salida << "------ Clon creado con arco: " << *candidatos[i] << std::endl;
		}

		AgregarPatron(nuevoPatron);
	}
}

int Matcheador::MatcheaGrafos()
{
	// Creamos la forma canónica de nuestro grafo de muestra, para poder
	// empezar nuestra búsqueda de patrones.
	_muestra.CreaFormaCanonica();
	auto arcosMuestra = _muestra.GetArcos();
	// Mientras no se encuentre vacío el grafo de búsqueda o
	// aún queden elementos en la forma canónica actual.
	
	int numeroIteraciones = 0;

	while (!_busqueda.Vacio() && arcosMuestra.size() > 0)
	{
		// Marcamos expansiones
		MarcaExpansiones();
		// Generamos nuevos patrones a partir de la raiz de la forma canónica actual.
		ObtenerRaices(arcosMuestra[0], numeroIteraciones + 1);
		// Expandimos los patrones.
		ExpandirPatrones();
		// Eliminamos todos los arcos que han sido matcheados en el grafo de búsqueda
		// ya que no se volverán a expandir.
		_busqueda.EliminaMatcheados();
		// Obtenemos la siguiente forma canónica derivada.
		_muestra.CreaFormaCanonica();
		arcosMuestra = _muestra.GetArcos();
		numeroIteraciones++;
	}
	return numeroIteraciones;
}

std::deque<std::shared_ptr<Patron> > Matcheador::GetPatrones(int soporte)
{
	std::deque<std::shared_ptr<Patron> > resultado;
	for (auto patron : _patrones)
	{
		if ((int)patron->ArcosGrafoBusqueda.size() >= soporte)
			resultado.push_back(patron);
	}
	return resultado;
}


void Matcheador::AgregarPatron(std::shared_ptr<Patron>& patron)
{
	_patrones.push_back(patron);
	_cuentaPatrones++;
}

void Matcheador::CambiaFlujo(std::ostream* flujo)
{
	if (flujo == nullptr) return;
	salida = flujo;
}