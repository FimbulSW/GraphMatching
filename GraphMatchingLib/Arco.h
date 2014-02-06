#pragma once

#include <iostream>
#include <string>
#include <memory>

class Vertice;
class Etiqueta;
class LVEV;

//Enumera los tipos de estados en los que un arco puede encontrarse.
//Ya sea como 'Visitado', 'Listo', 'En espera' o 'Matcheado
enum class EstadoArco
{
	VISITADO,
	LISTO,
	ESPERA,
	MATCHEADO
};

//Clase que maneja el comportamiento de los arcos.
//Contiene 2 vértices (origen y destino), etiqueta, grado de adyacencia
//Etiqueta del arco del tipo LVEV

class Arco
{
public:
	//Constructor del arco, admite 2 apuntadores (origen, destino) y la etiqueta del mismo.
	//El constructor por default ordenará el origen y destino en orden lexicográfico.
	//Así como el estado se pondrá por default como ESPERA
	Arco(const std::shared_ptr<Vertice>&, const std::shared_ptr<Vertice>&, const std::string&, int = 0);

	~Arco(void);

	//Sobrecarga el operador '<<' para objetos de tipo ostream.
	friend std::ostream& operator<<(std::ostream&, const Arco&);

	//Sobrecarga del operador '<' para poder ordenar los arcos en base reglas, se especifica en el archivo de implementación. =D
	bool operator<(const Arco&) const;

	//Nos regresa una referencia al apuntador inteligente del origen.
	const std::shared_ptr<Vertice>& GetOrigen();

	//Nos regresa una referencia al apuntador inteligente del destino.
	const std::shared_ptr<Vertice>& GetDestino();

	//Nos regresa el grado de adyacencia del arco.
	int GetGrado() const;

	//Nos regresa la frecuencia del arco.
	int GetFrecuencia() const;

	//Nos regresa la etiqueta del arco. No confundir con LVEV.
	const std::string& GetEtiqueta() const;

	//Nos regresa el LVEV en forma de cadena.
	const std::string& GetLVEVString() const;

	//Nos regresa un puntero a el LVEV
	const std::shared_ptr<LVEV>& GetLVEV() const;
	
	//Obtiene el estado actual del arco.
	EstadoArco GetEstado() const;

	//Cambia el estado del arco.
	void SetEstado(EstadoArco);

	//Calcula el grado del arco en base a su origen y destino.
	void CalcularGrado();

	//Verifica si 2 arcos comparten el mismo lvev, para asuntos de identificación del patrón.
	bool operator==(const Arco&) const;

private:
	std::shared_ptr<Vertice> _origen, _destino;
	std::shared_ptr<Etiqueta> _etiqueta;
	std::shared_ptr<LVEV> _lvev;
	int _gradoAdyacencia;
	EstadoArco _estado;
};
