#include "gtest/gtest.h"
#include "Arco.h"
#include "Vertice.h"
#include "DespachadorLVEV.h"

#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

TEST(testArco, testLVEV)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Se crean 2 vértices.
	//Se crea el arco a través de esos vértices.

	//Se espera que el LVEV sea la concatenacion de:
	//Etiqueta de origen, etiqueta del arco, etiqueta destino.
	shared_ptr<Vertice> origen = make_shared<Vertice>("A", 1);
	shared_ptr<Vertice> destino = make_shared<Vertice>("C", 2);
	Arco arco(origen, destino, "b");

	EXPECT_EQ("AbC", arco.GetLVEVString());
}

TEST(testArco, testLVEVBucle)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Se crea 1 vértice.
	//Se crea el arco a través de éste vértice.

	//Se espera que el LVEV sea la concatenacion de:
	//Etiqueta de origen, etiqueta del arco, etiqueta de origen.
	shared_ptr<Vertice> origen = make_shared<Vertice>("A", 1);

	Arco arco(origen, origen, "b");

	EXPECT_EQ("AbA", arco.GetLVEVString());
}

TEST(testArco, testOrdenLexicografico)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Se crean vértices lexicográficamente distintos.
	//Se agregan de manera inversa para que el constructor los acomode de manera adecuada.
	shared_ptr<Vertice> origen = make_shared<Vertice>("A", 1);
	shared_ptr<Vertice> destino = make_shared<Vertice>("C", 2);
	Arco arco(destino, origen, "b");

	EXPECT_EQ(origen->GetEnumeracion(), arco.GetOrigen()->GetEnumeracion());
	EXPECT_EQ(destino->GetEnumeracion(), arco.GetDestino()->GetEnumeracion());
	EXPECT_EQ("AbC", arco.GetLVEVString())<<" se obtuvo: "<<arco.GetLVEVString();
}

TEST(testArco, testCalculaAdyacenciaPorConstructor)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Se crean los vertices con grado 3.
	//Se espera que el arco tenga grado 4.

	shared_ptr<Vertice> origen = make_shared<Vertice>("A", 1);
	shared_ptr<Vertice> destino = make_shared<Vertice>("C", 2);
	
	origen->SetGrado(3);
	destino->SetGrado(3);

	Arco arco(origen, destino, "b");

	EXPECT_EQ(4, arco.GetGrado());
}

TEST(testArco, testCalculaAdyacenciaPorConstructorBucle)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Se crea un único vértice con grado 3.
	//Se espera que el arco tenga grado 2.

	shared_ptr<Vertice> origen = make_shared<Vertice>("A", 1);

	origen->SetGrado(3);

	Arco arco(origen, origen, "b");

	EXPECT_EQ(2, arco.GetGrado());
}

TEST(testArco, testCalculaAdyacenciaPorMetodo)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Se crean 2 vértices.
	//Se crea el arco con los respectivos vértices.

	//Después se cambia el grado de los vértices
	//Al calcular el grado del arco, se espera que el grado actual sea de 4.
	shared_ptr<Vertice> origen = make_shared<Vertice>("A", 1);
	shared_ptr<Vertice> destino = make_shared<Vertice>("C", 2);

	Arco arco(origen, destino, "b");

	origen->SetGrado(3);
	destino->SetGrado(3);
	arco.CalcularGrado();

	EXPECT_EQ(4, arco.GetGrado());
}

TEST(testArco, testCalculaAdyacenciaPorMetodoBucle)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Se crea 1 sólo vértice.
	//Se crea el arco con éste vértice.

	//Después se cambia el grado del vértice.
	//Al calcular el grado del arco, se espera que el grado actual sea de 2.
	shared_ptr<Vertice> origen = make_shared<Vertice>("A", 1);

	Arco arco(origen, origen, "b");

	origen->SetGrado(3);
	arco.CalcularGrado();

	EXPECT_EQ(2, arco.GetGrado());

}

