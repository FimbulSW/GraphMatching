#include "Grafo.h"
#include "Arco.h"
#include "DespachadorLVEV.h"
#include "Vertice.h"

#include <algorithm>

Grafo::Grafo(int IdDespachador) : _idDespachador(IdDespachador), _leido(false), _nombre(), _calculadaFormaCanonica(false)
{
}


Grafo::~Grafo()
{
}

void Grafo::ExploraGrafo()
{
	//TODO:
	//Aplicar el algoritmo adecuado para la exploración del grafo y determinar la adyacencia de los vértices.

	//Verificaremos cada arco con todos los demás para determinar cuáles están conectados.
	for (int i = 0, longitud = _arcos.size(); i < longitud; i++)
	{
		//Tomamos el i-ésimo arco.
		auto& arcoBusqueda = _arcos[i];
		//Compararemos ese arco con todos los arcos siguientes.
		for (int j = i + 1; j < longitud; j++)
		{
			//Tomamos el j-ésimo arco.
			auto& arcoEncontrado = _arcos[j];
			//Si ambos arcos son la misma instancia entonces continuamos.
			if (arcoBusqueda == arcoEncontrado) continue;

			//Obtenemos los respectivos vértices.
			auto& busquedaOrigen = arcoBusqueda->GetOrigen();
			auto& busquedaDestino = arcoBusqueda->GetDestino();
			auto& encontradoOrigen = arcoEncontrado->GetOrigen();
			auto& encontradoDestino = arcoEncontrado->GetDestino();

			//Si el origen de la búsqueda concuerda con el origen o destino del arco actual entonces
			//están conectados
			if (busquedaOrigen == encontradoOrigen || busquedaOrigen == encontradoDestino)
			{
				//De ser así entonces llamamos AgregarALaLista
				AgregaALista(arcoBusqueda, arcoEncontrado, busquedaOrigen);
			}

			else if (busquedaDestino == encontradoOrigen || busquedaDestino == encontradoDestino)
			{
				AgregaALista(arcoBusqueda, arcoEncontrado, busquedaDestino);
			}
		}
	}

	//Una vez terminada la relación entonces calcularemos el grado de los arcos.
	for (auto& arco : _arcos)
	{
		arco->CalcularGrado();
	}
}

void Grafo::AgregaALista(const std::shared_ptr<Arco>& origen, const std::shared_ptr<Arco>& destino, const std::shared_ptr<Vertice>& vertice)
{
	//Aumentamos el grado del vértice.
	vertice->SetGrado(vertice->GetGrado() + 1);
	//Agregamos a la lista de adyacencia la relación de los respectivos arcos.
	_listaAdyacencia[origen].push_back(destino);
	_listaAdyacencia[destino].push_back(origen);
}

const std::deque<std::shared_ptr<Arco> >& Grafo::GetArcos() const
{
	return _arcos;
}

std::deque<std::shared_ptr<Arco> > Grafo::GetArcos(const std::shared_ptr<Arco>& busqueda) const
{
	std::deque<std::shared_ptr<Arco> > resultado;
	// Exploramos la lista de adyacencia
	for (auto it : _listaAdyacencia)
	{
		// Si el lvev de la lista es igual al lvev del arco entonces lo guardamos en el resultado.
		if (*it.first == *busqueda)
			resultado.push_back(it.first);
	}
	return resultado;
}

void Grafo::CreaFormaCanonica()
{
	//Si no hemos calculado la forma canónica...
	if (!_calculadaFormaCanonica)
		//Calculamos la forma canónica.
		CalculaFormaCanonica();
	//De otra manera...
	else
		//Calculamos la forma canónica derivada.
		CalculaFormaCanonicaDerivada();
	//Al terminar éste método al menos se ha calculado ya la forma canónica.
	_calculadaFormaCanonica = true;
}

