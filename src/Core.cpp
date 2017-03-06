#include "Core.h"

using namespace bkengine;


Core *Core::instance = NULL;
bool Core::depsInited = false;
std::vector<std::function<void()>> Core::cleanupFunctions;

Core::Core()
{
}

Core &Core::operator=(Core &&core)
{
    move(core);
    return *this;
}

Core::Core(Core &&core)
{
    move(core);
}

void Core::move(Core &core)
{
    environmentInited = core.environmentInited;
    windowTitle = core.windowTitle;
    windowHeight = core.windowHeight;
    windowWidth = core.windowWidth;
    renderer = core.renderer;
    window = core.window;
    core.renderer = NULL;
    core.window = NULL;
    core.environmentInited = false;
}

Core::Core(int width, int height, const std::string &windowTitle) :
    windowTitle(windowTitle),
    windowWidth(width),
    windowHeight(height),
    environmentInited(false),
    window(NULL),
    renderer(NULL)
{
    std::atexit(Core::quit);
}

Core::~Core()
{
    if (renderer != NULL) {
        MANGLE_SDL(SDL_DestroyRenderer)(renderer);
        renderer = NULL;
    }

    if (window != NULL) {
        MANGLE_SDL(SDL_DestroyWindow)(window);
        window = NULL;
    }
}

void Core::registerCleanup(std::function<void()> cleanupFunction)
{
    cleanupFunctions.push_back(cleanupFunction);
}

void Core::quit()
{
    if (!instance) {
        return;
    }

    for (auto &cleanup : cleanupFunctions) {
        cleanup();
    }

    Logger::LogDebug("Core::quit()");
    delete instance;
    instance = NULL;
    MANGLE_SDL(IMG_Quit)();
    MANGLE_SDL(TTF_Quit)();
    MANGLE_SDL(Mix_Quit)();
    MANGLE_SDL(SDL_Quit)();
}

bool Core::initDeps()
{
    if (depsInited) {
        return true;
    }

    if (MANGLE_SDL(SDL_Init)(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        Logger::LogCritical("Core::initDeps(): Failed to init SDL. " + std::string(
                                MANGLE_SDL(SDL_GetError)()));
        return false;
    }

    if (!MANGLE_SDL(SDL_SetHint)(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        Logger::LogCritical("Core::initDeps(): Failed to set hint. " + std::string(
                                MANGLE_SDL(SDL_GetError)()));
        MANGLE_SDL(SDL_Quit)();
        return false;
    }

    int imgFlags = IMG_INIT_PNG;

    if (!(MANGLE_SDL(IMG_Init)(imgFlags) & imgFlags)) {
        Logger::LogCritical("Core::initDeps(): Failed to init SDL image. " +
                            std::string(
                                MANGLE_SDL(SDL_GetError)()));
        MANGLE_SDL(SDL_Quit)();
        return false;
    }

    if (MANGLE_SDL(TTF_Init)() == -1) {
        Logger::LogCritical("Core::initDeps(): Failed to init SDL ttf. " + std::string(
                                MANGLE_SDL(SDL_GetError)()));
        MANGLE_SDL(SDL_Quit)();
        MANGLE_SDL(IMG_Quit)();
        return false;
    }

    if (MANGLE_SDL(Mix_OpenAudio)(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        Logger::LogCritical("Core::initDeps(): Failed to init SDL mixer. " +
                            std::string(
                                MANGLE_SDL(SDL_GetError)()));
        MANGLE_SDL(SDL_Quit)();
        MANGLE_SDL(IMG_Quit)();
        MANGLE_SDL(TTF_Quit)();
        return false;
    }

    Logger::LogDebug("Core::initDeps(): SDL initialization complete.");
    depsInited = true;
    return true;
}

Core *Core::getInstance()
{
    return instance;
}

Core *Core::createInstance(int width, int height,
                           const std::string &windowTitle)
{
    if (instance) {
        delete instance;
    }

    instance = new Core(width, height, windowTitle);

    if (!instance->environmentInited && !instance->initEnvironment()) {
        Logger::LogCritical("Core::getInstance(): Environment initialization failed. " +
                            std::string(MANGLE_SDL(SDL_GetError)()));
        delete instance;
        instance = nullptr;
        return nullptr;
    }

    return instance;
}



bool Core::initEnvironment()
{
    if (!depsInited && !initDeps()) {
        return false;
    }

    if (environmentInited) {
        return true;
    }

    window = MANGLE_SDL(SDL_CreateWindow)(windowTitle.c_str(),
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, windowWidth,
                                          windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        Logger::LogCritical("Core::initEnvironment(): Failed to create window. " +
                            std::string(MANGLE_SDL(SDL_GetError)()));
        return false;
    }

    renderer = MANGLE_SDL(SDL_CreateRenderer)(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        Logger::LogCritical("Core::initEnvironment(): Failed to create renderer. " +
                            std::string(
                                MANGLE_SDL(SDL_GetError)()));
        return false;
    }

    MANGLE_SDL(SDL_SetRenderDrawColor)(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    environmentInited = true;
    Logger::LogDebug("Core::initEnvironment(): Window and renderer creation complete.");
    return true;
}

bool Core::setIcon(const std::string &iconPath)
{
    SDL_Surface *iconSurface = MANGLE_SDL(IMG_Load)(iconPath.c_str());

    if (!iconSurface) {
        Logger::LogError("Core::setIcon(const std::string &=" + iconPath + "): " +
                         std::string(MANGLE_SDL(SDL_GetError)()));
        return false;
    }

    MANGLE_SDL(SDL_SetWindowIcon)(window, iconSurface);
    MANGLE_SDL(SDL_FreeSurface)(iconSurface);
    return true;
}

void Core::resizeWindow(int width, int height)
{
    MANGLE_SDL(SDL_SetWindowSize)(window, width, height);
    windowWidth = width;
    windowHeight = height;
}

void Core::setWindowTitle(const std::string &title)
{
    MANGLE_SDL(SDL_SetWindowTitle)(window, title.c_str());
    windowTitle = title;
}

Size Core::getTrueWindowSize() const
{
    int w, h;
    MANGLE_SDL(SDL_GetWindowSize)(window, &w, &h);
    return { (float) w, (float) h };
}

std::string Core::getTrueWindowTitle() const
{
    return MANGLE_SDL(SDL_GetWindowTitle)(window);
}

Size Core::getWindowSize() const
{
    return { (float) windowWidth, (float) windowHeight };
}

std::string Core::getWindowTitle() const
{
    return windowTitle;
}

SDL_Renderer *Core::getRenderer() const
{
    return renderer;
}
