#include "UIScreenAbstract.h"

UIScreenAbstract::UIScreenAbstract(std::string name)
{
    this->name = name;
}

UIScreenAbstract::~UIScreenAbstract()
{
}

std::string UIScreenAbstract::getName()
{
    return name;
}
