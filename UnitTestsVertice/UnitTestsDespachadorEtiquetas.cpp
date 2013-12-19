#include "gtest/gtest.h"

#include "Etiqueta.h"
#include "DespachadorEtiquetas.h"

#define Despachador DespachadorEtiquetas::GetInstancia() 

//Test para determinar si realmente sólo se entrega una sola instancia de etiqueta.
TEST(TestDespachadorEtiquetas, TestUnicaReferencia)
{
	auto primerEtiquta = Despachador.GetEtiqueta("A");
	auto segundaEtiqueta = Despachador.GetEtiqueta("A");

	EXPECT_EQ(primerEtiquta.get(), segundaEtiqueta.get());
}