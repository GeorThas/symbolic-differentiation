#pragma once
#include "DiffConstant.h"
#include <string>

class DiffConstant
{
    public:
    static bool IsIt(std::string func);

    static std::string Diff(std::string func);
   
};

