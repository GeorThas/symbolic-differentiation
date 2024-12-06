#include "DiffSinus.h"

    bool DiffSinus::IsIt(std::string func)
    {

        return (func == "sin");
    }

    std::string DiffSinus::Diff(std::string func)
    {
        return "cos";
    }
