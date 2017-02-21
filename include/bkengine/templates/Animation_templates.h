#ifndef ANIMATION_TEMPLATES_H
#define ANIMATION_TEMPLATES_H

template <typename T> void Animation::addImage(const std::string &path,
        const Rect &size, const Rect &clip)
{
    T t;
    int status = t.loadImage(path, size, clip);

    if (status != 0) {
        Logger::LogError("Animation::addImage(const std::string &): Failed to load Texture ("
                         + std::string(MANGLE_SDL(SDL_GetError)()) + ")");
        return;
    }

    addTexture<T>(t);
}

template <typename T> void Animation::addText(const std::string &fontName,
        const std::string &text, const Rect &size, const Color &color,
        TextQuality quality)
{
    T t;
    int status = t.loadText(fontName, text, size, color, quality);

    if (status != 0) {
        Logger::LogError("Animation::addText(const std::string &, SDL_Color, short): Failed to load text ("
                         + std::string(MANGLE_SDL(SDL_GetError)()) + ")");
        return;
    }

    addTexture<T>(t);
}

template <typename T> void Animation::addTexture(const T &texture)
{
    textures.push_back(std::move((T &) texture));

    if (textures.size() == 1) {
        currentIndex = 0;
    }
}

#endif
