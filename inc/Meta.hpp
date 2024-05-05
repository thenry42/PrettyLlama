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
		
		void addModel(string name, string size, string sizeType);
		Model* getModelBynName(string name);

	public:
		Meta();
		~Meta();

		void getModelsInfo();
		void printModels();
		void answerPrompt(string prompt);
};

#endif
