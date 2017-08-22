#ifndef BKENGINE_MOCK_FONT_INTERFACE_H
#define BKENGINE_MOCK_FONT_INTERFACE_H

#include <memory>
#include <string>

#include "interfaces/FontInterface.h"


namespace bkengine
{
    class MockFontTexture : public TextTexture
    {
    public:
        void onRender() override
        {
        }
    };
    class MockFontInterface : public FontInterface
    {
    public:
        void registerFont(const std::string &filePath, const std::string &fontName, double size) override
        {
        }

        std::shared_ptr<TextTexture>
        renderFontToTexture(const std::string &text, const std::string &fontName, double size, TextQuality) override
        {
            return std::make_shared<MockFontTexture>();
        }
    };
}

#endif  // BKENGINE_MOCK_FONT_INTERFACE_H