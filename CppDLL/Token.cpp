#include "Token.h"
#include <map>
#include <stdexcept>
#include <format>
#include "Error.h"


Token::Token(std::string token, Type type, OpAssociativity asc) : type{ type }, str{ token } //������ �������������
{
    // ���� ����� - ��������, �� ��������������� �� ������ - ������ (���������)
    if (type == OPERATOR && asc == NONE) 
    {
        throw std::logic_error("Associativity required!");
    }
    else if (type != OPERATOR && asc != NONE) 
    { // ���� ����� - �� ��������, �� ��������������� ������ - ������
        throw std::logic_error("Non-operator token can't have an associativity!");
    }

    opAsc = asc;
}

int Token::getPrecendance() const // ����������� ����������
{
    static std::map<std::string, int> OperLAssociative = //�����������������
    {
        {"+", 2},
        {"-", 2},
        {"/", 3},
        {"*", 3},
        {"^", 5}
    };


    static std::map<std::string, int> OpRAssociative = //������������������
    {
        {"-", 4} // ������� ���������
    };

    // � ����������� �� ��������������� ���� � ��� �� ������ �������� ������ ���������
    switch (opAsc)
    {
    case LEFT:
        // ���� str ��������� ������ map-�, ������ �� ����� ����� ��������
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