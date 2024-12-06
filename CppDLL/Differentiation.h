#pragma once
#include<string>
#include <map>
class Differentiation
{
public:
    static std::string Diff(std::string func);

    static std::string Diff(std::string func, std::map<std::string, std::string> DiffsList);

    static std::string SimplifyMult(std::string func1, std::string func2);

    static std::string SimplifyAdd(std::string func1, std::string func2, bool isAdd);
    

    /// <summary>
    /// Композиции
    /// </summary>
    static std::string Diff(std::string func1, std::string dfunc1, 
        std::string func2, std::string dfunc2, std::string oper);
};

