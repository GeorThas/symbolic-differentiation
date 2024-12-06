#include "myFunctions.h"
#include "Tokenizator.h"
#include "Error.h"
#include "RevPolNot.h"
#include "Differentiation.h"
#include "DiffParser.h"

int SubNumbers(int a, int b) {
	return a - b;
}

int AddNumbers(int a, int b) {
	return a + b;
}

void GetValue(char* str, int strlen) {

	std::string buf(str, 3);
	std::string res;// = "Result from c#" + buf;
	
	//===============

	std::vector<Token> tokensList, tokensListRPN;

	std::string expr(str); //= "8-x^3";
	//std::cout << "Expression: " << expr << std::endl;

	try
	{
		tokenize(expr, tokensList); // Токенизация строки с выражением

		//std::cout << GetTokensList(tokensList); // Вывод токенов

		ShuntingYard(tokensList, tokensListRPN); // 

		//std::cout << "\n Reverse Polish Notation: ";
		//for (auto& i : tokensListRPN)
		//	std::cout << i.getStr() << " ";
		//std::cout << "\n";

		//std::cout << "Answer: " << countRPN(tokensListRPN) << "\n"; //???
		std::vector<Token> arguments = tokensListRPN;
		res = DiffParser(arguments);
		//std::cout << "\n Derivative: " << DiffParser(arguments) << std::endl;

	}
	catch (Error& e)
	{
		//std::cerr << e.what() << "\n";
		exit(-1);
	}
	catch (const std::exception& e)
	{
		//std::cerr << e.what() << '\n';
		exit(-1);
	}

	//===============
	

	//std::string res = "Result from c#" + buf;
	res = res.substr(0, strlen);
	//str = strcat(str, res1);
	
	std::copy(res.begin(), res.end(), str);
	str[std::min(strlen - 1, (int)res.size() )] = 0;
}