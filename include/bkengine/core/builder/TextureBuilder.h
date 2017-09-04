#ifndef BKENGINE_TEXTURE_BUILDER_H
#define BKENGINE_TEXTURE_BUILDER_H

#include "core/LazyTextureContainer.h"
#include "core/Texture.h"
#include "exceptions/BuilderException.h"
#include "utils/Geometry.h"


namespace bkengine
{
    template <typename ParentBuilder>
    class TextureBuilder
    {
    public:
        ParentBuilder &setName(const std::string &);
        ParentBuilder &setTexturePosition(const Point &);
        ParentBuilder &setTextureSize(const RelRect &);
        ParentBuilder &setRotation(double);
        ParentBuilder &setFlip(bool horizontal, bool vertical);

    protected:
        std::shared_ptr<LazyTextureContainer> build(std::unique_ptr<Texture>) const;

    private:
        TextureBuilder() = delete;

        std::string name;
        Point position = {0, 0};
        Rect size = {0, 0, 100, 100};
        double angleRadians = 0;
        bool flipHorizontally = false;
        bool flipVertically = false;
    };
}

#include "templates/TextureBuilder.tpp"

#endif  // BKENGINE_TEXTURE_BUILDER_H