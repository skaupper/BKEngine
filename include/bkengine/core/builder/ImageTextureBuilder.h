#ifndef BKENGINE_IMAGE_TEXTURE_BUILDER_H
#define BKENGINE_IMAGE_TEXTURE_BUILDER_H

#include <memory>
#include <string>

#include "core/Game.h"
#include "core/Texture.h"
#include "core/builder/TextureBuilder.h"
#include "exceptions/BuilderException.h"
#include "utils/Geometry.h"


namespace bkengine
{
    class Game;

    class ImageTextureBuilder : public TextureBuilder<ImageTextureBuilder>
    {
    public:
        ImageTextureBuilder &setFilePath(const std::string &);
        ImageTextureBuilder &setClip(const AbsRect &);

        std::unique_ptr<Texture> build() const;

    private:
        ImageTextureBuilder() = default;

        std::string filePath;
        Rect clipRect = {0, 0, 0, 0};
    };
}

#endif  // BKENGINE_IMAGE_TEXTURE_BUILDER_H