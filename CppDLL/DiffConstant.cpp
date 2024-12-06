#include "DiffConstant.h"
#include <sstream>
#include <string>


bool DiffConstant::IsIt(std::string func)
{
	try
	{

		//=

		double buf;
		std::stringstream ss, ss2;
		ss2.str(func);
		ss2 >> buf;

		if (!ss2.eof() || ss2.fail()) {
			return false;
		}

		ss2.clear();

		//=


		double i = stod(func);
		return true;
	}
	catch (std::exception& e)
	{
		return false;
	}
}

std::string DiffConstant::Diff(std::string func)
{
	return "0";
}

