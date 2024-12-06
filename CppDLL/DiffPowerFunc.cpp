#include "DiffPowerFunc.h"
#include <string>
#include <format>


//
bool isnum(std::string& line)
{
	auto end = line.end();
	auto i = line.begin();
	if (i == end) return false;
	bool exp = false;
	bool dot = false;
	if (*i == '-' || *i == '+' || (*i >= '0' && *i <= '9'))
	{
		i++;
		for (; i != end; i++)
		{
			if (*i >= '0' && *i <= '9') continue;
			else if (*i == 'E' && exp == false)
			{
				i++;
				if (i == end) return false;
				if (*i == '-' || *i == '+' || (*i >= '0' && *i <= '9'))
				{
					exp = true;
					continue;
				}
				else return false;
			}
			else if (*i == '.' && i != line.begin() && dot == false)
			{
				dot = true;
				continue;
			}
			else return false;
		}
	}
	else return false;
	return true;
}
//



bool DiffPowerFunc::IsIt(std::string func)
{
	if (func.length() > 2 && func.substr(0, 2) == "x^") //+проверки
	{
		try
		{
			std::string m = func.substr(2, func.length());
			if (isnum(m))
				return true;
			else
				return false;

			//stod(func.substr(2, func.length()));
			//return true;
		}
		catch (...) {}
	}

	return false;
}

std::string DiffPowerFunc::Diff(std::string func)
{

	//int i = func.find(".");
	if (func.find('.') != std::string::npos) {
		double power = stod(func.substr(2));
		//return std::to_string(power) + "*x^" + std::to_string(power - 1);
		return std::format("{:.2f}", power) + "*x^" + std::format("{:.2f}", power - 1);
	}
	else {
		int power = stoi(func.substr(2));
		return std::to_string(power) + "*x^" + std::to_string(power - 1);
		//return std::format(":.2f\n", power) + "*x^" + std::format(":.2f\n", power - 1);
	}


}

