#include "DiffVariable.h"
#include <string>


    bool DiffVariable::IsIt(std::string func)
    {
        return (func == "x");
    }

     std::string DiffVariable::Diff(std::string func)
    {
        return "1";
    }
