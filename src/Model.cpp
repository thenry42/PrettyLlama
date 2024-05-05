#include "Model.hpp"

Model::Model(std::string name, string size, string sizeType) : _name(name), _size(size), _sizeType{sizeType} {}

Model::~Model() {}

Model::Model(const Model &) {}

Model &Model::operator=(const Model &)
{
    return (*this);
}

string Model::getName() const
{
    return (_name);
}

string Model::getSize() const
{
    return (_size);
}

string Model::getSizeType() const
{
    return (_sizeType);
}