#ifndef BKENGINE_MOCK_IMAGE_INTERFACE_H
#define BKENGINE_MOCK_IMAGE_INTERFACE_H

#include <memory>
#include <string>

#include "interfaces/ImageInterface.h"


namespace bkengine
{
    class MockImageTexture : public ImageTexture
    {
    public:
        void onRender() override
        {
        }
    };

    class MockImageInterface : public ImageInterface
    {
    public:
        std::shared_ptr<ImageTexture> renderImageFileToTexture(const std::string &, const AbsRect &) override
        {
            return std::make_shared<MockImageTexture>();
        }
    };
}

#endif  // BKENGINE_MOCK_IMAGE_INTERFACE_H