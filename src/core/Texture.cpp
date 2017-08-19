#include "core/Texture.h"

using namespace bkengine;


std::string Texture::getName() const
{
    return name;
}

void Texture::setName(const std::string &name)
{
    Texture::name = name;
}

Rect Texture::getSize() const
{
    return size;
}

void Texture::setSize(const Rect &size)
{
    Texture::size = size;
}
