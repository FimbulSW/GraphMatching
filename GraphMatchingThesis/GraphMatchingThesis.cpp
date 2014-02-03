// GraphMatchingThesis.cpp : Defines the entry point for the console application.
//

#include "Vertice.h"
#include "Arco.h"
#include "Grafo.h"
#include "Matcheador.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <utility>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

const int parametrosMinimos = 4;

int main(int argc, char** argv)
{
	if (argc < parametrosMinimos)
	{
		cerr << "Numero de parametros invalido, minimamente tiene que tener:" << endl;
		cerr << "1) Direccion del grafo de muestra." << endl;
		cerr << "2) Direccion del grafo de busqueda." << endl;
		cerr << "3) Direccion del archivo de salida." << endl;
		cerr << "4) Soporte (opcional, numero entero)." << endl;

		cerr << endl << "----Ejemplo----" << endl;
		cerr << "Sistemas LINUX-like:" << endl;
		cerr << "./GraphMatchingThesis GrafoMuestra.g GrafoBusqueda.g Resultados.log 8" << endl;
		cerr << "Sistemas WINDOWS:" << endl;
		cerr << "GraphMatchingThesis.exe GrafoMuestra.g GrafoBusqueda.g Resultados.log 8" << endl;
		
		return 1;
	}

	int soporte = 1;

	if (argc > parametrosMinimos)
	{
		stringstream ss(argv[parametrosMinimos]);
		ss >> soporte;
		if (ss.fail() || soporte <= 0)
		{
			cerr << "El soporte tiene que ser un numero entero positivo mayor a 0." << endl;
			return 1;
		}
	}

	ifstream flujoGrafoMuestra(argv[1]);
	ifstream flujoGrafoBusqueda(argv[2]);
	ofstream flujoSalida(argv[3]);


	Grafo grafoMuestra;
	Grafo grafoBusqueda(1);

	flujoGrafoMuestra >> grafoMuestra;
	flujoGrafoBusqueda >> grafoBusqueda;

	flujoGrafoMuestra.close();
	flujoGrafoBusqueda.close();

	grafoMuestra.ExploraGrafo();
	grafoBusqueda.ExploraGrafo();

	Matcheador matcher(grafoMuestra, grafoBusqueda);

	steady_clock::time_point inicio = steady_clock::now();

	int iteraciones = matcher.MatcheaGrafos();

	steady_clock::time_point fin = steady_clock::now();

	auto patrones = matcher.GetPatrones(soporte);

	sort(patrones.begin(), patrones.end(), [](const shared_ptr<Patron> p1, const shared_ptr<Patron> p2)
	{
		return p1->ArcosGrafoBusqueda.size() < p2->ArcosGrafoBusqueda.size();
	}
	);

	flujoSalida << "Se han encontrado " << patrones.size() << " patrones con soporte " << soporte << endl << endl;
	for (int i = 0, tam = patrones.size(); i < tam; i++)
	{
		flujoSalida << "  ( " << i + 1 << " ) " << "de tamano: " << patrones[i]->ArcosGrafoBusqueda.size() << endl;
		for (auto arco : patrones[i]->ArcosGrafoBusqueda)
		{
			flujoSalida << "------" << *arco << endl;
		}
		flujoSalida << "[-------------------------------------------]" << endl << endl;
	}

	flujoSalida << "Tiempo de CPU: " << duration_cast<milliseconds>(fin - inicio).count() << " milisegundos." << endl;
	flujoSalida << "En un total de " << iteraciones << " iteraciones." << endl;
	flujoSalida.close();

	return 0;
}
