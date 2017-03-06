
#include "Texture.h"
#include <sstream>

using namespace bkengine;

bool Texture::cleanupRegistered = false;
std::map<std::string, std::shared_ptr<TextureWrapper>> Texture::imageCache;
std::map<std::string, std::map<Rect, std::map<Color, std::shared_ptr<TextureWrapper>>>>
Texture::textCache;

static void recalculateRect(Rect &rect, int w, int h)
{
    if (rect.h == 0) {
        rect.h = (rect.w / w) * h;
    } else if (rect.w == 0) {
        rect.w = (rect.h / h) * w;
    }
}

std::shared_ptr<TextureWrapper> Texture::getCached(const std::string &s)
{
    return imageCache[s];
}

std::shared_ptr<TextureWrapper> Texture::getCached(const std::string &s,
        const Rect &size, const Color &c)
{
    return textCache[s][size][c];
}

bool Texture::hasTextureCached(const std::string &s)
{
    if (imageCache.find(s) == imageCache.end()) {
        return false;
    }

    return true;
}

bool Texture::hasTextureCached(const std::string &s, const Rect &size,
                               const Color &c)
{
    if (textCache.find(s) == textCache.end()) {
        return false;
    }

    if (textCache[s].find(size) == textCache[s].end()) {
        return false;
    }

    if (textCache[s][size].find(c) == textCache[s][size].end()) {
        return false;
    }

    return true;
}

Texture::Texture() : texture(nullptr)
{
    if (!cleanupRegistered) {
        Core::registerCleanup(cleanup);
        cleanupRegistered = true;
    }
}

Texture::Texture(const std::string &fontName, const std::string &text,
                 const Rect &size, const Color &color, TextQuality quality) : Texture()
{
    if (!loadText(fontName, text, size, color, quality)) {
        Logger::LogCritical("Texture::Texture(const std::string &=" + fontName +
                            ", const std::string &=" + text + ", const Color &=" + color.toString() +
                            ", const Rect &=" + size.toString() + ", TextQuality=" + std::to_string(
                                (int) quality) + "): Failed to load text. Texture is invalidated.");
        texture = nullptr;
    }
}

Texture::Texture(const std::string &path, const Rect &size,
                 const Rect &clip) : Texture()
{
    if (!loadImage(path, size, clip)) {
        Logger::LogCritical("Texture::Texture(const std::string &=" + path +
                            ", const Rect &=" + size.toString() + ", const Rect &=" + clip.toString() +
                            "): Failed to load image. Texture is invalidated.");
        texture = nullptr;
    }
}


Texture::~Texture()
{
}

