#include "Ollama.hpp"

Ollama::Ollama() {}

Ollama::~Ollama() {}

Ollama::Ollama(const Ollama &) {}

Ollama &Ollama::operator=(const Ollama &)
{
    return (*this);
}

void Ollama::getOllamaList(void)
{
    // GET ALL MODELS (NAME)
    string cmd = "ollama list | awk '{print $1}' | sed 's/:latest//' | tail -n +2";
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
    {
        cerr << "popen failed" << endl;
        return ;
    }
    char buffer[256];
    string result = "";
    while (!feof(pipe))
    {
        if (fgets(buffer, 256, pipe) != NULL)
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
}

Model* Ollama::getModelByName(string name)
{
    if (_models.find(name) == _models.end())
        throw ModelNotFoundException();
    return (_models[name]);
}

void Ollama::printModels()
{
    for (map<string, Model*>::iterator it = _models.begin(); it != _models.end(); it++)
    {
        cout << it->first << endl;
    }
}

void Ollama::askModels(map<string, Model*> models)
{
    for (map<string, Model*>::iterator it = models.begin(); it != models.end(); it++)
    {
        askOneModel(it->second);
    }
}

void Ollama::askOneModel(Model *model)
{
    modelHeader(model->getName());
    string cmd = "ollama run " + model->getName() + " \"" + getQuestion() + "\"" + " | glow"; 
    system(cmd.c_str());
}

string Ollama::getPrompt(void)
{
    return (_prompt);
}

string Ollama::getQuestion(void)
{
    return (_question);
}

void Ollama::setPrompt(void)
{
    if (_effectiveModels.size() == 0)
        _prompt = string(RED "PrettyLlama > " RESET);
    else
    {
        _prompt = RED "PrettyLlama(" BLUE;
        for (auto it = _effectiveModels.begin(); it != _effectiveModels.end(); it++)
        {
            if (_metaModelSet == true && it->first == _metaModel->getName())
                _prompt += string(CYAN) + it->first + string(BLUE) + "/";
            else
                _prompt += string(BLUE) + it->first + "/";
        }
        _prompt.erase(_prompt.size() - 1);
        _prompt += RED ") > " RESET;
    }
}

void Ollama::setQuestion(string question)
{
    _question = question;
}

int Ollama::handleCommand(string cmd)
{
    if (cmd.find("/exit") != string::npos || cmd.find("/quit") != string::npos)
        return (-1);
    else if (cmd.find("/list") != string::npos)
        printModels();
    else if (cmd.find("/add") != string::npos)
        add(cmd);
    else if (cmd.find("/remove") != string::npos)
        remove(cmd);
    else if (cmd.find("/help") != string::npos)
        help();
    else if (cmd.find("/set-meta") != string::npos)
        setMeta(cmd);
    else if (cmd.find("/rm-meta") != string::npos)
        removeMeta(cmd);
    else
        ask(cmd); // ASK MODEL(S)
    return (0);
}

void Ollama::printWelcome(void)
{
    ifstream file(WELCOME_FILE);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
            cout << line << endl;
        file.close();
    }
    else
        cerr << "Unable to open file" << endl;
}

void Ollama::add(string cmd)
{
    try
    {
        if (cmd.size() < 5)
            throw ModelNotFoundException();
        string name = cmd.substr(5);
        _effectiveModels[name] = getModelByName(name);
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    setPrompt();
}

void Ollama::remove(string cmd)
{
    try
    {
        if (cmd.size() < 8)
            throw ModelNotFoundException();
        string name = cmd.substr(8);
        auto it = _effectiveModels.find(name);
        if (it != _effectiveModels.end())
            _effectiveModels.erase(it);
        else
            throw ModelNotFoundException();
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    setPrompt();
}

void Ollama::help(void)
{
    cout << endl;
    cout << BLUE "Available commands:" RESET << endl;
    cout << GREEN "/list: " RESET "list all models" << endl;
    cout << GREEN "/add [model]: " RESET "add a model" << endl;
    cout << GREEN "/remove [model]: " RESET "remove a model" << endl;
    cout << GREEN "/set-meta [model]: " RESET "set a specific model to Meta-Model" << endl;
    cout << GREEN "/rm-meta [model]: " RESET "remove the Meta-model" << endl;
    cout << GREEN "/ask: " RESET "ask selected models" << endl;
    cout << GREEN "/exit OR /quit: " RESET "exit" << endl;
    cout << endl;
}

void Ollama::setMeta(string cmd)
{
    try
    {
        if (cmd.size() < 10)
            throw ModelNotFoundException();
        string name = cmd.substr(10);
        Model *model = getModelByName(name);
        
        // SET META MODEL
        _metaModelSet = true;
        _metaModel = model;
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    setPrompt();
}

void Ollama::removeMeta(string cmd)
{
    try
    {
        if (cmd.size() < 9)
            throw ModelNotFoundException();
        string name = cmd.substr(9);
        Model *model = getModelByName(name);
    
        // REMOVE META MODEL
        if (_metaModelSet == true && _metaModel->getName() == model->getName())
            _metaModelSet = false;
        else
            throw ModelNotFoundException();
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    setPrompt();
}

void Ollama::ask(string cmd)
{
    if (_effectiveModels.size() == 0)
        cout << RED "No models selected" RESET << endl;
    else
    {
        setQuestion(cmd);
        askModels(_effectiveModels);
    }
}

void Ollama::modelHeader(string name)
{
    cout << endl;
    if (_metaModelSet == true && _metaModel->getName() == name)
        cout << CYAN "Meta-Model: " RESET << name << endl;
    else
        cout << BLUE "Model: " RESET << name << endl;
}