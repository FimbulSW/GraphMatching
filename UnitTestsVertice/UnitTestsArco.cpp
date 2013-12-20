#include "gtest/gtest.h"
#include "Arco.h"
#include "Vertice.h"
#include "DespachadorLVEV.h"
#include <memory>

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

	//Tiene que retornar verdad.
	EXPECT_EQ(true, verifica);
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