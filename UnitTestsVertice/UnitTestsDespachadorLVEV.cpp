#include "gtest/gtest.h"

#include "DespachadorLVEV.h"
#include "LVEV.h"
#include "Etiqueta.h"
#include "DespachadorEtiquetas.h"

TEST(testDespachadorLVEV, testCreaLVEVConStrings)
{
	DespachadorLVEV::GetInstancia().Vacia();
	auto lvev = DespachadorLVEV::GetInstancia().GetLVEV("A", "b", "C");
	EXPECT_EQ(1, lvev->GetFrecuencia());
	EXPECT_EQ("AbC", lvev->GetLVEVString());
}

TEST(testDespachadorLVEV, testCreaLVEVConEtiquetas)
{
	DespachadorLVEV::GetInstancia().Vacia();
	auto etiquetaOrigen = DespachadorEtiquetas::GetInstancia().GetEtiqueta("A");
	auto etiquetaDestino = DespachadorEtiquetas::GetInstancia().GetEtiqueta("C");
	auto etiquetaArco = DespachadorEtiquetas::GetInstancia().GetEtiqueta("b");

	auto lvev = DespachadorLVEV::GetInstancia().GetLVEV(etiquetaOrigen, etiquetaArco, etiquetaDestino);
	EXPECT_EQ(1, lvev->GetFrecuencia());
	EXPECT_EQ("AbC", lvev->GetLVEVString());
}

TEST(testDespachadorLVEV, testVerificaUnicaInstancia)
{
	DespachadorLVEV::GetInstancia().Vacia();
	auto lvev1 = DespachadorLVEV::GetInstancia().GetLVEV("A", "b", "C");
	auto lvev2 = DespachadorLVEV::GetInstancia().GetLVEV("A", "b", "C");
	auto lvev3 = DespachadorLVEV::GetInstancia().GetLVEV("A", "b", "C");

	EXPECT_EQ(lvev3.get(), lvev2.get());
}

TEST(testDespachadorLVEV, testVerificaAumentoFrecuencia)
{
	DespachadorLVEV::GetInstancia().Vacia();
	//Crearemos 10 lvev identicos, cuando preguntemos por el primer lvev tiene que decir que su frecuencia es 10.
	auto lvev = DespachadorLVEV::GetInstancia().GetLVEV("A", "b", "C");
	for (int i = 1; i < 10; i++)
	{
		DespachadorLVEV::GetInstancia().GetLVEV("A", "b", "C");
	}

	EXPECT_EQ(10, lvev->GetFrecuencia())<<" pero se obtuvo: "<<lvev->GetFrecuencia();
}

TEST(testDespachadorLVEV, testVerificaDistintosDespachadores)
{
	DespachadorLVEV::GetInstancia().Vacia();
	DespachadorLVEV::GetInstancia(1).Vacia();

	auto lvevID0 = DespachadorLVEV::GetInstancia().GetLVEV("A", "a", "A");
	for (int i = 1; i < 10; i++)
	{
		DespachadorLVEV::GetInstancia().GetLVEV("A", "a", "A");
	}

	auto lvevID1 = DespachadorLVEV::GetInstancia(1).GetLVEV("A", "a", "A");

	EXPECT_EQ(1, lvevID1->GetFrecuencia());
	EXPECT_EQ(10, lvevID0->GetFrecuencia());
}

TEST(testDespachadorLVEV, testIgualdadLVEVDiferentesDespachadores)
{
	//Limpiaremos 3 instancias para que las frecuencias siempre sean 1.
	DespachadorLVEV::GetInstancia().Vacia();
	DespachadorLVEV::GetInstancia(1).Vacia();
	DespachadorLVEV::GetInstancia(2).Vacia();

	//Crearemos 3 arcos, idénticos en contenido pero de diferente despachador.
	auto lvevID0 = DespachadorLVEV::GetInstancia().GetLVEV("A", "b", "C");
	auto lvevID1 = DespachadorLVEV::GetInstancia(1).GetLVEV("A", "b", "C");
	auto lvevID2 = DespachadorLVEV::GetInstancia(2).GetLVEV("A", "b", "C");

	//Esperamos que entre todos ellos sean iguales.
	EXPECT_EQ(true, *lvevID0 == *lvevID1);
	EXPECT_EQ(true, *lvevID0 == *lvevID2);
	//Esperamos que las instancias sean diferentes.
	EXPECT_NE(lvevID0.get(), lvevID1.get());
	EXPECT_NE(lvevID0.get(), lvevID2.get());
	EXPECT_NE(lvevID1.get(), lvevID2.get());
}