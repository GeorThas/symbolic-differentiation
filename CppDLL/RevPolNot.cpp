#include "RevPolNot.h"
#include "Error.h"
#include <iostream>
#include <stack>
#include <cmath>
#include <tuple>
#include <format>

void ShuntingYard(const std::vector<Token>& expr, std::vector<Token>& outQueue)
{
	std::stack<Token> stack;
	auto fromStackToQueue = [&]() { outQueue.push_back(stack.top()); stack.pop(); }; //лямбда, которая перемещает токен с вершины стека в очередь вывода.
	for (const auto& token : expr) //[&] означает, что все переменные, фиксируются по ссылке
	{
		switch (token.getType())
		{
		/*case Token::INT_LITERAL:
		case Token::FLOAT_LITERAL:*/
		case Token::NUM_LITERAL:
		case Token::VARIABLE:
			outQueue.push_back(token);
			break;
		case Token::L_PARENTHESIS:
		case Token::FUNCTION:
			stack.push(token);
			break;
		case Token::OPERATOR:
			if (!stack.empty())
			{
				while (stack.top().getType() == Token::OPERATOR && ((stack.top().getPrecendance() > token.getPrecendance())
					|| (stack.top().getPrecendance() == token.getPrecendance() && token.getAsc() == Token::LEFT)))
				{
					fromStackToQueue();
					if (stack.empty())
						break;
				}
			}
			stack.push(token);
			break;

		case Token::R_PARENTHESIS:
			if (stack.empty())
				throw Error("Non-balanced on paranthesis expression!", Error::Syntax);
			while (stack.top().getType() != Token::L_PARENTHESIS)
			{
				fromStackToQueue();
				if (stack.empty())
					throw Error("Non-balanced on paranthesis expression!", Error::Syntax);
			}
			stack.pop();
			if (!stack.empty() && stack.top().getType() == Token::FUNCTION)
				fromStackToQueue();
			break;

		/*case Token::SEPARATOR: // нужна доработка!
			if (stack.empty())
				throw Error("Paranthesis or separator missed!", Error::Syntax);
			while (stack.top().getType() != Token::L_PARENTHESIS)
			{
				fromStackToQueue();
				if (stack.empty())
					throw Error("Paranthesis-unbalanced expression!", Error::Syntax);
			}
			break;*/
		}
	}
	while (!stack.empty())
	{
		if (stack.top().getType() == Token::L_PARENTHESIS)
			throw Error("Paranthesis-unbalanced expression!", Error::Syntax);
		else
			fromStackToQueue();
	}
}

/*
	Пока не все токены обработаны:

		-Прочитать токен.

			-Если токен — число, то добавить его в очередь вывода.

			-Если токен — функция, то поместить его в стек.

			-Если токен — разделитель аргументов функции (запятая):

				-Пока токен на вершине стека не открывающая скобка:

					-Переложить оператор из стека в очередь вывода.

					-Если стек закончился до того, как был встречен токен открывающая скобка, то в выражении пропущен разделитель аргументов функции (запятая), либо пропущена открывающая скобка.

			-Если токен — оператор op1, то:

				-Пока присутствует на вершине стека токен оператор op2, чей приоритет выше или равен приоритету op1, и при равенстве приоритетов op1 является левоассоциативным:

					-Переложить op2 из стека в очередь вывода;

				-Положить op1 в стек.

			-Если токен — открывающая скобка, то положить его в стек.

			-Если токен — закрывающая скобка:

				-Пока токен на вершине стека не открывающая скобка:

					-Переложить оператор из стека в очередь вывода.

					-Если стек закончился до того, как был встречен токен открывающая скобка, то в выражении пропущена скобка.

				-Выкинуть открывающую скобку из стека, но не добавлять в очередь вывода.

			-Если токен на вершине стека — функция, переложить её в очередь вывода.

	-Если больше не осталось токенов на входе:

		-Пока есть токены операторы в стеке:

			-Если токен оператор на вершине стека — открывающая скобка, то в выражении пропущена скобка.

			-Переложить оператор из стека в очередь вывода.

	-Конец.
*/


