#include "Core.h"

using namespace bkengine;


Core *Core::instance = NULL;
bool Core::depsInited = false;

Core::Core()
{
}

#define move(core) \
    { \
        windowTitle = core.windowTitle; \
        windowHeight = core.windowHeight; \
        windowWidth = core.windowWidth; \
        renderer = core.renderer; \
        window = core.window; \
        largeFont = core.largeFont; \
        mediumFont = core.mediumFont; \
        smallFont = core.smallFont; \
        isValid = core.isValid; \
        core.renderer = NULL; \
        core.window = NULL; \
        core.largeFont = NULL; \
        core.mediumFont = NULL; \
        core.smallFont = NULL; \
        core.isValid = false; \
    }

Core &Core::operator=(Core &&core)
{
    move(core);
    core.isValid = false;
    return *this;
}

Core::Core(Core &&core)
{
    move(core);
    core.isValid = false;
}

#undef move

Core::Core(int width, int height, const std::string &windowTitle) :
    inited(false),
    window(NULL),
    largeFont(NULL),
    mediumFont(NULL),
    smallFont(NULL),
    windowHeight(height),
    windowWidth(width),
    windowTitle(windowTitle),
    renderer(NULL)
{
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

    if (largeFont != NULL) {
        MANGLE_SDL(TTF_CloseFont)(largeFont);
        largeFont = NULL;
    }

    if (mediumFont != NULL) {
        MANGLE_SDL(TTF_CloseFont)(mediumFont);
        mediumFont = NULL;
    }

    if (smallFont != NULL) {
        MANGLE_SDL(TTF_CloseFont)(smallFont);
        smallFont = NULL;
    }
}

void Core::quit()
{
    delete instance;
    instance = NULL;
    MANGLE_SDL(IMG_Quit)();
    MANGLE_SDL(TTF_Quit)();
    MANGLE_SDL(Mix_Quit)();
    MANGLE_SDL(SDL_Quit)();
}

int Core::init()
{
    //initialisiert sdl, sdl_image, sdl_ttf, sdl_mixer
    if (MANGLE_SDL(SDL_Init)(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        return -1;
    }

    if (!MANGLE_SDL(SDL_SetHint)(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        MANGLE_SDL(SDL_Quit)();
        return -2;
    }

    int imgFlags = IMG_INIT_PNG;

    if (!(MANGLE_SDL(IMG_Init)(imgFlags) & imgFlags)) {
        MANGLE_SDL(SDL_Quit)();
        return -3;
    }

    if (MANGLE_SDL(TTF_Init)() == -1) {
        MANGLE_SDL(SDL_Quit)();
        MANGLE_SDL(IMG_Quit)();
        return -4;
    }

    if (MANGLE_SDL(Mix_OpenAudio)(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        MANGLE_SDL(SDL_Quit)();
        MANGLE_SDL(IMG_Quit)();
        MANGLE_SDL(TTF_Quit)();
        return -5;
    }

    depsInited = true;
    return 0;
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
        //erstellt ein sdl fenster mit titel weite und h�he
        window = MANGLE_SDL(SDL_CreateWindow)(windowTitle.c_str(),
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED, windowWidth,
                                              windowHeight, SDL_WINDOW_SHOWN);

        if (window == NULL) {
            return -6;
        }

        SDL_Surface *iconSurface = MANGLE_SDL(IMG_Load)("icon.ico");
        MANGLE_SDL(SDL_SetWindowIcon)(window, iconSurface);
        MANGLE_SDL(SDL_FreeSurface)(iconSurface);
        renderer = MANGLE_SDL(SDL_CreateRenderer)(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer == NULL) {
            return -7;
        }

        //setzt den standard hintergrund
        MANGLE_SDL(SDL_SetRenderDrawColor)(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        int size = 50;

        // TODO: make font size relative
        if (windowHeight == 480) {
            size = 40;
        } else if (windowHeight == 600) {
            size = 48;
        } else if (windowHeight == 768) {
            size = 58;
        }

        largeFont = MANGLE_SDL(TTF_OpenFont)("FUTURAB.ttf", size);
        mediumFont = MANGLE_SDL(TTF_OpenFont)("FUTURAB.ttf", size / 2);
        smallFont = MANGLE_SDL(TTF_OpenFont)("FUTURAB.ttf", size / 4);

        if (largeFont == NULL || mediumFont == NULL || smallFont == NULL) {
            Logger::LogError("Core::setup: Failed to load font (" + std::string(MANGLE_SDL(
                                 SDL_GetError)()) + ")");
            return -8;
        }

        inited = true;
    }

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
    //singleton
    if (!instance) {
        return (instance = new Core(width, height, windowTitle));
    }

    return instance;
}




SDL_Renderer *Core::getRenderer()
{
    return renderer;
}

int Core::getWindowHeight()
{
    return windowHeight;
}

int Core::getWindowWidth()
{
    return windowWidth;
}

std::string Core::getWindowTitle()
{
    return windowTitle;
}

TTF_Font *Core::getFont(FontSize size)
{
    switch (size) {
        case FontSize::SMALL:
            return smallFont;

        case FontSize::MEDIUM:
            return mediumFont;

        case FontSize::LARGE:
            return largeFont;
    }

    return NULL;
}
