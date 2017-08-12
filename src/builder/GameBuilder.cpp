#include "builder/GameBuilder.h"

using namespace bkengine;


GameBuilder GameBuilder::createBuilder()
{
    return GameBuilder();
}

GameBuilder &GameBuilder::setWindowSize(Size size)
{
    windowSize = size;
    return *this;
}

GameBuilder &GameBuilder::setWindowTitle(const std::string &title)
{
    windowTitle = title;
    return *this;
}

GameBuilder &GameBuilder::setIconFile(const std::string &file)
{
    iconFile = file;
    return *this;
}