#include "core/Animation.h"

using namespace bkengine;


bool Animation::onRender()
{
    return false;
}

uint32_t Animation::getFramesPerTexture() const
{
    return framesPerTexture;
}


void Animation::_onRender()
{
    uint32_t currentTextureIndex = getActivatedIndex();
    auto textures = getAllChildren();
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
