#include "Meta.hpp"

Meta::Meta() {}

Meta::~Meta() {}

Meta::Meta(const Meta &) {}

Meta &Meta::operator=(const Meta &)
{
    return (*this);
}

void Meta::addModel(string name, string size, string sizeType)
{
    Model *model = new Model(name, size, sizeType);
    _models[name] = model;
}

void Meta::getModelsInfo()
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

    // PUT EVERY MODEL INFO INTO A VECTOR
    size_t pos = 0;
    vector<string> models;
    while ((pos = result.find("\n", pos)) != string::npos)
    {
        models.push_back(result.substr(0, pos));
        result.erase(0, pos + 1);
        pos = 0;
    }

    // ADD MODELS TO _models
    for (long unsigned int i = 0; i < models.size(); i++)
    {
        string name = models[i].substr(0, models[i].find(" "));
        size_t firstSpaceIndex = models[i].find(" ");
        size_t secondSpaceIndex = models[i].find(" ", firstSpaceIndex + 1);
        string size = models[i].substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1);
        string sizeType = models[i].substr(secondSpaceIndex + 1);
        addModel(name, size, sizeType);
    }
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
    }
}

void Meta::answerPrompt(string prompt)
{
    cout << "your question is: '" << prompt  << "'." << endl;
}