// GraphMatchingThesis.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Vertice.h"
#include "Arco.h"
#include <memory>
#include <utility>

using namespace std;

int main(int argc, char** argv)
{
	auto origen = make_shared<Vertice>("A", 1);
	auto destino = make_shared<Vertice>("C", 2);
	auto arco = make_shared<Arco>(origen, destino, "b");

	cout<<*arco<<endl;

	return 0;
}

