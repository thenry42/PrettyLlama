#ifndef META_HPP
#define META_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include "Model.hpp"

using namespace std;

class Model;

class Meta
{
	private:
		map<string, Model*> _models;
	
		Meta(const Meta &);
		Meta &operator=(const Meta &);
		
	public:
		Meta();
		~Meta();

		Model* getModelByName(string name);
		Model* getModelByIndex(int index);
		std::map<string, Model*> getModels(void);

		void getOllamalist(void);
		void printModels(void);
		void setPrompt(string prompt);
		void askModels(void);
		void askOneModel(Model *model);
};

#endif
