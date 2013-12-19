#pragma once

#include <iostream>
#include <string>
#include <memory>

class Vertice;
class Etiqueta;

//Enumera los tipos de estados en los que un arco puede encontrarse.
//Ya sea como 'Visitado', 'Listo', o 'En espera'
enum class EstadoArco
{
	VISITADO,
	LISTO,
	ESPERA
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
	Arco(const std::shared_ptr<Vertice>&, const std::shared_ptr<Vertice>&, const std::string&);

	~Arco(void);

	//Sobrecarga el operador '<<' para objetos de tipo ostream.
	friend std::ostream& operator<<(std::ostream&, const Arco&);

	//Sobrecarga del operador '<' para poder ordenar los arcos en base a su forma canónica.
	bool operator<(const Arco&) const;

	//Nos regresa una referencia al apuntador inteligente del origen.
	const std::shared_ptr<Vertice>& GetOrigen();

	//Nos regresa una referencia al apuntador inteligente del destino.
	const std::shared_ptr<Vertice>& GetDestino();

	//Nos regresa el grado de adyacencia del arco.
	int GetGrado() const;

	//Nos regresa la frecuencia del arco.
	int GetFrecuencia() const;

	//Asignamos la frecuencia del Arco
	void SetFrecuencia(int);

	//Nos regresa el LVEV.
	const std::string& GetLVEV() const;

	//Calcula el grado del arco en base a su origen y destino.
	void CalcularGrado();
private:
	std::shared_ptr<Vertice> _origen, _destino;
	int _gradoAdyacencia;
	int _frecuencia;
	std::shared_ptr<Etiqueta> _etiqueta;
	std::string _vev;
	EstadoArco _estado;
};
