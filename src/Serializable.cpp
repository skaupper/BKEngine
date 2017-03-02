#include "Serializable.h"

using namespace bkengine;


std::map<std::string, constructor> Serializer::typeConstructors;

Serializable::Serializable()
{
    
}

Serializable::Serializable(const Json::Value &json)
{
    Json::Value v(json);
    swap(v);
}

std::string Serializable::toString() const
{
    return Json::StyledWriter().write(serialize());
}
