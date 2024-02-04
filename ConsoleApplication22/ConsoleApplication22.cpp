#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <cassert>
#include <windows.h>
#include <sstream>
#include  <fstream>
using namespace std;

class Answers
{
	string answer1;
	string answer2;
	string answer3;
	string answer4;
	string real_ans;
public:
	Answers()
	{
		answer1 = "";
		answer2 = "";
		answer3 = "";
		answer4 = "";
		real_ans = "";
	}
	Answers(string _answer1, string _answer2, string _answer3, string _answer4, string _real_ans) : Answers()
	{
		this->answer1 = _answer1;
		this->answer2 = _answer2;
		this->answer3 = _answer3;
		this->answer4 = _answer4;
		this->real_ans = _real_ans;
	}
	Answers(const Answers& other)
	{
		answer1 = other.answer1;
		answer2 = other.answer2;
		answer3 = other.answer3;
		answer4 = other.answer4;
		real_ans = other.real_ans;
	}
	Answers& operator=(const Answers& other)
	{
		answer1 = other.answer1;
		answer2 = other.answer2;
		answer3 = other.answer3;
		answer4 = other.answer4;
		real_ans = other.real_ans;
		return *this;
	}
	string get_answer1()
	{
		return answer1;
	}
	string get_answer2()
	{
		return answer2;
	}
	string get_answer3()
	{
		return answer3;
	}
	string get_answer4()
	{
		return answer4;

	}
	string get_real_ans()
	{
		return real_ans;
	}
	bool check_real_answer(string _real)
	{
		if (real_ans == _real)
		{
			return true;
		}
		return false;
	}
};



class Question
{
	string* _questions;
	Answers* _answers;
public:
	Question()
	{
		_questions = nullptr;
		_answers = nullptr;
	}
	Question(string question, Answers aswer) : Question()
	{
		_questions = new string(question);
		_answers = new Answers(aswer);
	}
	Question(string question, string _answer1, string _answer2, string _answer3, string _answer4, string _real_ans) : Question()
	{
		_questions = new string(question);
		_answers = new Answers(_answer1, _answer2, _answer3, _answer4, _real_ans);
	}
	Question(const Question& other)
	{
		_questions = other._questions;
		_answers = other._answers;
	}
	Question& operator=(const Question& other)
	{
		_questions = other._questions;
		_answers = other._answers;
		return *this;
	}

	string* get_questions()
	{
		return _questions;
	}
	Answers* get_answers()
	{
		return _answers;
	}
	void Print()
	{
		cout << *_questions << endl;
		cout << _answers->get_answer1()
			<< " " << _answers->get_answer2()
			<< " " << _answers->get_answer3()
			<< " " << _answers->get_answer4() << endl;
	}

	Question operator=(Question& other)
	{
		this->_questions = other._questions;
		this->_answers = other._answers;
	}

	~Question()
	{
		if (_questions != nullptr)
		{
			delete _questions;
		}
		if (_answers != nullptr)
		{
			delete _answers;
		}
	}
};



class Quiz
{
	string _quiz_name;
	vector<Question*> _questions;
public:
	Quiz()
	{
		_quiz_name = "";
		_questions;
	}
	Quiz(string name)
	{
		_quiz_name = name;
	}
	Quiz(string _name, vector<Question*> questionn)
	{
		_quiz_name = _name;
		_questions = questionn;
	}
	Quiz(Quiz& other)////Name yazmaq lazimdi?
	{
		this->_questions = other._questions;
	}
	Quiz operator=(Quiz& other)////Name yazmaq lazimdi?
	{
		this->_questions = other._questions;
	}
	vector<Question*> get_questions()
	{
		return _questions;
	}
	auto set_name(string name)
	{
		if (name.size() >= 3 && name.size() <= 15)
		{
			this->_quiz_name = name;
			return _quiz_name;
		}
	}
	string get_quiz_name() const
	{
		return _quiz_name;
	}
	int GetQuestionCount() const {
		return static_cast<int>(_questions.size());
	}
	void save_to_file()
	{
		ofstream file(_quiz_name + ".txt", ios::out);

		if (!file.is_open())
		{
			throw "File is not open (save to file)";
		}

		for (auto i : _questions)
		{
			file << "~^" << *(i->get_questions()) << "?^"
				<< i->get_answers()->get_answer1() << "^"
				<< i->get_answers()->get_answer2() << "^"
				<< i->get_answers()->get_answer3() << "^"
				<< i->get_answers()->get_answer4() << "^"
				<< i->get_answers()->get_real_ans() << "\n";
		}
		file.close();
	}
	void clear_questions()
	{
		for (Question* question : _questions) {
			delete question;
		}
		(_questions).clear();
	}
	void add_question(string questionText, string answer1, string answer2, string answer3, string answer4, string real_answer) {
		Answers* answers = new Answers(answer1, answer2, answer3, answer4, real_answer);

		Question* question = new Question(questionText, *answers);
		_questions.push_back(question);
	}

