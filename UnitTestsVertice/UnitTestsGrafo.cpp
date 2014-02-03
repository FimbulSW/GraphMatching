#include "gtest/gtest.h"

#include "Grafo.h"
#include "Arco.h"
#include "DespachadorLVEV.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

//Esta prueba pretende la lectura simple de un grafo
//S�lo se leer�n 2 v�rtices y un arco.
TEST(testGrafo, testLecturaGrafoSimple)
{
	//Limpiamos el despachador, s�lo para fines de testeo.
	DespachadorLVEV::GetInstancia().Vacia();
	
	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	stringstream ss;
	ss << "Grafo de prueba" << endl;
	ss << "% Esto es solo un comentario, tiene que ignorarlo" << endl;
	ss << "v 1 A" << endl;
	ss << "v 2 C" << endl;
	ss << "% Esto es solo un comentario, tiene que ignorarlo" << endl;
	ss << "e 2 1 b" << endl;

	//Se llena el grafo con la informaci�n que contenga el flujo.
	ss >> g;

	//Se espera que el nombre sea le�do correctamente.
	EXPECT_EQ("Grafo de prueba", g.GetNombre());
	//Se espera que s�lo exista un s�lo arco en el grafo.
	EXPECT_EQ(1, g.GetArcos().size());
	//Se espera que la informaci�n del grafo haya sido correctamente le�da, por eso corroboramos la cadena del LVEV
	EXPECT_EQ("AbC", g.GetArcos()[0]->GetLVEVString());
}

