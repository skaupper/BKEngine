#include "Serializable.h"

using namespace bkengine;


std::map<std::string, constructor> Serializer::typeConstructors;

Serializable::Serializable()
{
}

void Serializable::deserialize(const Json::Value &obj)
{
    original = obj;
}

void Serializable::set()
{
    original = serialize();
}

void Serializable::reset()
{
    deserialize(original);
}

std::string Serializable::toString() const
{
    return Json::StyledWriter().write(serialize());
}
