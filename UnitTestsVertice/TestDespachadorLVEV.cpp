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