//Esta prueba pretende leer un grafo peque�o de 7 v�rtices y 5 �rcos.
TEST(testGrafo, testLecutraGrafoMediano)
{
	//Limpiamos el despachador, s�lo para fines de testeo.
	DespachadorLVEV::GetInstancia().Vacia();

	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	stringstream ss;
	//Estos son los resultados de los LVEV que se tienen que encontrar en el grafo.
	string resultado[] = { "AaA", "BbC", "CcE", "DdG", "EeI" };
	//Se manda la informaci�n al flujo
	ss << "Grafo de prueba" << endl;
	//En este ejemplo mandamos primero los v�rtices y despu�s los arcos por cuestiones de facilidad.
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

	//Se llena el grafo con la informaci�n que contenga el flujo.
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

//Esta prueba pretende calcular los grados de los arcos, aprovechando la comparaci�n con referencias
//de la implementaci�n.
TEST(testGrafo, testCalculaGradoArcos)
{
	//Limpiamos el despachador, s�lo para fines de testeo.
	DespachadorLVEV::GetInstancia().Vacia();

	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	stringstream ss;
	//Nombre del arco
	ss << "Grafo de prueba" << endl;
	//Inserci�n de los v�rtices.
	ss << "v 1 A" << endl;
	ss << "v 2 B" << endl;
	ss << "v 3 D" << endl;
	ss << "v 4 C" << endl;
	ss << "v 5 J" << endl;
	ss << "v 6 A" << endl;
	ss << "v 7 B" << endl;
	//Inserci�n de aristas.
	ss << "e 1 2 c" << endl;
	ss << "e 1 3 b" << endl;
	ss << "e 3 4 c" << endl;
	ss << "e 3 6 b" << endl;
	ss << "e 2 4 d" << endl;
	ss << "e 4 7 d" << endl;
	ss << "e 2 5 a" << endl;
	ss << "e 5 7 a" << endl;
	ss << "e 6 7 c" << endl;

	//Llenaremos el grafo con el flujo
	ss >> g;

	//Exploraremos el grafo y en base a eso calcularemos el grado.
	g.ExploraGrafo();

	auto arcos = g.GetArcos();

	int gradosEsperados[] = { 3, 3, 4, 3, 4, 4, 3, 3, 3 };

	//Se supone que el grafo deber�a tener 9 arcos.
	EXPECT_EQ(9, arcos.size());

	for (int i = 0; i < 9; i++)
	{
		int gradoAdyacencia = g.GetAdyacencia(arcos[i]).size();
		EXPECT_EQ(gradosEsperados[i], gradoAdyacencia) << " fallo!!!! en la posici�n " << i << endl;
	}
}

//Esta prueba pretende verificar que la colecci�n de arcos adyacentes unos con otros funcione de manera adecuada.
TEST(testGrafo, testVerificaAdyacenciasArcos)
{
	//Limpiamos el despachador, s�lo para fines de testeo.
	DespachadorLVEV::GetInstancia().Vacia();

	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	stringstream ss;
	//Nombre del arco
	ss << "Grafo de prueba" << endl;
	//Inserci�n de los v�rtices.
	ss << "v 1 A" << endl;
	ss << "v 2 B" << endl;
	ss << "v 3 D" << endl;
	ss << "v 4 C" << endl;
	ss << "v 5 J" << endl;
	ss << "v 6 A" << endl;
	ss << "v 7 B" << endl;
	//Inserci�n de aristas.
	ss << "e 1 2 c" << endl;
	ss << "e 1 3 b" << endl;
	ss << "e 3 4 c" << endl;
	ss << "e 3 6 b" << endl;
	ss << "e 2 4 d" << endl;
	ss << "e 4 7 d" << endl;
	ss << "e 2 5 a" << endl;
	ss << "e 5 7 a" << endl;
	ss << "e 6 7 c" << endl;

	//Llenaremos el grafo con el flujo
	ss >> g;

	//Exploraremos el grafo y en base a eso calcularemos el grado.
	g.ExploraGrafo();

	//Obtenemos los arcos del grafo.
	auto arcos = g.GetArcos();
	auto arcoCcD = arcos[2];

	EXPECT_EQ("CcD", arcoCcD->GetLVEVString());
	//Obtenemos todos los adyacentes al arco CcD
	auto adyacentesCcD = g.GetAdyacencia(arcoCcD);
	                        
	//								AbD AbD BdC BdC
	int posicionesDeAdyacentes[] = { 1,  3,  4,  5  };

	//El arco CcD tiene 4 adyacentes, as� que lo verificamos.
	EXPECT_EQ(4, adyacentesCcD.size());

	for (int i = 0; i < 4; i++)
	{
		EXPECT_EQ(arcos[posicionesDeAdyacentes[i]], adyacentesCcD[i]) << " fallo en la posicion: " << i << endl;
	}

}

TEST(testGrafo, testFormaCanonicaGrafoSimple)
{
	//Limpiamos el despachador, s�lo para fines de testeo.
	DespachadorLVEV::GetInstancia().Vacia();

	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	stringstream ss;
	//Nombre del arco
	ss << "Grafo de prueba" << endl;
	//Inserci�n de los v�rtices.
	ss << "v 1 A" << endl;
	ss << "v 2 U" << endl;
	ss << "v 3 R" << endl;
	ss << "v 4 Z" << endl;
	//Inserci�n de aristas.
	ss << "e 1 4 a" << endl;
	ss << "e 1 3 b" << endl;
	ss << "e 3 4 c" << endl;
	ss << "e 2 4 a" << endl;

	//Llenaremos el grafo con el flujo
	ss >> g;

	//Exploraremos el grafo.
	g.ExploraGrafo();

	auto arcosFormaNormal = g.GetArcos();
	int resultadosEsperados[] = { 1, 0, 3, 2 };

	//Creamos la forma can�nica.
	g.CreaFormaCanonica();
	auto arcosFormaCanonica = g.GetArcos();

	for (int i = 0; i < 4; i++)
	{
		EXPECT_EQ(arcosFormaNormal[resultadosEsperados[i]], arcosFormaCanonica[i]) << "fallo en la posicion " << i << endl
			<< "Se esperaba: " << arcosFormaNormal[resultadosEsperados[i]]->GetLVEVString() << endl
			<< "Se obtuvo: " << arcosFormaCanonica[i]->GetLVEVString() << endl;
	}
}

TEST(testGrafo, testFormaCanonicaGrafoMediano)
{
	//Limpiamos el despachador, s�lo para fines de testeo.
	DespachadorLVEV::GetInstancia().Vacia();

	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	//Para mayor informaci�n, leer el grafo en la direcci�n del archivo.
	ifstream entrada("C:\\Grafos\\g2.g");

	//Llenamos el grafo con el flujo de entrada.
	entrada >> g;

	//Exploramos el grafo.
	g.ExploraGrafo();

	//Obtenemos los arcos en su forma normal.
	auto arcosFormaNormal = g.GetArcos();

	//Calculamos la forma can�nica.
	g.CreaFormaCanonica();

	//Obtenemos los arcos ordenados en su forma can�nica.
	auto arcosFormaCanonica = g.GetArcos();

	//Son los resultados de las posiciones que esperar�amos leer, para llegar a eso ver el archivo g2.g.out
	int resultadosEsperados[] = { 1, 0, 2, 3, 4, 5, 7, 9, 8, 14, 13, 6, 12, 11, 10 };

	for (int i = 0; i < 14; i++)
	{
		EXPECT_EQ(arcosFormaNormal[resultadosEsperados[i]], arcosFormaCanonica[i]) << "fallo en la posicion " << i << endl
			<< "Se esperaba: " << arcosFormaNormal[resultadosEsperados[i]]->GetLVEVString() << endl
			<< "Se obtuvo: " << arcosFormaCanonica[i]->GetLVEVString() << endl;
	}
}

TEST(testGrafo, testFormaCanonicaDerivadaGrafoMediano)
{
	//Limpiamos el despachador, s�lo para fines de testeo.
	DespachadorLVEV::GetInstancia().Vacia();

	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	//Para mayor informaci�n, leer el grafo en la direcci�n del archivo.
	ifstream entrada("C:\\Grafos\\g2.g");

	//Llenamos el grafo con el flujo de entrada.
	entrada >> g;

	//Exploramos el grafo.
	g.ExploraGrafo();

	//Obtenemos los arcos de la forma can�nica.
	g.CreaFormaCanonica();
	auto arcosFC = g.GetArcos();

	//Marcaremos como matcheados a los arcos 5, 6, 10 de la forma can�nica.
	arcosFC[5]->SetEstado(EstadoArco::MATCHEADO);
	arcosFC[6]->SetEstado(EstadoArco::MATCHEADO);
	arcosFC[10]->SetEstado(EstadoArco::MATCHEADO);

	//Generamos la forma can�nica derivada.
	g.CreaFormaCanonica();
	//Obtenemos los arcos de la forma can�nica derivada
	auto arcosFCD = g.GetArcos();

	int resultadosEsperados[] = { 5, 6, 10, 1, 3, 7, 2, 4, 8, 9, 11, 12, 13, 14 };

	//Al formar la forma can�nica derivada se supone que la lista de arcos se reduce en 1
	//dado que siempre se elimina la raiz.
	EXPECT_EQ(arcosFC.size() - 1, arcosFCD.size());

	for (int i = 0, longitud = arcosFCD.size(); i < longitud; i++)
	{
		EXPECT_EQ(arcosFC[resultadosEsperados[i]], arcosFCD[i]) << "fallo en la posicion " << i << endl
			<< "Se esperaba: " << arcosFC[resultadosEsperados[i]]->GetLVEVString() << endl
			<< "Se obtuvo: " << arcosFCD[i]->GetLVEVString() << endl;
	}
}

TEST(testGrafo, testSegundaFormaCanonicaDerivadaGrafoMediano)
{
	//Limpiamos el despachador, s�lo para fines de testeo.
	DespachadorLVEV::GetInstancia().Vacia();

	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	//Para mayor informaci�n, leer el grafo en la direcci�n del archivo.
	ifstream entrada("C:\\Grafos\\g2.g");

	//Llenamos el grafo con el flujo de entrada.
	entrada >> g;

	//Exploramos el grafo.
	g.ExploraGrafo();

	//Obtenemos los arcos de la forma can�nica.
	g.CreaFormaCanonica();
	auto arcosFC = g.GetArcos();

	//Marcaremos como matcheados a los arcos 5, 6, 10 de la forma can�nica.
	arcosFC[5]->SetEstado(EstadoArco::MATCHEADO);
	arcosFC[6]->SetEstado(EstadoArco::MATCHEADO);
	arcosFC[10]->SetEstado(EstadoArco::MATCHEADO);

	//Obtenemos la primera forma can�nica derivada.
	g.CreaFormaCanonica();

	//Obtenemos los arcos de la primera forma can�nica derivada.
	auto arcosPFCD = g.GetArcos();

	//Pondremos como matcheados los siguientes arcos
	//3, 4, 13
	arcosPFCD[3]->SetEstado(EstadoArco::MATCHEADO);
	arcosPFCD[4]->SetEstado(EstadoArco::MATCHEADO);
	arcosPFCD[13]->SetEstado(EstadoArco::MATCHEADO);

	//Obtenemos la segunda forma can�nica derivada.
	g.CreaFormaCanonica();

	//Obtenemos los arcos de la segunda forma can�nica derivada.
	auto arcosSFCD = g.GetArcos();

	//Los resultados esperados (el orden de los arcos) son en base a los arcos de la forma can�nica original.
	int resultadosEsperados[] = { 6, 10, 1, 3, 14, 7, 13, 2, 4, 8, 9, 11, 12 };

	//Esperamos que el tama�o de la segunda forma can�nica derivada sea uno menor 
	//que el de la primera forma can�nica derivada.
	EXPECT_EQ(arcosPFCD.size() - 1, arcosSFCD.size());

	//Ahora corroboramos las posiciones en comparaci�n a los de la forma can�nica.
	for (int i = 0, longitud = arcosSFCD.size(); i < longitud; i++)
	{
		EXPECT_EQ(arcosFC[resultadosEsperados[i]], arcosSFCD[i]) << "fallo en la posicion " << i << endl
			<< "Se esperaba: " << arcosFC[resultadosEsperados[i]]->GetLVEVString() << endl
			<< "Se obtuvo: " << arcosSFCD[i]->GetLVEVString() << endl;
	}
}

TEST(testGrafo, testVerificaAdyacencia)
{
	//Limpiamos el despachador, s�lo para fines de testeo.
	DespachadorLVEV::GetInstancia().Vacia();

	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	//Para mayor informaci�n, leer el grafo en la direcci�n del archivo.
	ifstream entrada("C:\\Grafos\\g1p.g");

	//Llenamos el grafo con el flujo de entrada.
	entrada >> g;

	//Exploramos el grafo.
	g.ExploraGrafo();

	//Obtenemos los arcos.
	auto arcos = g.GetArcos();

	//De acuerdo a la lectura del grafo, �ste deber�a ser el arco AbR 1 3
	auto arcoAbR = arcos[0]; 
	//Este tendr�a que ser el arco AaZ 1 4
	auto arcoAaZ = arcos[1];
	//Este tendr�a que ser el arco UaZ 2 4
	auto arcoUaZ = arcos[2];

	//Se supone que el primer y segundo arco son adyacentes
	EXPECT_EQ(true, g.EsAdyacente(arcoAbR, arcoAaZ));
	//El segundo y el tercero son adyacentes
	EXPECT_EQ(true, g.EsAdyacente(arcoUaZ, arcoAaZ));
	//El primero y el tercero NO son adyacentes.
	EXPECT_EQ(false, g.EsAdyacente(arcoAbR, arcoUaZ));

}

TEST(testGrafo, testObtenerArcosConIgualLVEV)
{
	//Limpiamos el despachador, s�lo para fines de testeo.
	DespachadorLVEV::GetInstancia().Vacia();

	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	//Para mayor informaci�n, leer el grafo en la direcci�n del archivo.
	ifstream entrada("C:\\Grafos\\g5.g");

	const int tamanoAcB = 2;
	const int tamanoAbD = 2;

	//Llenamos el grafo con el flujo de entrada.
	entrada >> g;

	//Exploramos el grafo.
	g.ExploraGrafo();

	auto arcosTotales = g.GetArcos();

	//La posici�n 0 deber�a ser del arco AcB 1 2.
	auto arcoAcB_1_2 = arcosTotales[0];
	//La posicion 1 deber�a ser del arco AbD 1 3.
	auto arcoAbD_1_3 = arcosTotales[1];
	
	//Nos deber�a regresar una colecci�n con todos los arcos que existen en la lista de adyacencia
	//que comparten en mismo LVEV, en este caso deber�an ser 2.
	auto arcosSimilaresAcB = g.GetArcos(arcoAcB_1_2);
	
	//Lo mismo aplica para este arco.
	auto arcosSimilaresAbD = g.GetArcos(arcoAbD_1_3);

	EXPECT_EQ(tamanoAbD, arcosSimilaresAbD.size());
	EXPECT_EQ(tamanoAcB, arcosSimilaresAcB.size());

	for (int i = 0; i < tamanoAbD; i++)
	{
		EXPECT_EQ(*arcoAbD_1_3, *arcosSimilaresAbD[i]);
	}

	for (int i = 0; i < tamanoAcB; i++)
	{
		EXPECT_EQ(*arcoAcB_1_2, *arcosSimilaresAcB[i]);
	}
}

TEST(testGrafo, testEliminaArcosMatcheados)
{
	//Limpiamos el despachador, s�lo para fines de testeo.
	DespachadorLVEV::GetInstancia().Vacia();

	Grafo g;
	//Flujo que utilizaremos para la lectura del grafo
	//Para mayor informaci�n, leer el grafo en la direcci�n del archivo.
	ifstream entrada("C:\\Grafos\\g1p.g");

	//Llenamos el grafo con el flujo de entrada.
	entrada >> g;

	//Exploramos el grafo.
	g.ExploraGrafo();

	//Obtenemos los arcos.
	auto arcosTotales = g.GetArcos();

	//Sabemos que la posici�n 0 del arco tiene el arco AcB 1 2
	//por lo que marcaremos como matcheados a esos arcos

	//Marcaremos como matcheados a todos los arcos AcB
	auto arcosAcB = g.GetArcos(arcosTotales[0]);
	//Haremos lo mismo con los arcos AbD, que est� en la posici�n 1 del grafo.
	auto arcosAbD = g.GetArcos(arcosTotales[1]);


	const int tamanoArcosTotal = arcosTotales.size();
	const int totalArcosEliminados = arcosAcB.size() + arcosAbD.size();

	//Verificamos que el tamano de la lista de adyacencia sea la esperada.
	EXPECT_EQ(tamanoArcosTotal, g.TamanoAdyacencia());

	//Marcaremos como matcheados los arcos deseados.
	for (int i = 0, tamano = arcosAcB.size(); i < tamano; i++)
	{
		arcosAcB[i]->SetEstado(EstadoArco::MATCHEADO);
	}

	for (int i = 0, tamano = arcosAbD.size(); i < tamano; i++)
	{
		arcosAbD[i]->SetEstado(EstadoArco::MATCHEADO);
	}

	//Eliminando los matcheados
	g.EliminaMatcheados();

	//Se supone que el tamano de la adyacencia deber�a de bajar en base al tamano de arcos eliminados.
	EXPECT_EQ(tamanoArcosTotal - totalArcosEliminados, g.TamanoAdyacencia());
	
	//Esperamos tambi�n que dichos arcos ya no aparezcan en la lista.
	for (int i = 0, tamano = arcosAcB.size(); i < tamano; i++)
	{
		EXPECT_EQ(false, g.Existe(arcosAcB[i]));
	}

	for (int i = 0, tamano = arcosAbD.size(); i < tamano; i++)
	{
		EXPECT_EQ(false, g.Existe(arcosAbD[i]));
	}
}