#pragma once
#include <vector>
#include <string>
#include "Token.h"

enum State
{
	Start, // s0 Стартовое 
	ParenthOperTokenization, // s1 Токенизация скобки/оператора
	IntToBuf, // s2 Запись целого числа в буфер
	FloatToBuf, // s3 Запись floating-point числа в буфер
	FuncToBuf, // s4 Запись функции в буфер
	VarToBuf, // s5 Запись переменной в буфер
	BufTokenization,  // s6 Токенизация записанного числа/функции из буфера
	NumToBuf
};

// Прототип функции для вывода токенов
std::string GetTokensList(std::vector<Token>&);
// Прототип токенизатора
void tokenize(const std::string& expr, std::vector<Token>& tokens);


