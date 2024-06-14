#include "Model.hpp"

Model::Model(string name): _name(name) {}

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

string Model::getQuestion() const
{
    return (_question);
}

void Model::setQuestion(string question)
{
    _question = question;
}

void Model::setAnswer(string answer)
{
    _answer = answer;
}

string Model::getAnswer() const
{
    return (_answer);
}