TEST(testArco, testOrdenPorAdyacencia)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Creamos los vértices para el arcoMenor, con un grado de adyacencia de 3 cada uno
	//De esta forma sabemos que el arco tiene un grado de 4.
	shared_ptr<Vertice> origenArco1 = make_shared<Vertice>("A", 1);
	shared_ptr<Vertice> destinoArco1 = make_shared<Vertice>("C", 2);

	origenArco1->SetGrado(3);
	destinoArco1->SetGrado(3);

	//Creamos los vértices para el arcoMayor, con un grado de adyacencia de 4 cada uno
	//De esta forma sabemos que el arco tiene un grado de 6.
	shared_ptr<Vertice> origenArco2 = make_shared<Vertice>("D", 3);
	shared_ptr<Vertice> destinoArco2 = make_shared<Vertice>("F", 4);

	origenArco2->SetGrado(4);
	destinoArco2->SetGrado(4);

	Arco arcoMenor(origenArco1, destinoArco1, "b");
	Arco arcoMayor(origenArco2, destinoArco2, "e");

	//Verificamos que el arcoMayor sea precísamente mayor que el arcoMenor.

	bool verifica = arcoMenor < arcoMayor;
	bool verificaMatematicamente = !(arcoMayor < arcoMenor);

	//Tiene que retornar verdad.
	EXPECT_EQ(true, verifica);
	EXPECT_EQ(true, verificaMatematicamente);
}

TEST(testArco, testOrdenPorFrecuencia)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Creamos los vértices para el arcoMenor, con un grado de adyacencia de 3 cada uno
	//De esta forma sabemos que el arco tiene un grado de 4.
	shared_ptr<Vertice> origenArco1 = make_shared<Vertice>("A", 1);
	shared_ptr<Vertice> destinoArco1 = make_shared<Vertice>("C", 2);

	origenArco1->SetGrado(3);
	destinoArco1->SetGrado(3);

	//Creamos los vértices para el arcoMayor, con un grado de adyacencia de 3 cada uno
	//De esta forma sabemos que el arco tiene un grado de 4.
	shared_ptr<Vertice> origenArco2 = make_shared<Vertice>("D", 3);
	shared_ptr<Vertice> destinoArco2 = make_shared<Vertice>("F", 4);

	origenArco2->SetGrado(3);
	destinoArco2->SetGrado(3);

	Arco arcoMenor(origenArco1, destinoArco1, "b");
	Arco arcoMayor(origenArco2, destinoArco2, "e");

	//El orden es descendente con respecto a la frecuencia, por lo que pondremos una frecuencia mayor al arcoMenor
	//y viceversa.

	//Para esto crearemos 5 nuevos LVEV AbC y sólo 3 nuevos DeF

	for (int i = 0; i < 5; i++)
	{
		DespachadorLVEV::GetInstancia().GetLVEV("A", "b", "C");
	}
	
	for (int i = 0; i < 3; i++)
	{
		DespachadorLVEV::GetInstancia().GetLVEV("D", "e", "F");
	}

	//Verificamos que el arcoMayor sea precísamente mayor que el arcoMenor.

	bool verifica = arcoMenor < arcoMayor;

	//Tiene que retornar verdad.
	EXPECT_EQ(true, verifica);
}