bool Texture::loadText(const std::string &fontName, const std::string &text,
                       const Rect &size, const Color &color, TextQuality quality)
{
    if (hasTextureCached(text, size, color)) {
        texture = getCached(text, size, color);
        int w, h;
        MANGLE_SDL(SDL_QueryTexture)(texture->get(), NULL, NULL, &w, &h);
        Texture::size = size;
        recalculateRect(Texture::size, w, h);
        Texture::clip = Rect();
        return true;
    }

    Rect windowSize = Core::getInstance()->getTrueWindowSize();
    float fontSize = RelativeCoordinates::apply(size, windowSize).h;
    TTF_Font *font = Fonts::getFont(fontName, fontSize);

    if (!font) {
        font = Fonts::registerFont(fontName, fontSize);

        if (!font) {
            Logger::LogError("Texture::loadText(const std::string &=" + fontName +
                             ", const std::string &=" + text + ", const Color &=" + color.toString() +
                             ", const Rect &=" + size.toString() + ", TextQuality=" + std::to_string(
                                 (int) quality) + "): Failed to register font.");
            return false;
        }
    }

    SDL_Surface *textSurface = NULL;

    switch (quality) {
        case TextQuality::SOLID:
            textSurface = MANGLE_SDL(TTF_RenderUTF8_Solid)(font, text.c_str(), { color.r, color.g, color.b, color.a });
            break;

        case TextQuality::BLENDED:
            textSurface = MANGLE_SDL(TTF_RenderUTF8_Blended)(font, text.c_str(), { color.r, color.g, color.b, color.a });
            break;
    }

    if (textSurface == NULL) {
        Logger::LogError("Texture::loadText(const std::string &=" + fontName +
                         ", const std::string &=" + text + ", const Color &=" + color.toString() +
                         ", const Rect &=" + size.toString() + ", TextQuality=" + std::to_string(
                             (int) quality) + "): Failed to load surface. " +
                         std::string(MANGLE_SDL(SDL_GetError)()));
        return false;
    }

    SDL_Texture *nTexture = MANGLE_SDL(SDL_CreateTextureFromSurface)
                            (Core::getInstance()->getRenderer(),
                             textSurface);

    if (nTexture == NULL) {
        Logger::LogError("Texture::loadText(const std::string &=" + fontName +
                         ", const std::string &=" + text + ", const Color &=" + color.toString() +
                         ", const Rect &=" + size.toString() + ", TextQuality=" + std::to_string(
                             (int) quality) + "): Failed to create texture. " +
                         std::string(MANGLE_SDL(SDL_GetError)()));
        return false;
    }

    int w = textSurface->w, h = textSurface->h;
    MANGLE_SDL(SDL_FreeSurface)(textSurface);
    texture = textCache[text][size][color] = std::make_shared<TextureWrapper>
              (nTexture, text, fontName, color, quality);
    Texture::size = size;
    recalculateRect(Texture::size, w, h);
    Texture::clip = Rect();
    return true;
}

bool Texture::loadImage(const std::string &path, const Rect &size,
                        const Rect &clip)
{
    if (hasTextureCached(path)) {
        texture = getCached(path);
        int w, h;
        MANGLE_SDL(SDL_QueryTexture)(texture->get(), NULL, NULL, &w, &h);
        Rect tmpSize = size;
        recalculateRect(tmpSize, w, h);
        Texture::clip = clip;
        Texture::size = tmpSize;
        return true;
    }

    SDL_Texture *nTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL) {
        Logger::LogError("Texture::loadImage(const std::string &=" + path +
                         ", const Rect &=" + size.toString() + ", const Rect &=" + clip.toString() +
                         "): Failed to load surface. " + std::string(MANGLE_SDL(SDL_GetError)()));
        return false;
    }

    nTexture = MANGLE_SDL(SDL_CreateTextureFromSurface)
               (Core::getInstance()->getRenderer(),
                loadedSurface);

    if (nTexture == NULL) {
        Logger::LogError("Texture::loadImage(const std::string &=" + path +
                         ", const Rect &=" + size.toString() + ", const Rect &=" + clip.toString() +
                         "): Failed to create texture. " + std::string(MANGLE_SDL(SDL_GetError)()));
        return false;
    }

    MANGLE_SDL(SDL_FreeSurface)(loadedSurface);
    texture = imageCache[path] = std::make_shared<TextureWrapper>(nTexture, path);
    Rect tmpSize = size;
    recalculateRect(tmpSize, loadedSurface->w, loadedSurface->h);
    Texture::clip = clip;
    Texture::size = tmpSize;
    return true;
}

Rect Texture::getSize() const
{
    return size;
}


void Texture::setSize(int w, int h)
{
    if (w != 0) {
        size.w = (float) w;
    }

    if (h != 0) {
        size.h = (float) h;
    }
}

void Texture::setSize(const Rect &rect)
{
    size = rect;
}

