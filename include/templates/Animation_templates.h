#ifndef ANIMATION_TEMPLATES_H
#define ANIMATION_TEMPLATES_H

template <typename T> void Animation::addImage(const std::string &path)
{
    T t;
    int status = t.loadImage(path);

    if (status != 0) {
        Logger::LogError("Animation::addImage(const std::string &): Failed to load Texture ("
                         + std::string(MANGLE_SDL(SDL_GetError)()) + ")");
        return;
    }

    addTexture<T>(t);
}

template <typename T> void Animation::addImage(const std::string &path,
        Rect size)
{
    addImage<T>(path);
    textures.back().setSize(size);
}

template <typename T> void Animation::addText(const std::string &text,
        const Color &color, short size)
{
    T t;
    int status = t.loadText(text, color, size);

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
