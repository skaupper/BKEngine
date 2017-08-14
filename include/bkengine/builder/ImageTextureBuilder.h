#ifndef BKENGINE_IMAGE_TEXTURE_BUILDER_H
#define BKENGINE_IMAGE_TEXTURE_BUILDER_H

#include <memory>
#include <string>

#include "core/Game.h"
#include "core/Texture.h"
#include "utils/Geometry.h"


namespace bkengine
{
    class Game;

    class ImageTextureBuilder
    {
        friend class TextureBuilder;

    public:
        ImageTextureBuilder &setGame(const std::shared_ptr<Game> &);
        ImageTextureBuilder &setFilePath(const std::string &);
        ImageTextureBuilder &setClip(const Rect &);
        ImageTextureBuilder &setTextureSize(const Rect &);

        template <typename T>
        std::shared_ptr<T> build() const;

    private:
        ImageTextureBuilder() = default;

        std::shared_ptr<Game> game;
        std::string filePath;
        Rect clipRect;
        Rect textureSize;
    };
}

#include "templates/ImageTextureBuilder_templates.h"

#endif  // BKENGINE_IMAGE_TEXTURE_BUILDER_H