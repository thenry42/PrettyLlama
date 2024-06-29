#include "Ollama.hpp"

Ollama::Ollama()
{
    _models = map<string, Model*>();
    _effectiveModels = map<string, Model*>();
    _superModel = NULL;
    _superModelSet = false;
    _prompt = "";
    _question = "";
    _cmd = NULL;
}

Ollama::~Ollama() {}

Ollama::Ollama(const Ollama &) {}

Ollama &Ollama::operator=(const Ollama &)
{
    return (*this);
}

// GETTERS

string Ollama::getPrompt(void)
{
    return (_prompt);
}

string Ollama::getQuestion(void)
{
    return (_question);
}

void Ollama::getOllamaList(void)
{
    // GET ALL MODELS (NAME)
    string cmd = GET_OLLAMA_LIST;
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

char* Ollama::getCmd(void)
{
    return (_cmd);
}

// SETTERS

void Ollama::setPrompt(void)
{
    if (_effectiveModels.size() == 0)
        _prompt = string(RED "PrettyLlama > " RESET);
    else
    {
        _prompt = RED "PrettyLlama(" BLUE;
        for (auto it = _effectiveModels.begin(); it != _effectiveModels.end(); it++)
        {
            if (_superModelSet == true && it->first == _superModel->getName())
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

void Ollama::setCmd(char* cmd)
{
    _cmd = cmd;
}

// METHODS

void Ollama::printModels()
{
    system(PRINT_LIST);
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
    else if (cmd.find("/set-super") != string::npos)
        setSuper(cmd);
    else if (cmd.find("/rm-super") != string::npos)
        removeSuper();
    else if (cmd.find("/config") != string::npos)
        setConfig();
    else if (cmd[0] == '/' && cmd.find('/') != string::npos)
        cout << RED "Invalid command" RESET << endl;
    else
        ask(cmd); // ASK MODEL(S)
    return (0);
}

void printWelcome(void)
{
    string welcome = WELCOME_FILE;
    string cmd = "cat " + welcome + " | glow";
    system(cmd.c_str());
}

void Ollama::add(string cmd)
{
    try
    {
        if (cmd.size() < 5)
            throw ModelNotFoundException();
        string str = cmd.substr(5);
        std::istringstream ss(str);
        string model;
        while (ss >> model)
        {
            _effectiveModels[model] = getModelByName(model);
        }
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
        string str = cmd.substr(8);
        std::istringstream ss(str);
        string model;
        while (ss >> model)
        {
            auto it = _effectiveModels.find(model);
            if (it != _effectiveModels.end())
                _effectiveModels.erase(it);
            else
                throw ModelNotFoundException();
        }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    setPrompt();
}

void Ollama::help(void)
{
    string help = HELP_FILE;
    string cmd = "cat " + help + " | glow";
    system(cmd.c_str());
}

void Ollama::setSuper(string cmd)
{
    try
    {
        if (cmd.size() < 11)
            throw ModelNotFoundException();
        string name = cmd.substr(11);
        Model *model = getModelByName(name);
        
        // SET META MODEL
        _superModelSet = true;
        _superModel = model;
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    setPrompt();
}

void Ollama::removeSuper(void)
{
    try
    {
        // REMOVE META MODEL
        if (_superModelSet == true)
            _superModelSet = false;
        else
            throw SuperModelNotFoundException();
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    setPrompt();
}

void Ollama::extractModelsFromConfig(json &j)
{
    if (j.contains("EffectiveModels"))
    {
        for (auto& model : j["EffectiveModels"])
        {
            if (model.is_string())
            {
                string name = model.get<string>();
                _effectiveModels[name] = getModelByName(name);
            }
        }
    }
    if (j.contains("SuperModel") && j["SuperModel"].is_object())
    {
        if (j["SuperModel"].contains("name"))
        {
            if (j["SuperModel"]["name"].is_string())
            {
                std::string superModelName = j["SuperModel"]["name"].get<std::string>();
                _superModel = getModelByName(superModelName);
                _superModelSet = true;
            } 
        }
    }
    setPrompt();
}

void Ollama::loadConfig(void)
{
    ifstream file(CONFIG_FILE);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file" << endl;
        return ;
    }
    
    try
    {
        file >> _j;
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << endl;
    }
    extractModelsFromConfig(_j);
}

void Ollama::setConfig(void)
{
    // Removing current Effective Models
    if (_j.contains("EffectiveModels"))
        _j["EffectiveModels"].clear();

    // Removing current Super Model
    if (_j.contains("SuperModel"))
        _j["SuperModel"].clear();

    // Adding new Effective Models
    for (auto it = _effectiveModels.begin(); it != _effectiveModels.end(); it++)
    {
        _j["EffectiveModels"].push_back(it->first);
    }

    // Adding new Super Model
    if (_superModelSet == true)
    {
        _j["SuperModel"]["name"] = _superModel->getName();
    }

    try
    {
        saveJsonToFile(_j, CONFIG_FILE);
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
}

void saveJsonToFile(json &j, string filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file" << endl;
        return ;
    }
    file << j.dump(4);
    file.close();
}

void Ollama::ask(string cmd)
{
    if (_effectiveModels.size() == 0)
        cout << RED "No models selected" RESET << endl;
    else if (_superModelSet == true)
    {
        setQuestion(cmd);
        askSuperModel(_effectiveModels, _superModel);
    }
    else
    {
        setQuestion(cmd);
        askModels(_effectiveModels);
    }
}

void Ollama::modelHeader(string name)
{
    cout << endl;
    if (_superModelSet == true && _superModel->getName() == name)
        cout << CYAN "Super-Model: " RESET << name << endl;
    else
        cout << BLUE "Model: " RESET << name << endl;
}

void Ollama::askSuperModel(map<string, Model*> effectiveModels, Model *superModel)
{
    modelHeader(superModel->getName());

    string fullAnswer;

    for (map<string, Model*>::iterator it = effectiveModels.begin(); it != effectiveModels.end(); it++)
    {
        string cmd = "ollama run " + it->first + " \"" + getQuestion() + "\"";
        FILE *pipe = popen(cmd.c_str(), "r");
        if (!pipe)
        {
            cerr << "popen failed" << endl;
            return ;
        }
        char buffer[512];
        string result = "";
        while (!feof(pipe))
        {
            if (fgets(buffer, 512, pipe) != NULL)
                result += buffer;
        }
        pclose(pipe);
        fullAnswer += result;
        fullAnswer += "\n";
    }

    fullAnswer = escapeSpecialCharacters(fullAnswer);
    string cmd2 = "ollama run " + _superModel->getName() + " \" " + fullAnswer + " \"" + " | glow";
    system(cmd2.c_str());
}

// UTILS

string escapeSpecialCharacters(string str)
{
    std::unordered_set<char> specialChars ={
        '*', '?', '[', ']', '{', '}', '$', '`', '&', ';', '|', '>', '<', '(', ')', 
        '!', '#', '~', '"', '\'', '\\', '=', '+', '-', '/', ' ', ':', '%', '@', '^'
    };

    string result;

    for (char c: str)
    {
        if (specialChars.find(c) != specialChars.end())
            result += '\\';
        result += c;
    } 

    return (result);
}