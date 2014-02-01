#include "gtest/gtest.h"
#include "Arco.h"
#include "Vertice.h"
#include "DespachadorLVEV.h"
#include "Grafo.h"
#include "Matcheador.h"

#include <memory>
#include <deque>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

// Esta es una clase proxy de Matcheador, para exponer de manera pública los métodos protegidos que contiene.
// Todos con el prefijo "p_"
// Ésto se hace con el propósito de poder testear cada uno de los métodos.
class MatcheadorPublico : public Matcheador
{
public:
	bool p_EsCandidato(shared_ptr<Patron>& patron, const shared_ptr<Arco>& arcoMuestra, const shared_ptr<Arco>& arcoBusqueda)
	{
		return Matcheador::EsCandidato(patron, arcoMuestra, arcoBusqueda);
	}

	deque<shared_ptr<Arco> > p_FiltraCandidatos(shared_ptr<Patron>& patron, shared_ptr<Arco>& arcoMuestra, deque<shared_ptr<Arco> >& arcosSimilares)
	{
		return Matcheador::FiltraCandidatos(patron, arcoMuestra, arcosSimilares);
	}

	void p_MarcaExpansionPatron(shared_ptr<Patron>& patron)
	{
		Matcheador::MarcaExpansionPatron(patron);
	}
	void p_MarcaExpansiones()
	{
		Matcheador::MarcaExpansiones();
	}
	void p_ObtenerRaices(shared_ptr<Arco>& raiz)
	{
		Matcheador::ObtenerRaices(raiz);
	}
	void p_ExpandirPatrones()
	{
		Matcheador::ExpandirPatrones();
	}
	void p_ExpandirPatron(std::shared_ptr<Patron>& patron)
	{
		Matcheador::ExpandirPatron(patron);
	}
	void p_CreaClones(shared_ptr<Patron>& patron, shared_ptr<Arco>& arcoMuestra, deque<shared_ptr<Arco> >& candidatos)
	{
		Matcheador::CreaClones(patron, arcoMuestra, candidatos);
	}

	MatcheadorPublico(Grafo& gm, Grafo& gb, bool log = false) : Matcheador(gm, gb, log) { }
};

class testMatcheador : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
		DespachadorLVEV::GetInstancia().Vacia();
		DespachadorLVEV::GetInstancia(1).Vacia();

		grafoMuestra = make_shared<Grafo>();
		grafoBusqueda = make_shared<Grafo>(1);
	}

	virtual void TearDown() override
	{

	}

	shared_ptr<Grafo> grafoMuestra;
	shared_ptr<Grafo> grafoBusqueda;
};

TEST_F(testMatcheador, testCreaNuevasRaicesGrafoPequeno)
{
	ifstream fgm("C:\\Grafos\\g1p.g");
	ifstream fgb("C:\\Grafos\\g1p.g");

	fgm >> *grafoMuestra;
	fgb >> *grafoBusqueda;

	grafoMuestra->ExploraGrafo();
	grafoBusqueda->ExploraGrafo();

	MatcheadorPublico mp(*grafoMuestra, *grafoBusqueda);
	grafoMuestra->CreaFormaCanonica();

	auto arcos = grafoMuestra->GetArcos();

	mp.p_ObtenerRaices(arcos[0]);

	const int tamanoPatrones = 1;

	auto patrones = mp.GetPatrones(0);

	EXPECT_EQ(tamanoPatrones, patrones.size());
}

TEST_F(testMatcheador, testCreaNuevasRaicesGrafoMismosLVEV)
{
	ifstream fgm("C:\\Grafos\\g16.g");
	ifstream fgb("C:\\Grafos\\g16.g");

	fgm >> *grafoMuestra;
	fgb >> *grafoBusqueda;

	grafoMuestra->ExploraGrafo();
	grafoBusqueda->ExploraGrafo();

	MatcheadorPublico mp(*grafoMuestra, *grafoBusqueda);
	grafoMuestra->CreaFormaCanonica();

	auto arcos = grafoMuestra->GetArcos();

	mp.p_ObtenerRaices(arcos[0]);

	const int tamanoPatrones = 15;

	auto patrones = mp.GetPatrones(0);

	EXPECT_EQ(tamanoPatrones, patrones.size());
}

TEST_F(testMatcheador, testMatcheaGrafosPequenoSoporte01)
{
	ifstream fgm("C:\\Grafos\\g16.g");
	ifstream fgb("C:\\Grafos\\g16.g");

	ofstream log("C:\\Grafos\\g16.log");

	fgm >> *grafoMuestra;
	fgb >> *grafoBusqueda;

	grafoMuestra->ExploraGrafo();
	grafoBusqueda->ExploraGrafo();

	MatcheadorPublico mp(*grafoMuestra, *grafoBusqueda);
	mp.CambiaFlujo(&log);

	mp.MatcheaGrafos();

	const int soporte = 15;
	auto patronesSoporte1 = mp.GetPatrones(soporte);
	cout << endl << endl << "Se encontraron " << patronesSoporte1.size() << " patrones" << endl << endl;
	for (int i = 0, tam = patronesSoporte1.size(); i < tam; i++)
	{
		cout << "Para el patron " << i << " tiene tamano: " << patronesSoporte1[i]->ArcosGrafoMuestra.size() << endl;
	}
}