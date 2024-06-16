#ifndef OLLAMA_HPP
#define OLLAMA_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <cstdio>
#include <vector>
#include <cstring>
#include "Model.hpp"

#define WELCOME_FILE "/usr/share/PrettyLlama/WelcomeHeader"
#define HELP_FILE "/usr/share/PrettyLlama/HelpFile"
#define GET_OLLAMA_LIST "ollama list | awk '{print $1}' | sed 's/:latest//' | tail -n +2"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

using namespace std;

class Model;

class Ollama
{
	private:

		map<string, Model*> _models;
		map<string, Model*> _effectiveModels;
		Model* _superModel;
		bool _superModelSet;
		string _prompt;
		string _question;
	
	public:
		
		string cmd;
		
		Ollama(void);
		Ollama(const Ollama &);
		Ollama &operator=(const Ollama &);
		~Ollama();
		
		void printModels(void);
		void askModels(map<string, Model*> models);
		void askSuperModel(map<string, Model*> effectiveModels, Model *superModel);
		void askOneModel(Model *model);
		int handleCommand(string cmd);
		void printWelcome(void);
		
		Model* getModelByName(string name);
		void getOllamaList(void);
		string getPrompt(void);
		string getQuestion(void);
		
		void setQuestion(string question);
		void setPrompt(void);

		class ModelNotFoundException : public exception
		{
			public:
				virtual const char* what() const throw()
				{
					return (RED "Model not found" RESET);
				}
		};
		
		class SuperModelNotFoundException : public exception
		{
			public:
				virtual const char* what() const throw()
				{
					return (RED "Super Model not found" RESET);
				}
		};

		void add(string cmd);
		void remove(string cmd);
		void setSuper(string cmd);
		void removeSuper(void);
		void help(void);
		void ask(string cmd);

		void modelHeader(string modelName);
};

string escapeSpecialCharacters(string str);

#endif
