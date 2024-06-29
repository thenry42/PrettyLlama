#ifndef OLLAMA_HPP
#define OLLAMA_HPP

#include <map>
#include <set>
#include <string>
#include <cstdio>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>
#include <unordered_set>
#include <nlohmann/json.hpp>

#include "Model.hpp"

#define HELP_FILE "/usr/share/PrettyLlama/HelpFile"
#define CONFIG_FILE "/usr/share/PrettyLlama/config.json"
#define WELCOME_FILE "/usr/share/PrettyLlama/WelcomeHeader"

#define GET_OLLAMA_LIST "ollama list | awk '{print $1}' | sed 's/:latest//' | tail -n +2"
#define PRINT_LIST "ollama list | awk '{print $1, $3, $4}' | sed 's/:latest//' | tail -n +2"

#define RESET 	"\033[0m"
#define RED 	"\033[1;31m"
#define BLUE 	"\033[1;34m"
#define CYAN 	"\033[1;36m"
#define GREEN 	"\033[1;32m"
#define YELLOW 	"\033[1;33m"
#define MAGENTA "\033[1;35m"

using namespace std;
using json = nlohmann::json;

class Model;

class Ollama
{
	private:

		json 		_j;
		char* 		_cmd;
		string 		_prompt;
		string 		_question;
		Model* 		_superModel;
		bool 		_superModelSet;
		map<string, Model*> _models;
		map<string, Model*> _effectiveModels;
	
	public:
			
		Ollama(void);
		Ollama(const Ollama &);
		Ollama &operator=(const Ollama &);
		~Ollama();

		// Getters
		char* 	getCmd(void);
		string 	getPrompt(void);
		string 	getQuestion(void);
		void 	getOllamaList(void);
		Model* 	getModelByName(string name);

		// Setters
		void 	setPrompt(void);
		void 	setCmd(char* cmd);
		void 	setQuestion(string question);

		// Methods		
		
		void 	printModels(void);
		void 	askOneModel(Model *model);
		int 	handleCommand(string s_cmd);	
		void 	askModels(map<string, Model*> models);
		void 	askSuperModel(map<string, Model*> effectiveModels, Model *superModel);

		void 	help(void);
		void 	setConfig(void);
		void 	loadConfig(void);
		void 	add(string s_cmd);
		void 	removeSuper(void);
		void 	ask(string s_cmd);
		void 	remove(string s_cmd);
		void 	setSuper(string s_cmd);
		void 	modelHeader(string modelName);
		void 	extractModelsFromConfig(json &j);

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
};

void 	printWelcome(void);
string 	escapeSpecialCharacters(string str);
void 	saveJsonToFile(json &j, string filename);

#endif
