#include "Arco.h"
#include "Vertice.h"


Arco::Arco(const std::shared_ptr<Vertice>& v1, const std::shared_ptr<Vertice>& v2, const std::string& etiqueta)
	: _origen(nullptr), _destino(nullptr), _etiqueta("")
{
	bool comparacion = *v1 < *v2;
	_origen = comparacion ? v1 : v2;
	_destino = comparacion ? v2 : v1;

	std::string or = comparacion ? v1->GetEtiqueta() : v2->GetEtiqueta();
	std::string de = comparacion ? v2->GetEtiqueta() : v1->GetEtiqueta(); 

	_etiqueta = or + etiqueta + de;
}


Arco::~Arco(void)
{
}

std::ostream& operator<<(std::ostream& salida, const Arco& arco)
{
	salida<<"Arco con etiqueta: "<<arco._etiqueta<<std::endl;
	salida<<"Origen: "<<*arco._origen<<std::endl;
	salida<<"Destino: "<<*arco._destino<<std::endl;
	return salida;
}