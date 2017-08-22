#ifndef BKENGINE_FONTINTERFACE_H
#define BKENGINE_FONTINTERFACE_H

#include <string>

#include "core/TextTexture.h"


namespace bkengine
{
    class FontInterface
    {
    public:
        virtual void registerFont(const std::string &filePath, const std::string &fontName, double size) = 0;

        virtual std::shared_ptr<TextTexture>
        renderFontToTexture(const std::string &text, const std::string &fontName, double size, TextQuality) = 0;
    };
}

#endif