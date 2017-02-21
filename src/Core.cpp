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
    windowTitle = core.windowTitle;
    windowHeight = core.windowHeight;
    windowWidth = core.windowWidth;
    renderer = core.renderer;
    window = core.window;
    core.renderer = NULL;
    core.window = NULL;
}

Core::Core(int width, int height, const std::string &windowTitle) :
    inited(false),
    windowWidth(width),
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

int Core::init()
{
    if (MANGLE_SDL(SDL_Init)(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        Logger::LogCritical("Core::init(): Failed to init SDL. " + std::string(MANGLE_SDL(SDL_GetError)()));
        return -1;
    }

    if (!MANGLE_SDL(SDL_SetHint)(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        Logger::LogCritical("Core::init(): Failed to set hint. " + std::string(MANGLE_SDL(SDL_GetError)()));
        MANGLE_SDL(SDL_Quit)();
        return -2;
    }

    int imgFlags = IMG_INIT_PNG;

    if (!(MANGLE_SDL(IMG_Init)(imgFlags) & imgFlags)) {
        Logger::LogCritical("Core::init(): Failed to init SDL image. " + std::string(MANGLE_SDL(SDL_GetError)()));
        MANGLE_SDL(SDL_Quit)();
        return -3;
    }

    if (MANGLE_SDL(TTF_Init)() == -1) {
        Logger::LogCritical("Core::init(): Failed to init SDL ttf. " + std::string(MANGLE_SDL(SDL_GetError)()));
        MANGLE_SDL(SDL_Quit)();
        MANGLE_SDL(IMG_Quit)();
        return -4;
    }

    if (MANGLE_SDL(Mix_OpenAudio)(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        Logger::LogCritical("Core::init(): Failed to init SDL mixer. " + std::string(MANGLE_SDL(SDL_GetError)()));
        MANGLE_SDL(SDL_Quit)();
        MANGLE_SDL(IMG_Quit)();
        MANGLE_SDL(TTF_Quit)();
        return -5;
    }

    depsInited = true;
    return 0;
}

Core *Core::getInstance()
{
    if (!instance) {
        instance = new Core(800, 600, "TestWindow");
    }

    if (!instance->inited) {
        if (instance->setup() != 0) {
            Logger::LogCritical("Core::getInstance(): Core setup failed (" + std::string(
                                    MANGLE_SDL(SDL_GetError)()) + ")");
            throw "Core setup failed";
        }
    }

    return instance;
}

Core *Core::getInstance(int width, int height, const std::string &windowTitle)
{
    if (!instance) {
        return (instance = new Core(width, height, windowTitle));
    }

    return instance;
}



int Core::setup()
{
    if (!depsInited) {
        int status = init();

        if (status != 0) {
            return status;
        }
    }

    if (!inited) {
        window = MANGLE_SDL(SDL_CreateWindow)(windowTitle.c_str(),
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED, windowWidth,
                                              windowHeight, SDL_WINDOW_SHOWN);

        if (window == NULL) {
            Logger::LogCritical("Core::setup(): Failed to create window. " + std::string(MANGLE_SDL(SDL_GetError)()));
            return -6;
        }

        renderer = MANGLE_SDL(SDL_CreateRenderer)(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer == NULL) {
            Logger::LogCritical("Core::setup(): Failed to create renderer. " + std::string(MANGLE_SDL(SDL_GetError)()));
            return -7;
        }

        MANGLE_SDL(SDL_SetRenderDrawColor)(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        inited = true;
    }

    return 0;
}

int Core::setIcon(const std::string &iconPath)
{
    SDL_Surface *iconSurface = MANGLE_SDL(IMG_Load)(iconPath.c_str());
    if (!iconSurface) {
        Logger::LogError("Core::setIcon(const std::string &=" + iconPath + "): " + std::string(MANGLE_SDL(SDL_GetError)()));
        return -1;
    }
    MANGLE_SDL(SDL_SetWindowIcon)(window, iconSurface);
    MANGLE_SDL(SDL_FreeSurface)(iconSurface);
    return 0;
}

Rect Core::getWindowSize()
{
    int w, h;
    MANGLE_SDL(SDL_GetWindowSize)(window, &w, &h);
    return { (float) w, (float) h };
}

std::string Core::getWindowTitle() const
{
    return MANGLE_SDL(SDL_GetWindowTitle)(window);
}

SDL_Renderer *Core::getRenderer() const
{
    return renderer;
}
