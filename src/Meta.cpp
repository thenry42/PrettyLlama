#include "Meta.hpp"

Meta::Meta() {}

Meta::~Meta() {}

Meta::Meta(const Meta &) {}

Meta &Meta::operator=(const Meta &)
{
    return (*this);
}

void Meta::getModelInfos()
{
    // GET ALL MODELS (name | SIZE | SIZE_TYPE)
    string cmd = "ollama list | awk '{print $1, $3, $4}' | sed 's/:latest//' | tail -n +2";
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
    {
        cerr << "popen failed" << endl;
        return ;
    }
    char buffer[128];
    string result = "";
    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);

    // CREATE MODELS
    size_t pos = 0;
    vector<string> models;
    while ((pos = result.find("\n", pos)) != string::npos)
    {
        Model *model = new Model(result.substr(0, pos));
        _models[model->getName()] = model;
        result.erase(0, pos + 1);
        pos = 0;
    }

    // MODELS TO IGNORE
    _models["dolphin-mixtral"]->setStatus(false);
    _models["starcoder2"]->setStatus(false);
    _models["mixtral"]->setStatus(false);
}

Model* Meta::getModelBynName(string name)
{
    return (_models[name]);
}

void Meta::printModels()
{
    for (map<string, Model*>::iterator it = _models.begin(); it != _models.end(); it++)
    {
        cout << "Name: " << it->first << endl;
        cout << "Size: " << it->second->getSize() << endl;
        cout << "Size Type: " << it->second->getSizeType() << endl;
        cout << "Prompt: " << it->second->getPrompt() << endl;
    }
}

void Meta::setPrompt(string prompt)
{
    for (std::map<string, Model*>::iterator it = _models.begin(); it != _models.end(); it++)
    {
        it->second->setPrompt(prompt);
    }
}

void Meta::askModels()
{
    // Iterate thru all models and ask for answers
    for (std::map<string, Model*>::iterator it = _models.begin(); it != _models.end(); it++)
    {
        askOneModel(it->second);
    }
}

void Meta::askOneModel(Model *model)
{
    if (!model->getStatus())
        return ;
    string cmd = "ollama run " + model->getName() + " " + model->getPrompt();
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
    {
        cerr << "popen failed" << endl;
        return ;
    }
    char buffer[128];
    string answer = "";
    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL)
            answer += buffer;
    }
    pclose(pipe);
    answer.erase(answer.size() - 1);
    model->setAnswer(answer);
    cout << model->getName() << " answer: " << answer;
}