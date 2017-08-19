#include "core/Texture.h"

using namespace bkengine;


void Texture::setName(const std::string &name)
{
    Texture::name = name;
}

std::string Texture::getName() const
{
    return name;
}