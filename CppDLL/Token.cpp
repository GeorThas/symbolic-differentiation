#include "Token.h"
#include <map>
#include <stdexcept>
#include <format>
#include "Error.h"


Token::Token(std::string token, Type type, OpAssociativity asc) : type{ type }, str{ token } //список инициализации
{
    // если токен - оператор, но ассоциативность не задана - ошибка (алгоритма)
    if (type == OPERATOR && asc == NONE) 
    {
        throw std::logic_error("Associativity required!");
    }
    else if (type != OPERATOR && asc != NONE) 
    { // если токен - НЕ оператор, но ассоциативность задана - ошибка
        throw std::logic_error("Non-operator token can't have an associativity!");
    }

    opAsc = asc;
}

int Token::getPrecendance() const // Определение приоритета
{
    static std::map<std::string, int> OperLAssociative = //левоассоциативные
    {
        {"+", 2},
        {"-", 2},
        {"/", 3},
        {"*", 3},
        {"^", 5}
    };


    static std::map<std::string, int> OpRAssociative = //правоассоциативные
    {
        {"-", 4} // унарное отрицание
    };

    // В зависимости от ассоциативности один и тот же символ означает разные операторы
    switch (opAsc)
    {
    case LEFT:
        // Если str явлеяется ключом map-а, значит мы знаем такой оператор
        if (OperLAssociative.count(str)) //contains()
        {
            return OperLAssociative[str];
        }
        else 
        {
            throw Error("Unknown Operator!", Error::Syntax);
        }
        break;

    case RIGHT:

        if (OpRAssociative.count(str)) //contains()
        {
            return OpRAssociative[str];
        }
        else
        {
            throw Error("Unknown Operator!", Error::Syntax);
        }
        break;

    case NONE:

        throw std::logic_error(std::format("Token \"{}\" is not an operatator, impossible.", str));
        break;
    }
}