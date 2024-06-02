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
		bool	_needToAnswer;
		bool 	_tabStatus;

		Model();
		Model(const Model &);
		Model &operator=(const Model &);

	public:
		Model(string infos);
		~Model();

		string getName() const;
		string getSize() const;
		string getSizeType() const;
		string getPrompt() const;
		bool getNeedAnswer() const;
		bool getTabStatus() const;

		void setPrompt(string prompt);
		void setAnswer(string answer);
		void setNeedAnswer(bool status);
		void setTabStatus(bool status);
};

#endif
