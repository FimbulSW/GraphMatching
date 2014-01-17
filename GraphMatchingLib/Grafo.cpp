#include "Grafo.h"
#include "Arco.h"
#include "DespachadorLVEV.h"
#include "Vertice.h"

#include <algorithm>

Grafo::Grafo(int IdDespachador) : _idDespachador(IdDespachador), _offset(0), _leido(false), _nombre()
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

void Grafo::CreaFormaCanonica()
{
	//Crearemos 2 deque, uno para los sucesores y otro para la forma canónica.
	std::deque<Arco> canonica, sucesores;
	//Ordenamos en base a la comparación de los arcos.
	sort(_arcos.begin() + _offset, _arcos.end(), [](const std::shared_ptr<Arco>& a1, const std::shared_ptr<Arco>& a2)
	{
		return *a1 < *a2;
	}
	);

	//Obtenemos la referencia del primer arco que cumpla todas las condiciones.
	auto& arco = _arcos[_offset];

	//Si nuestro desplazamiento ya alcanza el final de nuestra  colección entonces lo dejamos con su valor, de otra forma aumentaremos 1.
	_offset = _arcos.begin() + _offset == _arcos.end() ? _offset : _offset + 1;
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

const std::string& Grafo::GetNombre() const
{
	return _nombre;
}

const std::deque<std::shared_ptr<Arco> >& Grafo::GetAdyacencia(const std::shared_ptr<Arco>& arco) const
{
	auto& lista = _listaAdyacencia.find(arco)->second;
	return lista;
}