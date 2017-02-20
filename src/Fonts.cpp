#include "Fonts.h"


using namespace bkengine;

bool Fonts::cleanupRegistered = false;
std::map<std::string, std::map<int, TTF_Font *>> Fonts::fontCache;
std::map<std::string, std::string> Fonts::fontFileCache;

TTF_Font *Fonts::registerFont(const std::string &fontFile, int size,
                              const std::string &fontName)
{
    if (!cleanupRegistered) {
        registerCleanup();
    }

    if (fontCache.find(fontName) != fontCache.end()
            && fontCache[fontName].find(size) != fontCache[fontName].end()) {
        Logger::LogInfo("Fonts::registerFont(const std::string &=" + fontFile +
                        ", short=" + std::to_string(size) + ", const std::string &=" + fontName +
                        "): No need to register font!");
        return fontCache[fontName][size];
    }

    std::string name = fontName;

    if (name.size() == 0) {
        name = fontFile;
    } else {
        fontFileCache[name] = fontFile;
    }

    fontCache[fontName][size] = MANGLE_SDL(TTF_OpenFont)(fontFile.c_str(), size);
    Logger::LogDebug("Fonts::registerFont(const std::string &=" + fontFile +
                     ", short=" + std::to_string(size) + ", const std::string &=" + fontName +
                     "): created font " +  std::to_string((unsigned long long int)
                             fontCache[fontName][size]));
    return fontCache[fontName][size];
}

TTF_Font *Fonts::getFont(const std::string &fontName, int size)
{
    if (!cleanupRegistered) {
        registerCleanup();
    }

    if (fontCache.find(fontName) == fontCache.end()) {
        Logger::LogWarning("Fonts::getFont(const std::string &=" + fontName + ", short="
                           + std::to_string(size) + "): No font found with given name!");

        if (fontFileCache.find(fontName) != fontFileCache.end()) {
            Logger::LogInfo("Fonts::getFont(const std::string &=" + fontName + ", short=" +
                            std::to_string(size) + "): Register font with cached filename '" +
                            fontFileCache[fontName] + "'");
            return registerFont(fontFileCache[fontName], size, fontName);
        }

        return nullptr;
    }

    if (fontCache[fontName].find(size) == fontCache[fontName].end()) {
        Logger::LogWarning("Fonts::getFont(const std::string &=" + fontName + ", short="
                           + std::to_string(size) + "): No font found with given size!");

        if (fontFileCache.find(fontName) != fontFileCache.end()) {
            Logger::LogInfo("Fonts::getFont(const std::string &=" + fontName + ", short=" +
                            std::to_string(size) + "): Register font with cached filename '" +
                            fontFileCache[fontName] + "'");
            return registerFont(fontFileCache[fontName], size, fontName);
        }

        return nullptr;
    }

    return fontCache[fontName][size];
}

void Fonts::releaseFont(const std::string &fontName, int size)
{
    if (!cleanupRegistered) {
        registerCleanup();
    }

    if (fontCache.find(fontName) == fontCache.end()) {
        Logger::LogWarning("Fonts::releaseFont(const std::string &=" + fontName +
                           ", short=" + std::to_string(size) + "): No font found with given name!");
        return;
    }

    if (fontCache[fontName].find(size) == fontCache[fontName].end()) {
        Logger::LogWarning("Fonts::releaseFont(const std::string &=" + fontName +
                           ", short=" + std::to_string(size) + "): No font found with given size!");
        return;
    }

    Logger::LogDebug("Fonts::releaseFont(const std::string &=" + fontName + ", int="
                     + std::to_string(size) + "): destruct font " +  std::to_string((
                                 unsigned long long int) fontCache[fontName][size]));
    MANGLE_SDL(TTF_CloseFont)(fontCache[fontName][size]);
    fontCache[fontName].erase(size);

    if (fontCache[fontName].size() == 0) {
        fontCache.erase(fontName);
        fontFileCache.erase(fontName);
    }
}

void Fonts::registerCleanup()
{
    Core::registerCleanup(Fonts::cleanup);
    cleanupRegistered = true;
}

void Fonts::cleanup()
{
    for (auto &cache1 : fontCache) {
        for (auto &cache2 : cache1.second) {
            if (cache2.second) {
                Logger::LogDebug("Fonts::cleanup(): destruct font " +  std::to_string((
                                     unsigned long long int) cache2.second));
                MANGLE_SDL(TTF_CloseFont)(cache2.second);
            }
        }
    }

    fontCache.clear();
}