/*
double countRPN(const std::vector<Token>& expr)
{
	std::stack<double> stack;

	auto getOneToken = [&]() // достать 1 токен
	{
		if (stack.empty()) 
			throw Error("Not enough arguments in function!", Error::Syntax);


		double x = stack.top();
		stack.pop();
		return x;
	};

	auto getTwoTokens = [&]() // достать 2 токена
	{ 
		double x = getOneToken(), 
		y = getOneToken(); 
		return std::tuple{ y,x };
	};

	auto checkedDivision = [&](double a, double b) // проверка на допустимость
	{ 
		if (b == 0.f) 
			throw Error("Division by zero", Error::Math); 
		return a / b; 
	};

	double res;
	for (auto& token : expr)
	{
		const std::string& str = token.getStr();
		switch (token.getType())
		{
		/*case Token::INT_LITERAL:

			stack.push(std::stoi(str));
			break;

		case Token::FLOAT_LITERAL:

			stack.push(std::stof(str));
			break;
		case Token::NUM_LITERAL:

			stack.push(std::stof(str));
			break;
		case Token::VARIABLE:

			//stack.push(str);
			break;

		case Token::OPERATOR:


			switch (token.getAsc())
			{
			case Token::LEFT:
			{
				auto [a, b] = getTwoTokens();
				if (str == "+") 
					res = a + b;
				else if (str == "-") 
					res = a - b;
				else if (str == "*") 
					res = a * b;
				else if (str == "/") 
					res = checkedDivision(a, b);
				else if (str == "^") 
					res = std::pow(a, b);
				else    
					throw Error("Unknown operator!", Error::Syntax);
				break;

			}
			case Token::RIGHT: // в принципе доступен только один правоассоциативный оператор
			{
				auto a = getOneToken();
				if (str == "-") 
					res = -a;
				else 
					throw Error("Unknown operator!", Error::Syntax);

				break;

			}
			case Token::NONE:
				throw std::logic_error("Operator must have associativity!");
				break;

			}


			stack.push(res);
			break;

		case Token::FUNCTION:

			if (str == "log")
			{
				auto [a, b] = getTwoTokens();
				if (a <= 0.f || a == 1.0f) 
					throw Error(std::format("log(a,x): not defined for a = {}", a), Error::Math);
				if (b <= 0.f) 
					throw Error("log(a,x): out of function's domain", Error::Math);

				res = std::log(b) / std::log(a);
			}
			else if (str == "log2")
			{
				auto a = getOneToken();
				if (a <= 0.f) 
					throw Error("log2(x): out of function's domain", Error::Math);

				res = std::log2(a);
			}
			else if (str == "ln")
			{
				auto a = getOneToken();
				if (a <= 0.f) 
					throw Error("ln(x): out of function's domain", Error::Math);

				res = std::log(a);
			}
			else if (str == "lg")
			{
				auto a = getOneToken();
				if (a <= 0.f) 
					throw Error("lg(x): out of function's domain", Error::Math);

				res = std::log10(a);
			}
			else if (str == "max")
			{
				auto [a, b] = getTwoTokens();
				res = a > b ? a : b;
			}
			else if (str == "min")
			{
				auto [a, b] = getTwoTokens();
				res = a < b ? a : b;
			}
			else if (str == "sqrt")
			{
				auto a = getOneToken();
				res = std::sqrt(a);
			}
			else if (str == "sin")
			{
				auto a = getOneToken();
				res = std::sin(a);
			}
			else if (str == "cos")
			{
				auto a = getOneToken();
				res = std::cos(a);
			}
			else if (str == "tg")
			{
				auto a = getOneToken();
				res = std::tan(a);
			}
			else if (str == "ctg")
			{
				auto a = getOneToken();
				res = 1 / std::tan(a);
			}
			else
				throw Error("Unknown function!", Error::Syntax);


			stack.push(res);
			break;

		default:
			break;
		}
	}
	return stack.top();
}*/