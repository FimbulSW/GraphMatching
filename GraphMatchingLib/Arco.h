#pragma once

#include <iostream>
#include <string>
#include <memory>

class Vertice;

class Arco
{
public:
	Arco(const std::shared_ptr<Vertice>&, const std::shared_ptr<Vertice>&, const std::string&);
	~Arco(void);
	friend std::ostream& operator<<(std::ostream&, const Arco&);
private:
	std::shared_ptr<Vertice> _origen, _destino;
	int _gradoAdyacencia;
	std::string _etiqueta;
};

