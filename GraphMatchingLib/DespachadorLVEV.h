#pragma once

#include <memory>
#include <map>

class LVEV;

class DespachadorLVEV
{
private:
	std::map<std::string, std::shared_ptr<LVEV> > _coleccionLVEV;
	DespachadorLVEV();
public:

	DespachadorLVEV(const DespachadorLVEV&) = delete;
	~DespachadorLVEV();
};

