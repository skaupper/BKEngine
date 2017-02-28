#ifndef BKENGINE_TEXTURE_H
#define BKENGINE_TEXTURE_H

#include <string>
#include <memory>
#include <map>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Core.h"
#include "Fonts.h"
#include "Misc.h"
#include "Logger.h"


namespace bkengine
{
    class Texture
    {
            /* caching */
        public:
        protected:
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


            /* getter and setter */
        public:
            Rect getSize() const;
            void setSize(int w, int h);
            void setSize(const Rect &rect);

        protected:
            Rect clip;
            Rect size;

        /* other stuff */
        public:
            Texture();
            Texture(const std::string &fontName, const std::string &text,
                    const Rect &size, const Color &color = Color(),
                    TextQuality quality = TextQuality::SOLID);
            Texture(const std::string &path, const Rect &size = Rect(),
                    const Rect &clip = Rect());
            virtual ~Texture();

            virtual bool loadText(const std::string &fontName, const std::string &text,
                                  const Rect &size, const Color &color = Color(),
                                  TextQuality quality = TextQuality::SOLID);
            virtual bool loadImage(const std::string &path, const Rect &clip = Rect(),
                                   const Rect &size = Rect());

            virtual void onRender(const Rect &parentRect = Rect(), bool flip = false);

        protected:
            bool flip;
            std::shared_ptr<TextureWrapper> texture;
    };
}

#endif
