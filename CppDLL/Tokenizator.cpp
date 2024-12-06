#include "Tokenizator.h"
#include <iostream>
#include <format>
#include <map>
#include <string>
#include "Error.h"
#include <sstream>

std::string GetTokensList(std::vector<Token>& tokensList) {

	std::stringstream ss;

	for (auto& token : tokensList)
	{
		std::string type, asc;

		switch (token.getType()) // ������ � ����
		{
		case Token::OPERATOR:
			type = "OPERATOR";
			break;
		case Token::L_PARENTHESIS:
			type = "L_PARANTHESIS";
			break;
		case Token::R_PARENTHESIS:
			type = "R_PARANTHESIS";
			break;
		case Token::NUM_LITERAL:
			type = "NUM_LITERAL";
			break;
		case Token::FUNCTION:
			type = "FUNCTION";
			break;
		case Token::SEPARATOR:
			type = "OPERATOR";
			break;
		case Token::VARIABLE:
			type = "VARIABLE";
			break;
		}

		switch (token.getAsc()) //������ �� ���������������
		{
		case Token::NONE:
			asc = "NONE";
			break;
		case Token::RIGHT:
			asc = "RIGHT";
			break;
		case Token::LEFT:
			asc = "LEFT";
			break;
		}
		ss << token.getStr() << "\t\t" << type << "\t\t" << asc << "\n";
	}

	return ss.str();
}

void tokenize(const std::string& expr, std::vector<Token>& tokens)
{
	State state = Start;

	std::string validOperators = "+-*^/"; // ���������� ��������
	std::string validFunctions = "sincos";

	bool isDigit, isLetter, isOp, isParanth, isPoint, isSep, isLParanth, isRParanth; // ���� ��������

	std::string buffer; //����� ��� ����� � �������
	Token::Type bufferTokenType = Token::VARIABLE; // ��� �������� ������

	for (auto& s : expr)
	{
		// ���������� ��� �������
		isDigit = std::isdigit(s); //�����
		isLetter = std::isalpha(s); //�����
		isLParanth = s == '(';
		isRParanth = s == ')';
		isParanth = isLParanth || isRParanth; // ������
		isPoint = s == '.';
		isSep = s == ',';
		isOp = validOperators.find(s) != validOperators.npos; //���������� ��������

		// ���� ��� ������� �����������, ������ ������ � ����������
		if (!(isDigit || isLetter || isParanth || isPoint || isSep || isOp))
			throw Error(std::format("Unknown symbol: {}", s), Error::Syntax);

		// ����� ���������
		switch (state)
		{
		case Start:

			if (isOp || isParanth) 
			{
				state = ParenthOperTokenization;
			}
			else if (isDigit) 
			{
				state = IntToBuf;
				bufferTokenType = Token::NUM_LITERAL; //020524 !!
			}
			else if (isLetter) 
			{
				//state = FuncToBuf;
				state = VarToBuf;
			}
			else if (isPoint || isSep) 
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;

		case ParenthOperTokenization:

			if (isDigit) 
			{
				state = NumToBuf;//IntToBuf;
				bufferTokenType = Token::NUM_LITERAL; //???
			}
			else if (isLetter) 
			{
				//state = FuncToBuf;
				state = VarToBuf;
			}
			else if (isPoint || isSep || isOp) 
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			if (isPoint || isSep || isOp)
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;
			//v1
		case IntToBuf: // ����� ������ ������, ��������� � ����. �������

			if (isDigit) //020524!!!
				bufferTokenType = Token::NUM_LITERAL;//Token::FLOAT_LITERAL;

			if (isPoint)
				state = NumToBuf;
			if (isParanth || isOp || isSep)
			{
				state = BufTokenization;
			}
			else if (isLetter) //020524!!!
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;

			//v2 110524
		case NumToBuf://FloatToBuf:

			if(isDigit) //020524!!!
				bufferTokenType = Token::NUM_LITERAL;//Token::FLOAT_LITERAL;

			if (isParanth || isOp || isSep) 
			{
				state = BufTokenization;
			}
			else if (isPoint || isLetter) //020524!!!
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;

		case FuncToBuf:
			
			bufferTokenType = Token::FUNCTION;

			if (isLParanth) 
			{
				//bufferTokenType = Token::FUNCTION;
				state = BufTokenization;
			}
			else if (isOp /*|| isRParanth*/ || isSep) 
			{
				throw Error(std::format("Unexpected symbol \"{}\"", s), Error::Syntax); //������
			}

			break;

		case VarToBuf:

			bufferTokenType = Token::VARIABLE;

			if (isLParanth)
			{
				//state = FuncToBuf; //
				state = BufTokenization;
				bufferTokenType = Token::FUNCTION;
			}
			else if (isOp || isSep|| isParanth)
			{
				state = BufTokenization;
			}
			else if (isPoint)
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;
			
		case BufTokenization:

			if (isParanth || isOp) //v1 110524 ?
			{
				state = ParenthOperTokenization;
			}
			else if (isDigit) 
			{
				state = IntToBuf;
				bufferTokenType = Token::NUM_LITERAL;//INT_LITERAL;//
			}
			else if (isLetter) 
			{
				//state = FuncToBuf;
				state = VarToBuf;
				bufferTokenType = Token::VARIABLE;//
			}
			else if (isPoint || isSep)
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;

		default:
			break;
		}

		auto tokenize_Op_Paranth_Sep = [&]() //������-���������
		{
			if (isOp)
			{
					// ��������� (-x). ������ ������� ��������� ������������ ��������, ������� ������� � ������
				if (tokens.size() == 0 || tokens[tokens.size() - 1].getType() == Token::L_PARENTHESIS) 
				{
					tokens.push_back({ std::string{s}, Token::OPERATOR, Token::RIGHT });
				}
				else 
				{
					tokens.push_back({ std::string{s}, Token::OPERATOR, Token::LEFT });
				}

			}
			else if (isParanth)
			{
				tokens.push_back({ std::string{s}, isRParanth ? Token::R_PARENTHESIS : Token::L_PARENTHESIS });
			}
			else if (isSep)/// �� �����
			{
				tokens.push_back({ std::string{s}, Token::SEPARATOR });
			}
		};

		// ��������
		switch (state)
		{
		case ParenthOperTokenization:
			tokenize_Op_Paranth_Sep();
			break;
		case IntToBuf: //v1 110524
			buffer.push_back(s);
			break;
		case NumToBuf:
			buffer.push_back(s);
			break;
		case VarToBuf: 
			buffer.push_back(s);
			break;
		case FuncToBuf:
			buffer.push_back(s);
			break;
		case BufTokenization:
			tokens.push_back({ buffer, bufferTokenType });
			buffer.clear();
			tokenize_Op_Paranth_Sep();
			break;
		}

	}

	if (!buffer.empty())
		tokens.push_back({ buffer, bufferTokenType });
}