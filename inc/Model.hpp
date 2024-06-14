#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>

using namespace std;

class Model
{
	private:

		string 	_name;
		string 	_question;
		string 	_answer;

	public:
		
		Model(string name);
		Model(const Model &);
		Model &operator=(const Model &);	
		~Model();

		string getName() const;
		string getQuestion() const;
		string getAnswer() const;

		void setQuestion(string question);
		void setAnswer(string answer);
};

#endif
