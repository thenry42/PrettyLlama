#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>

using namespace std;

class Model
{
	private:
		string 	_name;
		string	_size;
		string 	_sizeType;
		string 	_prompt;
		string 	_answer;
		bool	needToAnswer;

		Model();
		Model(const Model &);
		Model &operator=(const Model &);

	public:
		Model(string name, string size, string sizeType);
		~Model();

		string getName() const;
		string getSize() const;
		string getSizeType() const;
		string getPrompt() const;

		void setPrompt(string prompt);
		void setAnswer(string answer);
};

#endif
