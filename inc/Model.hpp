#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>

using namespace std;

class Model
{
	private:

		string 	_name;
		string 	_answer;
		string 	_question;

	public:
		
		Model(string name);
		Model(const Model &);
		Model &operator=(const Model &);	
		~Model();

		// Getters
		string getName() const;
		string getQuestion() const;
		string getAnswer() const;

		// Setters
		void setQuestion(string question);
		void setAnswer(string answer);
};

#endif
