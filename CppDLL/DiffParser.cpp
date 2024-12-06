#include "DiffParser.h"
#include "Differentiation.h"
#include <map>
#include <iostream>

std::string DiffParser(std::vector<Token>& arguments)
{

	std::string diff; //Производная
	std::map<std::string, std::string> DiffsList; //Список уже вычисленных функций и их производных
	std::vector<std::string> operations = { "(", "+", "-", "*", "/", "^", ")", "(", "()","sin", "cos",  "tan", "ctg" };

	try {
		//1 Нужен обработчик единичных аргументов(переменных или числел)!
		if (arguments.size() == 1) { 
			if (arguments[0].getType() == Token::VARIABLE)
				diff = "1";
			else if (arguments[0].getType() == Token::NUM_LITERAL)
				diff = "0";
		}
		//1 кусок кода не проверен, может вызрать некорректное поведение


		while (arguments.size() > 1)
		{
			std::string firstOper = "";
			int firstOperIndex = arguments.size();
			for (auto& str : operations)
			{
				int indexOf = 0;
				for (indexOf = 0; indexOf < arguments.size(); indexOf += 1)
					if (arguments[indexOf].getStr() == str)
						break;

				if (indexOf > 0 && indexOf < firstOperIndex)
				{
					firstOperIndex = indexOf;
					firstOper = str;
				}
			}

			std::string f1 = "", f2 = "", df1 = "", df2 = "", oper = "", expression = "";

			
			if (arguments[firstOperIndex].getType() == Token::FUNCTION) //Обработка функций
			{
				int ComposeIndex = firstOperIndex;

				f1 = arguments[ComposeIndex].getStr();
				df1 = Differentiation::Diff(f1, DiffsList);
				f2 = arguments[ComposeIndex - 1].getStr();
				df2 = Differentiation::Diff(f2, DiffsList);
				oper = "Compose";
				expression = f1 + "(" + f2 + ")";
				diff = Differentiation::Diff(f1, df1, f2, df2, oper);

				arguments[ComposeIndex].setStr(expression);
				arguments.erase(arguments.begin() + ComposeIndex - 1);
			} 
			else //Обработка бинарных операций
			{
				
				if (arguments[firstOperIndex].getAsc() == Token::RIGHT && arguments[firstOperIndex].getStr() == "-")
				{ // для унарных операций (-х) ,, рассматривается как (0-х)
					f1 = "0";
					Token zero("0", Token::NUM_LITERAL, Token::NONE); // Нулевой токен
					auto iterator = arguments.insert(arguments.begin()+firstOperIndex-1, zero);
					firstOperIndex++;
				}
				else
				{
					if (firstOperIndex - 2 >= 0)
						f1 = arguments[firstOperIndex - 2].getStr();
					else
						throw std::string{ "An error was made in the expression!" };
				}

				df1 = Differentiation::Diff(f1, DiffsList);
				f2 = arguments[firstOperIndex - 1].getStr();
				df2 = Differentiation::Diff(f2, DiffsList);
				oper = arguments[firstOperIndex].getStr();
				expression = f1 + oper + f2;
				diff = Differentiation::Diff(f1, df1, f2, df2, oper);

				arguments.erase(arguments.begin() + firstOperIndex); //удаление уже использованных аргументов
				arguments.erase(arguments.begin() + firstOperIndex - 1);
				arguments[firstOperIndex - 2].setStr(expression); 
			}

			if (!DiffsList.contains(expression))
			{
				DiffsList.insert({ expression, diff });
			}
		}
		return diff;
	}
	catch (std::exception& e)
	{
		return "Differentiation error!";
	}
	catch (std::string errMes) 
	{
		return errMes;
	}
}
