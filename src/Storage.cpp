#include "Storage.h"

using namespace bkengine;


const std::string Storage::TYPE = "STORAGE";

Storage::Storage(const std::string &type) : type(type)
{
}

Storage::~Storage()
{
}

const std::string &Storage::getType() const
{
    return type;
}