TEST(testArco, testOrdenPorLexicografia)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Creamos los vértices para el arcoMenor, con un grado de adyacencia de 3 cada uno
	//De esta forma sabemos que el arco tiene un grado de 4.
	shared_ptr<Vertice> origenArco1 = make_shared<Vertice>("A", 1);
	shared_ptr<Vertice> destinoArco1 = make_shared<Vertice>("C", 2);

	origenArco1->SetGrado(3);
	destinoArco1->SetGrado(3);

	//Creamos los vértices para el arcoMayor, con un grado de adyacencia de 3 cada uno
	//De esta forma sabemos que el arco tiene un grado de 4.
	shared_ptr<Vertice> origenArco2 = make_shared<Vertice>("D", 3);
	shared_ptr<Vertice> destinoArco2 = make_shared<Vertice>("F", 4);

	origenArco2->SetGrado(3);
	destinoArco2->SetGrado(3);

	Arco arcoMenor(origenArco1, destinoArco1, "b");
	Arco arcoMayor(origenArco2, destinoArco2, "e");

	//El orden lexicografico actua cuando tienen el mismo grado de adyacencia y la misma frecuencia.
	//Se ordena lexicograficamente de manera ascendente.

	//Para fines prácticos dejaremos a la frecuencia en 0 y el mismo grado, por lo que la única diferencia
	//está en la etiqueta AbC y DeF

	//Verificaremos si el arcoMayor es en verdad mayor que el arcoMenor.
	//De ser así entonces nos devolverá false.

	bool verifica = arcoMayor < arcoMenor;

	//Tiene que retornar false.
	EXPECT_EQ(false, verifica);
}

TEST(testArco, testOrdenPorVerticesOrigen)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Creamos los vértices para el arcoMenor, con un grado de adyacencia de 3 cada uno
	//De esta forma sabemos que el arco tiene un grado de 4.
	shared_ptr<Vertice> origenArco1 = make_shared<Vertice>("A", 1);
	shared_ptr<Vertice> destinoArco1 = make_shared<Vertice>("C", 2);

	origenArco1->SetGrado(3);
	destinoArco1->SetGrado(3);

	//Creamos los vértices para el arcoMayor, con un grado de adyacencia de 3 cada uno
	//De esta forma sabemos que el arco tiene un grado de 4.
	shared_ptr<Vertice> origenArco2 = make_shared<Vertice>("A", 3);
	shared_ptr<Vertice> destinoArco2 = make_shared<Vertice>("C", 4);

	origenArco2->SetGrado(3);
	destinoArco2->SetGrado(3);

	Arco arcoMenor(origenArco1, destinoArco1, "b");
	Arco arcoMayor(origenArco2, destinoArco2, "b");

	//El orden por vértice ocurre cuando la etiqueta es la misma, por lo que el orden lexicográfico no aplica.


	//Para fines prácticos dejaremos a la frecuencia en 0 y el mismo grado y etiqueta
	//Por lo que la única diferencia será que los vértices de origen serán distintos.
	//Se ordenará de manera ascendente con respecto a los vértices de origen.

	//Verificaremos si el arcoMayor es en verdad mayor que el arcoMenor.
	//De ser así entonces nos devolverá false.

	bool verifica = arcoMayor < arcoMenor;

	//Tiene que retornar false.
	EXPECT_EQ(false, verifica);
}

TEST(testArco, testOrdenPorVerticesDestino)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Creamos los vértices para el arcoMenor, con un grado de adyacencia de 3 cada uno
	//De esta forma sabemos que el arco tiene un grado de 4.
	shared_ptr<Vertice> origenArco1 = make_shared<Vertice>("A", 1);
	shared_ptr<Vertice> destinoArco1 = make_shared<Vertice>("C", 2);

	origenArco1->SetGrado(3);
	destinoArco1->SetGrado(3);

	//Creamos los vértices para el arcoMayor, con un grado de adyacencia de 3 cada uno
	//De esta forma sabemos que el arco tiene un grado de 4.
	shared_ptr<Vertice> destinoArco2 = make_shared<Vertice>("C", 4);

	destinoArco2->SetGrado(3);

	Arco arcoMenor(origenArco1, destinoArco1, "b");
	Arco arcoMayor(origenArco1, destinoArco2, "b");

	//El orden por vértice destino ocurre cuando el origen es el mismo.


	//Para fines prácticos dejaremos a la frecuencia en 0 y el mismo grado y etiqueta, así como el mismo vértice origen
	//Por lo que la única diferencia será que los vértices destino son distinos.
	//Se ordenará de manera ascendente con respecto a los vértices de destino.

	//Verificaremos si el arcoMayor es en verdad mayor que el arcoMenor.
	//De ser así entonces nos devolverá false.

	bool verifica = arcoMayor < arcoMenor;

	//Tiene que retornar false.
	EXPECT_EQ(false, verifica);
}

