#include "Fonts.h"


using namespace bkengine;

std::map<std::string, std::map<short, TTF_Font *>> Fonts::fontCache;

TTF_Font *Fonts::registerFont(const std::string &fontFile, short size, const std::string &fontName)
{
    return nullptr;
}

TTF_Font *Fonts::getFont(const std::string &fontName, short size)
{
    return nullptr;
}

void Fonts::releaseFont(const std::string &fontName, short size)
{

}

void Fonts::atExit()
{

}
