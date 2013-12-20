#include "gtest/gtest.h"

#include "Grafo.h"
#include "Arco.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//Esta prueba pretende la lectura simple de un grafo
//Sólo se leerán 2 vértices y un arco.
TEST(testGrafo, testLecturaGrafoSimple)
{
	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	stringstream ss;
	ss << "Grafo de prueba" << endl;
	ss << "v 1 A" << endl;
	ss << "v 2 C" << endl;
	ss << "e 2 1 b" << endl;
	
	//Se llena el grafo con la información que contenga el flujo.
	ss >> g;

	//Se espera que el nombre sea leído correctamente.
	EXPECT_EQ("Grafo de prueba", g.GetNombre());
	//Se espera que sólo exista un sólo arco en el grafo.
	EXPECT_EQ(1, g.GetArcos().size());
	//Se espera que la información del grafo haya sido correctamente leída, por eso corroboramos la cadena del LVEV
	EXPECT_EQ("AbC", g.GetArcos()[0]->GetLVEVString());
}

//Esta prueba pretende leer un grafo pequeño de 7 vértices y 5 árcos.
TEST(testGrafo, testLecutraGrafoMediano)
{
	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	stringstream ss;
	//Estos son los resultados de los LVEV que se tienen que encontrar en el grafo.
	string resultado[] = { "AaA", "BbC", "CcE", "DdG", "EeI" };
	//Se manda la información al flujo
	ss << "Grafo de prueba" << endl;
	//En este ejemplo mandamos primero los vértices y después los arcos por cuestiones de facilidad.
	ss << "v 1 A" << endl;
	ss << "v 2 B" << endl;
	ss << "v 3 C" << endl;
	ss << "v 4 D" << endl;
	ss << "v 5 E" << endl;
	ss << "v 6 G" << endl;
	ss << "v 7 I" << endl;
	
	ss << "e 1 1 a" << endl;
	ss << "e 2 3 b" << endl;
	ss << "e 3 5 c" << endl;
	ss << "e 4 6 d" << endl;
	ss << "e 5 7 e" << endl;

	//Se llena el grafo con la información que contenga el flujo.
	ss >> g;

	auto arcos = g.GetArcos();
	//Se supone que el grafo debe tener exactamente 5 arcos.
	EXPECT_EQ(5, arcos.size());

	for (int i = 0; i < 5; i++)
	{
		//Dichos arcos tienen que estar en el orden descrito en el arreglo 'resultado'.
		EXPECT_EQ(resultado[i], arcos[i]->GetLVEVString());
	}
}