void Grafo::CalculaFormaCanonica()
{
	//Crearemos un deque temporal para guardar nuestra forma canonica.
	std::deque<std::shared_ptr<Arco> > canonica;

	//Antes de comenzar pondremos todos los arcos en estado de espera, desde el _offset hasta el final de la lista.
	for (int i = 0, longitud = _arcos.size(); i < longitud; i++)
	{
		_arcos[i]->SetEstado(EstadoArco::ESPERA);
	}

	//Con ésta función ordenaremos tanto _arcos.
	ComparadorPunterosArcos funcionComparadora = [](const std::shared_ptr<Arco>& a1, const std::shared_ptr<Arco>& a2)
	{
		return *a1 < *a2;
	};

	//Con ésta funcion damos prioridad al priority_queue.
	ComparadorPunterosArcos funcionColaPrioridad = [](const std::shared_ptr<Arco>& a1, const std::shared_ptr<Arco>& a2)
	{
		return *a2 < *a1;
	};

	//Instancia de nuestra cola priorizada.
	ColaPriorizadaArcos colaSucesores(funcionColaPrioridad);

	//Ordenamos en base a la comparación de los arcos.
	sort(_arcos.begin(), _arcos.end(), funcionComparadora);

	//Obtenemos la referencia del primer arco que cumpla todas las condiciones.
	std::shared_ptr<Arco> arco = _arcos[0];

	//Agregamos el primero a la cola priorizada, ya sabemos que es la raiz de la forma canónica.
	colaSucesores.push(arco);

	//Mientras nuestra cola no esté vacía...
	while (!colaSucesores.empty())
	{
		//Obtenemos el primer arco en la cola, dado que está priorizada sabemos que es el mejor.
		arco = colaSucesores.top();
		colaSucesores.pop();

		//Antes de agregarlo a la forma canónica lo pondremos como visitado.
		arco->SetEstado(EstadoArco::VISITADO);

		//Agregamos el arco a la forma canónica.
		canonica.push_back(arco);
		//Agregamos a la cola de prioridad todos los adyacentes al arco.
		AgregarSucesores(colaSucesores, GetAdyacencia(arco));
	}

	//En este momento la forma canónica tiene todos los arcos del grafo, así que sólo igualamos _arcos a la forma canónica.
	_arcos = canonica;
}

void Grafo::CalculaFormaCanonicaDerivada()
{
	//Si la forma canónica anterior sólo tenía un arco, entonces la derivada es vacía.
	//Y por lo mismo ya no hace falta hacer más cálculos.
	if (_arcos.size() <= 1)
	{
		_arcos.clear();
		return;
	}

	//Crearemos un deque temporal para guardar nuestra forma canonica.
	std::deque<std::shared_ptr<Arco> > canonica;

	//Antes de comenzar pondremos todos los arcos en estado de espera, desde el _offset hasta el final de la lista.
	//Todos aquellos elementos que hayan matcheado se pasarán en ese mismo orden a la nueva forma canónica
	//y no se les cambiará su estado, seguirán siempre como matcheados.
	for (int i = 1, longitud = _arcos.size(); i < longitud; i++)
	{
		if (_arcos[i]->GetEstado() == EstadoArco::MATCHEADO)
		{
			canonica.push_back(_arcos[i]);
			continue;
		}
		_arcos[i]->SetEstado(EstadoArco::ESPERA);
	}
	//Si resulta que ninguno de los arcos logró hacer cumplir con algún patrón entonces tomaremos a la siguiente
	//posición de la forma canónica anterior como nuestra raiz nueva.
	if (canonica.size() == 0)
	{
		canonica.push_back(_arcos[1]);
	}

	//Con ésta funcion damos prioridad al priority_queue.
	ComparadorPunterosArcos funcionColaPrioridad = [](const std::shared_ptr<Arco>& a1, const std::shared_ptr<Arco>& a2)
	{
		return *a2 < *a1;
	};

	//Instancia de nuestra cola priorizada.
	ColaPriorizadaArcos colaSucesores(funcionColaPrioridad);

	//Exploraremos todos los arcos que se encuentren en la lista canónica, incluyendo los que se irán
	//agregando conforme se encuentren los adyacentes del mejor en turno.
	for (int i = 0; canonica.begin() + i != canonica.end(); i++)
	{
		AgregarSucesores(colaSucesores, GetAdyacencia(canonica[i]));

		if (colaSucesores.empty()) continue;

		std::shared_ptr<Arco> arco = colaSucesores.top();
		colaSucesores.pop();

		arco->SetEstado(EstadoArco::VISITADO);
		canonica.push_back(arco);
	}

	//En este momento la forma canónica tiene todos los arcos del grafo, así que sólo igualamos _arcos a la forma canónica.
	_arcos = canonica;
}

