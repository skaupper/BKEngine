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

Json::Value Serializable::serialize() const
{
    return original;
}

void Serializable::set()
{
    original = serialize();
}

void Serializable::reset()
{
    auto tmp = original;
    deserialize(original);
    original = tmp;
}

std::string Serializable::toString() const
{
    return Json::StyledWriter().write(serialize());
}
