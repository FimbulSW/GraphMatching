// GraphMatchingThesis.cpp : Defines the entry point for the console application.
//

#include "Vertice.h"
#include "Arco.h"
#include "Grafo.h"
#include "Matcheador.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <memory>
#include <utility>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

const int parametrosMinimos = 4;

// Alias para el tipo de dato set, con una comparación personalizada.
using SetVertices = set < shared_ptr<Vertice>, function < bool(const shared_ptr<Vertice>&, const shared_ptr<Vertice>&) > >;

// Imprime en el formato de subdue.
void ImpresionPatron(ostream& salida, shared_ptr<Patron>& patron)
{
	// Creamos un conjunto de vértices, de esta forma no se van a repetir durante la impresión.
	// Los ordenaremos en base a su enumeración.
	SetVertices setVertices([](const shared_ptr<Vertice>& v1, const shared_ptr<Vertice>& v2)
		{
			return v1->GetEnumeracion() < v2->GetEnumeracion();
		}
	);

	// Conjunto de arcos, igual para no repetir arcos en la impresión.
	set<shared_ptr<Arco> > setArcos;
	
	// Agregamos a nuestros conjuntos todos los vértices y arcos que se encuentran en el patrón.
	for (int i = 0, tam = patron->ArcosGrafoBusqueda.size(); i < tam; i++)
	{
		// Insertamos el vértice de origen.
		setVertices.insert(patron->ArcosGrafoBusqueda[i]->GetOrigen());
		// Insertamos el vértice de destino.
		setVertices.insert(patron->ArcosGrafoBusqueda[i]->GetDestino());

		// Insertamos el arco que se desplegará.
		setArcos.insert(patron->ArcosGrafoBusqueda[i]);
	}

	// Imprimimos todos los vértices en el mismo formato que subdue.
	for (auto vertice : setVertices)
	{
		//    v Enumeracion Etiqueta
		salida << "   v " << vertice->GetEnumeracion() << " " << vertice->GetEtiqueta() << endl;
	}

	// Imprimimos todos los arcos en el mismo formato que subdue.
	for (auto arco : setArcos)
	{
		//    u EnumeracionOrigen EnumeracionDestino Etiqueta
		salida << "   u " << arco->GetOrigen()->GetEnumeracion()
			<< " " << arco->GetDestino()->GetEnumeracion() << " " << arco->GetEtiqueta() << endl;
	}
}

int main(int argc, char** argv)
{
	// Se requieren mínimamente 4 parámetros para correr el programa.
	if (argc < parametrosMinimos)
	{
		cerr << "Numero de parametros invalido, minimamente tiene que tener:" << endl;
		cerr << "1) Direccion del grafo de muestra." << endl;
		cerr << "2) Direccion del grafo de busqueda." << endl;
		cerr << "3) Direccion del archivo de salida." << endl;
		cerr << "4) Tamanio de los patrones. (opcional, numero entero)." << endl;

		cerr << endl << "----Ejemplo----" << endl;
		cerr << "Sistemas LINUX-like:" << endl;
		cerr << "./GraphMatchingThesis GrafoMuestra.g GrafoBusqueda.g Resultados.log 8" << endl;
		cerr << "Sistemas WINDOWS:" << endl;
		cerr << "GraphMatchingThesis.exe GrafoMuestra.g GrafoBusqueda.g Resultados.log 8" << endl;
		
		return 1;
	}

	int tamanio = 1;


	// Verificamos que no nos den números negativos o letras en el parámetro de tamaño.
	if (argc > parametrosMinimos)
	{
		stringstream ss(argv[parametrosMinimos]);
		ss >> tamanio;
		if (ss.fail() || tamanio <= 0)
		{
			cerr << "El tamanio tiene que ser un numero entero positivo mayor a 0." << endl;
			return 1;
		}
	}
	// Flujos de entrada y salida.
	ifstream flujoGrafoMuestra(argv[1]);
	ifstream flujoGrafoBusqueda(argv[2]);
	ofstream flujoSalida(argv[3]);


	// Creamos los grafos, el de muestra con despachador 0 y el de búsqueda con despachador 1.
	// Ésto para poder comparar referencias del LVEV pero sin afectar las frecuencias.
	Grafo grafoMuestra;
	Grafo grafoBusqueda(1);

	// Llenamos los grafos con la información de los flujos.
	flujoGrafoMuestra >> grafoMuestra;
	flujoGrafoBusqueda >> grafoBusqueda;

	// Cerramos los flujos de entrada, para evitar posibles problemas.
	flujoGrafoMuestra.close();
	flujoGrafoBusqueda.close();

	// Se inicia la exploración de los grafos.
	grafoMuestra.ExploraGrafo();
	grafoBusqueda.ExploraGrafo();

	// Se crea el matcheador, pasándole los grafos de muestra y búsqueda.
	Matcheador matcher(grafoMuestra, grafoBusqueda);

	// Tomamos el tiempo antes de comenzar la ejecución del algoritmo.
	steady_clock::time_point inicio = steady_clock::now();

	int iteraciones = matcher.MatcheaGrafos();

	// Tomamos el tiempo después de terminada la ejecución del algoritmo.
	steady_clock::time_point fin = steady_clock::now();

	// Obtenemos todos los patrones que tengan un tamaño mayor o igual al del parámetro.
	auto patrones = matcher.GetPatrones(tamanio);

	/* Quitamos la ordenación, para mostrar los patrones en orden de iteración.
	sort(patrones.begin(), patrones.end(), [](const shared_ptr<Patron> p1, const shared_ptr<Patron> p2)
	{
		return p1->ArcosGrafoBusqueda.size() < p2->ArcosGrafoBusqueda.size();
	}
	);*/

	// Empezamos a mostrar el reporte.
	flujoSalida << "Se han encontrado " << patrones.size() << " patrones con tamanio " << tamanio << endl << endl;
	for (int i = 0, tam = patrones.size(); i < tam; i++)
	{
		flujoSalida << "(" << i + 1 << ") " << "tamano: " << patrones[i]->ArcosGrafoBusqueda.size()
			<<" creado en iteracion: "<<patrones[i]->Iteracion << endl;
		ImpresionPatron(flujoSalida, patrones[i]);

		flujoSalida << endl;
/*
		flujoSalida << "  ( " << i + 1 << " ) " << "de tamano: " << patrones[i]->ArcosGrafoBusqueda.size() << endl;
		for (auto arco : patrones[i]->ArcosGrafoBusqueda)
		{
			flujoSalida << "------" << *arco << endl;
		}
		flujoSalida << "[-------------------------------------------]" << endl << endl;
*/
	}

	flujoSalida << "Tiempo de CPU: " << duration_cast<milliseconds>(fin - inicio).count() << " milisegundos." << endl;
	flujoSalida << "En un total de " << iteraciones << " iteraciones." << endl;
	flujoSalida.close();

	return 0;
}
