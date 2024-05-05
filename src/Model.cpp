#include "Model.hpp"

Model::Model(string infos)
{
    size_t firstSpaceIndex = infos.find(" ");
    size_t secondSpaceIndex = infos.find(" ", firstSpaceIndex + 1);
    _name = infos.substr(0, firstSpaceIndex);
    _size = infos.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1);
    _sizeType = infos.substr(secondSpaceIndex + 1);
    _prompt = "";
    _answer = "";
    _needToAnswer = true;
}

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

string Model::getPrompt() const
{
    return (_prompt);
}

bool Model::getStatus() const
{
    return (_needToAnswer);
}

void Model::setPrompt(string prompt)
{
    _prompt = prompt;
}

void Model::setAnswer(string answer)
{
    _answer = answer;
}

void Model::setStatus(bool status)
{
    _needToAnswer = status;
}