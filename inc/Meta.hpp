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
		
		Model* getModelBynName(string name);

	public:
		Meta();
		~Meta();

		void getModelInfos();
		void printModels();
		void setPrompt(string prompt);
		void askModels();
		void askOneModel(Model *model);
};

#endif
