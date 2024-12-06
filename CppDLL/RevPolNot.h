#pragma once
#include <vector>
#include "Token.h"

void ShuntingYard(const std::vector<Token>& expr, std::vector<Token>& outQueue);

double countRPN(const std::vector<Token>& expr);