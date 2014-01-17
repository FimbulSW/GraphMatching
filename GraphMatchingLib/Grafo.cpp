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
	//Aplicar el algoritmo adecuado para la exploraci�n del grafo y determinar la adyacencia de los v�rtices.

	//Verificaremos cada arco con todos los dem�s para determinar cu�les est�n conectados.
	for (int i = 0, longitud = _arcos.size(); i < longitud; i++)
	{
		//Tomamos el i-�simo arco.
		auto& arcoBusqueda = _arcos[i];
		//Compararemos ese arco con todos los arcos siguientes.
		for (int j = i + 1; j < longitud; j++)
		{
			//Tomamos el j-�simo arco.
			auto& arcoEncontrado = _arcos[j];
			//Si ambos arcos son la misma instancia entonces continuamos.
			if (arcoBusqueda == arcoEncontrado) continue;

			//Obtenemos los respectivos v�rtices.
			auto& busquedaOrigen = arcoBusqueda->GetOrigen();
			auto& busquedaDestino = arcoBusqueda->GetDestino();
			auto& encontradoOrigen = arcoEncontrado->GetOrigen();
			auto& encontradoDestino = arcoEncontrado->GetDestino();

			//Si el origen de la b�squeda concuerda con el origen o destino del arco actual entonces
			//est�n conectados
			if (busquedaOrigen == encontradoOrigen || busquedaOrigen == encontradoDestino)
			{
				//De ser as� entonces llamamos AgregarALaLista
				AgregaALista(arcoBusqueda, arcoEncontrado, busquedaOrigen);
			}

			else if (busquedaDestino == encontradoOrigen || busquedaDestino == encontradoDestino)
			{
				AgregaALista(arcoBusqueda, arcoEncontrado, busquedaDestino);
			}
		}
	}

	//Una vez terminada la relaci�n entonces calcularemos el grado de los arcos.
	for (auto& arco : _arcos)
	{
		arco->CalcularGrado();
	}
}

void Grafo::AgregaALista(const std::shared_ptr<Arco>& origen, const std::shared_ptr<Arco>& destino, const std::shared_ptr<Vertice>& vertice)
{
	//Aumentamos el grado del v�rtice.
	vertice->SetGrado(vertice->GetGrado() + 1);
	//Agregamos a la lista de adyacencia la relaci�n de los respectivos arcos.
	_listaAdyacencia[origen].push_back(destino);
	_listaAdyacencia[destino].push_back(origen);
}

const std::deque<std::shared_ptr<Arco> >& Grafo::GetArcos() const
{
	return _arcos;
}

void Grafo::CreaFormaCanonica()
{
	//Crearemos 2 deque, uno para los sucesores y otro para la forma can�nica.
	std::deque<Arco> canonica, sucesores;
	//Ordenamos en base a la comparaci�n de los arcos.
	sort(_arcos.begin() + _offset, _arcos.end(), [](const std::shared_ptr<Arco>& a1, const std::shared_ptr<Arco>& a2)
	{
		return *a1 < *a2;
	}
	);

	//Obtenemos la referencia del primer arco que cumpla todas las condiciones.
	auto& arco = _arcos[_offset];

	//Si nuestro desplazamiento ya alcanza el final de nuestra  colecci�n entonces lo dejamos con su valor, de otra forma aumentaremos 1.
	_offset = _arcos.begin() + _offset == _arcos.end() ? _offset : _offset + 1;
}

std::istream& operator >>(std::istream& entrada, Grafo& g)
{
	//Podemos leer 2 posibles opciones:
	// v --- Crea un v�rtice, se espera leer: "enumeraci�n, NombreVertice"
	// e --- Crea un arco, se espera leer: "numeroVertice1, numeroVertice2, NombreArco"
	char opcion;
	//Leemos el nombre del arco
	getline(entrada, g._nombre);
	//Mientras tengamos datos que leer...
	while (entrada >> opcion)
	{
		//Si la opcion le�da es V
		if (opcion == 'v')
		{
			//Leemos el nombre (como cadena completa, con espacios)
			//Leemos la enumeraci�n.
			std::string nombreVertice;
			int enumeracion;
			entrada >> enumeracion;
			entrada.ignore();
			getline(entrada, nombreVertice);
			//Guardamos el v�rtice creado en nuestra colecci�n.
			g._vertices[enumeracion] = std::make_shared<Vertice>(nombreVertice, enumeracion);
		}
		//De otra forma ser�a un arco.
		else
		{
			//Leemos la enumeraci�n de los v�rtices que se juntan y el nombre del arco.
			int v1, v2;
			std::string nombreArco;
			entrada >> v1 >> v2;
			entrada.ignore();
			getline(entrada, nombreArco);
			//Generamos el arco y lo agregamos a nuestra colecci�n.
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