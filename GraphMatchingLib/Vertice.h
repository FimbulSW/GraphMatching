#pragma once

#include <string>
#include <iostream>

class Vertice
{
public:
	Vertice(const std::string&, int);
	~Vertice(void);

	const std::string& GetEtiqueta();
	int GetEnumeracion();
	int GetGrado();
	void SetGrado(int);
	bool operator < (const Vertice&);
	friend std::ostream& operator<<(std::ostream&, const Vertice&);

private:
	std::string _etiqueta;
	int _enumeracion;
	int _grado;
};

