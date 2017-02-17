#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <string>
#include <memory>
#include <map>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Core.h"
#include "Misc.h"


namespace bkengine
{
    class Texture
    {
        public:
            Texture();
            virtual ~Texture();

            std::shared_ptr<TextureWrapper> getCached(const std::string &s);
            std::shared_ptr<TextureWrapper> getCached(const std::string &s, const Color &c,
                    short size);

            bool hasTextureCached(const std::string &s);
            bool hasTextureCached(const std::string &s, const Color &c, short size);

            int loadText(const std::string &text, const Color &color, short size = 0);

            int loadImage(const std::string &path);
            int loadImage(const std::string &path, const Rect &clip);
            int loadImage(const std::string &path, const Rect &clip,
                          const Rect &size);

            Rect getSize();
            void setSize(int w, int h);
            void setSize(const Rect &rect);

            int onRender(const Location &loc, bool flip = false);

        protected:
            bool flip;
            std::shared_ptr<TextureWrapper> texture;
            Rect clip;
            Rect size;

            static std::map<std::string, std::shared_ptr<TextureWrapper>> imageCache;
            static std::map<std::string, std::map<Color, std::map<short, std::shared_ptr<TextureWrapper>>>>
            textCache;
    };
}

#endif // TEXTURE_H_INCLUDED
