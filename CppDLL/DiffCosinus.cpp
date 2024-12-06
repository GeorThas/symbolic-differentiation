#include "DiffCosinus.h"

    bool DiffCosinus::IsIt(std::string func)
    {

        return (func == "cos");
    }

    std::string DiffCosinus::Diff(std::string func)
    {
        return "-sin";
    }