void Grafo::AgregarSucesores(ColaPriorizadaArcos& cola, const std::deque<std::shared_ptr<Arco> >& listaArcos)
{
	//Agregaremos a nuestra cola priorizada sólo aquellos arcos que no estén visitados
	for (auto arco : listaArcos)
	{
		if (arco->GetEstado() == EstadoArco::ESPERA)
		{
			arco->SetEstado(EstadoArco::LISTO);
			cola.push(arco);
		}
	}
}

std::istream& operator >>(std::istream& entrada, Grafo& g)
{
	//Podemos leer 2 posibles opciones:
	// v --- Crea un vértice, se espera leer: "enumeración, NombreVertice"
	// e --- Crea un arco, se espera leer: "numeroVertice1, numeroVertice2, NombreArco"
	char opcion;
	//Leemos el nombre del arco
	getline(entrada, g._nombre);
	//Mientras tengamos datos que leer...
	while (entrada >> opcion)
	{
		//Si la opcion leída es V
		if (opcion == 'v')
		{
			//Leemos el nombre (como cadena completa, con espacios)
			//Leemos la enumeración.
			std::string nombreVertice;
			int enumeracion;
			entrada >> enumeracion;
			entrada.ignore();
			getline(entrada, nombreVertice);
			//Guardamos el vértice creado en nuestra colección.
			g._vertices[enumeracion] = std::make_shared<Vertice>(nombreVertice, enumeracion);
		}
		//De otra forma sería un arco.
		else
		{
			//Leemos la enumeración de los vértices que se juntan y el nombre del arco.
			int v1, v2;
			std::string nombreArco;
			entrada >> v1 >> v2;
			entrada.ignore();
			getline(entrada, nombreArco);
			//Generamos el arco y lo agregamos a nuestra colección.
			auto arcoNuevo = std::make_shared<Arco>(g._vertices[v1], g._vertices[v2], nombreArco, g._idDespachador);
			g._arcos.push_back(arcoNuevo);
			g._listaAdyacencia[arcoNuevo].clear();
		}
	}
	return entrada;
}

bool Grafo::EsAdyacente(const std::shared_ptr<Arco>& arcoVerificar, const std::shared_ptr<Arco>& arcoBuscar) const
{
	//Buscamos si es que se encuentra el arco a verificar en el grafo.
	auto it = _listaAdyacencia.find(arcoVerificar);
	//De no ser así entonces no sabemos si es adyacente, por lo que regresamos false.
	if (it == _listaAdyacencia.end()) return false;
	
	auto adyacentes = it->second;
	for (auto arcoAdyacente : adyacentes)
	{
		//Si el arco a buscar se encuentra en la lista de adyacentes entonces retornamos true.
		if (arcoAdyacente == arcoBuscar) return true;
	}
	return false;
}

const std::string& Grafo::GetNombre() const
{
	return _nombre;
}

const std::deque<std::shared_ptr<Arco> >& Grafo::GetAdyacencia(const std::shared_ptr<Arco>& arco) const
{
	auto& lista = _listaAdyacencia.find(arco)->second;
	return lista;
}

void Grafo::EliminaArco(std::shared_ptr<Arco>& arco)
{
	//Encontramos el arco a eliminar
	auto it = _listaAdyacencia.find(arco);
	//Si ya no existe entonces salimos.
	if (it == _listaAdyacencia.end()) return;
	//De lo contrario lo eliminamos.
	_listaAdyacencia.erase(it);
}

void Grafo::EliminaMatcheados()
{
	//Buscamos en toda nuestra lista de arcos de búsqueda y eliminamos los matcheados.
	for (auto arco : _arcos)
	{
		if (arco->GetEstado() == EstadoArco::MATCHEADO)
		{
			EliminaArco(arco);
		}
	}
}

bool Grafo::Vacio() const
{
	return _listaAdyacencia.size() == 0;
}

int Grafo::TamanoAdyacencia() const
{
	return _listaAdyacencia.size();
}

bool Grafo::Existe(std::shared_ptr<Arco>& arco) const
{
	return _listaAdyacencia.find(arco) != _listaAdyacencia.end();
}