TEST(testArco, testColeccionOrdenadaMismasFrecuencias)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Creamos una colección de arcos, para tratar de ordenarlos.
	vector<shared_ptr<Arco> > coleccion;
	//Creamos un arreglo de vértices
	shared_ptr<Vertice> vertices[10];
	//Predefinimos las etiqutas que queremos usar para la prueba.
	string etiquetasV[10] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
	string etiquetasA[5] = { "a", "b", "c", "d", "e" };
	//Al ser un caso con pocos elementos podemos calcular cuales son los resultados esperados después del ordenamiento.
	string resultadosEsperados[] = { "BbC", "CcE", "DdG", "EeI", "AaA" };

	//Creamos todos los vértices.
	for (int i = 0; i < 10; i++)
	{
		
		vertices[i] = make_shared<Vertice>(etiquetasV[i], i + 1);
	}

	//Creamos los arcos y los metemos en la colección.
	for (int i = 0; i < 5; i++)
	{
		coleccion.push_back(make_shared<Arco>(vertices[i], vertices[i * 2], etiquetasA[i]));
	}

	//Ordenamos la colección usando sort de algorithm
	sort(coleccion.begin(), coleccion.end(), [](const std::shared_ptr<Arco>& a1, const std::shared_ptr<Arco>& a2)
	{
		return *a1 < *a2;
	});

	//Recorremos la lista para tratar de obtener los resultados esperados.
	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(resultadosEsperados[i], coleccion[i]->GetLVEVString());
	}
}

TEST(testArco, testColeccionOrdenadaDistintasFrecuencias)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Creamos una colección de arcos, para tratar de ordenarlos.
	vector<shared_ptr<Arco> > coleccion;
	//Creamos un arreglo de vértices
	shared_ptr<Vertice> vertices[10];
	//Predefinimos las etiqutas que queremos usar para la prueba.
	string etiquetasV[10] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
	string etiquetasA[5] = { "a", "b", "c", "d", "e" };
	//Al ser un caso con pocos elementos podemos calcular cuales son los resultados esperados después del ordenamiento.
	string resultadosEsperados[] = { "EeI", "CcE", "BbC", "DdG", "AaA" };

	//Creamos todos los vértices.
	for (int i = 0; i < 10; i++)
	{

		vertices[i] = make_shared<Vertice>(etiquetasV[i], i + 1);
	}

	//Creamos los arcos y los metemos en la colección.
	for (int i = 0; i < 5; i++)
	{
		coleccion.push_back(make_shared<Arco>(vertices[i], vertices[i * 2], etiquetasA[i]));
	}

	//Para el caso de prueba propuesto se ocuparán las siguientes frecuencias:
	// AaA --- 3
	// BbC --- 1
	// CcE --- 2
	// DdG --- 1
	// EeI --- 3

	//Aumentamos la frecuencia del LVEV de AaA
	DespachadorLVEV::GetInstancia().GetLVEV("A", "a", "A");
	DespachadorLVEV::GetInstancia().GetLVEV("A", "a", "A");
	//Con esto debe tener frecuencia 3

	//Aumentamos la frecuencia del LVEV de CcE
	DespachadorLVEV::GetInstancia().GetLVEV("C", "c", "E");
	//Con esto debe tener frecuencia 2

	//Aumentamos la frecuencia del LVEV de EeI
	DespachadorLVEV::GetInstancia().GetLVEV("E", "e", "I");
	DespachadorLVEV::GetInstancia().GetLVEV("E", "e", "I");
	//Con esto debe tener frecuencia 3

	//Ordenamos la colección usando sort de algorithm
	sort(coleccion.begin(), coleccion.end(), [](const std::shared_ptr<Arco>& a1, const std::shared_ptr<Arco>& a2)
	{
		return *a1 < *a2;
	});

	//Recorremos la lista para tratar de obtener los resultados esperados.
	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(resultadosEsperados[i], coleccion[i]->GetLVEVString());
	}
}

