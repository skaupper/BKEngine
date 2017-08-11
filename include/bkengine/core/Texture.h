#ifndef BKENGINE_TEXTURE_H
#define BKENGINE_TEXTURE_H

#include <string>
#include <memory>
#include <map>

#include <SDL.h>
#include <SDL_ttf.h>

#include "interfaces/GraphicsInterface.h"
#include "interfaces/FontInterface.h"
#include "interfaces/ImageInterface.h"
#include "utils/Fonts.h"
#include "utils/Logger.h"
#include "utils/Misc.h"
#include "serialization/Serializable.h"


namespace bkengine
{
    class Texture : public Serializable
    {
        public:
            explicit Texture();
            Texture(std::shared_ptr<FontInterface> fontInterface,
                    std::shared_ptr<GraphicsInterface> graphicsInterface,
                    const std::string &fontName, const std::string &text,
                    const Rect &size, const Color &color = {},
                    TextQuality quality = TextQuality::SOLID);
            Texture(std::shared_ptr<ImageInterface> imageInterface,
                    std::shared_ptr<GraphicsInterface> graphicsInterface, const std::string &path,
                    const Rect &size = {},
                    const Rect &clip = {});
            virtual ~Texture();

            virtual bool loadText(std::shared_ptr<FontInterface> fontInterface,
                                  std::shared_ptr<GraphicsInterface> graphicsInterface,
                                  const std::string &fontName, const std::string &text,
                                  const Rect &size, const Color &color = {},
                                  TextQuality quality = TextQuality::SOLID);
            virtual bool loadImage(std::shared_ptr<ImageInterface> imageInterface,
                                   std::shared_ptr<GraphicsInterface> graphicsInterface,
                                   const std::string &path, const Rect &clip = {},
                                   const Rect &size = {});

            virtual void onRender(std::shared_ptr<GraphicsInterface> graphicsInterface,
                                  const Rect &parentRect = {}, bool flip = false);

            virtual void deserialize(const Json::Value &) override;
            virtual Json::Value serialize() const override;

            Rect getSize() const;
            void setSize(int w, int h);
            void setSize(const Rect &rect);

        protected:
            struct StaticConstructor {
                StaticConstructor();
                ~StaticConstructor();
            };
            static StaticConstructor _;

            static std::shared_ptr<TextureWrapper> getCached(const std::string &s);
            static std::shared_ptr<TextureWrapper> getCached(const std::string &s,
                    const Rect &size, const Color &c);

            static bool hasTextureCached(const std::string &s);
            static bool hasTextureCached(const std::string &s, const Rect &size,
                                         const Color &c);

            static std::map<std::string, std::shared_ptr<TextureWrapper>> imageCache;
            static std::map<std::string, std::map<Rect, std::map<Color, std::shared_ptr<TextureWrapper>>>>
            textCache;

            static bool cleanupRegistered;
            static void cleanup();


            Rect clip;
            Rect size;

            std::shared_ptr<TextureWrapper> texture;
    };
}

#endif
