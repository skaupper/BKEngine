#include "Animation.h"

using namespace bkengine;

Animation::Animation(const std::string &description,
                     unsigned int framesPerTexture) :
    frameCounter(0),
    framesPerTexture(framesPerTexture),
    currentIndex(0),
    description(description)
{
}

void Animation::reset()
{
    frameCounter = 0;
    currentIndex = -1;
}

Texture &Animation::getNextTexture()
{
    auto &tmp = getCurrentTexture();
    incFrameCount();
    return tmp;
}

Texture &Animation::getCurrentTexture()
{
    if (hasTexture(currentIndex)) {
        return textures.at(currentIndex);
    }

    Logger::LogCritical("Animation::getCurrentTexture(): Texture not found");
    throw "Texture not found";
}

bool Animation::hasTexture(unsigned int index) const
{
    return index < textures.size();
}

void Animation::incFrameCount()
{
    if (framesPerTexture == 0) {
        return;
    }

    if (frameCounter < framesPerTexture - 1) {
        frameCounter++;
    } else {
        frameCounter = 0;
        currentIndex = (currentIndex + 1) % textures.size();
    }
}


void Animation::addImage(const std::string &path)
{
    addImage<Texture>(path);
}

void Animation::addImage(const std::string &path, const Rect &size)
{
    addImage<Texture>(path, size);
}

void Animation::addText(const std::string &fontName, const std::string &text,
                        const Color &color, const Rect &size, TextQuality quality)
{
    addText<Texture>(fontName, text, color, size, quality);
}

void Animation::setFramesPerTexture(unsigned int frames)
{
    framesPerTexture = frames;
}

Animation::~Animation()
{
    textures.clear();
}

std::string Animation::getDescription() const
{
    return description;
}