TEST(testArco, testColeccionOrdenadaDistintosGradosAdyacencia)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Creamos una colección de arcos, para tratar de ordenarlos.
	vector<shared_ptr<Arco> > coleccion;
	//Creamos un arreglo de vértices
	shared_ptr<Vertice> vertices[10];
	//Predefinimos las etiqutas que queremos usar para la prueba.
	string etiquetasV[10] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
	string etiquetasA[5] = { "a", "b", "c", "d", "e" };
	//Al ser un caso con pocos elementos podemos calcular cuales son los resultados esperados después del ordenamiento.
	string resultadosEsperados[] = { "DdG", "CcE", "AaA", "EeI", "BbC" };

	//Creamos todos los vértices.
	//Para asuntos de simplicidad en la prueba se han acordado que los valores de los grados de los vértices serán los siguientes:
	//A --- 7
	//B --- 5
	//C --- 4
	//D --- 1
	//E --- 2
	//F --- 0
	//G --- 3
	//H --- 0
	//I --- 6
	//J --- 0

	for (int i = 0; i < 10; i++)
	{
		vertices[i] = make_shared<Vertice>(etiquetasV[i], i + 1);
		if (etiquetasV[i] == "A") vertices[i]->SetGrado(7);
		else if (etiquetasV[i] == "B") vertices[i]->SetGrado(5);
		else if (etiquetasV[i] == "C") vertices[i]->SetGrado(4);
		else if (etiquetasV[i] == "D") vertices[i]->SetGrado(1);
		else if (etiquetasV[i] == "E") vertices[i]->SetGrado(2);
		else if (etiquetasV[i] == "G") vertices[i]->SetGrado(3);
		else if (etiquetasV[i] == "I") vertices[i]->SetGrado(6);
		else vertices[i]->SetGrado(0);
	}

	//Creamos los arcos y los metemos en la colección.
	for (int i = 0; i < 5; i++)
	{
		coleccion.push_back(make_shared<Arco>(vertices[i], vertices[i * 2], etiquetasA[i]));
	}

	//Para el caso de prueba propuesto se ocuparán las siguientes frecuencias:
	// AaA --- 3
	// BbC --- 1
	// CcE --- 2
	// DdG --- 1
	// EeI --- 3

	//Aumentamos la frecuencia del LVEV de AaA
	DespachadorLVEV::GetInstancia().GetLVEV("A", "a", "A");
	DespachadorLVEV::GetInstancia().GetLVEV("A", "a", "A");
	//Con esto debe tener frecuencia 3

	//Aumentamos la frecuencia del LVEV de CcE
	DespachadorLVEV::GetInstancia().GetLVEV("C", "c", "E");
	//Con esto debe tener frecuencia 2

	//Aumentamos la frecuencia del LVEV de EeI
	DespachadorLVEV::GetInstancia().GetLVEV("E", "e", "I");
	DespachadorLVEV::GetInstancia().GetLVEV("E", "e", "I");
	//Con esto debe tener frecuencia 3

	//Ordenamos la colección usando sort de algorithm
	sort(coleccion.begin(), coleccion.end(), [](const std::shared_ptr<Arco>& a1, const std::shared_ptr<Arco>& a2)
	{
		return *a1 < *a2;
	});

	//Recorremos la lista para tratar de obtener los resultados esperados.
	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(resultadosEsperados[i], coleccion[i]->GetLVEVString());
	}
}