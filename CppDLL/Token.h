#pragma once

#include <string>

class Token
{
public:

	enum Type
	{
		OPERATOR,      // �������/�������� ��������
		L_PARENTHESIS, // ����������� ������
		R_PARENTHESIS, // ����������� ������
		NUM_LITERAL,   // �����
		FUNCTION,      // �������
		SEPARATOR,      // ����������� ���������� �������
		VARIABLE        // ����������
	};

	enum OpAssociativity
	{
		NONE,
		RIGHT,
		LEFT
	};

	Token(std::string token, Type type, OpAssociativity asc = NONE);

	int getPrecendance() const;

	//getters
	const Type& getType() const
	{
		return type;
	}

	const OpAssociativity& getAsc() const
	{
		return opAsc;
	}

	const std::string& getStr() const
	{
		return str;
	}

private:
	Type type;
	OpAssociativity opAsc;
	std::string str;

public:
	void setStr(std::string foo)
	{
		str = foo;
	}
};

