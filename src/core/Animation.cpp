#include "core/Animation.h"

using namespace bkengine;


bool Animation::onRender()
{
    return false;
}

std::string Animation::getName() const
{
    return name;
}

void Animation::setName(const std::string &name)
{
    Animation::name = name;
}

uint32_t Animation::getFramesPerTexture() const
{
    return framesPerTexture;
}

void Animation::setFramesPerTexture(uint32_t framesPerTexture)
{
    Animation::framesPerTexture = framesPerTexture;
}


void Animation::_onRender()
{
    bool suppress = onRender();
    if (suppress) {
        return;
    }

    if (framesPerTexture == 0) {
        return;
    }

    if (frameCounter < framesPerTexture - 1) {
        frameCounter++;
    } else {
        frameCounter = 0;
        currentTextureIndex = (currentTextureIndex + 1) % textures.size();
    }

    assert(currentTextureIndex < textures.size());

    textures[currentTextureIndex]->onRender();
}
