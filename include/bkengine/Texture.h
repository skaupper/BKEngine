#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

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
        public:
            static std::shared_ptr<TextureWrapper> getCached(const std::string &s);
            static std::shared_ptr<TextureWrapper> getCached(const std::string &s,
                    const Rect &size, const Color &c);

            static bool hasTextureCached(const std::string &s);
            static bool hasTextureCached(const std::string &s, const Rect &size,
                                         const Color &c);

            Texture();
            Texture(const std::string &fontName, const std::string &text,
                    const Rect &size, const Color &color = Color(),
                    TextQuality quality = TextQuality::SOLID);
            Texture(const std::string &path, const Rect &size = Rect(),
                    const Rect &clip = Rect());
            virtual ~Texture();

            bool loadText(const std::string &fontName, const std::string &text,
                         const Rect &size, const Color &color = Color(),
                         TextQuality quality = TextQuality::SOLID);
            bool loadImage(const std::string &path, const Rect &clip = Rect(),
                          const Rect &size = Rect());

            Rect getSize() const;
            void setSize(int w, int h);
            void setSize(const Rect &rect);

            virtual int onRender(const Rect &parentRect = Rect(), bool flip = false);

        protected:
            bool flip;
            std::shared_ptr<TextureWrapper> texture;
            Rect clip;
            Rect size;

            static bool cleanupRegistered;
            static void cleanup();
            static std::map<std::string, std::shared_ptr<TextureWrapper>> imageCache;
            static std::map<std::string, std::map<Rect, std::map<Color, std::shared_ptr<TextureWrapper>>>>
            textCache;
    };
}

#endif // TEXTURE_H_INCLUDED
