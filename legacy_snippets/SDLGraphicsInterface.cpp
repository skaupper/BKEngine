#include "interfaces/impl/SDLGraphicsInterface.h"


SDLGraphicsInterface::StaticConstructor::StaticConstructor _;

SDLGraphicsInterface::StaticConstructor::StaticConstructor()
{
    SDLGraphicsInterface::inititialize();
}

SDLGraphicsInterface::StaticConstructor::~StaticConstructor()
{
    SDLGraphicsInterface::quit();
}


void SDLGraphicsInterface::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        Logger::LogCritical("Core::initDeps(): Failed to init SDL. " +
                            getLastError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        Logger::LogCritical("Core::initDeps(): Failed to set hint. " +
                            getLastError());
        SDL_Quit();
        return false;
    }

    int imgFlags = IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) & imgFlags)) {
        Logger::LogCritical("Core::initDeps(): Failed to init SDL image. " +
                            getLastError());
        SDL_Quit();
        return false;
    }

    if (TTF_Init() == -1) {
        Logger::LogCritical("Core::initDeps(): Failed to init SDL ttf. " +
                            getLastError());
        SDL_Quit();
        IMG_Quit();
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        Logger::LogCritical("Core::initDeps(): Failed to init SDL mixer. " +
                            getLastError());
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        return false;
    }

    Logger::LogInfo("Core::initDependencies(): SDL initialization complete.");
    return true;
}

void SDLGraphicsInterface::quit()
{
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}


SDLGraphicsInterface::~SDLGraphicsInterface()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
}

bool SDLGraphicsInterface::createWindow(int windowWidth, int windowHeight,
                                        const std::string &windowTitle)
{
    window = SDL_CreateWindow(windowTitle.c_str(),
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth,
                              windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        Logger::LogCritical("Core::initEnvironment(): Failed to create window. " +
                            getLastError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        Logger::LogCritical("Core::initEnvironment(): Failed to create renderer. " +
                            getLastError());
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    return true;
}

std::string SDLGraphicsInterface::getLastError()
{
    return std::string(SDL_GetError());
}

bool SDLGraphicsInterface::setIcon(const std::string &iconPath)
{
    SDL_Surface *iconSurface = IMG_Load(iconPath.c_str());

    if (!iconSurface) {
        Logger::LogError("Core::setIcon(const std::string &=" + iconPath + "): " +
                         getLastError());
        return false;
    }

    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);
    return true;
}