#ifndef BKENGINE_FONTINTERFACE_H
#define BKENGINE_FONTINTERFACE_H

#include <string>

#include "utils/Font.h"
#include "utils/TextTexture.h"


namespace bkengine
{
    class FontInterface
    {
    public:
        virtual Font registerFont(const std::string &filePath, const std::string &fontName, double size);
        virtual Font getFont(const std::string &fontName, double size);

        virtual std::shared_ptr<TextTexture> renderFontToTexture(const std::string &text, Font, TextQuality);
    };
}

#endif