#include "Differentiation.h"
#include "DiffConstant.h"
#include "DiffVariable.h"
#include "DiffPowerFunc.h"
#include "DiffCosinus.h"
#include "DiffSinus.h"
#include <string>
#include <map>
#include <utility>



    std::string Differentiation::Diff(std::string func)
    {
        std::string result = "";

        if (DiffConstant::IsIt(func))
        {
            result = DiffConstant::Diff(func);
        }
        else if (DiffVariable::IsIt(func))
        {
            result = DiffVariable::Diff(func);
        }
        else if (DiffPowerFunc::IsIt(func))
        {
            result = DiffPowerFunc::Diff(func);
        }
        else if (DiffCosinus::IsIt(func))
        {
            result = DiffCosinus::Diff(func);
        }
        else if (DiffSinus::IsIt(func))
        {
            result = DiffSinus::Diff(func);
        }
        /*else if (Exp.IsIt(func))
        {
            result = Exp.Diff(func);
        }*/

        return result;
    }

    std::string Differentiation::Diff(std::string func, std::map<std::string, std::string> DiffsList)
    {
        std::string dfunc = Diff(func);
        if (dfunc == "")
        {
            for(std::pair<std::string, std::string> pair : DiffsList)
            {
                if (pair.first == func)
                {
                    dfunc = pair.second;
                }
            }
        }

        return dfunc;
    }

    std::string Differentiation::SimplifyMult(std::string func1, std::string func2)
    {
        std::string result = "(" + func1 + ")*(" + func2 + ")";

        if (func1 == "0" || func2 == "0")
        {
            result = "0";
        }
        else if (func1 == "1")
        {
            result = func2;
        }
        else if (func2 == "1")
        {
            result = func1;
        }
        else if (DiffConstant::IsIt(func1))
        {
            result = func1 + "*(" + func2 + ")";
        }
        else if (DiffConstant::IsIt(func2))
        {
            result = func2 + "*(" + func1 + ")";
        }

        return result;
    }

    std::string Differentiation::SimplifyAdd(std::string func1, std::string func2, bool isAdd)
    {
        std::string result = "";
        if (func2 == "0")
        {
            result = func1;
        }
        else if (func1 == "0")
        {
            // Проверка на необходимость заключить выражение в скобки
            if (func2.find("+") != std::string::npos || func2.find("-") != std::string::npos)
            {
                result = (isAdd) ? func2 : "-(" + func2 + ")";
            }
            else
            //
            result = (isAdd) ? func2 : "-" + func2;
        }
        else
        {
            if (func2[0] == '-') {//////020524
                func2 = "(" + func2 + ")";
            }
           
                result = (isAdd) ?
                    func1 + "+" + func2 :
                    func1 + "-" + func2;
          
        }

        return result;
    }

    /// <summary>
    /// Композиции
    /// </summary>
    std::string Differentiation::Diff(std::string func1, std::string dfunc1, std::string func2, std::string dfunc2, std::string oper)
    {
        std::string result = "";
        if (oper == "+" /*&& dfunc2[0] != '-'*/) //020524
        {
            result = SimplifyAdd(dfunc1, dfunc2, true);
        }
        else if (oper == "-" /*|| (dfunc2[0] == '-' && oper != "-")*/) //020524!!!
        {
            result = SimplifyAdd(dfunc1, dfunc2, false);
        }
        else if (oper == "*")
        {
            std::string result1 = SimplifyMult(func1, dfunc2);
            std::string result2 = SimplifyMult(func2, dfunc1);
            result = result1 + "+" + result2;
        }
        else if (oper == "/")
        {
            result = "(" + SimplifyMult(func1, dfunc2) + "-" + SimplifyMult(func2, dfunc1) + ")/((" + func2 + ")^2)";
        }
        else if ( (oper == "^") && DiffVariable::IsIt(func1)  && DiffConstant::IsIt(func2) ) //
        {
            result = Diff(func1 + "^" + func2);
        }
        else if (oper == "Compose")
        {
            result = SimplifyMult(dfunc1 + "(" + func2 + ")", dfunc2);
        }

        return result;
    }