void Texture::onRender(const Rect &parentRect, bool flip)
{
    if (!texture) {
        Logger::LogCritical("Texture::onRender(const Rect &=" + parentRect.toString() +
                            ", bool=" + (flip ? "true" : "false") + "): Texture is null");
        return;
    }

    SDL_Renderer *renderer = Core::getInstance()->getRenderer();
    Rect rect = { 0, 0, size.w, size.h };
    Rect windowSize = Core::getInstance()->getTrueWindowSize();
    Rect absoluteSize = RelativeCoordinates::apply(RelativeCoordinates::apply(rect,
                        parentRect), windowSize);
    SDL_Rect sdlRect = absoluteSize.toSDLRect();
    SDL_Rect sdlClip = RelativeCoordinates::apply(clip,
                       texture->getSize()).toSDLRect();
    // SDL_Point point { (int) getSize().x / 2, 0 };
    // Logger::LogDebug("Texture::onRender(const Rect &=" + parentRect.toString() +
    //                  ", bool=" + (flip ? "true" : "false") + "): Texture is rendered to " +
    //                  absoluteSize.toString());
    int ret;

    if (flip) {
        ret = MANGLE_SDL(SDL_RenderCopyEx)(renderer, texture->get(), &sdlClip, &sdlRect,
                                           0,
                                           nullptr,
                                           SDL_FLIP_HORIZONTAL);
    } else {
        ret =  MANGLE_SDL(SDL_RenderCopy)(renderer, texture->get(), &sdlClip, &sdlRect);
    }

    if (ret != 0) {
        Logger::LogCritical("Texture::onRender(const Rect &=" + parentRect.toString() +
                            ", bool=" + (flip ? "true" : "false") + "): Failed to render texture. " +
                            std::string(MANGLE_SDL(SDL_GetError)()));
    }
}

void Texture::cleanup()
{
    Logger::LogDebug("Texture::cleanup(): clear caches");
    imageCache.clear();
    textCache.clear();
}

