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

	//Por cada vértice que se encuentra en el map
	for (auto& parVertices : _vertices)
	{
		//Se asigna la referencia.
		auto& vertice = parVertices.second;

		//Comparamos en cada arco si el vértice aparece ya sea en su origen o en su destino.
		for (auto& arco : _arcos)
		{
			if (arco->GetOrigen() == vertice || arco->GetDestino() == vertice)
			{
				vertice->SetGrado(vertice->GetGrado() + 1);
			}
		}
	}

	//Ya que hemos calculado el grado de los vértices, ahora calculamos el grado de los arcos.
	for (auto& arco : _arcos)
	{
		arco->CalcularGrado();
	}
}

const std::deque<std::shared_ptr<Arco> >& Grafo::GetArcos() const
{
	return _arcos;
}

void Grafo::CreaFormaCanonica()
{
	//Ordenamos en base a la comparación de los arcos.
	sort(_arcos.begin() + _offset, _arcos.end(), [](const std::shared_ptr<Arco>& a1, const std::shared_ptr<Arco>& a2)
	{
		return *a1 < *a2;
	}
	);
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
			g._arcos.push_back(std::make_shared<Arco>(g._vertices[v1], g._vertices[v2], nombreArco, g._idDespachador));
		}
	}
	return entrada;
}

const std::string& Grafo::GetNombre() const
{
	return _nombre;
}