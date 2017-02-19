#ifndef FONTS_H
#define FONTS_H

#include <string>
#include <map>

#include <SDL_ttf.h>

namespace bkengine
{
    class Fonts
    {
    public:
        static TTF_Font *registerFont(const std::string &fontFile, short size, const std::string &fontName = "");
        static TTF_Font *getFont(const std::string &fontName, short size);

        static void releaseFont(const std::string &fontName, short size);

    private:
        // TODO: register to be called at exit
        static void atExit();
        static std::map<std::string, std::map<short, TTF_Font *>> fontCache;
    };
}

#endif