	void load_from_file()
	{
		ifstream file(_quiz_name + ".txt");
		if (!file.is_open())
		{
			throw "File is not open (load from file)";
		}

		while (!(file.eof()))
		{
			string questionText;
			string sd, answer1, answer2, answer3, answer4, real_answer;
			getline(file, sd, '^');
			if (!(file.eof()))
			{
				getline(file, questionText, '^');
				getline(file, answer1, '^');
				getline(file, answer2, '^');
				getline(file, answer3, '^');
				getline(file, answer4, '^');
				getline(file, real_answer, '\n');
				this->_questions.push_back(new Question(questionText, answer1, answer2, answer3, answer4, real_answer));
			}
		}
		file.close();
	}

};



#pragma region Musteqil Functions
void loading_screen()
{

}

void write_to_leader_board(string name, int question_size, int tru, int wrng, int pass)
{
	ofstream file("Leader Board.txt", ios::app);
	if (file.is_open())
	{
		file << "Name: " << name << "\n"
			<< "Question size: " << question_size << "\n"
			<< "True answers: " << tru << "\n"
			<< "False answers: " << wrng << "\n"
			<< "Passes answers: " << pass << "\n" << "\n";
	}
	file.close();
}
void write_quiz_names_to_file(const vector<Quiz*>& quizzes) {
	ofstream file("Quiz_names.txt", ios::app);
	if (file.is_open()) {
		for (const Quiz* quiz : quizzes) {
			file << quiz->get_quiz_name() << endl;
		}

		file.close();
	}
	else {
		cout << "Error: Unable to write to file." << endl;
	}
	file.close();
}
void read_leader_board_from_file()
{
	ifstream file("Leader Board.txt", ios::in);

	if (file.is_open())
	{
		while (!file.eof())
		{
			string name, question_size, tru, wrng, pass, free;
			getline(file, name);
			getline(file, question_size);
			getline(file, tru);
			getline(file, wrng);
			getline(file, pass);

			cout << name << "\n"
				<< question_size << "\n"
				<< tru << "\n"
				<< wrng << "\n"
				<< pass << "\n"
				<< free;
		}
	}
	else
	{
		throw exception("Leader Board is not opened");
	}
	file.close();
}
vector<string> read_quiz_names_from_file()
{
	vector<string> quizNames;
	ifstream file("quiz_names.txt", ios::in);

	if (file.is_open()) {
		string quizName;
		while (getline(file, quizName)) {
			quizNames.push_back(quizName);
		}

		file.close();
	}
	else {
		cout << "\n\t\t\t\tError: Unable to read file." << endl;
	}
	file.close();
	return quizNames;
}
int find_quiz_index_by_name(string quizName, const vector<Quiz*>& quizzes) {
	for (size_t i = 0; i < quizzes.size(); i++) {
		if (quizzes[i]->get_quiz_name() == quizName) {
			return static_cast<int>(i);
		}
	}
	return -1;
}
#pragma endregion

