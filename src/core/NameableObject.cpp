#include "core/NameableObject.h"

using namespace bkengine;


std::string NameableObject::getName() const
{
    return name;
}

void NameableObject::setName(const std::string &newName)
{
    name = newName;
}