void Texture::deserialize(const Json::Value &obj)
{
    Json::FastWriter writer;
    Serializable::deserialize(obj);
    Rect size;

    if (obj.isMember("size")) {
        auto jsonSize = obj["size"];

        if (!jsonSize.isObject()) {
            Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): Member \"size\" has to be an object. Deserialization aborted");
            return;
        }

        if (!jsonSize.isMember("x") || !jsonSize.isMember("y")
                || !jsonSize.isMember("w") || !jsonSize.isMember("h")) {
            Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): Member \"size\" must have the members \"x\", \"y\", \"w\" and \"h\". Deserialization aborted");
            return;
        }

        if (!jsonSize["x"].isNumeric() || !jsonSize["y"].isNumeric()
                || !jsonSize["w"].isNumeric() || !jsonSize["h"].isNumeric()) {
            Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): Members \"x\", \"y\", \"w\" and \"h\" must be (floating point) numbers. Deserialization aborted");
            return;
        }

        size = { jsonSize["x"].asFloat(),
                 jsonSize["y"].asFloat(),
                 jsonSize["w"].asFloat(),
                 jsonSize["h"].asFloat()
               };
    } else {
        Logger::LogWarning("Texture::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"size\"");
    }

    if (!obj.isMember("texture_type")) {
        Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"texture_type\". Deserialization aborted");
        return;
    }

    auto texTypeString = obj["texture_type"].asString();

    if (texTypeString == "IMAGE") {
        Rect clip;

        if (obj.isMember("clip")) {
            auto jsonClip = obj["clip"];

            if (!jsonClip.isMember("x") || !jsonClip.isMember("y")
                    || !jsonClip.isMember("w") || !jsonClip.isMember("h")) {
                Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): Member \"clip\" must have the members \"x\", \"y\", \"w\" and \"h\". Deserialization aborted");
                return;
            }

            if (!jsonClip["x"].isNumeric() || !jsonClip["y"].isNumeric()
                    || !jsonClip["w"].isNumeric() || !jsonClip["h"].isNumeric()) {
                Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): Members \"x\", \"y\", \"w\" and \"h\" must be (floating point) numbers. Deserialization aborted");
                return;
            }

            clip = { jsonClip["x"].asFloat(),
                     jsonClip["y"].asFloat(),
                     jsonClip["w"].asFloat(),
                     jsonClip["h"].asFloat()
                   };
        } else {
            Logger::LogWarning("Texture::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"clip\"");
        }

        if (!obj.isMember("path")) {
            Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"path\" although the texture_type is IMAGE. Deserialization aborted");
            return;
        }

        loadImage(obj["path"].asString(), clip, size);
    } else if (texTypeString == "TEXT") {
        Color color;

        if (obj.isMember("color")) {
            auto jsonColor = obj["color"];

            if (!jsonColor.isMember("r") || !jsonColor.isMember("g")
                    || !jsonColor.isMember("b") || !jsonColor.isMember("a")) {
                Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): Member \"clip\" must have the members \"r\", \"g\", \"b\" and \"a\". Deserialization aborted");
                return;
            }

            if (!jsonColor["r"].isNumeric() || !jsonColor["g"].isNumeric()
                    || !jsonColor["b"].isNumeric() || !jsonColor["a"].isNumeric()
                    || jsonColor["r"].asUInt() > 255 || jsonColor["g"].asUInt() > 255
                    || jsonColor["b"].asUInt() > 255 || jsonColor["a"].asUInt() > 255) {
                Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): Members \"r\", \"g\", \"b\" and \"a\" must be numbers between 0 and 255. Deserialization aborted");
                return;
            }

            color =  { (uint8_t) jsonColor["r"].asUInt(),
                       (uint8_t) jsonColor["g"].asUInt(),
                       (uint8_t) jsonColor["b"].asUInt(),
                       (uint8_t) jsonColor["a"].asUInt()
                     };
        } else {
            Logger::LogWarning("Texture::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"color\"");
        }

        TextQuality quality = TextQuality::SOLID;

        if (obj.isMember("quality")) {
            auto qualityString = obj["quality"];

            if (qualityString == "BLENDED") {
                quality = TextQuality::BLENDED;
            } else if (qualityString == "SOLID") {
                quality = TextQuality::SOLID;
            } else {
                Logger::LogWarning("Texture::deserialize(const Json::Value &=<optimized out>): Member \"quality\" must be one of BLENDED or SOLID. Default value SOLID is used");
            }
        } else {
            Logger::LogWarning("Texture::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"quality\"");
        }

        if (!obj.isMember("font_name")) {
            Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"font_name\". Deserialization aborted");
            return;
        }

        if (!obj.isMember("text")) {
            Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"text\". Deserialization aborted");
            return;
        }

        loadText(obj["font_name"].asString(), obj["text"].asString(), size,
                 color, quality);
    } else {
        Logger::LogCritical("Texture::deserialize(const Json::Value &=<optimized out>): Member \"texture_type\" must be one of IMAGE or TEXT. Deserialization aborted");
        return;
    }
}

Json::Value Texture::serialize() const
{
    Json::Value json;
    json["type"] = "TEXTURE";
    json["size"]["x"] = size.x;
    json["size"]["y"] = size.y;
    json["size"]["w"] = size.w;
    json["size"]["h"] = size.h;
    json["clip"]["x"] = clip.x;
    json["clip"]["y"] = clip.y;
    json["clip"]["w"] = clip.w;
    json["clip"]["h"] = clip.h;
    std::string texType;

    if (texture->type == TextureType::IMAGE) {
        texType = "IMAGE";
        json["path"] = texture->path;
    } else if (texture->type == TextureType::TEXT) {
        texType = "TEXT";
        json["text"] = texture->text;
        json["font_name"] = texture->fontName;
        json["color"]["r"] = texture->color.r;
        json["color"]["g"] = texture->color.g;
        json["color"]["b"] = texture->color.b;
        json["color"]["a"] = texture->color.a;
        std::string quality;

        if (texture->quality == TextQuality::SOLID) {
            quality = "SOLID";
        } else if (texture->quality == TextQuality::BLENDED) {
            quality = "BLENDED";
        }

        json["quality"] = quality;
    }

    json["texture_type"] = texType;
    return json;
}