int main()
{
	string menu = R"(
            [1] Create Quiz
            [2] Start Quiz
            [3] Leaderboard
            [0] Exit    )";
	int secim;

	while (true)
	{
		cout << menu << endl;
		cout << "Secim daxil edin: ";

		cin >> secim;

#pragma region Create Quiz
		if (secim == 1)
		{
			cin.ignore();
			vector<Quiz*>quizzes;
			string quizName;
			cout << "Enter the name of the new quiz: ";
			getline(cin, quizName);

			Quiz* newQuiz = new Quiz(quizName);

			quizzes.push_back(newQuiz);

			while (true) {
				string questionText;
				cout << "\nEnter the question text (or 'exit' to finish adding questions): ";
				getline(cin, questionText);

				if (questionText == "exit") {
					newQuiz->save_to_file();
					write_quiz_names_to_file(quizzes);
					break;
				}

				string answer1, answer2, answer3, answer4, real;
				cout << "\n\t\t\t\t\tEnter answer 1: ";
				getline(cin, answer1);
				cout << "\n\t\t\t\t\tEnter answer 2: ";
				getline(cin, answer2);
				cout << "\n\t\t\t\t\tEnter answer 3: ";
				getline(cin, answer3);
				cout << "\n\t\t\t\t\tEnter answer 4: ";
				getline(cin, answer4);
				cout << "\n\t\t\t\t\tEnter real answer: ";
				getline(cin, real);

				newQuiz->add_question(questionText, answer1, answer2, answer3, answer4, real);
			}
		}
#pragma endregion


#pragma region Start Quiz
		else if (secim == 2)
		{
			cin.ignore();
			string name;
			vector<Quiz*> quizzes;
			cout << "Enter your name: ";
			getline(cin, name);
			vector<string> quizNames = read_quiz_names_from_file();
			if (quizNames.empty()) {
				cout << "Quiz yoxdur" << endl;
				break;
			}

			cout << "Quizler:   " << endl;
			for (const string& name : quizNames)
			{
				cout << name << endl;
			}

			string quizName;
			cout << "Quiz adini daxil edin: ";
			getline(cin, quizName);

			int quizIndex = find_quiz_index_by_name(quizName, quizzes);
			if (quizIndex == -1) {
				bool isCheck = false;
				for (const string& name : quizNames)
				{
					if (name == quizName) {
						isCheck = true;
						break;
					}
				}

				if (isCheck)
				{
					Quiz* newQuiz = new Quiz(quizName);
					quizzes.push_back(newQuiz);
					quizIndex = quizzes.size() - 1;
				}
				else
				{
					cout << "Bele adda quiz yoxdur.";
					break;
				}
			}

			Quiz& chosenQuiz = *quizzes[quizIndex];

			system("cls");
			try {
				chosenQuiz.load_from_file();
			}
			catch (const exception& e) {
				cout << e.what() << endl;
				break;
			}

			cout << "\n\t\t\t\t\tStarting quiz: " << chosenQuiz.get_quiz_name() << endl;

			int totalQuestions = chosenQuiz.GetQuestionCount();
			int correctAnswers = 0;

			if (totalQuestions == 0) {
				cout << "Quiz boshdur!" << endl;
				break;
			}

			system("cls");
			string asn;
			int pass = 0;
			int wrng = 0;
			int count = 0;
			for (int lindex = 0; lindex < totalQuestions; ++lindex)
			{
				auto questions = chosenQuiz.get_questions();
				auto answers = questions[lindex]->get_answers();

				cout << (*(*(questions[lindex])).get_questions()) << endl;
				cout << answers->get_answer1() << endl;
				cout << answers->get_answer2() << endl;
				cout << answers->get_answer3() << endl;
				cout << answers->get_answer4() << endl;

				cout << "Cavab(pass etmek ucun sadece entere basin): ";
				getline(cin, asn);
				cout << endl;
				if (asn == (answers->get_real_ans()))
				{
					count++;
				}
				else if (asn == "")
				{
					pass++;
				}
				else
				{
					wrng++;
				}
			}
			write_to_leader_board(name, totalQuestions, count, wrng, pass);
		}

#pragma endregion


#pragma region Leader Board
		else if (secim == 3)
		{
			cin.ignore();
			system("cls");
			read_leader_board_from_file();

		}
#pragma endregion

		else if (secim == 0)
		{
			cout << "Exited...";
			break;
		}
	}
}