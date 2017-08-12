#include "builder/AnimationBuilder.h"

using namespace bkengine;


AnimationBuilder AnimationBuilder::createBuilder()
{
    return AnimationBuilder();
}

AnimationBuilder &AnimationBuilder::setName(const std::string &name)
{
    AnimationBuilder::name = name;
    return *this;
}

AnimationBuilder &AnimationBuilder::setFramesPerTexture(uint32_t frames)
{
    AnimationBuilder::framesPerTexture = frames;
    return *this;
}