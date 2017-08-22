#ifndef BKENGINE_IMAGE_TEXTURE_BUILDER_H
#define BKENGINE_IMAGE_TEXTURE_BUILDER_H

#include <memory>
#include <string>

#include "core/Game.h"
#include "core/Texture.h"
#include "exceptions/BuilderException.h"
#include "utils/Geometry.h"


namespace bkengine
{
    class Game;

    class ImageTextureBuilder
    {
        friend class TextureBuilder;

    public:
        ImageTextureBuilder &setGame(const std::shared_ptr<Game> &);
        ImageTextureBuilder &setName(const std::string &);
        ImageTextureBuilder &setFilePath(const std::string &);
        ImageTextureBuilder &setClip(const AbsRect &);
        ImageTextureBuilder &setTexturePosition(const Point &);
        ImageTextureBuilder &setTextureSize(const RelRect &);
        ImageTextureBuilder &setRotation(double);
        ImageTextureBuilder &setFlip(bool horizontal, bool vertical);

        std::shared_ptr<Texture> build() const;

    private:
        ImageTextureBuilder() = default;

        std::shared_ptr<Game> game = nullptr;
        std::string name;
        std::string filePath;
        Rect clipRect = {0, 0, 0, 0};
        Point position = {0, 0};
        Rect textureSize = {0, 0, 100, 100};
        double angleRadians = 0;
        bool flipHorizontally = false;
        bool flipVertically = false;
    };
}

#endif  // BKENGINE_IMAGE_TEXTURE_BUILDER_H