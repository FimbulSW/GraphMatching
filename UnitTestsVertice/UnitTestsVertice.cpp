#include "gtest/gtest.h"
#include "Vertice.h"

TEST(testVertice, testEnumeracion)
{
	Vertice ver("Etiqueta", 1);
	EXPECT_EQ(1, ver.GetEnumeracion());
}

TEST(testVertice, testEtiqueta)
{
	Vertice ver("Etiqueta", 1);
	EXPECT_EQ("Etiqueta", ver.GetEtiqueta());
}

TEST(testVertice, testGrado)
{
	Vertice ver("Etiqueta", 1);
	EXPECT_EQ(0, ver.GetGrado());
	ver.SetGrado(5);
	EXPECT_EQ(5, ver.GetGrado());
}