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

void Ollama::askModels(vector<Model*> models)
{
    for (vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
    {
        askOneModel(*it);
    }
}

void Ollama::askOneModel(Model *model)
{
    string cmd = "ollama run " + model->getName() + " " + model->getQuestion();
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
            _prompt += string(it->first) + "/";
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
    if (cmd == "/exit")
        return (-1);
    else if (cmd.find("/list") != string::npos)
        printModels();
    else if (cmd.find("/add") != string::npos)
    {
        try
        {
            string name = cmd.substr(5); 
            _effectiveModels[name] = getModelByName(name);
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
        }
        setPrompt();
    }
    else if (cmd.find("/remove") != string::npos)
    {
        try
        {
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
    else if (cmd.find("/help") != string::npos)
    {
        cout << endl;
        cout << BLUE "Available commands:" RESET << endl;
        cout << GREEN "/list: " RESET "list all models" << endl;
        cout << GREEN "/add [model]: " RESET "add a model" << endl;
        cout << GREEN "/remove [model]: " RESET "remove a model" << endl;
        cout << GREEN "/ask: " RESET "ask selected models" << endl;
        cout << GREEN "/exit: " RESET "exit" << endl;
        cout << endl;
    }
    else //ASK MODEL(S)
    {
        if (_effectiveModels.size() == 0)
        {
            cout << RED "No models selected" RESET << endl;
            return (0);
        }
    }

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